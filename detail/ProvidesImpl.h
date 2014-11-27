#ifndef SCOPEGRAPH_DETAIL_PROVIDES_IMPL_H__
#define SCOPEGRAPH_DETAIL_PROVIDES_IMPL_H__

#include <scopegraph/Signals.h>

namespace sg {
namespace detail {

// base class for all Provides
class ProvideBase {

protected:

	signals::Sender& getSender() {

		return _sender;
	}

private:

	signals::Sender _sender;
};

// recursive inheritance
template <typename SignalType, typename ... Rest>
class ProvidesImpl : public ProvidesImpl<Rest...> {

public:

	ProvidesImpl() {

		getSender().registerSlot(_slot);
	}

protected:

	using ProvidesImpl<Rest...>::getSender;
	using ProvidesImpl<Rest...>::send;

	inline void send(SignalType& signal) {

		_slot(signal);
	}

private:

	signals::Slot<SignalType> _slot;
};

// base case
template <typename SignalType>
class ProvidesImpl<SignalType> : public ProvideBase {

public:

	ProvidesImpl() {

		getSender().registerSlot(_slot);
	}

protected:

	inline void send(SignalType& signal) {

		_slot(signal);
	}

private:

	signals::Slot<SignalType> _slot;
};

// specialisation
template <>
class ProvidesImpl<Nothing> : public ProvideBase {

protected:

	inline void send(Nothing&) {}
};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_DETAIL_PROVIDES_IMPL_H__

