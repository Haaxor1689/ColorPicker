#include "Engine.hpp"

#include "Enums.hpp"
#include "Random.hpp"

Engine::Engine() {
	// Font loading
	renderer.addFont("14Regular", "resources/segoeui.ttf", 14);
	renderer.addFont("24Bold", "resources/segoeuib.ttf", 24);

	// Color setup
	leftColor = { colorModel::RGB, static_cast<Uint8>(Random::get(0, 255)), static_cast<Uint8>(Random::get(0, 255)), static_cast<Uint8>(Random::get(0, 255)) };
	rightColor = { colorModel::RGB, static_cast<Uint8>(Random::get(0, 255)), static_cast<Uint8>(Random::get(0, 255)), static_cast<Uint8>(Random::get(0, 255)) };

	// Buttons set up
	buttons.emplace_back("+", SDL_Rect{ 300, 100 , 30, 30 }, std::bind(&Engine::bIncR, this));
	buttons.emplace_back("-", SDL_Rect{ 100, 100 , 30, 30 }, std::bind(&Engine::bDecR, this));
	buttons.emplace_back("+", SDL_Rect{ 300, 130 , 30, 30 }, std::bind(&Engine::bIncG, this));
	buttons.emplace_back("-", SDL_Rect{ 100, 130 , 30, 30 }, std::bind(&Engine::bDecG, this));
	buttons.emplace_back("+", SDL_Rect{ 300, 160 , 30, 30 }, std::bind(&Engine::bIncB, this));
	buttons.emplace_back("-", SDL_Rect{ 100, 160 , 30, 30 }, std::bind(&Engine::bDecB, this));

	buttons.emplace_back("+", SDL_Rect{ 600, 100 , 30, 30 }, std::bind(&Engine::bIncH, this));
	buttons.emplace_back("-", SDL_Rect{ 400, 100 , 30, 30 }, std::bind(&Engine::bDecH, this));
	buttons.emplace_back("+", SDL_Rect{ 600, 130 , 30, 30 }, std::bind(&Engine::bIncS, this));
	buttons.emplace_back("-", SDL_Rect{ 400, 130 , 30, 30 }, std::bind(&Engine::bDecS, this));
	buttons.emplace_back("+", SDL_Rect{ 600, 160 , 30, 30 }, std::bind(&Engine::bIncV, this));
	buttons.emplace_back("-", SDL_Rect{ 400, 160 , 30, 30 }, std::bind(&Engine::bDecV, this));

	for (auto& i : buttons) {
		i.setFont("24Bold");
		i.setFill({ colorModel::RGB, 51, 51, 51 });
	}

	sliders8.reserve(5);

	// Sliders
	sliders8.emplace_back(SDL_Rect{ 130, 100, 170, 30 }, rightColor.r, static_cast<Uint8>(0), static_cast<Uint8>(255));
	sliders8.emplace_back(SDL_Rect{ 130, 130, 170, 30 }, rightColor.g, static_cast<Uint8>(0), static_cast<Uint8>(255));
	sliders8.emplace_back(SDL_Rect{ 130, 160, 170, 30 }, rightColor.b, static_cast<Uint8>(0), static_cast<Uint8>(255));

	sliders16.emplace_back(SDL_Rect{ 430, 100, 170, 30 }, rightColor.h, static_cast<Uint16>(0), static_cast<Uint16>(360));
	sliders8.emplace_back(SDL_Rect{ 430, 130, 170, 30 }, rightColor.s, static_cast<Uint8>(0), static_cast<Uint8>(100));
	sliders8.emplace_back(SDL_Rect{ 430, 160, 170, 30 }, rightColor.v, static_cast<Uint8>(0), static_cast<Uint8>(100));

	for (auto& i : sliders8)
		i.setFill({ colorModel::RGB, 0, 0, 0 });

	for (auto& i : sliders16)
		i.setFill({ colorModel::RGB, 0, 0, 0 });
}

void Engine::run() {
	while (running) {
		Event event;
		while (event.poll())
			input(event);
		step();
		draw();
	}
}

void Engine::input(const Event& event) {
	if (event.getType() == eventType::Quit)
		running = false;

	for (auto& i : buttons)
		i.input(event);

	for (auto& i : sliders8)
		i.input(event);

	for (auto& i : sliders16)
		i.input(event);
}

void Engine::step() {
	for (auto& i : sliders8)
		i.step();

	for (auto& i : sliders16)
		i.step();
}

void Engine::draw() {
	SDL_RenderClear(renderer.getRenderer());
	SDL_SetRenderDrawColor(renderer.getRenderer(), 255, 0, 0, 255);

	for (auto& i : buttons)
		i.draw(renderer);

	for (auto& i : sliders8)
		i.draw(renderer);

	for (auto& i : sliders16)
		i.draw(renderer);

	renderer.drawText("Color Picker", "24Bold", { 480, 24 });
	renderer.drawText("Try to match the color of square on right with the color of square on left by adjusting sliders on the bottom of the screen.",
	                  "14Regular", { 480, 60 });

	renderer.drawText("R:", "14Regular", { 80, 115 }, verticalAlign::Top);
	renderer.drawText("G:", "14Regular", { 80, 145 }, verticalAlign::Top);
	renderer.drawText("B:", "14Regular", { 80, 175 }, verticalAlign::Top);

	renderer.drawText(std::to_string(rightColor.r), "14Regular", { 215, 115 }, verticalAlign::Top);
	renderer.drawText(std::to_string(rightColor.g), "14Regular", { 215, 145 }, verticalAlign::Top);
	renderer.drawText(std::to_string(rightColor.b), "14Regular", { 215, 175 }, verticalAlign::Top);

	renderer.drawText("H:", "14Regular", { 380, 115 }, verticalAlign::Top);
	renderer.drawText("S:", "14Regular", { 380, 145 }, verticalAlign::Top);
	renderer.drawText("V:", "14Regular", { 380, 175 }, verticalAlign::Top);

	renderer.drawText(std::to_string(rightColor.h), "14Regular", { 515, 115 }, verticalAlign::Top);
	renderer.drawText(std::to_string(rightColor.s), "14Regular", { 515, 145 }, verticalAlign::Top);
	renderer.drawText(std::to_string(rightColor.v), "14Regular", { 515, 175 }, verticalAlign::Top);

	renderer.drawRectangle(leftColor, { 40, 200, 400, 600 });
	renderer.drawRectangle(rightColor, { 520, 200, 400, 600 });
	SDL_RenderPresent(renderer.getRenderer());
}

void Engine::bIncR() {
	if (rightColor.r != 255)
		rightColor = { colorModel::RGB, ++rightColor.r, rightColor.g, rightColor.b };
}

void Engine::bDecR() {
	if (rightColor.r != 0)
		rightColor = { colorModel::RGB, --rightColor.r, rightColor.g, rightColor.b };
}

void Engine::bIncG() {
	if (rightColor.g != 255)
		rightColor = { colorModel::RGB, rightColor.r, ++rightColor.g, rightColor.b };
}

void Engine::bDecG() {
	if (rightColor.g != 0)
		rightColor = { colorModel::RGB, rightColor.r, --rightColor.g, rightColor.b };
}

void Engine::bIncB() {
	if (rightColor.b != 255)
		rightColor = { colorModel::RGB, rightColor.r, rightColor.g, ++rightColor.b };
}

void Engine::bDecB() {
	if (rightColor.b != 0)
		rightColor = { colorModel::RGB, rightColor.r, rightColor.g, --rightColor.b };
}

void Engine::bIncH() {
	if (rightColor.h != 360)
		rightColor = { colorModel::HSV, ++rightColor.h, rightColor.s, rightColor.v };
}

void Engine::bDecH() {
	if (rightColor.h != 0)
		rightColor = { colorModel::HSV, --rightColor.h, rightColor.s, rightColor.v };
}

void Engine::bIncS() {
	if (rightColor.s != 100)
		rightColor = { colorModel::HSV, rightColor.h, ++rightColor.s, rightColor.v };
}

void Engine::bDecS() {
	if (rightColor.s != 0)
		rightColor = { colorModel::HSV, rightColor.h, --rightColor.s, rightColor.v };
}

void Engine::bIncV() {
	if (rightColor.v != 100)
		rightColor = { colorModel::HSV, rightColor.h, rightColor.s, ++rightColor.v };
}

void Engine::bDecV() {
	if (rightColor.v != 0)
		rightColor = { colorModel::HSV, rightColor.h, rightColor.s, --rightColor.v };
}
