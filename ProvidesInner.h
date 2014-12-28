#ifndef SCOPEGRAPH_PROVIDES_INNER_H__
#define SCOPEGRAPH_PROVIDES_INNER_H__

#include "detail/ProvidesInnerImpl.h"

namespace sg {

template <typename ... T>
class Spy;

/**
 * Mix-in for user specified signals that are sent from a scope to the agents 
 * held by the scope. For each signal, a
 *
 *   void sendInner(SignalType& signal);
 *
 * method will be provided. Additionally,
 *
 *   template <typename SignalType, typename ... Args>
 *   void sendInner(Args ... args);
 *
 * can be used to generate and send a signal. This mix-in uses the sender of a 
 * spy, which has to be introduced via init().
 */
template <typename ... Signals>
class ProvidesInner : public detail::ProvidesInnerRec<Signals...> {

protected:

	/**
	 * Initialize this mix-in for the given spy. The spy's sender will be used 
	 * to register the slots of this mix-in, i.e., the spy will hold pointers to 
	 * mix-in members. The caller has to ensure that the mix-in survives the 
	 * spy.
	 */
	template <typename SpyType>
	void init(SpyType& spy) {

		detail::ProvidesInnerRec<Signals...>::collectSlots(spy.getSender());
	}

	using detail::ProvidesInnerRec<Signals...>::sendInner;

	template <typename SignalType, typename ... Args>
	void sendInner(Args ... args) {

		SignalType signal(args ...);
		sendInner(signal);
	}
};

} // namespace sg

#endif // SCOPEGRAPH_PROVIDES_INNER_H__

