#include "../../includes/pipex.h"
#include <signal.h>

void	ft_putstr_fd_report(const char *str, int fd)
{
	char	*report;

	report = ft_strprintable_sign(str);
	if (ft_putstr_fd(str, fd) == -1)
		ft_dprintf(2, "failed to put (%s) into (fd: %d)\n", report, fd);
	free(report);
}

//forking
// #include <sys/wait.h>
// #include <sys/types.h>
// int	main(int argc, char **argv, char **envp)
// {
// 	pid_t	child1;
// 	pid_t	child2;
// 	char	**cmd;

// 	int	grand = getpid();
// 	ft_printf("grandparent:	%d\n", grand);
// 	cmd = malloc(sizeof(char *) * 3);
// 	cmd[0] = "/bin/echo";
// 	cmd[1] = "	EXECVE";
// 	cmd[2] = 0;
// 	child1 = fork();
// 	if (getpid() != grand)
// 		ft_printf("fork1 current:	%d\n", getpid());
// 	child2 = fork();
// 	if (getpid() != grand)
// 		ft_printf("fork2 current:	%d\n", getpid());
// 	if (!child2)
// 	{
// 		ft_printf("	EXEC2 current:	%d\n", getpid());
// 		execve(*cmd, cmd, envp);
// 	}
// 	else
// 	{
// 		ft_printf("	waiting2:%d at(%d)\n", child2, getpid());
// 		ft_printf("wait2 return:	%d\n", waitpid(child2, 0, 0));
// 	}
// 	if (!child1)
// 	{
// 		ft_printf("	EXEC1 current:	%d\n", getpid());
// 		execve(*cmd, cmd, envp);
// 	}
// 	else
// 	{
// 		ft_printf("	waiting1:%d at(%d)\n", child1, getpid());
// 		ft_printf("wait1 return:	%d\n", waitpid(child1, 0, 0));
// 	}
// 	// static int status;
// 	// int status = -1;

// 	// ft_printf("wait1 return:	%d\n", waitpid(child1, 0, 0));
// 	// ft_printf("wait2 return:	%d\n", waitpid(child2, 0, 0));
// 	// ft_printf("	status:		%d\n", status);
// 	ft_printf("child1:	%d\n", child1);
// 	ft_printf("child2:	%d\n", child2);
// 	ft_printf("pid:	%d\n", getpid());
// }

// void	ft_pipe(int *arr)
// {
// 	int	status;

// 	status = pipe(arr);
// 	if (status)
// 	{
// 		ft_printf("pipe_error : %d\n", status);
// 		perror("pipex");
// 	}
// }

// // //piping
// int	main(int argc, char **argv, char **envp)
// {
// 	int		*pipex;
// 	char	**cmd;

// 	cmd = malloc(sizeof(char *) * 3);
// 	int	fd_out = open("piping", O_CREAT | O_RDWR | O_APPEND, 0644);
// 	if (fd_out == -1)
// 		return (ft_printf("fd_out error\n"));
// 	int	fd_in = open("../testin", O_RDONLY);
// 	if (fd_in == -1)
// 		return (ft_printf("fd_in error\n"));
// 	cmd[0] = "/bin/echo";
// 	cmd[1] = "Miku";
// 	cmd[2] = 0;
// 	pipex = malloc(sizeof(int) * 2);
// 	if (pipe(pipex))
// 		perror("pipe_error");
// 	else
// 		ft_printf("pipe success\n");
// 	dup2(pipex[0], fd_in);
// 	dup2(pipex[1], 1);
// 	if (ft_dprintf(pipex[0], "writing to the read_end of pipe\n") == -1)
// 		ft_dprintf(2, "write read_end failed\n");
// 	if (ft_dprintf(pipex[1], "writing to the write_end of pipe\n") == -1)
// 		ft_dprintf(2, "write write_end failed\n");

// 	pid_t	child;

// 	child = fork();
// 	if (!child)
// 		execve(*cmd, cmd, envp);
// 	else
// 		waitpid(child, 0, 0);
// 	dup2(fd_out, pipex[1]);
// 	ft_printf("writing to stdout\n");
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	int	pipex[2];

// 	if (pipe(pipex))
// 		return (ft_printf("pipe_error: %d\n", strerror(errno)));
// 	ft_printf("read_end(pipex[0]): %d\nwrite_end(pipex[1]): %d\n", pipex[0], pipex[1]);
// 	pid_t	child;

// 	child = fork();
// 	char	*cmd[2];

// 	cmd[0] = "/bin/cat";
// 	cmd[1] = 0;
// 	int	fd_in = open("../testin", O_RDONLY);
// 	if (fd_in == -1)
// 		return (ft_dprintf(2, "false infile\n"));
// 	int	fd_out = open("testout", O_CREAT | O_RDWR | O_APPEND, 0644);
// 	if (fd_out == -1)
// 		return (ft_dprintf(2, "outfile error\n"));
// 	if (!child)
// 	{
// 		dup2(fd_in, 0);
// 		// ft_dprintf(2, "dup2: %d\n", dup2(pipex[0], fd_in));
// 		// ft_dprintf(2, "dup2: %d\n", dup2(fd_out, 1));
// 		ft_dprintf(2, "dup2: %d\n", dup2(pipex[1], 1));
// 		// close(pipex[0]);
// 		// ft_putstr_fd_report("Hatsune Miku is stuck in here\n", 1);
// 		// dup2(pipex[0], 1);
// 		// ft_putstr_fd_report("(pipe: write_end)\n", pipex[1]);
// 		// close(pipex[1]);
// 		execve(*cmd, cmd, envp);
// 		ft_printf("child failed\n");
// 	}
// 	else
// 		waitpid(child, 0, 0);
// 	close(pipex[1]);
// 	dup2(pipex[0], 0);
// 	dup2(fd_out, 1);
// 	execve(*cmd, cmd, envp);
// 	// ft_printf("parent failed\n");
// 	{
// 		// char	*str;
		
// 		// str = get_next_line(pipex[0]);
// 		// while (str)
// 		// {
// 		// 	char	*pp;
// 		// 	pp = ft_strprintable_sign(str);
// 		// 	ft_printf("[%s]\n", pp);
// 		// 	free(pp);
// 		// 	free(str);
// 		// 	str = get_next_line(pipex[0]);
// 		// }
// 		// close(pipex[0]);
// 	}
// }

// dup:	return the lowest fd that is not occupied
// dup2:	specify the return fd with the second argument
// 	Note1:	if the specified fd is occupied, it will be first be closed
// 			and continue the process
// 	Note2:	always return the specified fd no matter if they are equal(same output)
// 	Return -1 if something went wrong

// void	ft_printto(int fd)
// {
// 	ft_dprintf(fd, "printing at: %d\n", fd);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	int	fd_file;

// 	// fd_file = open("fddup", O_CREAT | O_TRUNC | O_WRONLY, 0644);
// 	fd_file = open("sd", O_WRONLY);
// 	ft_printf("AYYYYYY: %d\n", fd_file);
// 	ft_printf("%s\n", strerror(errno));
// 	// ft_printf("dup2: %d\n", dup2(fd_file, 1));
// 	// ft_printf("dup2: %d\n", dup2(1, fd_file));
// 	ft_printto(2);
// 	ft_printto(1);
// 	ft_printto(fd_file);
// }


/// @brief Waitpid
int	main(void)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		perror("fork");
	else if (pid == 0)
	{
		printf("Miku and my child\n");
		exit(39);
	}
	else
	{
		sleep(4);
		/// @note Kill always return SUCESS if it is a valid pid
		printf("kill return: %d\n", kill(pid, SIGINT));
		printf("kill return: %d\n", kill(pid, SIGINT));
		printf("kill return: %d\n", kill(pid, SIGINT));
		printf("kill return: %d\n", kill(pid, SIGINT));
		/// @note Waitpid don't
		printf("waitpid return: %d\n", waitpid(-1, &status, 0));
		printf("waitpid return: %d\n", waitpid(-1, &status, 0));
		/// @note It doesn't fk up the status variable luckily
		printf("status: %d\n", WEXITSTATUS(status));
	}
}
