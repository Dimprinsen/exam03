#include <unistd.h>
#include <string.h>
#include <stdlib.h>


int	ft_popen(const char *file, char *const argv[], char type)
{
	int fd[2];
	pid_t pid;

	if (!file || !argv || (type != 'r' && type != 'w'))
		return -1;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		if (type == 'r')
			dup2(fd[1], 1);
		if (type == 'w')
			dup2(fd[0], 0);
		close(fd[1], 1);
		close(fd[0], 0);
		execvp(file, argv);
		exit (1);
	}
	if (type == 'r')
	{
		close(fd[1]);
		return (fd[0]);
	}
	else
	{
		close(fd[0]);
		return (fd[1]);
	}
}
//pipe, fork, dup2, execvp, close, exit
int ft_popen(const char *file, char *const argv[], char type)
{
	int fd[2];
	pid_t pid;

	if (!file || !argv || (type != 'r' && type != 'w'))
		return -1;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		if (type == 'r')
			dup2(fd[1], 1);
		if (type == 'w')
			dup2(fd[0], 0);
		close(fd[1], 1);
		close(fd[0], 0);
		execvp(file, argv);
		exit (1);
	}
	if (type == 'r')
	{
		close(fd[1]);
		return(fd[0]);
	}
	else
	{
		close(fd[0]);
		return(fd[1]);
	}
}

	//Pipe: Allows inter-process communication.
	//Data written to fd[1] can be read from fd[0].

	//Fork: Creates a child process. Both parent and child continue executing.

	//dup2(fd[1], 1) → redirect stdout to the pipe's write end
	//Dup2:  Duplicates a file descriptor to a standard stream:

	//dup2(fd[0], 0) → redirect stdin to the pipe's read end

	//Type 'r' (Read):
	// Parent reads from subprocess's output
	// Child writes stdout to pipe → parent reads from pipe
	// Type 'w' (Write):
	// Parent sends data to subprocess's input
	// Parent writes to pipe → child reads from stdin
}

int ft_popen(const char *file, char *const argv[], char type)
{
		int fd[2];
		pid_t pid;
		
		if (!file || !argv || (type != 'r' && type != 'w'))
			return (-1);
		pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			if (type == 'r')
				dup2(fd[1], 1);
			if (type == 'w')
				dup2(fd[0], 0);
			close(fd[0]);
			close(fd[1]);
			execvp(file, argv);
			exit (1);
		}
		if (type == 'r')
		{
				close(fd[1]);
				return (fd[0]);
		}
		else
		{
				close(fd[0]);
				return (fd[1]);
		}
}