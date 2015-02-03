#ifndef SCOPEGRAPH_PROVIDES_H__
#define SCOPEGRAPH_PROVIDES_H__

#include "Signals.h"

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
template <typename SignalType = Nothing, typename ... Rest>
class Provides {

public:

	typedef SignalType        Head;
	typedef Provides<Rest...> Tail;
};

} // namespace sg

#endif // SCOPEGRAPH_PROVIDES_H__

