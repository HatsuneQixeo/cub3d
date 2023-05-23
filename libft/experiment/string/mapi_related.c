#include "libft.h"

void	ft_mapiproto(char *str)
{
	char	*mapi;

	mapi = ft_strmapi(str, ft_mapi_capitalize);
	ft_putendl_fd(mapi, 1);
	free(mapi);
}

void	tellme_eng(void)
{
	ft_mapiproto("Not to forget the intangible feelings\n\
I deleted the routine layout\n\
Grasp the phrase I happened to be humming\n\
Spread secret words of the heart into the sky\n\
\
I want to tell you\n\
I want to give you\n\
Nodes of feelings form a link\n\
Echoing to the faraway distance\n\
Words I want to tell you\n\
Sounds I want to give you\n\
Links of feelings form a world\n\
Connecting everything Connecting to everywhere\n\
\
The pure white light feels like you\n\
The voice flows through my hand held against the light\n\
On the rhythm my fingertips suddenly make\n\
Spread all words of the heart into the sky\n\
\
I want to tell you\n\
I want to give you\n\
Nodes of feelings form a link\n\
Reaching over the faraway distance\n\
Words I want to tell you\n\
Sounds I want to give you\n\
Links of feelings form a world\n\
Connecting everything Connecting to everywhere\n\
\
I had been playing the tune without a doubt about the rhythm of my days\n\
I had thought the coming of mornings is a given\n\
The sounds I believe in even for a second, shift my sceneries\n\
Tell your world\n\
\
You want to tell\n\
You want to give\n\
Nodes of feelings form a link\n\
Echoing to the faraway distance\n\
Words you want to tell\n\
Sounds you want to give\n\
Links of feelings form a world\n\
Connecting everything Connecting to everywhere\n");
}

void	tellme_romaji(void)
{
	ft_mapiproto("katachi no nai kimochi wasurenai you ni\n\
kimarikitta reiauto o keshita\n\
futo kuchizusanda fureezu o tsukamaete\n\
mune ni himeta kotoba nose sora ni tokihanatsu no\n\
\
kimi ni tsutaetai koto ga\n\
kimi ni todoketai koto ga\n\
takusan no ten wa sen ni natte\n\
tooku kanata e to hibiku\n\
kimi ni tsutaetai kotoba\n\
kimi ni todoketai oto ga\n\
ikutsu mono sen wa en ni natte\n\
subete tsunageteku doko ni datte\n\
\
masshiro ni sunda hikari wa kimi no you\n\
kazashita te no sukima o tsutau koe ga\n\
futo ugoita yubisaki kizamu rizumu ni\n\
arittake no kotoba nose sora ni tokihanatsu no\n\
\
kimi ni tsutaetai koto ga\n\
kimi ni todoketai koto ga\n\
takusan no ten wa sen ni natte\n\
tooku kanata made ugatsu\n\
kimi ni tsutaetai kotoba\n\
kimi ni todoketai oto ga\n\
ikutsu mono sen wa en ni natte\n\
subete tsunageteku doko ni datte\n\
\
kanadete ita kawaranai hibi o utagawazu ni\n\
asa wa dareka ga kureru mono da to omotteta\n\
isshun demo shinjita oto keshiki o yurasu no\n\
oshiete yo kimi dake no sekai\n\
\
kimi ga tsutaetai koto wa\n\
kimi ga todoketai koto wa\n\
takusan no ten wa sen ni natte\n\
tooku kanata e to hibiku\n\
kimi ga tsutaetai kotoba\n\
kimi ga todoketai oto wa\n\
ikutsu mono sen wa en ni natte\n\
subete tsunageteku doko ni datte\n");
}

void	tellme_both(void)
{
	ft_mapiproto("katachi no nai kimochi wasurenai you ni\n\
	Not to forget the intangible feelings\n\
kimarikitta reiauto o keshita\n\
	I deleted the routine layout\n\
futo kuchizusanda fureezu o tsukamaete\n\
	Grasp the phrase I happened to be humming\n\
mune ni himeta kotoba nose sora ni tokihanatsu no\n\
	Spread secret words of the heart into the sky\n\
\
kimi ni tsutaetai koto ga\n\
	I want to tell you\n\
kimi ni todoketai koto ga\n\
	I want to give you\n\
takusan no ten wa sen ni natte\n\
	Nodes of feelings form a link\n\
tooku kanata e to hibiku\n\
	Echoing to the faraway distance\n\
kimi ni tsutaetai kotoba\n\
	Words I want to tell you\n\
kimi ni todoketai oto ga\n\
	Sounds I want to give you\n\
ikutsu mono sen wa en ni natte\n\
	Links of feelings form a world\n\
subete tsunageteku doko ni datte\n\
	Connecting everything Connecting to everywhere\n\
\
masshiro ni sunda hikari wa kimi no you\n\
	The pure white light feels like you\n\
kazashita te no sukima o tsutau koe ga\n\
	The voice flows through my hand held against the light\n\
futo ugoita yubisaki kizamu rizumu ni\n\
	On the rhythm my fingertips suddenly make\n\
arittake no kotoba nose sora ni tokihanatsu no\n\
	Spread all words of the heart into the sky\n\
\
kimi ni tsutaetai koto ga\n\
	I want to tell you\n\
kimi ni todoketai koto ga\n\
	I want to give you\n\
takusan no ten wa sen ni natte\n\
	Nodes of feelings form a link\n\
tooku kanata made ugatsu\n\
	Reaching over the faraway distance\n\
kimi ni tsutaetai kotoba\n\
	Words I want to tell you\n\
kimi ni todoketai oto ga\n\
	Sounds I want to give you\n\
ikutsu mono sen wa en ni natte\n\
	Links of feelings form a world\n\
subete tsunageteku doko ni datte\n\
	Connecting everything Connecting to everywhere\n\
\
kanadete ita kawaranai hibi o utagawazu ni\n\
	I had been playing the tune without a doubt about the rhythm of my days\n\
asa wa dareka ga kureru mono da to omotteta\n\
	I had thought the coming of mornings is a given\n\
isshun demo shinjita oto keshiki o yurasu no\n\
	The sounds I believe in even for a second, shift my sceneries\n\
oshiete yo kimi dake no sekai\n\
	Tell your world\n\
\
kimi ga tsutaetai koto wa\n\
	You want to tell\n\
kimi ga todoketai koto wa\n\
	You want to give\n\
takusan no ten wa sen ni natte\n\
	Nodes of feelings form a link\n\
tooku kanata e to hibiku\n\
	Echoing to the faraway distance\n\
kimi ga tsutaetai kotoba\n\
	Words you want to tell\n\
kimi ga todoketai oto wa\n\
	Sounds you want to give\n\
ikutsu mono sen wa en ni natte\n\
	Links of feelings form a world\n\
subete tsunageteku doko ni datte\n");
}

	// ft_mapiproto("hatsune miku is 8very cuteo very very 31cute ");
	// ft_mapiproto("1miku");
	// ft_mapiproto("hatsune mIKu's BirtHday is 2007AUGUST 31, same as our country's indePENDEnce day.");
