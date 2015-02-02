#ifndef SCOPEGRAPH_FORWARDS_H__
#define SCOPEGRAPH_FORWARDS_H__

#include <cohear/Tunnel.h>

namespace sg {

// recursive inheritance
template <typename SignalType, typename ... Rest>
class Forwards : public Forwards<Rest...> {

public:

	template <typename ScopeType>
	void init(ScopeType& scope) {

		scope.getSpy().getSender().registerSlot(_tunnel.getSlot());
		scope.getReceiver().registerCallback(_tunnel.getCallback());

		Forwards<Rest...>::init(scope);
	}

private:

	chr::Tunnel<SignalType> _tunnel;
};

// base case
template <typename SignalType>
class Forwards<SignalType> {

public:

	template <typename ScopeType>
	void init(ScopeType& scope) {

		scope.getSpy().getSender().registerSlot(_tunnel.getSlot());
		scope.getReceiver().registerCallback(_tunnel.getCallback());
	}

private:

	chr::Tunnel<SignalType> _tunnel;
};

// specialisation
template <>
class Forwards<Nothing> {

public:

	template <typename ScopeType>
	void init(ScopeType&) {}
};

} // namespace sg

#endif // SCOPEGRAPH_FORWARDS_H__

