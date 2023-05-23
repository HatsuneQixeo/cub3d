#include "libft.h"
#include <stdio.h>

#if BYTE_ORDER == LITTLE_ENDIAN
/*
	One mistake that went overlooked and not result in any error during testing,
	is that the order of r,g,b byte seems to not matter no matter how I shuffle it.
	a byte is the exception tho.

	No, I do not know why.
*/
typedef union u_colour
{
	uint32_t	hexa;
	struct
	{
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
		uint8_t	a;
	}	comp;
}			t_colour;
#else
typedef union u_colour
{
	uint32_t	hexa;
	struct
	{
		uint8_t	a;
		uint8_t	r;
		uint8_t	g;
		uint8_t	b;
	}	comp;
}			t_colour;
#endif

t_colour	colour_from_uint(const uint32_t hexa)
{
	return ((t_colour)hexa);
}

t_colour	colour_from_rgba(const uint8_t r, const uint8_t g, const uint8_t b,
			const uint8_t a)
{
	const t_colour	colour = {
		.comp = {
			.r = r,
			.g = g,
			.b = b,
			.a = a,
		}
	};

	return (colour);
}

t_colour	colour_add1(const t_colour a, const t_colour b)
{
	const double	a_opacity = 1 - (a.comp.a / 255.0);
	const double	b_opacity = 1 - (b.comp.a / 255.0);
	const double	sum_opacity = a_opacity + b_opacity;
	const t_colour	result = {
		.comp = {
			.r = ((a.comp.r * a_opacity) + (b.comp.r * b_opacity)) / sum_opacity,
			.g = ((a.comp.g * a_opacity) + (b.comp.g * b_opacity)) / sum_opacity,
			.b = ((a.comp.b * a_opacity) + (b.comp.b * b_opacity)) / sum_opacity,
			.a = (a.comp.a * b.comp.a) / 255
		}
	};

	return (result);
}

t_colour	colour_add2(const t_colour a, const t_colour b)
{
	const double	a_opacity = 1 - (a.comp.a / 255.0);
	const double	b_opacity = 1 - (b.comp.a / 255.0);
	const t_colour	result = {
		.comp = {
			.r = (a.comp.r * b_opacity) + (b.comp.r * b_opacity),
			.g = (a.comp.g * b_opacity) + (b.comp.g * b_opacity),
			.b = (a.comp.b * b_opacity) + (b.comp.b * b_opacity),
			.a = (((1 - a_opacity) * b_opacity) + (1 - b_opacity)) * 255,
		}
	};

	return (result);
}

t_colour	colour_add4(const t_colour bottom, const t_colour top)
{
	const double	bottom_opacity = 1 - (bottom.comp.a / 255.0);
	const double	top_opacity = 1 - (top.comp.a / 255.0);
	const t_colour	result = {
		.comp = {
			.r = (top.comp.r * top_opacity) + (bottom.comp.r * (1 - top_opacity)),
			.g = (top.comp.g * top_opacity) + (bottom.comp.g * (1 - top_opacity)),
			.b = (top.comp.b * top_opacity) + (bottom.comp.b * (1 - top_opacity)),
			.a = (top_opacity + (bottom_opacity * (1 - top_opacity))) * 255,
		}
	};

	return (result);
}

t_colour	colour_add3(const t_colour a, const t_colour b)
{
	const t_colour	result = {
		.comp = {
			.r = a.comp.r + b.comp.r,
			.g = a.comp.g + b.comp.g,
			.b = a.comp.b + b.comp.b,
			.a = a.comp.a + (255 - a.comp.a) * b.comp.a,
		}
	};

	return (result);
}

/*
	(1 - transparency) is inverting the percentage into opacity,
	which the is how the formula calculates.

	Vise versa, (1 - opacity) is inverting it back to transparency.


	Pretty much an abandoned idea due to being resource heavy,
	probably because of those getmask overheads.

	Function like this really shows the flaw of doing integer manipulation,
	so inconvenient to access each component.

	Also met some unexpected bug by replacing setpixel with this.

	The a mask also needs to be discarded
	to fit the colour finalized on the screen.
	Although it's not impossible that the formula is calculated in other way,
	and then finalized before putting it on screen,
	not something I could deduct for sure.
*/
/*
	Ran some basic test, pretty much the same,
	other than certain colour looks less vibrant.

	Don't think it work's practically for whatever reason I'm not going to debug
*/
/* Closest, but not pinpoint accurate. */
t_colour	my_add(const t_colour bottom, const t_colour top)
{
	const double	bottom_opacity_ratio = 1 - (bottom.comp.a / 255.0);
	const double	top_transparency_ratio = top.comp.a / 255.0;
	const double	top_opacity_ratio = 1 - top_transparency_ratio;

	const t_colour	result = {
		.comp = {
			.r = ((bottom.comp.r * bottom_opacity_ratio * top_transparency_ratio) + (top.comp.r * top_opacity_ratio)),
			.g = ((bottom.comp.g * bottom_opacity_ratio * top_transparency_ratio) + (top.comp.g * top_opacity_ratio)),
			.b = ((bottom.comp.b * bottom_opacity_ratio * top_transparency_ratio) + (top.comp.b * top_opacity_ratio)),
			// .r = ((bottom.comp.r * bottom_opacity * top.comp.a) / 255 + (top.comp.r * top.comp.a)) / 255,
			// .g = ((bottom.comp.g * bottom_opacity * top.comp.a) / 255 + (top.comp.g * top.comp.a)) / 255,
			// .b = ((bottom.comp.b * bottom_opacity * top.comp.a) / 255 + (top.comp.b * top.comp.a)) / 255,
			// .a = ((bottom.comp.a * top_transparency_ratio) + (top.comp.a * top_opacity_ratio)),
			// .a = (bottom.comp.a * top.comp.a) / 255,
			.a = 0,
		}
	};

	return (result);
}

t_colour	my_add2(const t_colour bottom, const t_colour top)
{
	const double	bottom_transparency_ratio = bottom.comp.a / 255.0;
	const double	bottom_opacity_ratio = 1 - bottom_transparency_ratio;
	const double	top_transparency_ratio = top.comp.a / 255.0;
	const double	top_opacity_ratio = 1 - top_transparency_ratio;

	const t_colour	result = {
		.comp = {
			.r = ((bottom.comp.r * top_transparency_ratio) + (top.comp.r * top_opacity_ratio)),
			.g = ((bottom.comp.g * top_transparency_ratio) + (top.comp.g * top_opacity_ratio)),
			.b = ((bottom.comp.b * top_transparency_ratio) + (top.comp.b * top_opacity_ratio)),
			// .r = ((bottom.comp.r * bottom_opacity * top.comp.a) / 255 + (top.comp.r * top.comp.a)) / 255,
			// .g = ((bottom.comp.g * bottom_opacity * top.comp.a) / 255 + (top.comp.g * top.comp.a)) / 255,
			// .b = ((bottom.comp.b * bottom_opacity * top.comp.a) / 255 + (top.comp.b * top.comp.a)) / 255,
			// .a = ((bottom.comp.a * top_transparency_ratio) + (top.comp.a * top_opacity_ratio)),
			// .a = (bottom.comp.a * top.comp.a) / 255,
			.a = 255 - ((bottom_opacity_ratio + (bottom_transparency_ratio * top_opacity_ratio)) * 255)
			// .a = 0,
		}
	};

	return (result);
}

void	colour_idk(t_colour colour)
{
	const double	colour_opacity = 1 - (colour.comp.a / 255.0);

	colour.comp.r *= colour_opacity;
	colour.comp.g *= colour_opacity;
	colour.comp.b *= colour_opacity;
	colour.comp.a = 0;
	printf("don't think this is how it works: %8x\n", colour.hexa);
}

t_colour	test(const char *type, const t_colour a, const t_colour b)
{
	if (type != NULL)
		printf("test %s\n", type);
	printf("adding a(%8x) and b(%8x)\n", a.hexa, b.hexa);
	printf("1: %8x\n", colour_add1(a, b).hexa);
	printf("2: %8x\n", colour_add2(a, b).hexa);
	printf("3: %8x\n", colour_add3(a, b).hexa);
	printf("4: %8x\n", colour_add4(a, b).hexa);
	printf("m: %8x\n", my_add(a, b).hexa);
	printf("M: %8x\n", my_add2(a, b).hexa);
	printf("\n");
	return (my_add(a, b));
}

#define BLUE				0x000000ff
#define RED					0x00ff0000
#define GREEN				0x0000ff00
#define ALPHA				0xff000000
#define HALF				0x7f000000
/* Quarter amount of transparency */
#define QUARTER				0x3f000000
#define THREE_QUARTERS		0xbf000000

void	test_combine(const unsigned int amount, ...)
{
	va_list			args;
	t_colour		result;
	unsigned int	i;

	if (amount == 0)
		return ;
	va_start(args, amount);
	result = va_arg(args, t_colour);
	i = 0;
	while (++i < amount)
		result = test(NULL, result, va_arg(args, t_colour));
	va_end(args);
	printf("combine %u colours\n", amount);
	printf("result: %8x\n", result.hexa);
	printf("\n");
}

int	main(void)
{
	// test("overwrite", colour_from_uint(BLUE), colour_from_uint(GREEN));
	// test("fully transparent", colour_from_uint(ALPHA + BLUE), colour_from_uint(ALPHA + GREEN));
	// test("retain", colour_from_uint(BLUE), colour_from_uint(ALPHA + GREEN));
	// test("overwrite", colour_from_uint(ALPHA + BLUE), colour_from_uint(GREEN));
	// test("overwrite", colour_from_uint(HALF + BLUE), colour_from_uint(GREEN));
	/* Combination */
	{
		/* blue, half green, half red */
		// test_combine(3, colour_from_uint(BLUE), colour_from_uint(HALF + GREEN), colour_from_uint(HALF + RED));
		/* blue, quarter green, quarter red */
		// test_combine(3, colour_from_uint(BLUE), colour_from_uint(QUARTER + GREEN), colour_from_uint(QUARTER + RED));
		/* blue, quarter green, half red */
		// test_combine(3, colour_from_uint(BLUE), colour_from_uint(QUARTER + GREEN), colour_from_uint(HALF + RED));
		/* blue, quarter green, three quarter red */
		// test_combine(3, colour_from_uint(BLUE), colour_from_uint(QUARTER + GREEN), colour_from_uint(THREE_QUARTERS + RED));
		/* blue, half green, three quarter red */
		// test_combine(3, colour_from_uint(BLUE), colour_from_uint(HALF + GREEN), colour_from_uint(THREE_QUARTERS + RED));
		/* Half blue, half green, half red */
		test_combine(3, colour_from_uint(HALF + BLUE), colour_from_uint(HALF + GREEN), colour_from_uint(HALF + RED));
	}
}
