#ifndef SCOPEGRAPH_BACKWARDS_H__
#define SCOPEGRAPH_BACKWARDS_H__

#include <cohear/Tunnel.h>

namespace sg {

// recursive inheritance
template <typename SignalType, typename ... Rest>
class Backwards : public Backwards<Rest...> {

public:

	template <typename ScopeType>
	void init(ScopeType& scope) {

		scope.getSpy().getReceiver().registerCallback(_tunnel.getCallback());
		scope.getSender().registerSlot(_tunnel.getSlot());

		Backwards<Rest...>::init(scope);
	}

private:

	chr::Tunnel<SignalType> _tunnel;
};

// base case
template <typename SignalType>
class Backwards<SignalType> {

public:

	template <typename ScopeType>
	void init(ScopeType& scope) {

		scope.getSpy().getReceiver().registerCallback(_tunnel.getCallback());
		scope.getSender().registerSlot(_tunnel.getSlot());
	}

private:

	chr::Tunnel<SignalType> _tunnel;
};

// specialisation
template <>
class Backwards<Nothing> {

public:

	template <typename ScopeType>
	void init(ScopeType&) {}
};

} // namespace sg

#endif // SCOPEGRAPH_BACKWARDS_H__

