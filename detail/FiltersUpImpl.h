#ifndef SCOPEGRAPH_DETAIL_FILTERS_UP_IMPL_H__
#define SCOPEGRAPH_DETAIL_FILTERS_UP_IMPL_H__

#include <cohear/Filter.h>

namespace sg {
namespace detail {

// for each SignalType in FiltersUpTypes
template <typename Derived, typename FiltersUpTypes>
class FiltersUpImpl : public FiltersUpImpl<Derived, typename FiltersUpTypes::Tail> {

protected:

	typedef typename FiltersUpTypes::Head SignalType;

	FiltersUpImpl() :
		_filter(
				chr::FilterDelegate<SignalType>::template from_method<Derived, &Derived::filterUp>(static_cast<Derived*>(this)),
				chr::Delegate<SignalType>::template from_method<Derived, &Derived::unfilterUp>(static_cast<Derived*>(this))
		) {}

	template <typename ScopeType>
	void init(ScopeType& scope) {

		scope.getSender().registerSlot(_filter.getSlot());
		scope.getSpy().getReceiver().registerCallback(_filter.getCallback(), 1 /* group one, i.e., after Accepts signals */);

		FiltersUpImpl<Derived, typename FiltersUpTypes::Tail>::init(scope);
	}

private:

	chr::Filter<SignalType> _filter;
};

// last on in inheritance chain
template <typename Derived>
class FiltersUpImpl<Derived, FiltersUp<>> {

protected:

	template <typename ScopeType>
	void init(ScopeType&) {}
};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_DETAIL_FILTERS_UP_IMPL_H__

