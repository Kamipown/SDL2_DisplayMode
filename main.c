#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

void	print_mode_info(SDL_DisplayMode *mode)
{
	Uint32 f;

	f = mode->format;
	printf("Bpp %i\t", SDL_BITSPERPIXEL(f)); // Bit Per Pixel
	printf("%s\t", SDL_GetPixelFormatName(f)); // Pixel Format
	printf("%i x %i\t", mode->w, mode->h); // Dimensions
	printf("Refresh Rate %i\n", mode->refresh_rate); // Refresh Rate
}

void	print_display_info(int displayNumber)
{
	int i;
	int display_mode_count;
	SDL_DisplayMode mode;
	Uint32 f;

	// SDL_GetNumDisplayModes returns the number of available modes for a specific screen.
	display_mode_count = SDL_GetNumDisplayModes(displayNumber);
	if (display_mode_count < 1)
	{
		// If SDL does not detect modes for a screen (display_mode_count < 1)
		// We put an error and the function is stopped.
		printf("SDL_GetNumDisplayModes failed for the display %i: %s\n", displayNumber, SDL_GetError());
		return ;
	}

	// We print the number of available modes for the current screen.
	printf("-----------------------------------------------------------------------\n");
	printf("Informations for the display number %i:\n", displayNumber);
	printf("%i Display Mode(s) available.\n", display_mode_count);

	// We print informations of each mode.
	i = 0;
	while (i < display_mode_count)
	{
		if (SDL_GetDisplayMode(displayNumber, i, &mode) != 0)
		{
			// If SDL_GetDisplayMode return an error (!= 0)
			// We put an error and the funciton is stopped.
			printf("SDL_GetDisplayMode failed: %s\n", SDL_GetError());
			return ;
		}

		printf("Mode %i\t", i);
		print_mode_info(&mode);
		++i;
	}

	if (SDL_GetDesktopDisplayMode(displayNumber, &mode) != 0)
	{
		// If SDL_GetDesktopDisplayMode returns an error (!= 0)
		// We put an error and the function is stopped.
		printf("SDL_GetDisplayMode failed: %s\n", SDL_GetError());
		return ;
	}
	printf("\nDesktop Display Mode:\n");
	print_mode_info(&mode);

	if (SDL_GetCurrentDisplayMode(displayNumber, &mode) != 0)
	{
		// If SDL_GetCurrentDisplayMode returns an error (!= 0)
		// We put an error and the function is stopped.
		printf("SDL_GetCurrentDisplayMode failed: %s\n", SDL_GetError());
		return ;
	}
	printf("\nCurrent Display Mode:\n");
	print_mode_info(&mode);

	/*
		NOTE :
		You can set the window display mode with :
		int SDL_SetWindowDisplayMode(SDL_Window *window, const SDL_DisplayMode* mode)
		This will only affects the display mode used when the window is fullscreen.

		If your window is not fullscreen, you can use :
		void SDL_SetWindowSize(SDL_Window *window, int w, int h);

		To set a window fullscreen, you can use :
		int SDL_SetWindowFullscreen(SDL_Window *window, Uint32 flags)
	*/
}

int		main(int argc, char *argv[])
{
	int numVideoDisplays;
	int i;

	SDL_SetMainReady();

	// SDL_GetNumVideoDisplays will return 0 if the VIDEO module is not initialized.
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("SDL_Init failed: %s\n", SDL_GetError());
		return (1);
	}

	// SDL_GetNumVideoDisplays returns the number of screens detected by SDL.
	if ((numVideoDisplays = SDL_GetNumVideoDisplays()) < 1)
	{
		// If SDL does not detect screens (numVideoDisplays < 1)
		// We put an error and the program is stopped.
		printf("SDL_GetNumVideoDisplays failed: %s\n", SDL_GetError());
		return (1);
	}

	// We print the number of detected screens.
	printf("You have %i display(s).\n\n", numVideoDisplays);

	// Then we print informations of each screen.
	i = 0;
	while (i < numVideoDisplays)
		print_display_info(i++);

	SDL_Quit();
	return (0);
}
