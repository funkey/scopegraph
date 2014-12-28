#ifndef SCOPEGRAPH_DETAIL_SPY_H__
#define SCOPEGRAPH_DETAIL_SPY_H__

#include <scopegraph/ProvidesInner.h>

namespace sg {
namespace detail {

class Spy : public Agent<
		Accepts<AddAgent>
> {

private:

	void onSignal(AddAgent& /*signal*/) {/*TODO*/}
};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_DETAIL_SPY_H__

