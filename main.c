#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

void	get_display_info(int displayNumber)
{
	int i;
	int display_mode_count;
	SDL_DisplayMode mode;
	Uint32 f;

	display_mode_count = SDL_GetNumDisplayModes(displayNumber);
	if (display_mode_count < 1)
	{
		printf("SDL_GetNumDisplayModes failed: %s\n", SDL_GetError());
		return ;
	}

	printf("-----------------------------------------------------------------------\n");
	printf("Informations for the display number %i :\n", displayNumber);
	printf("%i Display Modes\n", display_mode_count);

	i = 0;
	while (i < display_mode_count)
	{
		if (SDL_GetDisplayMode(displayNumber, i, &mode) != 0)
		{
			printf("SDL_GetDisplayMode failed: %s\n", SDL_GetError());
			return ;
		}

		f = mode.format;

		printf("Mode %i\t", i);
		printf("Bpp %i\t", SDL_BITSPERPIXEL(f));
		printf("%s\t", SDL_GetPixelFormatName(f));
		printf("%i x %i\t", mode.w, mode.h);
		printf("Refresh Rate %i\n", mode.refresh_rate);
		++i;
	}
}

int		main(int argc, char *argv[])
{
	int numVideoDisplays;
	int i;

	SDL_SetMainReady();

	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("SDL_Init failed: %s\n", SDL_GetError());
		return (1);
	}

	if ((numVideoDisplays = SDL_GetNumVideoDisplays()) < 1)
	{
		printf("SDL_GetNumVideoDisplays failed: %s\n", SDL_GetError());
		return (1);
	}

	printf("%i displays.\n\n", numVideoDisplays);

	i = 0;
	while (i < numVideoDisplays)
		get_display_info(i++);

	SDL_Quit();
	return (0);
}
