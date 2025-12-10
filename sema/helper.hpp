//
// Created by yhwach on 11/28/25.
//

#ifndef INZ_HELPER_HPP
#define INZ_HELPER_HPP

#include <algorithm>
#include <stack>
#include <vector>

namespace sema::helper
{
    template <class C>
    concept HasBeginEnd = requires(C c)
    {
        c.begin();
        c.end();
    };

    template <typename T, class C>
        requires HasBeginEnd<C>
    std::vector<T> stackToVector(std::stack<T, C>& s)
    {
        struct OpenStack : std::stack<T, C>
        {
            using std::stack<T, C>::c;
        };

        auto opened = static_cast<OpenStack&>(s).c;
        std::vector<T> v(opened.begin(), opened.end());
        std::reverse(v.begin(), v.end());

        return v;
    }

    template <typename T, class C>
        requires (!HasBeginEnd<C>)
    std::vector<T> stackToVector(std::stack<T, C>& s)
    {
        std::vector<T> v;

        v.reserve(s.size());

        while (!s.empty())
        {
            v.push_back(s.top());
            s.pop();
        }

        std::reverse(v.begin(), v.end());

        return v;
    }
}

#endif //INZ_HELPER_HPP
