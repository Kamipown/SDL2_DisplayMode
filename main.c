#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

// You have to init SDL_VIDEO to use these functions.

void	print_displays_number()
{
	printf("Number of Display: %d\n", SDL_GetNumVideoDisplays());
}

int		main(int argc, char *argv[])
{
	SDL_DisplayMode	*mode;

	SDL_SetMainReady();
	SDL_Init(SDL_INIT_VIDEO);

	print_displays_number();

	SDL_GetDisplayMode(0, 0, mode);
	printf("Screen width : %d\n", mode->w);
	printf("Screen height : %d\n", mode->h);
 	printf("Hertz : %d\n", mode->refresh_rate);

	SDL_Quit();
	return (0);
}
