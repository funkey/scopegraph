#ifndef SCOPEGRAPH_DETAIL_FILTERS_DOWN_IMPL_H__
#define SCOPEGRAPH_DETAIL_FILTERS_DOWN_IMPL_H__

#include <cohear/Filter.h>

namespace sg {
namespace detail {

// for each SignalType in FiltersDownTypes
template <typename Derived, typename FiltersDownTypes>
class FiltersDownImpl : public FiltersDownImpl<Derived, typename FiltersDownTypes::Tail> {

protected:

	typedef typename FiltersDownTypes::Head SignalType;

	FiltersDownImpl() :
		_filter(
				chr::FilterDelegate<SignalType>::template from_method<Derived, &Derived::filterDown>(static_cast<Derived*>(this)),
				chr::Delegate<SignalType>::template from_method<Derived, &Derived::unfilterDown>(static_cast<Derived*>(this))
		) {}

	template <typename ScopeType>
	void init(ScopeType& scope) {

		scope.getSpy().getSender().registerSlot(_filter.getSlot());
		scope.getReceiver().registerCallback(_filter.getCallback());

		FiltersDownImpl<Derived, typename FiltersDownTypes::Tail>::init(scope);
	}

private:

	chr::Filter<SignalType> _filter;
};

// last on in inheritance chain
template <typename Derived>
class FiltersDownImpl<Derived, FiltersDown<>> {

protected:

	template <typename ScopeType>
	void init(ScopeType&) {}
};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_DETAIL_FILTERS_DOWN_IMPL_H__

