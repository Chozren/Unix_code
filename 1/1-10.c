#include"../apue.h"
#include<sys/wait.h>

static void sig_int (int);	/* our signal-catching function */

int main ()
{
	char	buf[MAXLINE];	/*from apue.h*/
	pid_t	pid;
	int		status;

	if (signal (SIGINT, sig_int) == SIG_ERR)
		err_sys ("signal error");

	printf("%% ");	/* print % */
	while (fgets (buf, MAXLINE, stdin) != NULL) {	
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0;	/* replace newline with null */
		if ((pid = fork ()) < 0) {
			err_sys ("fork error");
		} else if (pid == 0) {			/* child */
			execlp (buf, buf, (char *)0);
			err_ret("couldn't execute: %s", buf);
			exit (127);

		}

		/* parent */
		if ((pid = waitpid (pid, &status, 0)) < 0)
			err_sys ("waitpid error");
		printf ("%%");

	}
	exit(0);
}
//在子进程正常结束之前(pid > 0时)是否返回到终端执行了命令？

void sig_int (int signo)
{
	printf("interrupt\n");
}
