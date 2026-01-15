#ifndef INZ_SEMA_PATH_POOL_HPP
#define INZ_SEMA_PATH_POOL_HPP

#include <cstdint>
#include <vector>
#include <llvm/ADT/ArrayRef.h>

namespace sema
{
    struct PathRef
    {
        uint32_t ofs{};
        uint16_t len{};
        uint16_t _pad{};
    };

    struct PathPool
    {
        std::vector<lex::SymId> segs;

        PathRef append(llvm::ArrayRef<lex::SymId> path)
        {
            PathRef r;
            r.ofs = static_cast<uint32_t>(segs.size());
            r.len = static_cast<uint16_t>(path.size());
            segs.insert(segs.end(), path.begin(), path.end());

            return r;
        }

        llvm::ArrayRef<lex::SymId> view(PathRef r) const
        {
            return {segs.data() + r.ofs, r.len};
        }
    };
}

#endif
