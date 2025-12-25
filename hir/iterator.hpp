//
// Created by yhwach on 12/23/25.
//

#ifndef INZ_ITERATOR_HPP
#define INZ_ITERATOR_HPP

#include <functional>
#include <iostream>


namespace hir
{
    template <typename EnumKind,
              typename IndexType>
    struct NodeRef
    {
        EnumKind kind;
        IndexType index;
    };

    template <template <class> class CoreVisitor,
              template <class, class...> class ApplyingVisitor,
              typename EnumKind,
              typename IndexType,
              typename On,
              auto... VecRefs>
    struct Iterator
    {
        using Self = Iterator<CoreVisitor, ApplyingVisitor, EnumKind, IndexType, On, VecRefs...>;
        using CVisitor = CoreVisitor<Self>;
        using AVisitor = ApplyingVisitor<Self>;
        using ContractedEnum = EnumKind;
        using ContractedIndex = std::underlying_type_t<ContractedEnum>;

        template <class Visitor>
        using Fn = void(*)(Self&, Visitor&, IndexType);

        std::vector<NodeRef<ContractedEnum, IndexType>> stack_;
        On& a;
        CVisitor cVisitor;
        std::optional<std::reference_wrapper<AVisitor>> aVisitor;

        inline static constexpr auto vec_tuple = std::tuple{VecRefs...};

        void setAVisitor(AVisitor& visitor)
        {
            aVisitor = visitor;
        }

        explicit Iterator(On& a, size_t size)
            : a(a), cVisitor(*this), aVisitor(std::nullopt)
        {
            stack_.reserve(size);
        }

        void defer(ContractedEnum kind, IndexType index)
        {
            stack_.push_back({kind, index});
        }

        void start_place(ContractedEnum kind, IndexType index)
        {
            stack_.push_back({kind, index});
        }

        void start_apply_inline()
        {
            assert(!stack_.empty() && "use start_place() before start()");
            // for (size_t i = 0; i < stack_.size(); ++i)
            // {
            //     auto n = stack_[i];
            //
            //     dispatch(n, cVisitor); // may push more nodes via defer()
            //     dispatch(n, aVisitor); // apply at same point in traversal
            // }
            //
            // stack_.clear();

            while (!stack_.empty())
            {
                auto n = stack_.back();
                stack_.pop_back();

                dispatch(n, cVisitor);
                dispatch(n, aVisitor.value().get());
            }
        }

    private:
        template <ContractedIndex I, typename Visitor>
        static void dispatch_one(Self& self, Visitor& visitor, IndexType index)
        {
            auto pm = std::get<I>(self.vec_tuple);
            visitor.visit((self.a.*pm)[static_cast<std::size_t>(index)]);
        }

        template <typename Visitor>
        static consteval auto make_table()
        {
            return []<ContractedIndex... I>(std::index_sequence<I...>)
            {
                return std::array<Fn<Visitor>, sizeof...(I)>{&dispatch_one<I, Visitor>...};
            }(std::make_index_sequence<sizeof...(VecRefs)>{});
        }

        template <class Visitor>
        static constexpr auto table_for = make_table<Visitor>();

        template <class Visitor>
        void dispatch(NodeRef<ContractedEnum, IndexType> node, Visitor& vis)
        {
            table_for<Visitor>[static_cast<ContractedIndex>(node.kind)](*this, vis, node.index);
        }
    };
}
#endif //INZ_ITERATOR_HPP
