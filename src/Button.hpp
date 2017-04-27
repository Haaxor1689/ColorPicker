#pragma once

#include "Event.hpp"
#include "Position.hpp"
#include "RenderController.hpp"
#include <functional>
#include <optional>

class Engine;

class Button {
public:
	Button(const std::string& text,
	       const SDL_Rect& bBox,
	       std::function<void()> action)
		: _name(text),
		  _bBox(bBox),
		  _action(action) {}

	void input(const Event& event) const {
		switch (event.getType()) {
		case eventType::KeyDown:
			if (_shortcut && event.getKey() == _shortcut)
				_action();
			break;
		case eventType::MouseButtonDown:
			if (event.getPosition().isInside(_bBox))
				_action();
			break;
		default: break;
		} 
	}

	void draw(RenderController& renderer) {
		if (_fill) {
			if (_border && _borderColor)
				renderer.drawRectangle(_fill.value(), _bBox, _borderColor.value(), _border.value());
			else
				renderer.drawRectangle(_fill.value(), _bBox);
		}

		if (_sprite)
			renderer.drawSprite(_sprite.value(), _bBox);

		if (_text && _font)
			renderer.drawText(_text.value(), _font.value(), { _bBox.x + _bBox.w / 2, _bBox.y + _bBox.h / 2 }, verticalAlign::Top);
	}

	const std::string& name() const { return _name; }

	const SDL_Rect& bBox() const { return _bBox; }
	void bBox(const SDL_Rect& val) { _bBox = val; }

	int shortcut() const { return _shortcut.value(); }
	void shortcut(int val) { _shortcut.emplace(val); }
	void removeShortcut() { _shortcut.reset(); }

	const std::string& text() const { return _text.value(); }
	void text(const std::string& val) { _text.emplace(val); }
	void removeText() { _text.reset(); }

	const std::string& font() const { return _font.value(); }
	void font(const std::string& val) { _font.emplace(val); }
	void removeFont() { _font.reset(); }

	const std::string& sprite() const { return _sprite.value(); }
	void sprite(const std::string& val) { _sprite.emplace(val); }
	void removeSprite() { _sprite.reset(); }

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
	const std::string _name;
	SDL_Rect _bBox;
	std::function<void()> _action;

	std::optional<int> _shortcut;
	std::optional<std::string> _text;
	std::optional<std::string> _font;
	std::optional<std::string> _sprite;
	std::optional<Color> _fill;
	std::optional<unsigned> _border;
	std::optional<Color> _borderColor;
};
