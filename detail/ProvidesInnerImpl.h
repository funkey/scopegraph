#ifndef SCOPEGRAPH_DETAIL_PROVIDES_INNER_IMPL_H__
#define SCOPEGRAPH_DETAIL_PROVIDES_INNER_IMPL_H__

namespace sg {
namespace detail {

// for each SignalType in ProvidesTypes
template <typename Derived, typename ProvidesTypes>
class ProvidesInnerImpl : public ProvidesInnerImpl<Derived, typename ProvidesTypes::Tail> {

protected:

	typedef typename ProvidesTypes::Head SignalType;

	template <typename SpyType>
	void init(SpyType& spy) {

		spy.getSender().registerSlot(_slot);

		ProvidesInnerImpl<Derived, typename ProvidesTypes::Tail>::init(spy);
	}

	inline void sendInner(SignalType& signal) {

		_slot(signal);
	}

	using ProvidesInnerImpl<Derived, typename ProvidesTypes::Tail>::sendInner;

private:

	chr::Slot<SignalType> _slot;
};

// last on in inheritance chain
template <typename Derived>
class ProvidesInnerImpl<Derived, ProvidesInner<>> {

protected:

	template <typename SpyType>
	void init(SpyType&) {}

	inline void sendInner(Nothing&) {}
};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_DETAIL_PROVIDES_INNER_IMPL_H__

