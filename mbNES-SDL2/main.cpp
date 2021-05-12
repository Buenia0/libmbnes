#include <iostream>
#include <fstream>
#include <libmbNES/libmbnes.h>
#include <SDL2/SDL.h>
using namespace nes;
using namespace std;

class SDL2Frontend : public mbNESFrontend
{
    public:
	SDL2Frontend(NESCore *cb) : core(cb)
	{

	}

	~SDL2Frontend()
	{

	}

	bool init()
	{
	    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	    {
		return sdlerror("SDL2 could not be initialized!");
	    }

	    window = SDL_CreateWindow("mbNES-SDL2", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);

	    if (window == NULL)
	    {
		return sdlerror("Window could not be created!");
	    }

	    render = SDL_CreateRenderer(window, -1, 0);

	    if (render == NULL)
	    {
		return sdlerror("Renderer could not be created!");
	    }

	    return true;
	}

	void shutdown()
	{
	    if (render != NULL)
	    {
		SDL_DestroyRenderer(render);
		render = NULL;
	    }

	    if (window != NULL)
	    {
		SDL_DestroyWindow(window);
		window = NULL;
	    }

	    SDL_Quit();
	}

	void runapp()
	{
	    while (!quit)
	    {
		pollevents(quit);
		runmachine();
	    }
	}

	vector<uint8_t> loadfile(string filename)
	{
	    vector<uint8_t> result;

	    fstream file(filename.c_str(), ios::in | ios::binary | ios::ate);

	    if (file.is_open())
	    {
		streampos size = file.tellg();
		result.resize(size, 0);
		file.seekg(0, ios::beg);
		file.read((char*)result.data(), size);
		file.close();
	    }

	    return result;
	}

	void runmachine()
	{
	    // TODO: Output graphics from NES
	    SDL_SetRenderDrawColor(render, 255, 0, 0, 255);
	    SDL_RenderClear(render);
	    SDL_RenderPresent(render);
	}

	void pollevents(bool &quit)
	{
	    while (SDL_PollEvent(&event))
	    {
		if (event.type == SDL_QUIT)
		{
		    quit = true;
		}
	    }
	}

	bool sdlerror(string message)
	{
	    cout << message << " SDL_Error: " << SDL_GetError() << endl;
	    return false;
	}

	SDL_Window *window = NULL;
	SDL_Renderer *render = NULL;

	bool quit = false;
	SDL_Event event;

	NESCore *core = NULL;
};

int main(int argc, char* argv[])
{
    NESCore core;
    SDL2Frontend *front = new SDL2Frontend(&core);
    core.setfrontend(front);

    if (!core.loadROM("nestest.nes"))
    {
	return 1;
    }

    if (!core.initcore())
    {
	return 1;
    }

    core.runapp();
    core.shutdown();
    return 0;
}