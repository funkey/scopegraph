#ifndef SCOPEGRAPH_DETAIL_BACKWARDS_IMPL_H__
#define SCOPEGRAPH_DETAIL_BACKWARDS_IMPL_H__

namespace sg {
namespace detail {

// for each SignalType in BackwardsTypes
template <typename Derived, typename BackwardsTypes>
class BackwardsImpl : public BackwardsImpl<Derived, typename BackwardsTypes::Tail> {

protected:

	typedef typename BackwardsTypes::Head SignalType;

	template <typename ScopeType>
	void init(ScopeType& scope) {

		scope.getSender().registerSlot(_tunnel.getSlot());
		scope.getSpy().getReceiver().registerCallback(_tunnel.getCallback());

		BackwardsImpl<Derived, typename BackwardsTypes::Tail>::init(scope);
	}

private:

	chr::Tunnel<SignalType> _tunnel;
};

// last on in inheritance chain
template <typename Derived>
class BackwardsImpl<Derived, Backwards<>> {

protected:

	template <typename ScopeType>
	void init(ScopeType&) {}
};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_DETAIL_BACKWARDS_IMPL_H__

