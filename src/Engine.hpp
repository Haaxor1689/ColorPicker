#pragma once

#include "Event.hpp"
#include "RenderController.hpp"
#include "ResourceMap.hpp"

class Engine {
public:
	Engine();

	// Main game loop
	void run();

	// All input handling function
	void input(const Event& event);

	// Logic
	void step();

	// Rendering
	void draw();

private:
	static Color randomColor();

	RenderController renderer;
	ButtonMap buttons;
	SliderMap<Uint8> sliders8;
	SliderMap<Uint16> sliders16;
	bool running;

	Color lCol;
	Color rCol;
	Uint16 h;
	Uint8 s, v;

	bool result = false;
};
