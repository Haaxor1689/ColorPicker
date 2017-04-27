#include "Engine.hpp"

#include "Enums.hpp"
#include "Random.hpp"

Engine::Engine() {
	// Font loading
	renderer.addFont("14Regular", "resources/segoeui.ttf", 14);
	renderer.addFont("24Bold", "resources/segoeuib.ttf", 24);

	// Color setup
	lCol = randomColor();
	rCol = randomColor();

	// Buttons set up
	buttons.emplace("+r", SDL_Rect{ 570, 100 , 30, 30 }, [this]() {if (rCol.r != 255) rCol = { colorModel::RGB, ++rCol.r, rCol.g, rCol.b }; });
	buttons.emplace("-r", SDL_Rect{ 360, 100 , 30, 30 }, [this]() {if (rCol.r != 0) rCol = { colorModel::RGB, --rCol.r, rCol.g, rCol.b }; });
	buttons.emplace("+g", SDL_Rect{ 570, 150 , 30, 30 }, [this]() {if (rCol.g != 255) rCol = { colorModel::RGB, rCol.r, ++rCol.g, rCol.b }; });
	buttons.emplace("-g", SDL_Rect{ 360, 150 , 30, 30 }, [this]() {if (rCol.g != 0) rCol = { colorModel::RGB, rCol.r, --rCol.g, rCol.b }; });
	buttons.emplace("+b", SDL_Rect{ 570, 200 , 30, 30 }, [this]() {if (rCol.b != 255) rCol = { colorModel::RGB, rCol.r, rCol.g, ++rCol.b }; });
	buttons.emplace("-b", SDL_Rect{ 360, 200 , 30, 30 }, [this]() {if (rCol.b != 0) rCol = { colorModel::RGB, rCol.r, rCol.g, --rCol.b }; });

	buttons.emplace("+h", SDL_Rect{ 870, 100 , 30, 30 }, [this]() {if (rCol.h != 360) rCol = { colorModel::HSV, ++rCol.h, rCol.s, rCol.v }; });
	buttons.emplace("-h", SDL_Rect{ 660, 100 , 30, 30 }, [this]() {if (rCol.h != 0) rCol = { colorModel::HSV, --rCol.h, rCol.s, rCol.v }; });
	buttons.emplace("+s", SDL_Rect{ 870, 150 , 30, 30 }, [this]() {if (rCol.s != 100) rCol = { colorModel::HSV, rCol.h, ++rCol.s, rCol.v }; });
	buttons.emplace("-s", SDL_Rect{ 660, 150 , 30, 30 }, [this]() {if (rCol.s != 0) rCol = { colorModel::HSV, rCol.h, --rCol.s, rCol.v }; });
	buttons.emplace("+v", SDL_Rect{ 870, 200 , 30, 30 }, [this]() {if (rCol.v != 100) rCol = { colorModel::HSV, rCol.h, rCol.s, ++rCol.v }; });
	buttons.emplace("-v", SDL_Rect{ 660, 200 , 30, 30 }, [this]() {if (rCol.v != 0) rCol = { colorModel::HSV, rCol.h, rCol.s, --rCol.v }; });

	buttons["+r"].text("+");
	buttons["-r"].text("-");
	buttons["+g"].text("+");
	buttons["-g"].text("-");
	buttons["+b"].text("+");
	buttons["-b"].text("-");

	buttons["+h"].text("+");
	buttons["-h"].text("-");
	buttons["+s"].text("+");
	buttons["-s"].text("-");
	buttons["+v"].text("+");
	buttons["-v"].text("-");

	buttons.emplace("restart", SDL_Rect{ 40, 100, 240, 30 }, [this]() { lCol = randomColor(); result = false; });
	buttons["restart"].text("Restart");
	buttons.emplace("result", SDL_Rect{ 40, 150, 240, 30 }, [this]() { result = true; });
	buttons["result"].text("Show result");
	buttons.emplace("quit", SDL_Rect{ 40, 200, 240, 30 }, [this]() { running = false; });
	buttons["quit"].text("Quit");
	
	for (auto& i : buttons) {
		i.font("24Bold");
		i.fill({ colorModel::RGB, 51, 51, 51 });
		i.border(1);
		i.borderColor({ colorModel::HSV, 0, 0, 0 });
	}

	buttons["restart"].font("14Regular");
	buttons["result"].font("14Regular");
	buttons["quit"].font("14Regular");

	// Sliders
	sliders8.emplace("R", SDL_Rect{ 390, 100, 180, 30 }, rCol.r, static_cast<Uint8>(0), static_cast<Uint8>(255));
	sliders8.emplace("G", SDL_Rect{ 390, 150, 180, 30 }, rCol.g, static_cast<Uint8>(0), static_cast<Uint8>(255));
	sliders8.emplace("B", SDL_Rect{ 390, 200, 180, 30 }, rCol.b, static_cast<Uint8>(0), static_cast<Uint8>(255));

	sliders16.emplace("H", SDL_Rect{ 690, 100, 180, 30 }, rCol.h, static_cast<Uint16>(0), static_cast<Uint16>(360));
	sliders8.emplace("S", SDL_Rect{ 690, 150, 180, 30 }, rCol.s, static_cast<Uint8>(0), static_cast<Uint8>(100));
	sliders8.emplace("V", SDL_Rect{ 690, 200, 180, 30 }, rCol.v, static_cast<Uint8>(0), static_cast<Uint8>(100));

	sliders8["R"].onMove([this]() { rCol = { colorModel::RGB, rCol.r, rCol.g, rCol.b }; });
	sliders8["G"].onMove([this]() { rCol = { colorModel::RGB, rCol.r, rCol.g, rCol.b }; });
	sliders8["B"].onMove([this]() { rCol = { colorModel::RGB, rCol.r, rCol.g, rCol.b }; });

	sliders16["H"].onMove([this]() { rCol = { colorModel::HSV, rCol.h, rCol.s, rCol.v }; });
	sliders8["S"].onMove([this]() { rCol = { colorModel::HSV, rCol.h, rCol.s, rCol.v }; });
	sliders8["V"].onMove([this]() { rCol = { colorModel::HSV, rCol.h, rCol.s, rCol.v }; });

	for (auto& i : sliders8) {
		i.fill({ colorModel::RGB, 0, 0, 0 });
		i.handlerBorder(1);
		i.handlerBorderColor({ colorModel::HSV, 0, 0, 0 });
	}
		

	for (auto& i : sliders16) {
		i.fill({ colorModel::RGB, 0, 0, 0 });
		i.handlerBorder(1);
		i.handlerBorderColor({ colorModel::HSV, 0, 0, 0 });
	}
		
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

	if (result) {
		buttons["restart"].input(event);
		buttons["quit"].input(event);
	} else {
		for (auto& i : buttons)
			i.input(event);

		for (auto& i : sliders8)
			i.input(event);

		for (auto& i : sliders16)
			i.input(event);
	}
}

void Engine::step() {
	if (!result) {
		for (auto& i : sliders8)
			i.step();

		for (auto& i : sliders16)
			i.step();
	}
}

void Engine::draw() {
	SDL_RenderClear(renderer.getRenderer());
	SDL_SetRenderDrawColor(renderer.getRenderer(), 255, 0, 0, 255);

	renderer.drawText("Color Picker", "24Bold", { 480, 24 });
	renderer.drawText("Try to match the color of square on right with the color of square on left by adjusting sliders below.",
		"14Regular", { 480, 60 });

	if (result) {
		buttons["restart"].draw(renderer);
		buttons["result"].draw(renderer);
		buttons["quit"].draw(renderer);

		renderer.drawRectangle({ colorModel::RGB, 51, 51, 51 }, { 330, 100, 180, 130 }, { colorModel::HSV, 0, 0, 0 }, 2);
		renderer.drawText("Left Color:", "14Regular", { 340, 110 }, horizontalAlign::Left);
		renderer.drawText("R:", "14Regular", { 340, 140 }, horizontalAlign::Left);
		renderer.drawText("G:", "14Regular", { 340, 170 }, horizontalAlign::Left);
		renderer.drawText("B:", "14Regular", { 340, 200 }, horizontalAlign::Left);
		renderer.drawText(std::to_string(lCol.r), "14Regular", { 365, 140 }, horizontalAlign::Left);
		renderer.drawText(std::to_string(lCol.g), "14Regular", { 365, 170 }, horizontalAlign::Left);
		renderer.drawText(std::to_string(lCol.b), "14Regular", { 365, 200 }, horizontalAlign::Left);

		renderer.drawText("H:", "14Regular", { 420, 140 }, horizontalAlign::Left);
		renderer.drawText("S:", "14Regular", { 420, 170 }, horizontalAlign::Left);
		renderer.drawText("V:", "14Regular", { 420, 200 }, horizontalAlign::Left);
		renderer.drawText(std::to_string(lCol.h), "14Regular", { 445, 140 }, horizontalAlign::Left);
		renderer.drawText(std::to_string(lCol.s), "14Regular", { 445, 170 }, horizontalAlign::Left);
		renderer.drawText(std::to_string(lCol.v), "14Regular", { 445, 200 }, horizontalAlign::Left);

		renderer.drawRectangle({ colorModel::RGB, 51, 51, 51 }, { 530, 100, 180, 130 }, { colorModel::HSV, 0, 0, 0 }, 2);
		renderer.drawText("Your Error:", "14Regular", { 540, 110 }, horizontalAlign::Left);
		renderer.drawText("R:", "14Regular", { 540, 140 }, horizontalAlign::Left);
		renderer.drawText("G:", "14Regular", { 540, 170 }, horizontalAlign::Left);
		renderer.drawText("B:", "14Regular", { 540, 200 }, horizontalAlign::Left);
		renderer.drawText(std::to_string(static_cast<int>(lCol.r) - rCol.r), "14Regular", { 565, 140 }, horizontalAlign::Left);
		renderer.drawText(std::to_string(static_cast<int>(lCol.g) - rCol.g), "14Regular", { 565, 170 }, horizontalAlign::Left);
		renderer.drawText(std::to_string(static_cast<int>(lCol.b) - rCol.b), "14Regular", { 565, 200 }, horizontalAlign::Left);

		renderer.drawText("H:", "14Regular", { 620, 140 }, horizontalAlign::Left);
		renderer.drawText("S:", "14Regular", { 620, 170 }, horizontalAlign::Left);
		renderer.drawText("V:", "14Regular", { 620, 200 }, horizontalAlign::Left);
		renderer.drawText(std::to_string(static_cast<int>(lCol.h) - rCol.h), "14Regular", { 645, 140 }, horizontalAlign::Left);
		renderer.drawText(std::to_string(static_cast<int>(lCol.s) - rCol.s), "14Regular", { 645, 170 }, horizontalAlign::Left);
		renderer.drawText(std::to_string(static_cast<int>(lCol.v) - rCol.v), "14Regular", { 645, 200 }, horizontalAlign::Left);

		renderer.drawRectangle({ colorModel::RGB, 51, 51, 51 }, { 730, 100, 180, 130 }, { colorModel::HSV, 0, 0, 0 }, 2);
		renderer.drawText("Right Color:", "14Regular", { 740, 110 }, horizontalAlign::Left);
		renderer.drawText("R:", "14Regular", { 740, 140 }, horizontalAlign::Left);
		renderer.drawText("G:", "14Regular", { 740, 170 }, horizontalAlign::Left);
		renderer.drawText("B:", "14Regular", { 740, 200 }, horizontalAlign::Left);
		renderer.drawText(std::to_string(rCol.r), "14Regular", { 765, 140 }, horizontalAlign::Left);
		renderer.drawText(std::to_string(rCol.g), "14Regular", { 765, 170 }, horizontalAlign::Left);
		renderer.drawText(std::to_string(rCol.b), "14Regular", { 765, 200 }, horizontalAlign::Left);

		renderer.drawText("H:", "14Regular", { 820, 140 }, horizontalAlign::Left);
		renderer.drawText("S:", "14Regular", { 820, 170 }, horizontalAlign::Left);
		renderer.drawText("V:", "14Regular", { 820, 200 }, horizontalAlign::Left);
		renderer.drawText(std::to_string(rCol.h), "14Regular", { 845, 140 }, horizontalAlign::Left);
		renderer.drawText(std::to_string(rCol.s), "14Regular", { 845, 170 }, horizontalAlign::Left);
		renderer.drawText(std::to_string(rCol.v), "14Regular", { 845, 200 }, horizontalAlign::Left);
		
	} else {
		for (auto& i : sliders8)
			i.draw(renderer);

		for (auto& i : sliders16)
			i.draw(renderer);

		for (auto& i : buttons)
			i.draw(renderer);

		renderer.drawText("R:", "14Regular", { 340, 115 }, verticalAlign::Top, horizontalAlign::Left);
		renderer.drawText("G:", "14Regular", { 340, 165 }, verticalAlign::Top, horizontalAlign::Left);
		renderer.drawText("B:", "14Regular", { 340, 215 }, verticalAlign::Top, horizontalAlign::Left);

		renderer.drawText(std::to_string(rCol.r), "14Regular", { 480, 115 }, verticalAlign::Top);
		renderer.drawText(std::to_string(rCol.g), "14Regular", { 480, 165 }, verticalAlign::Top);
		renderer.drawText(std::to_string(rCol.b), "14Regular", { 480, 215 }, verticalAlign::Top);

		renderer.drawText("H:", "14Regular", { 640, 115 }, verticalAlign::Top, horizontalAlign::Left);
		renderer.drawText("S:", "14Regular", { 640, 165 }, verticalAlign::Top, horizontalAlign::Left);
		renderer.drawText("V:", "14Regular", { 640, 215 }, verticalAlign::Top, horizontalAlign::Left);

		renderer.drawText(std::to_string(rCol.h), "14Regular", { 780, 115 }, verticalAlign::Top);
		renderer.drawText(std::to_string(rCol.s), "14Regular", { 780, 165 }, verticalAlign::Top);
		renderer.drawText(std::to_string(rCol.v), "14Regular", { 780, 215 }, verticalAlign::Top);
	}

	renderer.drawRectangle(lCol, { 40, 250, 240, 250 }, { colorModel::HSV, 0, 0, 10 }, 2);
	renderer.drawRectangle(rCol, { 320, 250, 600, 250 }, { colorModel::HSV, 0, 0, 10 }, 2);
	SDL_RenderPresent(renderer.getRenderer());
}

Color Engine::randomColor() {
	return { colorModel::RGB, Random::get<Uint8>(0, 255), Random::get<Uint8>(0, 255), Random::get<Uint8>(0, 255) };
}
