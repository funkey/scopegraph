#ifndef SCOPEGRAPH_DETAIL_PROVIDES_IMPL_H__
#define SCOPEGRAPH_DETAIL_PROVIDES_IMPL_H__

#include <scopegraph/Signals.h>

namespace sg {
namespace detail {

template <typename SignalType>
class ProvidesImpl {

protected:

	void collectSlots(signals::Sender& sender) {

		sender.registerSlot(_slot);
	}

	inline void send(SignalType& signal) {

		_slot(signal);
	}

private:

	signals::Slot<SignalType> _slot;
};

// recursive inheritance
template <typename SignalType, typename ... Rest>
class ProvidesRec : public ProvidesImpl<SignalType>, public ProvidesRec<Rest...> {

protected:

	void collectSlots(signals::Sender& sender) {

		ProvidesImpl<SignalType>::collectSlots(sender);
		ProvidesRec<Rest...>::collectSlots(sender);
	}

	using ProvidesImpl<SignalType>::send;
	using ProvidesRec<Rest...>::send;
};

// base case
template <typename SignalType>
class ProvidesRec<SignalType> : public ProvidesImpl<SignalType> {

protected:

	void collectSlots(signals::Sender& sender) {

		ProvidesImpl<SignalType>::collectSlots(sender);
	}

	using ProvidesImpl<SignalType>::send;
};

// specialisation
template <>
class ProvidesRec<Nothing> {

protected:

	void collectSlots(signals::Sender&) {}

	inline void send(Nothing&) {}
};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_DETAIL_PROVIDES_IMPL_H__

