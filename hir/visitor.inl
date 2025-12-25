#ifndef INZ_VISITOR_INL
#define INZ_VISITOR_INL

namespace hir
{
    template <class Derived, class T>
        requires HasKind<T> && is_variant_v<decltype(std::declval<T&>().kind)>
    void DVisitSlot<Derived, T>::visit(T& t)
    {
        std::visit([this](auto& a)
        {
            static_cast<Derived*>(this)->visit(a);
        }, t.kind);
    }

    template <typename It>
    Visitor<It>::Visitor(It& it_)
        : it(it_)
    {
    }
}

#endif // INZ_VISITOR_INL
