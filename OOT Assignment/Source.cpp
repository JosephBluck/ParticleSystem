#include <SDL.h>
#include <SDL_ttf.h>
#include <chrono>
#include <iostream>
#include "World.h"
#include "Particle.h"
#include "Partition.h"

#undef main

int main()
{
	srand(time(NULL));

	// Initialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "Failed to initialise SDL: " << SDL_GetError() << "\nPress any key to exit...";
		std::getchar();
		return -1;
	}

	if (TTF_Init() != 0)
	{
		SDL_Quit();
		std::cout << "Failed to initialise SDL TTF: " << TTF_GetError() << "\nPress any key to exit...";
		std::getchar();
		return -2;
	}

	// Initialise window and renderer
	SDL_Window* window = SDL_CreateWindow("Particle Collisions", 30, 30, 1600, 900, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);

	std::shared_ptr<World> world = std::make_shared<World>(renderer);

	SDL_Event e;
	bool exit = false;

	float deltaTime = SDL_GetTicks() / 100.0f;
	float prevTime = SDL_GetTicks() / 100.0f;

	int mouseX, mouseY;

	while (!exit)
	{

		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT) { exit = true; }
		}

		
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 0);

		deltaTime = (SDL_GetTicks() / 100.0f) - prevTime;

		world->Update(deltaTime);
		world->Draw(true);

		if (SDL_GetMouseState(&mouseX, &mouseY) & SDL_BUTTON_LEFT)
		{
			world->GetPartitionInfo(mouseX, mouseY);
		}

		SDL_RenderPresent(renderer);

		// std::cout << "FPS: " << 1.0f / deltaTime << "\n";

		prevTime = SDL_GetTicks() / 100.0f;
	}
	
	world.reset();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit;
	SDL_Quit();

	std::cout << "Press any key to continue...";
	std::getchar();
    return 0;
}

