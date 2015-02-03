#ifndef SCOPEGRAPH_PROVIDES_H__
#define SCOPEGRAPH_PROVIDES_H__

#include "Signals.h"

namespace sg {

/**
 * Mix-in for agents to emit user specified signals. For each signal, a
 *
 *   void send(SignalType& signal);
 *
 * method will be provided. Additionally,
 *
 *   template <typename SignalType, typename ... Args>
 *   void send(Args ... args);
 *
 * can be used to generate and send a signal. Example usage:
 *
 *   class MrSmith :
 *     public Agent<
 *       MrSmith,
 *       Accepts<NewMission>,
 *       Provides<ImOnIt, ImBusy>
 *   > {
 *
 *   public:
 *
 *     void onSignal(NewMission& signal) {
 *
 *       if (_idle)
 *         send<ImOnIt>();
 *       else
 *         send<ImBusy>();
 *     }
 *   };
 */
template <typename SignalType = Nothing, typename ... Rest>
class Provides {

public:

	typedef SignalType        Head;
	typedef Provides<Rest...> Tail;
};

} // namespace sg

#endif // SCOPEGRAPH_PROVIDES_H__

