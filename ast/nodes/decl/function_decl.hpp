//
// Created by yhwach on 8/28/25.
//

#ifndef FUNCTION_DECL_HPP
#define FUNCTION_DECL_HPP


#include "decl.hpp"
#include "../type/type.hpp"

#include "../visit/decl_visitor.hpp"

#include "decl/param_decl.hpp"
#include "stmt/block_statement.hpp"


namespace ast {
    struct ParamDecl;
    struct BlockStatement;

    struct FunctionDecl final : Decl {
        CallableType *type{nullptr};
        lex::SymId name;
        BlockStatement *body_; //prototype or definition
        std::vector<ParamDecl *> params_;
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
              body_(body),
              params_(std::move(params)),
              ret(ret) {
            body_->parent = this;
            std::ranges::for_each(params_, [this](ParamDecl *&p) {
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
