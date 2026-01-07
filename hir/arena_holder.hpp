#ifndef INZ_ARENA_HOLDER_HPP
#define INZ_ARENA_HOLDER_HPP

#include <vector>
#include "arena.hpp"

namespace hir
{
    struct ArenaHolder
    {
        std::vector<Arena> arenas_;
        size_t next_ = 0;

        explicit ArenaHolder(size_t n)
        {
            arenas_.resize(n); // IMPORTANT: allocate actual elements
        }

        Arena& nextSpace()
        {
            return arenas_[next_++]; // sequential
        }

        [[nodiscard]] size_t size() const { return arenas_.size(); }
    };
}

#endif //INZ_ARENA_HOLDER_HPP
