#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <signal.h>
#include <sys/stat.h>


// struct termios {
// 	tcflag_t        c_iflag;        /* input flags */
// 	tcflag_t        c_oflag;        /* output flags */
// 	tcflag_t        c_cflag;        /* control flags */
// 	tcflag_t        c_lflag;        /* local flags */
// 	cc_t            c_cc[NCCS];     /* control chars */
// 	speed_t         c_ispeed;       /* input speed */
// 	speed_t         c_ospeed;       /* output speed */
// };

/**
 * isatty
 * ttyname
 * ttyslot
 * ioctl
 * tcsetattr
 * tcgetattr
 * tgetent
 * tgetflag
 * tgetnum
 * tgetstr
 * tgoto
 * tputs
 * 
 */

// void	statft(void)
// {
// 	struct stat	stt;

// 	stt.
// }

void	showattr(void *content)
{
	struct termios	*term = content;

	// for (int i = 0; i < NCCS; i++)
	// 	printf("[%d]", term->c_cc[i]);
	// printf("\n");
	printf("lflags: %lx\n", term->c_lflag);
	term->c_lflag &= ~ECHOCTL;
	// printf("ispeed: %lu\n", term->c_ispeed);
	// printf("ospeed: %lu\n", term->c_ospeed);
	printf("\n");
}

int	main(void)
{
	struct termios	term;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	for (int fd = 0, is = isatty(fd); 1 ; is = isatty(++fd))
	{
		printf("fd: {%d} is: %d\n", fd, is);
		printf("fd: {%d} name: %s\n", fd, ttyname(fd));
		printf("get: %d\n", tcgetattr(fd, &term));
		showattr(&term);
		printf("set: %d\n", tcsetattr(fd, TCSANOW, &term));
		sleep(2);
		if (!is)
			break ;
	}
	printf("slot: %d\n", ttyslot());
}
