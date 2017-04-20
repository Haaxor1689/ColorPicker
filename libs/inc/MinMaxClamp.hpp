#pragma once

namespace mmc {
	template <typename T, typename... Ts>
	T min(T&& first, T&& second, Ts&&... tail) {
		return first < second ? min(first, tail...) : min(second, tail...);
	}

	template <typename T>
	T min(T&& val) {
		return std::forward<T>(val);
	}

	template <typename T, typename... Ts>
	T max(T&& first, T&& second, Ts&&... tail) {
		return first > second ? max(first, tail...) : max(second, tail...);
	}

	template <typename T>
	T max(T&& val) {
		return std::forward<T>(val);
	}

	template <typename T>
	T clamp(T&& what, T&& from, T&& to) {
		return min(max(what, from), to);
	}
}
