#pragma once

#include <SDL.h>
#include <string>

/**
 * \brief Sets horizontal align of text. 
 */
enum class horizontalAlign {
	Left,
	Middle,
	Right
};

/**
 * \brief Sets vertical align of text.
 */
enum class verticalAlign {
	Top,
	Middle,
	Bottom
};

enum class colorModel {
	RGB,
	HSV
};

/**
 * \brief Enums for all suppoted SDL_Events.
 */
enum class eventType {
	KeyDown,
	KeyUp,
	MouseMotion,
	MouseButtonDown,
	MouseButtonUp,
	Quit,
	Unused
};

eventType toEventType(Uint32 value);

std::string toString(eventType value);
