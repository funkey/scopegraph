#ifndef SCOPEGRAPH_PROVIDES_H__
#define SCOPEGRAPH_PROVIDES_H__

#include <cohear/Sender.h>
#include "detail/ProvidesImpl.h"

namespace sg {

/**
 * Mix-in for user specified signals. For each signal, a
 *
 *   void send(SignalType& signal);
 *
 * method will be provided. Additionally,
 *
 *   template <typename SignalType, typename ... Args>
 *   void send(Args ... args);
 *
 * can be used to generate and send a signal. This mix-in holds a Sender, for 
 * which all signal slots are automatically registered on construction.
 */
template <typename ... Signals>
class Provides : public detail::ProvidesRec<Signals...> {

protected:

	Provides() {

		detail::ProvidesRec<Signals...>::collectSlots(_sender);
	}

	/**
	 * Get the sender that holds the slots for the requested signals.
	 */
	chr::Sender& getSender() {

		return _sender;
	}

	using detail::ProvidesRec<Signals...>::send;

	template <typename SignalType, typename ... Args>
	void send(Args ... args) {

		SignalType signal(args ...);
		send(signal);
	}

private:

	chr::Sender _sender;
};

} // namespace sg

#endif // SCOPEGRAPH_PROVIDES_H__

