//
// Created by yhwach on 8/28/25.
//

#ifndef FUNCTION_DECL_HPP
#define FUNCTION_DECL_HPP


#include "decl.hpp"
#include "../type/type.hpp"

#include "../visit/decl_visitor.hpp"


namespace ast {
    struct ParamDecl;
    struct BlockStatement;

    struct FunctionDecl final : Decl {
        CallableType *type{nullptr};
        lex::SymId name;
        BlockStatement *body; //prototype or definition
        std::vector<ParamDecl *> params;
        Type *ret;

        FunctionDecl(const lex::SymId name,
                     CallableType *type,
                     std::vector<ParamDecl *> &&params,
                     Type *ret,
                     BlockStatement *body,
                     const lex::Loc &loc)
            : Decl(NodeKind::Decl_Fn, loc),
              type(type),
              name(name),
              body(body),
              params(std::move(params)),
              ret(ret) {
            body->parent = this;
            std::ranges::for_each(params, [this](ParamDecl *&p) {
                p->parent = this;
            });
        }

        void accept(visitor::DeclVisitor &) override;
    };

    inline void FunctionDecl::accept(visitor::DeclVisitor &v) {
        v.visit(*this);
    }
}

#endif //FUNCTION_DECL_HPP
