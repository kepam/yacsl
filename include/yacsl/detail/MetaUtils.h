#pragma once

/* Various meta-programming utilities. */

#include <tuple>

namespace yacsl
{
namespace meta
{

/* for_each - tuple iteration */
template<std::size_t I = 0, typename FuncT, typename... Ts>
inline typename std::enable_if<I == sizeof...(Ts), void>::type for_each(const std::tuple<Ts...>&, FuncT) {}

template<std::size_t I = 0, typename FuncT, typename... Ts>
inline typename std::enable_if<I < sizeof...(Ts), void>::type for_each(const std::tuple<Ts...>& t, FuncT f)
{
	f(std::get<I>(t));
	for_each<I + 1, FuncT, Ts...>(t, f);
}

/* assign */
template<class ClassT, class T1, class T2>
inline typename std::enable_if<std::is_assignable<T1&, const T2&>::value, void>::type assign(ClassT& obj, T1 ClassT::*dest, const T2& src)
{
	obj.*dest = src;
}

template<class ClassT, class T1, class T2>
inline typename std::enable_if<!std::is_assignable<T1&, const T2&>::value, void>::type assign(ClassT&, T1 ClassT::*, const T2&) {}

/* push_back */
template<class ClassT, class ContainerT, class T2, class T1 = typename ContainerT::value_type>
inline typename std::enable_if<std::is_assignable<T1&, const T2&>::value, void>::type 
push_back(ClassT& obj, ContainerT ClassT::*dest, const T2& value)
{
	(obj.*dest).push_back(value);
}

template<class ClassT, class T1, class T2>
inline void push_back(ClassT&, T1, T2) {}

} // namespace meta
} // namespace yacsl
