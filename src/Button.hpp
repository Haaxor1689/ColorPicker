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
		: name(text),
		  bBox(bBox),
		  action(action) {}

	void input(const Event& event) {
		switch (event.getType()) {
		case eventType::KeyDown:
			if (shortcut && event.getKey() == shortcut)
				action();
			break;
		case eventType::MouseButtonDown:
			if (event.getPosition().isInside(bBox))
				action();
			break;
		default: break;
		}
	}

	void draw(RenderController& renderer) {
		if (fill)
			renderer.drawRectangle(fill.value(), bBox);

		try {
			renderer.drawSprite(sprite.value(), bBox);
		} catch (const std::bad_optional_access&) {}

		try {
			renderer.drawText(name, font.value(), { bBox.x + bBox.w / 2, bBox.y + bBox.h / 2 }, verticalAlign::Top);
		} catch (const std::bad_optional_access&) {}
	}

	void setBBox(const SDL_Rect& val) { bBox = val; }
	void setShortcut() { shortcut.reset(); }
	void setShortcut(int val) { shortcut.emplace(val); }
	void setFont() { font.reset(); }
	void setFont(const std::string& val) { font.emplace(val); }
	void setSprite() { sprite.reset(); }
	void setSprite(const std::string& val) { sprite.emplace(val); }
	void setFill() { fill.reset(); }
	void setFill(const Color& val) { fill.emplace(val); }

	const SDL_Rect& getBBox() const { return bBox; }

private:
	std::string name;
	SDL_Rect bBox;
	std::function<void()> action;

	std::optional<int> shortcut;
	std::optional<std::string> font;
	std::optional<std::string> sprite;
	std::optional<Color> fill;
};
