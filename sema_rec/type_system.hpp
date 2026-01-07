#pragma once

#include <cstdint>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>

#include "token.hpp"


namespace sema
{
    struct ModuleId final
    {
        uint32_t value = 0;
        friend bool operator==(ModuleId, ModuleId) = default;
    };

    template <typename>
    struct LocalId final
    {
        ModuleId module{};
        uint32_t index = 0;
        friend bool operator==(const LocalId&, const LocalId&) = default;
    };

    template <typename Tag>
    struct LocalIdHash final
    {
        size_t operator()(const LocalId<Tag>& id) const noexcept
        {
            // hash combine(module, index)
            const uint64_t a = static_cast<uint64_t>(id.module.value);
            const uint64_t b = static_cast<uint64_t>(id.index);
            const uint64_t x = (a << 32) ^ b;
            return std::hash<uint64_t>{}(x);
        }
    };

    struct StructTag
    {
    };

    struct FnTag
    {
    };

    struct LoadFnTag
    {
    };

    struct TypeId final
    {
        uint32_t value = 0;
        friend bool operator==(TypeId, TypeId) = default;
    };

    using LoadFnId = LocalId<LoadFnTag>;
    using StructId = LocalId<StructTag>;
    using FnId = LocalId<FnTag>;


    // Only builtins you actually need now.
    enum class BuiltinType : uint8_t
    {
        I8, I16, I32, I64, I128,
        U8, U16, U32, U64, U128,
        F32, F64,
        Bool, Char, Void, Str
    };

    struct ReservedStructId final
    {
        uint32_t index = 0;
        friend bool operator==(ReservedStructId, ReservedStructId) = default;
    };

    using StructId = LocalId<StructTag>;

    enum class TypeKind : uint8_t
    {
        Builtin,
        Struct, // user struct (StructId)
        ReservedStruct, // reserved struct (ReservedStructId)
        Box, // Box<T>
        Ref, // &T / &mut T
        TypeParam, // T
        ArrayFixed, // [T; N] (optional, may remain unsupported)
    };

    // NOTE: keep this node “wide” so both passes can use it.
    struct TypeNode final
    {
        TypeKind kind{};

        BuiltinType builtin{BuiltinType::Void};

        StructId struct_id{};
        ReservedStructId reserved_struct{};

        // TypeParam
        lex::SymId type_param_name{};

        // Box / Ref
        TypeId inner{};
        bool ref_mut = false;

        // ArrayFixed
        TypeId elem{};
        uint64_t array_len = 0;
    };

    struct TypeKey final
    {
        TypeKind kind{};

        BuiltinType builtin{BuiltinType::Void};

        StructId struct_id{};
        ReservedStructId reserved_struct{};

        lex::SymId type_param_name{};

        TypeId inner{};
        bool ref_mut = false;

        TypeId elem{};
        uint64_t array_len = 0;

        friend bool operator==(const TypeKey&, const TypeKey&) = default;
    };

    struct TypeKeyHash final
    {
        size_t operator()(const TypeKey& k) const noexcept
        {
            size_t h = 0;
            auto mix = [&](size_t x)
            {
                h ^= x + 0x9e3779b97f4a7c15ULL + (h << 6) + (h >> 2);
            };

            mix(std::hash<uint32_t>{}(static_cast<uint32_t>(k.kind)));
            mix(std::hash<uint32_t>{}(static_cast<uint32_t>(k.builtin)));

            mix(std::hash<uint32_t>{}(k.struct_id.module.value));
            mix(std::hash<uint32_t>{}(k.struct_id.index));

            mix(std::hash<uint32_t>{}(k.reserved_struct.index));
            mix(std::hash<uint32_t>{}(static_cast<uint32_t>(k.type_param_name)));

            mix(std::hash<uint32_t>{}(k.inner.value));
            mix(std::hash<uint8_t>{}(static_cast<uint8_t>(k.ref_mut)));

            mix(std::hash<uint32_t>{}(k.elem.value));
            mix(std::hash<uint64_t>{}(k.array_len));

            return h;
        }
    };

    struct TypeDB final
    {
        std::vector<TypeNode> nodes;
        std::unordered_map<TypeKey, TypeId, TypeKeyHash> intern;

        TypeId get_or_intern(const TypeKey& k)
        {
            if (auto it = intern.find(k); it != intern.end())
                return it->second;

            TypeId id{static_cast<uint32_t>(nodes.size())};

            TypeNode n{};
            n.kind = k.kind;
            n.builtin = k.builtin;
            n.struct_id = k.struct_id;
            n.reserved_struct = k.reserved_struct;
            n.type_param_name = k.type_param_name;
            n.inner = k.inner;
            n.ref_mut = k.ref_mut;
            n.elem = k.elem;
            n.array_len = k.array_len;

            nodes.push_back(n);
            intern.emplace(k, id);
            return id;
        }
    };

    template <typename T>
    struct PtrHash
    {
        size_t operator()(const T* p) const noexcept { return std::hash<const void*>{}(p); }
    };

    template <typename T>
    struct PtrEq
    {
        bool operator()(const T* a, const T* b) const noexcept { return a == b; }
    };
} // namespace sema
