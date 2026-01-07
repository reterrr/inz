#ifndef INZ_VISITOR_HPP
#define INZ_VISITOR_HPP

#include <type_traits>
#include <variant>

namespace ast
{
    struct Module;
}

namespace hir
{
    struct TypeBox;
    struct ImplMethod;
    struct TraitMethod;
    struct Method;
    struct Block;
    struct ParamNamed;
    struct ParamSelf;
    struct StmtBlock;
    struct StructFieldInit;
    struct StructFieldDecl;
    struct Param;
    struct TypeParam;
    struct Import;
    struct Module;
    struct TypeRef;
    struct TypeArray;
    struct ExprLitBool;
    struct ExprLitFloat;
    struct ExprLitArray;
    struct ExprUnary;
    struct StmtElseIf;
    struct StmtElse;
    struct StmtReturn;
    struct StmtVar;
    struct StmtWhile;
    struct StmtExpr;
    struct StmtDoWhile;
    struct ExprLitChar;
    struct ExprIndex;
    struct ExprCall;
    struct ExprBinary;
    struct ExprCast;
    struct ExprLitStruct;
    struct StmtIf;
    struct StmtContinue;
    struct StmtBreak;
    struct ExprField;
    struct ExprLitString;
    struct ExprPath;
    struct TypePath;
    struct TypeBuiltin;
    struct TypeAliasDecl;
    struct StructDecl;
    struct FnDecl;
    struct ExprAssign;
    struct ExprLitInt;
    struct Expr;
    struct Stmt;
    struct Type;
    struct Decl;
    struct LoadFnDecl;

#include <tuple>

    // -----------------------------------------------------------------------------
    // Small type-list utilities (for readability and "single source of truth" lists)
    // -----------------------------------------------------------------------------
    template <class... Ts>
    struct type_list
    {
        template <template <class...> class Z>
        using apply = Z<Ts...>;
    };

    template <class... Lists>
    struct concat_lists;

    template <>
    struct concat_lists<>
    {
        using type = type_list<>;
    };

    template <class... Ts>
    struct concat_lists<type_list<Ts...>>
    {
        using type = type_list<Ts...>;
    };

    template <class... A, class... B, class... Rest>
    struct concat_lists<type_list<A...>, type_list<B...>, Rest...>
        : concat_lists<type_list<A..., B...>, Rest...>
    {
    };

    template <class... Lists>
    using concat_t = concat_lists<Lists...>::type;

    // -----------------------------------------------------------------------------
    // Core visitor plumbing
    // -----------------------------------------------------------------------------
    template <typename T, typename... MetaData>
    struct VisitSlot
    {
        virtual ~VisitSlot() = default;

        // Virtuals cannot be perfect-forwarded; pass references via MetaData types if needed.
        virtual void visit(T&, MetaData...) = 0;
    };

    template <class V>
    concept StdVariant = requires
    {
        std::variant_size_v<std::remove_cvref_t<V>>;
    };

    template <class T>
    concept HasVariantKind = requires(T& t)
    {
        requires StdVariant<decltype(t.kind)>;
    };

    // Dispatch "sum" nodes that contain a std::variant in .kind
    template <class Derived, class T, class... MetaData>
        requires HasVariantKind<T>
    struct KindDispatch
    {
        void visit(T& t, MetaData... md)
        {
            std::visit(
                [this, &md...](auto& alt)
                {
                    static_cast<Derived*>(this)->visit(alt, md...);
                },
                t.kind
            );
        }
    };

    // Builds overload set for all "kind" carrier nodes (Decl/Expr/Stmt/...)
    template <class Derived, class MetaTuple, class KindCarriersList>
    struct DistributiveVisitor;

    template <class Derived, class... MetaData, class... KindCarriers>
    struct DistributiveVisitor<Derived, std::tuple<MetaData...>, type_list<KindCarriers...>>
        : KindDispatch<Derived, KindCarriers, MetaData...>...
    {
        using KindDispatch<Derived, KindCarriers, MetaData...>::visit...;
    };

    // Mixes distribution + leaf slots into one final abstract interface
    template <class Distribution, class MetaTuple, class LeafsList>
    struct VisitorImpl;

    template <class Distribution, class... MetaData, class... Leafs>
    struct VisitorImpl<Distribution, std::tuple<MetaData...>, type_list<Leafs...>>
        : Distribution
          , virtual VisitSlot<Leafs, MetaData...>...
    {
        using Distribution::visit;
        using VisitSlot<Leafs, MetaData...>::visit...;

        virtual ~VisitorImpl() = default;
    };

    // One “base builder” so your concrete Visitor stays short
    template <class Derived, class MetaTuple, class LeafsList, class KindCarriersList>
    using VisitorBase =
    VisitorImpl<
        DistributiveVisitor<Derived, MetaTuple, KindCarriersList>,
        MetaTuple,
        LeafsList
    >;

    // -----------------------------------------------------------------------------
    // Put ALL editable lists in one place (grouped), so changes are trivial.
    // -----------------------------------------------------------------------------

    // Your "kind carriers" (nodes that have `.kind` = std::variant<...>)
    using KindCarriers = type_list<Decl, Type, Expr, Stmt, Param, Method>;

    // Leaf nodes grouped by domain (edit here, not in the inheritance list)
    using CommonNodes = type_list<
        Module, Import, TypeParam, ParamSelf, ParamNamed,
        StructFieldDecl, StructFieldInit, Block
    >;

    using DeclNodes = type_list<
        FnDecl, StructDecl, TypeAliasDecl, TraitDecl, ImplDecl, LoadFnDecl
    >;

    using MethodNodes = type_list<TraitMethod, ImplMethod>;

    using TypeNodes = type_list<
        TypeBuiltin, TypePath, TypeRef, TypeArray
    >;

    using ExprNodes = type_list<
        ExprPath, ExprLitInt, ExprLitArray, ExprLitFloat, ExprLitBool, ExprLitChar,
        ExprLitString, ExprUnary, ExprBinary, ExprAssign, ExprCall, ExprIndex,
        ExprField, ExprLitStruct, ExprCast
    >;

    using StmtNodes = type_list<
        StmtBlock, StmtIf, StmtElseIf, StmtElse, StmtWhile, StmtDoWhile,
        StmtBreak, StmtContinue, StmtReturn, StmtVar, StmtExpr
    >;

    using AllLeafNodes = concat_t<CommonNodes, DeclNodes, TypeNodes, MethodNodes, ExprNodes, StmtNodes>;

    // -----------------------------------------------------------------------------
    // Final visitor: short, readable, no duplicated node packs
    // -----------------------------------------------------------------------------
    template <class It, class... MetaData>
    struct Visitor
        : VisitorBase<
            Visitor<It, MetaData...>,
            std::tuple<MetaData...>,
            AllLeafNodes,
            KindCarriers
        >
    {
        using Base = VisitorBase<
            Visitor,
            std::tuple<MetaData...>,
            AllLeafNodes,
            KindCarriers
        >;

        using Base::visit;

        It& it_;

        explicit Visitor(It& it)
            : it_(it)
        {
        }
    };
}

#endif
