//
// Created by yhwach on 12/23/25.
//

#ifndef INZ_ITERATOR_HPP
#define INZ_ITERATOR_HPP

#include <array>
#include <cassert>
#include <functional>
#include <optional>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

namespace hir
{
    template <typename EnumKind, typename IndexType, typename... MetaTypes>
    struct NodeRef
    {
        EnumKind kind;
        IndexType index;

        [[no_unique_address]] std::tuple<MetaTypes...> data;
    };

    template <typename EnumKind, typename IndexType>
    struct NodeRef<EnumKind, IndexType>
    {
        EnumKind kind;
        IndexType index;
    };

    template <template <class> class CoreVisitor,
              template <class> class ApplyingVisitor,
              typename EnumKind,
              typename IndexType,
              typename On,
              class MetaInfoTypeTuple,
              auto... VecRefs>
    struct Iterator;

    template <template <class> class CoreVisitor,
              template <class> class ApplyingVisitor,
              typename EnumKind,
              typename IndexType,
              typename On,
              typename... RawMeta,
              auto... VecRefs>
    struct Iterator<CoreVisitor, ApplyingVisitor, EnumKind, IndexType, On, std::tuple<RawMeta...>, VecRefs...>
    {
        using Self = Iterator;
        using CVisitor = CoreVisitor<Self>;
        using AVisitor = ApplyingVisitor<Self>;
        using ContractedEnum = EnumKind;
        using Index = IndexType;
        using ContractedIndex = std::underlying_type_t<ContractedEnum>;

        static constexpr bool HasMeta = sizeof...(RawMeta) != 0;

        using StoredMetaTuple = std::tuple<RawMeta...>;
        using Node = NodeRef<ContractedEnum, IndexType, RawMeta...>;


        template <class Visitor>
        using Fn = void(*)(Self&, Visitor&, IndexType, RawMeta...);

        std::vector<Node> stack_;
        std::vector<StoredMetaTuple> metaPool_;
        On& a;
        CVisitor cVisitor;
        std::optional<std::reference_wrapper<AVisitor>> aVisitor;

        static constexpr auto vec_tuple = std::tuple{VecRefs...};

        explicit Iterator(On& a, std::size_t size)
            : a(a), cVisitor(*this)
        {
            stack_.reserve(size);
        }

        void setAVisitor(AVisitor& visitor)
        {
            aVisitor = visitor;
        }

        template <typename T>
        void defer_first(T& t, RawMeta... meta)
        {
            cVisitor.visit(t, meta...);
        }

        void defer(ContractedEnum kind, IndexType index, RawMeta... args)
        {
            if constexpr (!HasMeta)
            {
                stack_.push_back(Node{kind, index});
            }
            else
            {
                stack_.push_back(Node{kind, index, StoredMetaTuple{args...}});
            }
        }

        void start_apply_inline()
        {
            while (!stack_.empty())
            {
                auto n = std::move(stack_.back());
                stack_.pop_back();

                dispatch(n, cVisitor);
                if (aVisitor) dispatch(n, aVisitor->get());
            }
        }

    private:
        template <ContractedIndex I, typename Visitor>
        static void dispatch_one(Self& self, Visitor& visitor, IndexType index, RawMeta... data)
        {
            auto pm = std::get<I>(vec_tuple);
            visitor.visit((self.a.*pm)[static_cast<std::size_t>(index)], data...);
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
        void dispatch(Node const& node, Visitor& vis)
        {
            const auto k = static_cast<ContractedIndex>(node.kind);

            if constexpr (!HasMeta)
            {
                table_for<Visitor>[k](*this, vis, node.index);
            }
            else
            {
                std::apply([this, &node, &vis, k](auto... xs)
                {
                    table_for<Visitor>[k](*this, vis, node.index, xs...);
                }, node.data);
            }
        }
    };
}

#endif // INZ_ITERATOR_HPP
