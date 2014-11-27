#ifndef SCOPEGRAPH_DETAIL_ACCEPTS_IMPL_H__
#define SCOPEGRAPH_DETAIL_ACCEPTS_IMPL_H__

namespace sg {
namespace detail {

// base class for all Accepts
class AcceptBase {

protected:

	signals::Receiver& getReceiver() { return _receiver; }

private:

	signals::Receiver _receiver;
};

// recursive inheritance
template <typename SignalType, typename ... Rest>
class AcceptsImpl : public AcceptsImpl<Rest...> {

public:

	typedef AcceptsImpl<SignalType, Rest...> MyType;

	AcceptsImpl() :
			_callback(boost::bind(&MyType::onSignal, this, _1)) {

		getReceiver().registerCallback(_callback);
	}

protected:

	using AcceptsImpl<Rest...>::getReceiver;

	virtual void onSignal(const SignalType&) = 0;

private:

	signals::Callback<SignalType> _callback;
};

// base case
template <typename SignalType>
class AcceptsImpl<SignalType> : public AcceptBase {

public:

	typedef AcceptsImpl<SignalType> MyType;

	AcceptsImpl() :
			_callback(boost::bind(&MyType::onSignal, this, _1)) {

		getReceiver().registerCallback(_callback);
	}

protected:

	virtual void onSignal(const SignalType&) = 0;

private:

	signals::Callback<SignalType> _callback;
};

// specialisation
template <>
class AcceptsImpl<Nothing> : public AcceptBase {};

} // namespace detail
} // namespace sg

#endif // SCOPEGRAPH_DETAIL_ACCEPTS_IMPL_H__

