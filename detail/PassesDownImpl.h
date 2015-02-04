#ifndef SCOPEGRAPH_DETAIL_PASSES_DOWN_IMPL_H__
#define SCOPEGRAPH_DETAIL_PASSES_DOWN_IMPL_H__

#include <cohear/Tunnel.h>

namespace sg {
namespace detail {

// for each SignalType in PassesDownTypes
template <typename Derived, typename PassesDownTypes>
class PassesDownImpl : public PassesDownImpl<Derived, typename PassesDownTypes::Tail> {

protected:

	typedef typename PassesDownTypes::Head SignalType;

	template <typename ScopeType>
	void init(ScopeType& scope) {

		scope.getSpy().getSender().registerSlot(_tunnel.getSlot());
		scope.getReceiver().registerCallback(_tunnel.getCallback());

		PassesDownImpl<Derived, typename PassesDownTypes::Tail>::init(scope);
	}

private:

	chr::Tunnel<SignalType> _tunnel;
};

// last on in inheritance chain
template <typename Derived>
class PassesDownImpl<Derived, PassesDown<>> {

protected:

	template <typename ScopeType>
	void init(ScopeType&) {}
};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_DETAIL_PASSES_DOWN_IMPL_H__

