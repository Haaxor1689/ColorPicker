#pragma once

#include <SDL.h>
#include "Button.hpp"
#include "Additions.hpp"

template <typename T>
class Slider {
public:
	Slider(const std::string& name, const SDL_Rect& bBox, T& value, T rangeFrom, T rangeTo)
		: _name(name),
		  _bBox(bBox),
		  _value(value),
		  _rangeFrom(rangeFrom),
		  _rangeTo(rangeTo),
		  _handler("", { bBox.x, bBox.y, 10, bBox.h }, [this]() { _held = true; }) {
		_handler.fill({ colorModel::RGB, 51, 51, 51 });
		_alignHandler();
	}

	void input(const Event& event) {
		_handler.input(event);

		switch (event.getType()) {
		case eventType::MouseMotion:
			if (_held) {
				_handler.bBox(SDL_Rect{ event.getPosition().x, _bBox.y, 10, _bBox.h });
				if (middle(_handler.bBox()).x < _bBox.x)
					_handler.bBox({ _bBox.x - 5, _bBox.y, 10, _bBox.h });
				if (middle(_handler.bBox()).x > _bBox.x + _bBox.w)
					_handler.bBox({ _bBox.x - 5 + _bBox.w, _bBox.y, 10, _bBox.h });
				_setValue();
				if (_onMove)
					_onMove.value()();
			}
			break;
		case eventType::MouseButtonUp:
			_held = false;
			break;
		default: break;
		}
	}

	void step() {
		_alignHandler();
	}

	void draw(RenderController& renderer) {
		if (_fill) {
			if (_border && _borderColor)
				renderer.drawRectangle(_fill.value(), _bBox, _borderColor.value(), _border.value());
			else
				renderer.drawRectangle(_fill.value(), _bBox);
		}
			

		_handler.draw(renderer);
	}


	const std::string& name() const { return _name; }

	const SDL_Rect& bBox() const { return _bBox; }
	void bBox(const SDL_Rect& val) {
		_bBox = val;
		_handler.bBox({val.x, val.y, 10, val.h});
		_alignHandler();
	}

	unsigned handlerBorder() const { return _handler.border(); }
	void handlerBorder(unsigned val) { _handler.border(val); }
	void removeHandlerBorder() { _handler.removeBorder(); }

	const Color& handlerBorderColor() const { return _handler.borderColor(); }
	void handlerBorderColor(const Color& val) { _handler.borderColor(val); }
	void removeHandlerBorderColor() { _handler.removeBorderColor(); }

	void onMove(const std::function<void()>& function) { _onMove.emplace(function); }
	void removeOnMove() { _onMove.reset(); }

	const Color& fill() const { return _fill.value(); }
	void fill(const Color& val) { _fill.emplace(val); }
	void removeFill() { _fill.reset(); }

	unsigned border() const { return _border.value(); }
	void border(unsigned val) { _border.emplace(val); }
	void removeBorder() { _border.reset(); }

	const Color& borderColor() const { return _borderColor.value(); }
	void borderColor(const Color& val) { _borderColor.emplace(val); }
	void removeBorderColor() { _borderColor.reset(); }

private:
	void _setValue() {
		_value = static_cast<T>(static_cast<float>(_rangeTo - _rangeFrom) * (static_cast<float>(middle(_handler.bBox()).x - _bBox.x) / _bBox.w) + static_cast<float>(_rangeFrom));
	}

	void _alignHandler() {
		_handler.bBox({ _bBox.x - 5 + static_cast<int>((static_cast<float>(_value - _rangeFrom) / _rangeTo) * _bBox.w), _bBox.y, 10, _bBox.h });
	}

	std::string _name;

	SDL_Rect _bBox;
	T& _value;
	T _rangeFrom;
	T _rangeTo;

	Button _handler;
	bool _held = false;

	std::optional<std::function<void()>> _onMove;
	std::optional<Color> _fill;
	std::optional<unsigned> _border;
	std::optional<Color> _borderColor;
};
