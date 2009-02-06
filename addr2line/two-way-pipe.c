/*
 * two-way-pipe.c  - two processes communicating both ways by using two
 *                   pipes. One process reads input from the user and handles
 *                   it. The other process makes some translation of the
 *                   input (translates upper-case letters to lower-case),
 *                   and hands it back to the first process for printing.
 */

#include <stdio.h>    /* standard I/O routines.                  */
#include <unistd.h>   /* defines pipe(), amongst other things.   */
#include <ctype.h>    /* defines isascii(), toupper(), and other */
                      /* character manipulation routines.        */

/* function executed by the user-interacting process. */
void user_handler(int input_pipe[], int output_pipe[])
{
    int c;    /* user input - must be 'int', to recognize EOF (= -1). */
    char ch;  /* the same - as a char. */
    int rc;   /* return values of functions. */

    /* first, close unnecessary file descriptors */
    close(input_pipe[1]);  /* we don't need to write to this pipe.  */
    close(output_pipe[0]); /* we don't need to read from this pipe. */

    /* loop: read input from user, send via one pipe to the translator, */
    /* read via other pipe what the translator returned, and write to   */
    /* stdout. exit on EOF from user.                                   */
    while ((c = getchar()) > 0) {
	/* note - when we 'read' and 'write', we must deal with a char, */
	/* rather then an int, because an int is longer then a char,    */
	/* and writing only one byte from it, will lead to unexpected   */
	/* results, depending on how an int is stored on the system.    */
	ch = (char)c;
	/* write to translator */
        rc = write(output_pipe[1], &ch, 1);
	if (rc == -1) { /* write failed - notify the user and exit. */
	    perror("user_handler: write");
	    close(input_pipe[0]);
	    close(output_pipe[1]);
	    exit(1);
        }
	/* read back from translator */
	rc = read(input_pipe[0], &ch, 1);
	c = (int)ch;
	if (rc <= 0) { /* read failed - notify user and exit. */
	    perror("user_handler: read");
	    close(input_pipe[0]);
	    close(output_pipe[1]);
	    exit(1);
        }
	/* print translated character to stdout. */
	putchar(c);
    }

    /* close pipes and exit. */
    close(input_pipe[0]);
    close(output_pipe[1]);
    exit(0);
}

/* now comes the function executed by the translator process. */
void translator(int input_pipe[], int output_pipe[])
{
    int c;    /* user input - must be 'int', to recognize EOF (= -1). */
    char ch;  /* the same - as a char. */
    int rc;   /* return values of functions. */

    /* first, close unnecessary file descriptors */
    close(input_pipe[1]); /* we don't need to write to this pipe.  */
    close(output_pipe[0]); /* we don't need to read from this pipe. */

    /* enter a loop of reading from the user_handler's pipe, translating */
    /* the character, and writing back to the user handler.              */
    while (read(input_pipe[0], &ch, 1) > 0) {
	c = ch;

	/* translate any upper-case letter to lowr-case. */
	if (isascii(c) && isupper(c))
            c = tolower(c);

	ch = c;
        /* write translated character back to user_handler. */
        rc = write(output_pipe[1], &ch, 1);
        if (rc == -1) { /* write failed - notify user and exit. */
            perror("translator: write");
            close(input_pipe[0]);
            close(output_pipe[1]);
            exit(1);
        }
    }

    /* close pipes and exit. */
    close(input_pipe[0]);
    close(output_pipe[1]);
    exit(0);
}

/* and finally, the main function: spawn off two processes, */
/* and let each of them execute its function.               */
int main(int argc, char* argv[])
{
    /* 2 arrays to contain file descriptors, for two pipes. */
    int user_to_translator[2];
    int translator_to_user[2];
    int pid;       /* pid of child process, or 0, as returned via fork.    */
    int rc;        /* stores return values of various routines.            */

    /* first, create one pipe. */
    rc = pipe(user_to_translator);
    if (rc == -1) {
	perror("main: pipe user_to_translator");
	exit(1);
    }
    /* then, create another pipe. */
    rc = pipe(translator_to_user);
    if (rc == -1) {
	perror("main: pipe translator_to_user");
	exit(1);
    }

    /* now fork off a child process, and set their handling routines. */
    pid = fork();

    switch (pid) {
	case -1:	/* fork failed. */
	    perror("main: fork");
	    exit(1);
	case 0:		/* inside child process.  */
	    translator(user_to_translator, translator_to_user); /* line 'A' */
	    /* NOT REACHED */
	default:	/* inside parent process. */
	    user_handler(translator_to_user, user_to_translator); /* line 'B' */
	    /* NOT REACHED */
    }

    return 0;	/* NOT REACHED */
}
