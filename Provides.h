#ifndef SCOPEGRAPH_PROVIDES_H__
#define SCOPEGRAPH_PROVIDES_H__

#include <signals/Slot.h>

namespace sg {

// recursive inheritance
template <typename SignalType, typename ... Rest>
class Provides : public Provides<Rest...> {

public:

	Provides() {

		getSender().registerSlot(_slot);
	}

protected:

	using Provides<Rest...>::getSender;

private:

	signals::Slot<SignalType> _slot;
};

// base case
template <typename SignalType>
class Provides<SignalType> {

public:

	Provides() {

		_sender.registerSlot(_slot);
	}

protected:

	signals::Sender& getSender() { return _sender; }

private:

	signals::Slot<SignalType> _slot;

	signals::Sender _sender;
};

} // namespace sg

#endif // SCOPEGRAPH_PROVIDES_H__

