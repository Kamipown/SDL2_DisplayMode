#include <stdio.h>
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>

static void	print_mode_info(SDL_DisplayMode *mode)
{
	Uint32 f;

	f = mode->format;
	printf("Bpp %i\t", SDL_BITSPERPIXEL(f)); // Bit Per Pixel
	printf("%s\t", SDL_GetPixelFormatName(f)); // Pixel Format
	printf("%i x %i\t", mode->w, mode->h); // Dimensions
	printf("Refresh Rate %i\n", mode->refresh_rate); // Refresh Rate
}

static void	display_modes_loop(int display_index, int display_mode_count)
{
	SDL_DisplayMode mode;
	int i;

	i = 0;
	while (i < display_mode_count)
	{
		if (SDL_GetDisplayMode(display_index, i, &mode) != 0)
		{
			printf("SDL_GetDisplayMode failed: %s\n", SDL_GetError());
			return ;
		}
		printf("Mode %i\t", i);
		print_mode_info(&mode);
		++i;
	}
}

static void	print_desktop_display_mode(int display_index)
{
	SDL_DisplayMode mode;

	if (SDL_GetDesktopDisplayMode(display_index, &mode) != 0)
	{
		printf("SDL_GetDisplayMode failed: %s\n", SDL_GetError());
		return ;
	}
	printf("\nDesktop Display Mode:\n");
	print_mode_info(&mode);
}

static void	print_current_display_mode(int display_index)
{
	SDL_DisplayMode mode;

	if (SDL_GetCurrentDisplayMode(display_index, &mode) != 0)
	{
		printf("SDL_GetCurrentDisplayMode failed: %s\n", SDL_GetError());
		return ;
	}
	printf("\nCurrent Display Mode:\n");
	print_mode_info(&mode);
}

static void	displays_loop(int display_index)
{
	int i;
	int display_mode_count;
	SDL_DisplayMode mode;

	display_mode_count = SDL_GetNumDisplayModes(display_index);
	if (display_mode_count < 1)
	{
		printf("SDL_GetNumDisplayModes failed for the display %i: %s\n", display_index, SDL_GetError());
		return ;
	}
	printf("Informations for the display number %i:\n", display_index);
	printf("%i Display Mode(s) available.\n", display_mode_count);
	
	display_modes_loop(display_index, display_mode_count);
	print_desktop_display_mode(display_index);
	print_current_display_mode(display_index);
}

static void	print_displays_info(void)
{
	int video_display_count;
	int i;

	if ((video_display_count = SDL_GetNumVideoDisplays()) < 1)
	{
		printf("SDL_GetNumVideoDisplays failed: %s\n", SDL_GetError());
		return ;
	}
	printf("You have %i display(s).\n\n", video_display_count);
	i = 0;
	while (i < video_display_count)
		displays_loop(i++);
}

int			main(int argc, char *argv[])
{
	SDL_SetMainReady();
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("SDL_Init failed: %s\n", SDL_GetError());
		return (1);
	}
	print_displays_info();
	SDL_Quit();
	return (0);
}

/*
	Functions used :

	int SDL_GetNumVideoDisplays(void)
	int SDL_GetNumDisplayModes(int displayIndex)
	int SDL_GetDisplayMode(int displayIndex, int modeIndex, SDL_DisplayMode *mode)
	int SDL_GetDesktopDisplayMode(int displayIndex, SDL_DisplayMode *mode)
	int SDL_GetCurrentDisplayMode(int displayIndex, SDL_DisplayMode *mode)

	SDL_GetNumVideoDisplays returns the number of screens detected by SDL.
		This function returns 0 if the VIDEO module is not initialized.

	SDL_GetNumDisplayModes returns the number of available display modes for a specific screen.

	SDL_GetDisplayMode get informations of a specific mode in a specific screen and fills an SDL_DisplayMode structure with.

	SDL_GetDesktopDisplayMode get informations of the desktop in a specific screen and fill an SDL_DisplayMode structure with.

	SDL_GetCurrentDisplayMode get informations of the current display mode fill an SDL_DisplayMode structure with.

	Notes :
	- The SDL_DisplayMode structure filled by SDL_GetDesktopDisplayMode and SDL_GetCurrentDisplayMode should be the same until you open a window.
	- You can set the window display mode with :
		int SDL_SetWindowDisplayMode(SDL_Window *window, const SDL_DisplayMode* mode)
			- This will only affects the display mode used when the window is fullscreen.
	- If your window is not fullscreen, you can use :
		void SDL_SetWindowSize(SDL_Window *window, int w, int h);
	- To set a window fullscreen, you can use :
		int SDL_SetWindowFullscreen(SDL_Window *window, Uint32 flags)
*/