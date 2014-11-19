#ifndef SCOPEGRAPH_FORWARDS_H__
#define SCOPEGRAPH_FORWARDS_H__

#include <signals/PassThroughCallback.h>
#include <signals/PassThroughSlot.h>

namespace sg {

// recursive inheritance
template <typename SignalType, typename ... Rest>
class Forwards : public Forwards<Rest...> {

public:

	Forwards() {

		_outerCallback.forwardTo(_innerSlot);
	}

	template <typename ScopeType>
	void init(ScopeType& scope) {

		scope.getSpy().getSender().registerSlot(_innerSlot);
		scope.getReceiver().registerCallback(_outerCallback);

		Forwards<Rest...>::init(scope);
	}

private:

	signals::PassThroughCallback<SignalType> _outerCallback;
	signals::PassThroughSlot<SignalType>     _innerSlot;
};

// base case
template <typename SignalType>
class Forwards<SignalType> {

public:

	Forwards() {

		_outerCallback.forwardTo(_innerSlot);
	}

	template <typename ScopeType>
	void init(ScopeType& scope) {

		scope.getSpy().getSender().registerSlot(_innerSlot);
		scope.getReceiver().registerCallback(_outerCallback);
	}

private:

	signals::PassThroughCallback<SignalType> _outerCallback;
	signals::PassThroughSlot<SignalType>     _innerSlot;
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

