#ifndef SCOPEGRAPH_DETAIL_FORWARDS_IMPL_H__
#define SCOPEGRAPH_DETAIL_FORWARDS_IMPL_H__

#include <cohear/Tunnel.h>

namespace sg {
namespace detail {

// for each SignalType in ForwardsTypes
template <typename Derived, typename ForwardsTypes>
class ForwardsImpl : public ForwardsImpl<Derived, typename ForwardsTypes::Tail> {

protected:

	typedef typename ForwardsTypes::Head SignalType;

	template <typename ScopeType>
	void init(ScopeType& scope) {

		scope.getSpy().getSender().registerSlot(_tunnel.getSlot());
		scope.getReceiver().registerCallback(_tunnel.getCallback());

		ForwardsImpl<Derived, typename ForwardsTypes::Tail>::init(scope);
	}

private:

	chr::Tunnel<SignalType> _tunnel;
};

// last on in inheritance chain
template <typename Derived>
class ForwardsImpl<Derived, Forwards<>> {

protected:

	template <typename ScopeType>
	void init(ScopeType&) {}
};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_DETAIL_FORWARDS_IMPL_H__

