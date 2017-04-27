#pragma once

#include "Button.hpp"
#include "Slider.hpp"
#include <map>

class _ResourceMapAccessor {
	template<typename Iter>
	class Iterator {
	protected:
		Iter _current;
		using traits = std::iterator_traits<Iter>;
	public:
		using iterator_type = std::bidirectional_iterator_tag;
		using value_type = typename traits::value_type;
		using pointer = typename traits::pointer;
		using reference = typename traits::reference;
		using difference_type = typename traits::difference_type;

		Iterator() : _current() { }
		Iterator(Iter iter) : _current(iter) { }
		Iterator(const Iterator &iter) : _current(iter._current) { }

		auto& operator*() const noexcept { return (*_current).second; }
		auto* operator->() const noexcept { return std::addressof(_current->second); }

		Iterator& operator++() noexcept {
			++_current;
			return *this;
		}

		Iterator operator++(int) noexcept {
			Iterator tmp = *this;
			++_current;
			return tmp;
		}

		Iterator& operator--() noexcept {
			--_current;
			return *this;
		}

		Iterator operator--(int) noexcept {
			Iterator tmp = *this;
			--_current;
			return tmp;
		}

		friend bool operator==(const Iterator &i1, const Iterator &i2) noexcept { return i1._current == i2._current; }
		friend bool operator!=(const Iterator &i1, const Iterator &i2) noexcept { return i1._current != i2._current; }
	};

	template <typename T>
	class ResourceMap {
		using map = std::map<std::string, T>;
	public:
		using iterator = Iterator<typename map::iterator>;
		using const_iterator = Iterator<typename map::const_iterator>;

		ResourceMap() = default;

		void insert(T&& value) {
			_data.insert(std::make_pair(value.name(), std::forward<T>(value)));
		}

		template <typename... Ts>
		void emplace(const std::string& key, Ts&&... args) {
			_data.emplace(std::piecewise_construct, 
				std::forward_as_tuple(key), 
				std::forward_as_tuple(key, std::forward<Ts>(args)...));
		}

		T& operator[](const std::string& key) {
			auto it = _data.find(key);
			if (it == _data.end())
				throw std::logic_error("Resource with name " + key + " wasn't found.");
			return it->second;
		}

		const T& operator[](const std::string& key) const {
			return const_cast<const T&>(const_cast<ResourceMap*>(this)->operator[](key));
		}

		unsigned size() const { return _data.size(); }
		bool empty() const { return _data.empty(); }

		iterator begin() { return iterator(_data.begin()); }
		iterator end() { return iterator(_data.end()); }
		const_iterator begin() const { return const_iterator(_data.begin()); }
		const_iterator end() const { return const_iterator(_data.end()); }
		const_iterator cbegin() const { return const_iterator(_data.cbegin()); }
		const_iterator cend() const { return const_iterator(_data.cend()); }

	private:
		std::map<std::string, T> _data;
	};

public:
	using ButtonMapAccessor = ResourceMap<Button>;
	template <typename Type>
	using SliderMapAccessor = ResourceMap<Slider<Type>>;
	
};

using ButtonMap = _ResourceMapAccessor::ButtonMapAccessor;
template <typename Type>
using SliderMap = _ResourceMapAccessor::SliderMapAccessor<Type>;