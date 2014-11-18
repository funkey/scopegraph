#ifndef SCOPEGRAPH_PROVIDES_H__
#define SCOPEGRAPH_PROVIDES_H__

#include <signals/Slot.h>
#include "Nothing.h"

namespace sg {

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
class Provides : public Provides<Rest...> {

public:

	Provides() {

		getSender().registerSlot(_slot);
	}

protected:

	using Provides<Rest...>::getSender;
	using Provides<Rest...>::send;

	inline void send(SignalType& signal) {

		_slot(signal);
	}

private:

	signals::Slot<SignalType> _slot;
};

// base case
template <typename SignalType>
class Provides<SignalType> : public ProvideBase {

public:

	Provides() {

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
class Provides<Nothing> : public ProvideBase {

protected:

	inline void send(Nothing&) {}
};

} // namespace sg

#endif // SCOPEGRAPH_PROVIDES_H__

