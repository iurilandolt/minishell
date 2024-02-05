#include "../include/read.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	char *line;

	while ((line = readline("minishell> ")))
	{
		printf("%s\n", line);
		if (strcmp(line, "exit") == 0)
		{
			free(line);
			rl_clear_history();
			break ;
		}
		if (line && strlen(line) > 0)
			add_history(line);
		free(line);
	}
	return (0);
}
