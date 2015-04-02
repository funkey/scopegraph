#ifndef SCOPEGRAPH_META_ADD_H__
#define SCOPEGRAPH_META_ADD_H__

namespace sg {
namespace meta {

template <template<typename...> class ListName, typename List, typename Element>
class Add {

public:

	typedef ListName<Element, typename List::Head, typename List::Tail> Value;
};

} // namespace meta
} // namesapce sg

#endif // SCOPEGRAPH_META_ADD_H__

