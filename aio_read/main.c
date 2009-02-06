#include <stdio.h>
#include <signal.h>
#include <aio.h>

int done = 0;
struct aiocb aio_buf = {0};

static void on_event()
{
    char* p_buf = (char*)(aio_buf.aio_buf);
    if (aio_error(&aio_buf) != 0)
        fprintf(stderr, "error in on_event\n");
    else
        if (aio_return(&aio_buf) == 1) {
            char c = *p_buf;
            fprintf(stderr, "char: %d, [%c]\n", c, c);
            if (c == 'Q' || c == EOF)
                done = 1;
        }
    aio_read(&aio_buf);
}

int main()
{
    signal(SIGIO, on_event);

    static char buff[1];
    aio_buf.aio_fildes = 0;
    aio_buf.aio_buf = buff;
    aio_buf.aio_nbytes = sizeof(buff);
    aio_buf.aio_offset = 0;
    aio_buf.aio_sigevent.sigev_notify = SIGEV_SIGNAL;
    aio_buf.aio_sigevent.sigev_signo = SIGIO;

    aio_read(&aio_buf);

    while(!done) {
        sleep(2);
        fprintf(stderr, "sleeping\n");
    }

    return 0;
}

