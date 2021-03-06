#pragma once

#include "Color.hpp"
#include "Enums.hpp"
#include "Text.hpp"
#include "Position.hpp"
#include "Sprite.hpp"
#include "Wrappers.hpp"
#include <SDL.h>
#include <map>
#include <stdexcept>

class RenderController {
public:
	using SpriteMap = std::map<std::string, Sprite>;
	using FontMap = std::map<std::string, Text>;

	RenderController() {
		window = SDL_CreateWindow("ColorPicker", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, 0);
		renderer = SDL_CreateRenderer(&window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		SDL_SetRenderDrawColor(&renderer, clearColor.r, clearColor.g, clearColor.b, 255);
	}

	void drawText(std::string text,
	              std::string font,
	              Position pos) {
		drawText(text, font, pos, horizontalAlign::Middle, verticalAlign::Middle);
	}

	void drawText(std::string text,
	              std::string font,
	              Position pos,
	              verticalAlign vAlign,
	              horizontalAlign hAlign = horizontalAlign::Middle) {
		drawText(text, font, pos, hAlign, vAlign);
	}

	void drawText(std::string text,
	              std::string font,
	              Position pos,
	              horizontalAlign hAlign,
	              verticalAlign vAlign = verticalAlign::Middle) {
		auto it = fonts.find(font);
		if (it == fonts.end())
			throw std::logic_error("No font with name " + font + " was loaded.");
		it->second.draw(&renderer, text, pos, hAlign, vAlign);
	}

	void drawSprite(std::string texture,
	                Position pos,
	                Uint8 alpha = 255) {
		auto it = sprites.find(texture);
		if (it == sprites.end())
			throw std::logic_error("No texture with name " + texture + " was loaded.");
		it->second.draw(&renderer, pos, alpha);
	}

	void drawSprite(std::string texture,
	                SDL_Rect& bBox,
	                Uint8 alpha = 255) {
		auto it = sprites.find(texture);
		if (it == sprites.end())
			throw std::logic_error("No texture with name " + texture + " was loaded.");
		it->second.draw(&renderer, bBox, alpha);
	}

	void drawRectangle(Color color, const SDL_Rect& bBox, Uint8 alpha = 255) {
		SDL_SetRenderDrawColor(&renderer, color.r, color.g, color.b, alpha);
		SDL_RenderFillRect(&renderer, &bBox);
		SDL_SetRenderDrawColor(&renderer, clearColor.r, clearColor.g, clearColor.b, 255);
	}

	void drawRectangle(Color color, const SDL_Rect& bBox, Color borderColor, int border, Uint8 alpha = 255) {
		drawRectangle(borderColor, bBox, alpha);
		drawRectangle(color, SDL_Rect{ bBox.x + border, bBox.y + border, bBox.w - 2 * border, bBox.h - 2 * border, }, alpha);
	}

	void addFont(std::string name, std::string path, int size, SDL_Color color = { 255, 255, 255, 255 }) {
		fonts.insert(make_pair(name, Text(&renderer, path, size, color)));
	}

	void addSprite(std::string name, std::string path) {
		sprites.insert(make_pair(name, Sprite(path, &renderer)));
	}

	SDL_Renderer* getRenderer() const noexcept {
		return &renderer;
	}

private:
	Color clearColor = { colorModel::RGB, 102, 102, 102 };
	Window window;
	Renderer renderer;
	SpriteMap sprites;
	FontMap fonts;
};
