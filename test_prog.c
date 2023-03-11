#include "stdlib.h"

static int	my_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

static int	my_isspace(char c)
{
	return (c == '\t' || c == '\n' || c == '\v' || c == '\f'
			|| c == '\r' || c == ' ');
}

static int	chr_to_dgt(char c)
{
	return (c - '0');
}

static int	whitespace_sign_limited(const char **nptr)
{
	while (my_isspace(*(*nptr)))
		(*nptr)++;
	if (*(*nptr) == '-')
	{
		(*nptr)++;
		return (-1);
	}
	else if (*(*nptr) == '+')
	{
		(*nptr)++;
	}
	return (1);
}

static int	my_atoi(const char *nptr)
{
	int	res;
	int	sign;

	res = 0;
	sign = whitespace_sign_limited(&nptr);
	while (my_isdigit(*nptr))
	{
		res = res * 10 + chr_to_dgt(*nptr);
		nptr ++;
	}
	return (res * sign);
}

extern char  **environ;

#include "unistd.h"
#include "stdlib.h"
#include "stdio.h"
int main(int argc, char *argv[])
{
	if (argc == 1)
		exit (69);
	/*char *prog = "test script.sh";
	fprintf(stderr, "executing prog %s\n", prog);
	int res = execve(prog, NULL, environ);
	fprintf(stderr, "res: %d\n", res);
	exit (my_atoi(argv[1]));*/
	return (0);
}
