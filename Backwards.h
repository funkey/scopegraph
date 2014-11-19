#ifndef SCOPEGRAPH_BACKWARDS_H__
#define SCOPEGRAPH_BACKWARDS_H__

#include <signals/PassThroughCallback.h>
#include <signals/PassThroughSlot.h>

namespace sg {

// recursive inheritance
template <typename SignalType, typename ... Rest>
class Backwards : public Backwards<Rest...> {

public:

	Backwards() {

		_innerCallback.forwardTo(_outerSlot);
	}

	template <typename ScopeType>
	void init(ScopeType& scope) {

		scope.getSpy().getReceiver().registerCallback(_innerCallback);
		scope.getSender().registerSlot(_outerSlot);

		Backwards<Rest...>::init(scope);
	}

private:

	signals::PassThroughCallback<SignalType> _innerCallback;
	signals::PassThroughSlot<SignalType>     _outerSlot;
};

// base case
template <typename SignalType>
class Backwards<SignalType> {

public:

	Backwards() {

		_innerCallback.forwardTo(_outerSlot);
	}

	template <typename ScopeType>
	void init(ScopeType& scope) {

		scope.getSpy().getReceiver().registerCallback(_innerCallback);
		scope.getSender().registerSlot(_outerSlot);
	}

private:

	signals::PassThroughCallback<SignalType> _innerCallback;
	signals::PassThroughSlot<SignalType>     _outerSlot;
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

