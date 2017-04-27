#pragma once

#include <random>

class Random {
public:
	template <typename T>
	static T get(T from, T to) {
		return static_cast<T>(std::uniform_int_distribution<int>{ static_cast<int>(from), static_cast<int>(to) }(randomEngine));
	}

	static std::random_device randomSeed;
private:
	static std::default_random_engine randomEngine;
};
