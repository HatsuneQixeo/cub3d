#include "libft.h"
#include "../../includes/pipex.h"
// MAN BASH

// Evaluated as reading variable
// ?Or the following expression becomes variable?
// Cannot contain backslash or another opening curly brace
void	shell_curlybrace(const char *str)
{

}

// Evaluated as running command
// Second opening parenthesis will be evaluated as math expression?
void	shell_parenthesis(const char *str)
{


}

void	shell_bracket(const char *str)
{

}

size_t	ms_varname_len(const char *input)
{
	size_t	i;

	i = 0;
	if (ft_isdigit(input[0]))
		return (1);
	while (ft_isalnum(input[i]) || input[i] == '_')
		i++;
	return (i);
}

char	*pipex_readvar(char **envp, const char *input, size_t len_var_name)
{
	char	*var_name;
	char	*str_var;

	var_name = ft_substr(input, 1, len_var_name);
	var_name = ft_strmodify(var_name, "=");
	str_var = ft_strliststr(envp, var_name);
	if (str_var == NULL)
		str_var = ft_strdup("");
	else
		str_var = ft_strdup(str_var + ft_strlen(var_name));
	free(var_name);
	return (str_var);
}

// int	pipex_varandcmd(char **envp, const char *input, int fd_heredoc)
// {
// 	size_t	len_var_name;

// 	if (input[1] == '(')
// 	{
// 		char	*cmd;
// 		char	*closing;
// 		int		pipex[2];

// 		closing = ft_strchr(input, ')');
// 		if (input[2] == '(' || !closing)
// 			ft_exitprintf(1, "zsh: parse error");
// 		ft_pipeinit(pipex);
// 		cmd = ft_substr(input, 2, closing - (input + 2));
// 		pipex_forking(cmd, -1, pipex[1], envp);
// 		free(cmd);
// 		char	*output;
// 		output = ft_file_extract(pipex[0]);
// 		close(pipex[0]);
// 		ft_strrelease_fd(ft_strmodify(output, "\n", ft_strtrim), fd_heredoc);
// 		return (closing - input + 1);
// 	}
// 	else
// 	{
// 		len_var_name = ms_varname_len(input + 1);
// 		ft_strrelease_fd(pipex_readvar(envp, input, len_var_name), fd_heredoc);
// 		return (len_var_name + 1);
// 	}
// }

// void	pipex_variable(char **envp, const char *input, int fd_heredoc)
// {
// 	while (*input != '\0')
// 	{
// 		if (!ft_strncmp(input, "$$", 2))
// 		{
// 			ft_putnbr_fd(getpid(), fd_heredoc);
// 			input += 2;
// 		}
// 		else if (!ft_strncmp(input, "\\$", 2))
// 		{
// 			ft_putchar_fd('$', fd_heredoc);
// 			input += 2;
// 		}
// 		else if (!ft_strncmp(input, "$(", 2))//command
// 			input += pipex_varandcmd(envp, input, fd_heredoc);
// 		else if (!ft_strncmp(input, "${", 2) || *input == '$')
// 			input += pipex_varandcmd(envp, input, fd_heredoc);
// 		else
// 			input += ft_putchar_fd(*input, fd_heredoc);
// 		ft_printf("inputloop: %b\n", input);
// 	}
// 	ft_putchar_fd('\n', fd_heredoc);
// }

void	shell_backslash(char *str)
{
	if (str[0] != '\\' || str[1] == '\0')
		return ;
	else if (str[1] == '\n')
		ft_memmove(str, str + 2, ft_strlen(str + 2) + 1);
	else
		ft_memmove(str, str + 1, ft_strlen(str + 1) + 1);
}

static int	ft_bquote(char *src)
{
	char	quote_start;
	char	*end;

	if (src == NULL || *src == '\0'  || !(*src == '\'' || *src == '\"'))
		return (0);
	quote_start = *src;
	end = ft_memmove(src, src + 1, ft_strlen(src + 1) + 1);
	while (*end != '\0' && *end != quote_start)
	{
		if (quote_start != '\'' && *end == '\\')
			shell_backslash(end);
		end++;
	}
	// if (*end != quote_start)
	if (*end == '\0')
		return (1 - !ft_dprintf(2, "zsh: parse error\n"));
	ft_memmove(end, end + 1, ft_strlen(end + 1) + 1);
	return (end - src);
}

static char	*ft_parse(char **str)
{
	char	*str_ptr;
	char	*start;
	int		read;

	str_ptr = *str;
	start = str_ptr;
	while (*str_ptr != '\0' && !ft_isspace(*str_ptr))
	{
		if (*str_ptr == '\'' || *str_ptr == '\"')
		{
			read = ft_bquote(str_ptr);
			if (read == -1)
			{
				ft_dprintf(2, "Missing closing quote (%c) at (%s)\n",
					*str_ptr, str_ptr);
				return (NULL);
			}
			str_ptr += read - 1;
		}
		else if (*str_ptr == '\\')
			shell_backslash(str_ptr);
		str_ptr++;
	}
	*str = str_ptr;
	return (ft_substr(start, 0, str_ptr - start));
}

static char	**ft_parsemove(char *src)
{
	t_list	*lst;
	char	*parse;

	lst = NULL;
	while (*src != '\0')
	{
		if (ft_isspace(*src))
		{
			src++;
			continue ;
		}
		parse = ft_parse(&src);
		if (parse == NULL)
		{
			ft_lstclear(&lst, free);
			return (NULL);
		}
		ft_lstadd_back(&lst, ft_lstnew(parse));
	}
	return (ft_lsttoaa_clear(&lst));
}

char	**ft_parsesplit(const char *src)
{
	char	*src_dup;
	char	**strlist;

	src_dup = ft_strdup(src);
	strlist = ft_parsemove(src_dup);
	free(src_dup);
	return (strlist);
}

#define bout	"Hatsune\\ Miku\\ is\\ cute"
#define bbquote		"Hatsune'\\''Miku'\\'is'\\'cute"// (valid)
#define bb		"Hatsune'\\\\'Miku'\\\\'is'\\\\'cute"
#define tab		"Hatsune'\t'Miku'\t'is'\t'cute"
#define space	"Hatsune' 'Miku' 'is' 'cute"
#define bquote	"Hatsune'\\''Miku'\\''is'\\''cute"
#define quote_error	"Hatsune'\''Miku'\''is'\''cute"
#define nlgone	"Hatsune\\\nMiku\\\nis\\\ncute"
//Parsing the user input
//Note: Backslash enter will connect the line \'\10'

char	*ft_prompt(const char *prompt)
{
	ft_putstr_fd(prompt, 1);
	return (get_next_line(STDIN_FILENO));
}

int	main(void)
{
	char	*input;

	input = ft_prompt("Parse test> ");
	while (input != NULL)
	{
		char	**strlist;

		// input = ft_strinsert(bb, "       ", bquote);
		ft_printf("src: %s\n", input);
		strlist = ft_parsesplit(input);
		ft_putstrlist_fd(strlist, 1);
		ft_strlistclear(strlist);
		free(input);
		input = ft_prompt("Parse test> ");
	}
	system("leaks -q shell_related.miku");
}

// Find envp
// 	if (**command == '.')
// 	{
// 		ft_memmove(*command, (*command) + 1, ft_strlen((*command) + 1) + 1);
// 		*command = ft_strmodify(*command, getvar_value(envp, "PWD"), ft_strrjoin);
// 		if (!access(*command, F_OK | X_OK))
// 			ft_dprintf(2, "access yes\n");
// 		else
// 			ft_dprintf(2, "access no\n");
// 	}
// 	else
