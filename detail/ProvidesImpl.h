#ifndef SCOPEGRAPH_DETAIL_PROVIDES_IMPL_H__
#define SCOPEGRAPH_DETAIL_PROVIDES_IMPL_H__

#include <cohear/Slot.h>

namespace sg {
namespace detail {

// for each SignalType in ProvidesTypes
template <typename Derived, typename ProvidesTypes>
class ProvidesImpl : public ProvidesImpl<Derived, typename ProvidesTypes::Tail> {

protected:

	typedef typename ProvidesTypes::Head SignalType;

	ProvidesImpl() {

		static_cast<Derived*>(this)->getSender().registerSlot(_slot);
	}

	inline void send(SignalType& signal) {

		_slot(signal);
	}

	using ProvidesImpl<Derived, typename ProvidesTypes::Tail>::send;

private:

	chr::Slot<SignalType> _slot;
};

// last on in inheritance chain
template <typename Derived>
class ProvidesImpl<Derived, Provides<>> {

protected:

	void send(Nothing&) {}
};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_DETAIL_PROVIDES_IMPL_H__

