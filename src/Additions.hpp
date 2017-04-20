#pragma once

#include "Position.hpp"
#include <SDL.h>

inline SDL_Rect operator+(SDL_Rect lhs, const SDL_Rect& rhs) {
	return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.w + rhs.w, lhs.h + rhs.h };
}

inline SDL_Rect operator-(SDL_Rect lhs, const SDL_Rect& rhs) {
	return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.w - rhs.w, lhs.h - rhs.h };
}

inline Position middle(const SDL_Rect& bBox) {
	return { bBox.x + bBox.w / 2, bBox.y + bBox.h / 2 };
}
