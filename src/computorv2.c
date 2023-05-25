#include "get_next_line.h"
#include <stdio.h>

int		main(int ac, char **av)
{
	int		ret;
	char	*buf;

	ret = 1;
	(void)ac;
	(void)av;
	while (ret)
	{
		buf = 0;
		ret = get_next_line(0, &buf);
		if (ret == -1 || ret == 0)
			return (0);
		printf("BUFFER : %s\n", buf);
	}
	return (0);
}
