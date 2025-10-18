#ifndef TYPE_INTERNER_HPP
#define TYPE_INTERNER_HPP

#include <unordered_set>
#include <limits>
#include <new>
#include <llvm/Support/Allocator.h>
#include "type/type.hpp"

template<typename T>
struct BumpAllocatorAdaptor {
    using value_type = T;
    using pointer = T *;

    llvm::BumpPtrAllocator *arena = nullptr;

    BumpAllocatorAdaptor() noexcept = default;

    explicit BumpAllocatorAdaptor(llvm::BumpPtrAllocator *a) noexcept : arena(a) {
    }

    template<typename U>
    explicit BumpAllocatorAdaptor(const BumpAllocatorAdaptor<U> &other) noexcept : arena(other.arena) {
    }

    pointer allocate(std::size_t n) {
        if (!arena) throw std::bad_alloc{};
        if (n > std::numeric_limits<std::size_t>::max() / sizeof(T)) throw std::bad_alloc{};
        void *mem = arena->Allocate(n * sizeof(T), alignof(T));
        return static_cast<pointer>(mem);
    }

    void deallocate(pointer, std::size_t) noexcept {
    }
};


struct TypeHash {
    using is_transparent = void;

    std::size_t operator()(const ast::Type *t) const noexcept { return t->hash(); }
    std::size_t operator()(const ast::Type &t) const noexcept { return t.hash(); }
};

struct TypeEq {
    using is_transparent = void;

    bool operator()(const ast::Type *a, const ast::Type *b) const noexcept { return a->equals(*b); }
    bool operator()(const ast::Type *a, const ast::Type &b) const noexcept { return a->equals(b); }
    bool operator()(const ast::Type &a, const ast::Type *b) const noexcept { return b->equals(a); }
    bool operator()(const ast::Type &a, const ast::Type &b) const noexcept { return a.equals(b); }
};

namespace sema::type {
    struct TypeInterner {
        using Alloc = BumpAllocatorAdaptor<ast::Type *>;

        TypeInterner() noexcept : arena{},
                                  types{Alloc(&arena)} {
        };

        llvm::BumpPtrAllocator arena;

        std::unordered_set<ast::Type *, TypeHash, TypeEq, Alloc> types;

        template<typename T, typename... Args>
            requires std::is_base_of_v<ast::Type, T>
        T *make(Args &&... args)
            noexcept(noexcept(T(std::forward<Args>(args)...))) {
            T probe(std::forward<Args>(args)...);

            if (auto it = types.find(probe); it != types.end()) {
                return *it;
            }

            void *mem = arena.Allocate(sizeof(T), alignof(T));
            T *obj = ::new(mem) T(std::forward<Args>(args)...);
            types.insert(obj);

            return obj;
        }
    };
}

#endif
