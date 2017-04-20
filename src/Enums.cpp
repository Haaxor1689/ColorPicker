#include "Enums.hpp"

eventType toEventType(Uint32 value) {
	switch (value) {
	case SDL_KEYDOWN:
		return eventType::KeyDown;
	case SDL_KEYUP:
		return eventType::KeyUp;
	case SDL_MOUSEMOTION:
		return eventType::MouseMotion;
	case SDL_MOUSEBUTTONDOWN:
		return eventType::MouseButtonDown;
	case SDL_MOUSEBUTTONUP:
		return eventType::MouseButtonUp;
	case SDL_QUIT:
		return eventType::Quit;
	default:
		return eventType::Unused;
	}
}

std::string toString(eventType value) {
	switch (value) {
	case eventType::KeyDown:
		return "KeyDown";
	case eventType::KeyUp:
		return "KeyUp";
	case eventType::MouseMotion:
		return "MouseMotion";
	case eventType::MouseButtonDown:
		return "MouseButtonDown";
	case eventType::MouseButtonUp:
		return "MouseButtonUp";
	case eventType::Quit:
		return "QuitEvent";
	default:
		return "Unused";
	}
}
