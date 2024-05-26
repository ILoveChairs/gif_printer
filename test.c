/* print */
#include <stdio.h>
/* execve */
#include <unistd.h>
/* malloc */
#include <stdlib.h>
/* strdup */
#include <string.h>
/* wait */
#include <sys/wait.h>

extern char **environ;

#include <time.h>
#include <errno.h>    

/* msleep(): Sleep for the requested number of milliseconds. */
int msleep(long msec)
{
	struct timespec ts;
	int res;

	if (msec < 0)
	{
		errno = EINVAL;
		return -1;
	}
	ts.tv_sec = msec / 1000;
	ts.tv_nsec = (msec % 1000) * 1000000;
	do {
	    res = nanosleep(&ts, &ts);
	} while (res && errno == EINTR);

	return res;
}

/**
 * print_image - Prints an ascii image calling jp2a program.
 *
 * @image_path: Path of image to print
 * @color: Color to print at the start.
 */
void print_image(char *image_path)
{
	pid_t pid;
	int status;
	char **args;

	pid = fork();

	if (pid == 0)
	{
		args = malloc(sizeof(char *) * 4);
		args[0] = strdup("/usr/bin/jp2a");
		args[1] = strdup("--colors");
		args[2] = image_path;
		args[3] = NULL;
		execve(args[0], args, environ);
	}
	else
	{
		wait(&status);
	}
}



/**
 * main - main
 *
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	int args_len = 2;
	int i;
	char *url;
	u12 num12;

	url = strdup("/root/carrot.png");

	for(i = 0; i < 5; i++)
	{
		system("clear");
		print_image(url);
		msleep(250);
	}

	free(url);
	return(0);
}

