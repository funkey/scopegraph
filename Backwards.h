#ifndef SCOPEGRAPH_BACKWARDS_H__
#define SCOPEGRAPH_BACKWARDS_H__

namespace sg {

// recursive inheritance
template <typename SignalType, typename ... Rest>
class Backwards : public Backwards<Rest...> {

public:

	Backwards() : _spy(std::make_shared<detail::Spy<SignalType>>()) {}

	template <typename ScopeType>
	void init(ScopeType& scope) {

		// register the spy's pass-through slot in the parent scope
		scope.getSender().registerSlot(_spy->getOuterSlot());

		// establish the spy connection to our scope
		scope.add(_spy);

		Backwards<Rest...>::init(scope);
	}

private:

	std::shared_ptr<detail::Spy<SignalType>> _spy;
};

// base case
template <typename SignalType>
class Backwards<SignalType> {

public:

	Backwards() : _spy(std::make_shared<detail::Spy<SignalType>>()) {}

	template <typename ScopeType>
	void init(ScopeType& scope) {

		// register the spy's pass-through slot in the parent scope
		scope.getSender().registerSlot(_spy->getOuterSlot());

		// establish the spy connection to our scope
		scope.add(_spy);
	}

private:

	std::shared_ptr<detail::Spy<SignalType>> _spy;
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

