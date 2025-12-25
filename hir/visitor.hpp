#ifndef INZ_VISITOR_HPP
#define INZ_VISITOR_HPP

#include <type_traits>
#include <utility>
#include <variant>

namespace ast
{
    struct Module;
}

namespace hir
{
    struct Block;
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
    struct StmtBlock;
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

    template <class It>
    struct Visitor;


    template <typename T>
    struct VisitSlot
    {
        virtual ~VisitSlot() = default;
        virtual void visit(T&) = 0;
    };

    template <class T>
    concept HasKind = requires(T& t) { t.kind; };

    template <class K>
    struct is_variant : std::false_type
    {
    };

    template <class... Ts>
    struct is_variant<std::variant<Ts...>> : std::true_type
    {
    };

    template <class T>
    inline constexpr bool is_variant_v = is_variant<std::remove_cvref_t<T>>::value;

    template <class Derived, class T>
        requires HasKind<T> && is_variant_v<decltype(std::declval<T&>().kind)>
    struct DVisitSlot
    {
        void visit(T& t)
        {
            std::visit([this](auto& a)
            {
                static_cast<Derived*>(this)->visit(a);
            }, t.kind);
        }
    };

    template <class Derived, class... Ts>
    struct DistributiveVisitor : DVisitSlot<Derived, Ts>...
    {
        using DVisitSlot<Derived, Ts>::visit...;
    };

    template <class Distribution, class... Leafs>
    struct Visiter : Distribution, virtual VisitSlot<Leafs>...
    {
        using Distribution::visit;
        using VisitSlot<Leafs>::visit...;
        virtual ~Visiter() = default;
    };

    template <class It>
    struct Visitor
        : Visiter<
            DistributiveVisitor<Visitor<It>, Decl, Type, Expr, Stmt>,

            Module, Import, TypeParam, Param,
            StructFieldDecl, StructFieldInit, Block,

            // decl alternatives:
            FnDecl, StructDecl, TypeAliasDecl,

            // type alternatives:
            TypeBuiltin, TypePath, TypeRef, TypeArray,

            // expr alternatives:
            ExprPath, ExprLitInt, ExprLitArray, ExprLitFloat, ExprLitBool, ExprLitChar,
            ExprLitString, ExprUnary, ExprBinary, ExprAssign, ExprCall, ExprIndex,
            ExprField, ExprLitStruct, ExprCast,

            // stmt alternatives:
            StmtBlock, StmtIf, StmtElseIf, StmtElse, StmtWhile, StmtDoWhile,
            StmtBreak, StmtContinue, StmtReturn, StmtVar, StmtExpr

        >
    {
        using Visiter<
            DistributiveVisitor<Visitor<It>, Decl, Type, Expr, Stmt>,

            Module, Import, TypeParam, Param,
            StructFieldDecl, StructFieldInit, Block,
            FnDecl, StructDecl, TypeAliasDecl,
            TypeBuiltin, TypePath, TypeRef, TypeArray,
            ExprPath, ExprLitInt, ExprLitArray, ExprLitFloat, ExprLitBool, ExprLitChar,
            ExprLitString, ExprUnary, ExprBinary, ExprAssign, ExprCall, ExprIndex,
            ExprField, ExprLitStruct, ExprCast,
            StmtBlock, StmtIf, StmtElseIf, StmtElse, StmtWhile, StmtDoWhile,
            StmtBreak, StmtContinue, StmtReturn, StmtVar, StmtExpr


        >::visit;

        It& it_;

        explicit Visitor(It& it)
            : it_(it)
        {
        }
    };
}

#endif
