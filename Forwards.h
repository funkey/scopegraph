#ifndef SCOPEGRAPH_FORWARDS_H__
#define SCOPEGRAPH_FORWARDS_H__

#include "detail/AgentBase.h"
#include "detail/Spy.h"

namespace sg {

// recursive inheritance
template <typename SignalType, typename ... Rest>
class Forwards : public Forwards<Rest...> {

public:

	Forwards() : _spy(std::make_shared<detail::Spy<SignalType>>()) {}

	template <typename ScopeType>
	void init(ScopeType& scope) {

		// register the spy's pass-through callback in the parent scope
		scope.getReceiver().registerCallback(_spy->getOuterCallback());

		// establish the spy connection to our scope
		scope.add(_spy);

		Forwards<Rest...>::init(scope);
	}

private:

	std::shared_ptr<detail::Spy<SignalType>> _spy;
};

// base case
template <typename SignalType>
class Forwards<SignalType> {

public:

	Forwards() : _spy(std::make_shared<detail::Spy<SignalType>>()) {}

	template <typename ScopeType>
	void init(ScopeType& scope) {

		// register the spy's pass-through callback in the parent scope
		scope.getReceiver().registerCallback(_spy->getOuterCallback());

		// establish the spy connection to our scope
		scope.add(_spy);
	}

private:

	std::shared_ptr<detail::Spy<SignalType>> _spy;
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

