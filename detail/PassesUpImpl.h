#ifndef SCOPEGRAPH_DETAIL_PASSES_UP_IMPL_H__
#define SCOPEGRAPH_DETAIL_PASSES_UP_IMPL_H__

namespace sg {
namespace detail {

// for each SignalType in PassesUpTypes
template <typename Derived, typename PassesUpTypes>
class PassesUpImpl : public PassesUpImpl<Derived, typename PassesUpTypes::Tail> {

protected:

	typedef typename PassesUpTypes::Head SignalType;

	template <typename ScopeType>
	void init(ScopeType& scope) {

		scope.getSender().registerSlot(_tunnel.getSlot());
		scope.getSpy().getReceiver().registerCallback(_tunnel.getCallback(), 1 /* group one, i.e., after Accepts signals */);

		PassesUpImpl<Derived, typename PassesUpTypes::Tail>::init(scope);
	}

private:

	chr::Tunnel<SignalType> _tunnel;
};

// last on in inheritance chain
template <typename Derived>
class PassesUpImpl<Derived, PassesUp<>> {

protected:

	template <typename ScopeType>
	void init(ScopeType&) {}
};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_DETAIL_PASSES_UP_IMPL_H__

