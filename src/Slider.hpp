#pragma once

#include <SDL.h>
#include "Button.hpp"
#include "Additions.hpp"

template <typename T>
class Slider {
public:
	Slider(const SDL_Rect& bBox, T& value, T rangeFrom, T rangeTo)
		: bBox(bBox),
		  value(value),
		  rangeFrom(rangeFrom),
		  rangeTo(rangeTo),
		  handler("", { bBox.x, bBox.y, 10, bBox.h }, std::bind(&Slider::hold, this)) {
		handler.setFill({ colorModel::RGB, 51, 51, 51 });
		alignHandler();
	}

	void input(const Event& event) {
		handler.input(event);

		switch (event.getType()) {
		case eventType::MouseMotion:
			if (held) {
				handler.setBBox(handler.getBBox() + SDL_Rect{ event.getMotion().x, 0, 0, 0 });
				if (middle(handler.getBBox()).x < bBox.x)
					handler.setBBox({ bBox.x - 5, bBox.y, 10, bBox.h });
				if (middle(handler.getBBox()).x > bBox.x + bBox.w)
					handler.setBBox({ bBox.x - 5 + bBox.w, bBox.y, 10, bBox.h });
				setValue();
			}
			break;
		case eventType::MouseButtonUp:
			held = false;
			break;
		default: break;
		}
	}

	void step() {
		alignHandler();
	}

	void draw(RenderController& renderer) {
		if (fill)
			renderer.drawRectangle(fill.value(), bBox);

		handler.draw(renderer);
	}

	void setValue() const {
		value = (rangeTo - rangeFrom) * (static_cast<float>(middle(handler.getBBox()).x - bBox.x) / bBox.w) + rangeFrom;
	}

	void alignHandler() {
		handler.setBBox({ bBox.x - 5 + static_cast<int>((static_cast<float>(value - rangeFrom) / rangeTo) * bBox.w), bBox.y, 10, bBox.h });
	}

	void setFill() { fill.reset(); }
	void setFill(const Color& val) { fill.emplace(val); }

private:
	void hold() {
		held = true;
		fill.reset();
	}

	SDL_Rect bBox;
	T& value;
	T rangeFrom;
	T rangeTo;

	Button handler;
	bool held = false;

	std::optional<Color> fill;
};
