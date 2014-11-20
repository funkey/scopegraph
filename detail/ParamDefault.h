#ifndef SCOPEGRAPH_DETAIL_DEFAULT_PARAM_H__
#define SCOPEGRAPH_DETAIL_DEFAULT_PARAM_H__

/**
 * A template meta-function that finds a named template parameter in a type 
 * list. If the parameter is not present, a specified default type is returned 
 * instead.
 *
 * Usage:
 *
 *   ParamDefault<ParamName<A,B>, Params>::Value
 *
 *   Returns the first occurence of ParamName<T...> in the list Params, or 
 *   ParamName<A,B> if no ParamName<T...> could be found.
 */

namespace sg {
namespace detail {

// Param is not ParamName<...> -- we have to continue searching
template <template <typename ...> class ParamName, typename DefaultParam, typename Param, typename ... Ps>
class ParamDefaultImpl : public ParamDefaultImpl<ParamName, DefaultParam, Ps...> {};

// specialization: last element, Param is not ParamName
template <template <typename ...> class ParamName, typename DefaultParam, typename Param>
class ParamDefaultImpl<ParamName, DefaultParam, Param> {
public:
	typedef DefaultParam Value;
};

// specialization: Param is ParamName<Ts...>
template <template <typename ...> class ParamName, typename DefaultParam, typename ... Ts, typename ... Ps>
class ParamDefaultImpl<ParamName, DefaultParam, ParamName<Ts...>, Ps...> {
public:
	typedef ParamName<Ts...> Value;
};

class End {};
template <typename Default, typename ... Params>
class ParamDefault {};
// specialization is what really does things
template <template <typename ...> class ParamName, typename ... DefaultValues, typename ... Params>
class ParamDefault<ParamName<DefaultValues...>, Params...> :
	public ParamDefaultImpl<ParamName, ParamName<DefaultValues...>, Params...,  End> {};

} // namespace detail
} // namesapce sg

#endif // SCOPEGRAPH_DETAIL_DEFAULT_PARAM_H__

