#include "../include/read.h"
#include "../include/quote_split.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;

	char *line;
	char **split;

	while ((line = readline("minishell> ")))
	{
		printf("line: %s\n", line);
		split = quote_split(line, ' ');
		split = clean_quotes(split);
		for (int i = 0; split[i]; i++)
			printf("%s\n", split[i]);
		if (strcmp(line, "exit") == 0) // replace with ft_strcmp
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
