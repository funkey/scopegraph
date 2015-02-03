#ifndef SCOPEGRAPH_PROVIDES_INNER_H__
#define SCOPEGRAPH_PROVIDES_INNER_H__

namespace sg {

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
template <typename SignalType = Nothing, typename ... Rest>
class ProvidesInner {

public:

	typedef SignalType             Head;
	typedef ProvidesInner<Rest...> Tail;
};

} // namespace sg

#endif // SCOPEGRAPH_PROVIDES_INNER_H__

