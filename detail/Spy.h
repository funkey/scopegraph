#ifndef SCOPEGRAPH_DETAIL_SPY_H__
#define SCOPEGRAPH_DETAIL_SPY_H__

#include <scopegraph/ProvidesInner.h>

namespace sg {
namespace detail {

template <typename ... Ts>
class Spy{};
template <typename ... ProvidesInnerSignals>
class Spy<ProvidesInner<ProvidesInnerSignals...>> : public Agent<Accepts<AddAgent>, Provides<ProvidesInnerSignals...>> {

private:

	void onSignal(AddAgent& /*signal*/) {/*TODO*/}
};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_DETAIL_SPY_H__

