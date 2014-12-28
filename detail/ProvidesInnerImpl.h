#ifndef SCOPEGRAPH_DETAIL_PROVIDES_INNER_IMPL_H__
#define SCOPEGRAPH_DETAIL_PROVIDES_INNER_IMPL_H__

#include <signals/VirtualCallbackInvoker.h>
#include <scopegraph/Signals.h>
#include "AcceptsImpl.h"

namespace sg {
namespace detail {

/**
 * Basically the same as Provides{Impl,Rec}, only with sendInner() instead of of 
 * send() methods.
 */

template <typename SignalType>
class ProvidesInnerImpl {

protected:

	void collectSlots(signals::Sender& sender) {

		sender.registerSlot(_slot);
	}

	inline void sendInner(SignalType& signal) {

		_slot(signal);
	}

private:

	signals::Slot<SignalType, signals::VirtualCallbackInvoker<SignalType, AcceptsImpl<SignalType>>> _slot;
};

// recursive inheritance
template <typename SignalType, typename ... Rest>
class ProvidesInnerRec : public ProvidesInnerImpl<SignalType>, public ProvidesInnerRec<Rest...> {

protected:

	void collectSlots(signals::Sender& sender) {

		ProvidesInnerImpl<SignalType>::collectSlots(sender);
		ProvidesInnerRec<Rest...>::collectSlots(sender);
	}

	using ProvidesInnerImpl<SignalType>::sendInner;
	using ProvidesInnerRec<Rest...>::sendInner;
};

// base case
template <typename SignalType>
class ProvidesInnerRec<SignalType> : public ProvidesInnerImpl<SignalType> {

protected:

	void collectSlots(signals::Sender& sender) {

		ProvidesInnerImpl<SignalType>::collectSlots(sender);
	}

	using ProvidesInnerImpl<SignalType>::sendInner;
};

// specialisation
template <>
class ProvidesInnerRec<Nothing> {

protected:

	void collectSlots(signals::Sender&) {}

	inline void sendInner(Nothing&) {}
};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_DETAIL_PROVIDES_INNER_IMPL_H__

