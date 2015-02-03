#ifndef SCOPEGRAPH_ACCEPTS_H__
#define SCOPEGRAPH_ACCEPTS_H__

#include "Signals.h"

namespace sg {

/**
 * Mix-in for agents to accept user specified signals. For each signal type 
 * provided, the mix-in connects a user provided method
 *
 *   void Derived::onSignal(SignalType& signal),
 *
 * which a concrete class should implement. Example usage:
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
class Accepts {

public:

	typedef SignalType       Head;
	typedef Accepts<Rest...> Tail;
};

} // namespace sg

#endif // SCOPEGRAPH_ACCEPTS_H__

