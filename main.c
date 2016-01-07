#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

void	get_display_info(int displayNumber)
{
	int i;
	int display_mode_count;
	SDL_DisplayMode mode;
	Uint32 f;

	// SDL_GetNumDisplayModes return the number of modes available for a specific screen.
	display_mode_count = SDL_GetNumDisplayModes(displayNumber);
	if (display_mode_count < 1)
	{
		// If SDL does not detect modes for a screen (display_mode_count < 1)
		// We put an error and the function is stopped.
		printf("SDL_GetNumDisplayModes failed for the display %i : %s\n", displayNumber, SDL_GetError());
		return ;
	}

	// We print the number of modes available for the current screen.
	printf("-----------------------------------------------------------------------\n");
	printf("Informations for the display number %i :\n", displayNumber);
	printf("%i Display Modes\n", display_mode_count);

	// We print informations of each modes.
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
		printf("Bpp %i\t", SDL_BITSPERPIXEL(f)); // Bit Per Pixel
		printf("%s\t", SDL_GetPixelFormatName(f)); // Pixel Format
		printf("%i x %i\t", mode.w, mode.h); // Dimensions
		printf("Refresh Rate %i\n", mode.refresh_rate); // Refresh Rate
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

	// SDL_GetNumVideoDisplays return the number of screens detected by SDL.
	if ((numVideoDisplays = SDL_GetNumVideoDisplays()) < 1)
	{
		// If SDL does not detect screens (numVideoDisplays < 1)
		// We put an error and the program is stopped.
		printf("SDL_GetNumVideoDisplays failed: %s\n", SDL_GetError());
		return (1);
	}

	// We print the number of screens detected.
	printf("%i displays.\n\n", numVideoDisplays);

	// Then we print informations of each screen.
	i = 0;
	while (i < numVideoDisplays)
		get_display_info(i++);

	SDL_Quit();
	return (0);
}
