#include "libft.h"

void	linebyline(const char *type)
{
	for (u_int8_t code = 0; code < 255; code++)
		printf("\033[%s%dm %3d \n", type, code, code);
	printf("\033[%s255m 255 \n", type);
	printf("\n");
}

void	grid(const char *type)
{
	for (int y = 0; y < 16; y++) {
		for (int x = 0; x < 16; x++) {
			int color_code = y * 16 + x;
			printf("\033[%s%dm %3d ", type, color_code, color_code);
		}
		printf("\033[0m\n");
	}
	printf("\n");
}

int main(void)
{
	const char	*text_colour = "38;5;";
	const char	*background_colour = "48;5;";

	// grid(background_colour);
	// grid(text_colour);
	for (int i = 0; i <= 255; i++)
	{
		char	buffer[1024];

		printf("i: %d\n", i);
		snprintf(buffer, sizeof(buffer), "%d;", i);
		// snprintf(buffer, sizeof(buffer), "%d;5;", i);
		// snprintf(buffer, sizeof(buffer), "%d;", i);
		printf("buffer: %s\n", buffer);
		grid(buffer);
		free(get_next_line(0));
	}
	(void)text_colour;
	(void)background_colour;
}
