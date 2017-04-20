#pragma once

#include "Button.hpp"
#include "Event.hpp"
#include "RenderController.hpp"
#include "Slider.hpp"
#include <vector>

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
	// Button functions
	void bIncR();
	void bDecR();
	void bIncG();
	void bDecG();
	void bIncB();
	void bDecB();

	void bIncH();
	void bDecH();
	void bIncS();
	void bDecS();
	void bIncV();
	void bDecV();

	RenderController renderer;
	std::vector<Button> buttons;
	std::vector<Slider<Uint8>> sliders8;
	std::vector<Slider<Uint16>> sliders16;
	bool running;

	Color leftColor;
	Color rightColor;
};
