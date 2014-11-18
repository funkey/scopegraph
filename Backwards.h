#ifndef SCOPEGRAPH_BACKWARDS_H__
#define SCOPEGRAPH_BACKWARDS_H__

namespace sg {

// recursive inheritance
template <typename SignalType, typename ... Rest>
class Backwards : public Backwards<Rest...> {
};

// base case
template <typename SignalType>
class Backwards<SignalType> {
};

} // namespace sg

#endif // SCOPEGRAPH_BACKWARDS_H__

