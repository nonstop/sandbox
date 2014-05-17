#include <stdio.h>
#include <string.h>
#include <assert.h>

#include <signal.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>

#include <iostream>
#include <stdexcept>

#define STDFMT "%s:%d "
#define STD __FILE__, __LINE__
#define TRACE(format, ...) fprintf(stderr, STDFMT # format, STD, ## __VA_ARGS__); fprintf(stderr, "\n")
#define STRACE(x) std::cerr << __FILE__ << ":" << __LINE__ << x << std::endl

namespace
{

void setupCore()
{
    volatile static sig_atomic_t called = 0;

    if(!called){
        struct rlimit rl;
        if(getrlimit(RLIMIT_CORE,&rl)<0){
            TRACE("cannot get rlimit (getrlimit):%.200s", strerror(errno)); 
            return;
        }
        if(rl.rlim_cur< rl.rlim_max){
            rl.rlim_cur=rl.rlim_max;
            if(setrlimit(RLIMIT_CORE,&rl)<0){
                TRACE("cannot set rlimit (setrlimit):%.200s",strerror(errno)); 
                return;
            }
        }
        called=1;
    }
}

int our_signal(int sig, void(*f)(int), sigset_t sigs)
{
    struct sigaction in;
    in.sa_handler=f;
    in.sa_mask=sigs;
    in.sa_flags=0;
    switch (sig) {
        case SIGABRT:
        case SIGSEGV:
        case SIGILL:
        case SIGFPE:
        case SIGBUS:
        case SIGQUIT: {
            if(getenv ("BROKEN_GDB")) {
                return 0;
            }
            in.sa_flags=SA_RESETHAND;
        }
    }
    if (sigaction(sig, &in, NULL) < 0) {
        TRACE("sigaction failed for signal: #%d", sig);
        return -2;
    }
    return 0;
}

void term3(int signo)
{
    volatile static sig_atomic_t waschdir = 0; // C++, ISO-IEC 14882, 3rd Ed, 1.9.6

    TRACE("term3 called pid %d sig %d", getpid(), signo);
    switch(signo) {
        case SIGTERM: {
            TRACE("Received SIGTERM");
            break;
        }
        default:
            TRACE("Killed in action :-( by %d SIGABRT=%d", signo, SIGABRT);
            {
                sigset_t se;
                sigemptyset(&se);
                sigaddset(&se,SIGABRT);
                sigaddset(&se,signo);
                our_signal(signo,SIG_DFL,se); 
                our_signal(SIGABRT,SIG_DFL,se); 
                if(!waschdir){
                    waschdir = 1;
                    char buf[128];
                    snprintf(buf,sizeof(buf),"Cores/%d",getpid());
                    mkdir(buf,0755);
                    if(chdir(buf) < 0) {
                        waschdir = 0;
                    }
                }
                setupCore();
                raise(signo);
                return;
            }
    }

    switch (signo) {
        case -1:
        case SIGINT:
        case SIGPIPE:
        case SIGTERM:
        case SIGXFSZ:
            break;
        default: 
            TRACE("nothing for %d", signo);
    }
    _exit(1); // man 2 _exit
}

static void term33(int signo)
{
    TRACE("term33 with signal %d", signo);
    signal(signo, SIG_DFL);
    raise(signo);
}

void set_signal(void(*f) (int))
{
#define regsignal(x) {x,#x},
    static struct {
        int s;
        const char *name; 
    }tab[]={
        regsignal(SIGINT)
        regsignal(SIGQUIT)
        regsignal(SIGILL)
        regsignal(SIGABRT)
        regsignal(SIGTRAP)
        regsignal(SIGIOT)
        regsignal(SIGBUS)
        regsignal(SIGFPE)
        regsignal(SIGSEGV)
        regsignal(SIGPIPE)
        regsignal(SIGTERM)
        regsignal(SIGVTALRM)
        regsignal(SIGPWR)
        regsignal(SIGXFSZ)
        regsignal(SIGUSR2)
    };
#undef regsignal


    sigset_t sigset;
    assert(sigemptyset(&sigset)>=0 && "sigemptyset");
    assert(sigprocmask(SIG_SETMASK,&sigset,NULL)>=0 && "sigprocmask");


    for (size_t i = 0; i < sizeof(tab)/sizeof(tab[0]); i++) {
        if (sigaddset(&sigset, tab[i].s) < 0){
            TRACE(">>>>> sigaddset failed on %s\n",tab[i].name);
        }
    }
    for (size_t i = 0; i < sizeof(tab)/sizeof(tab[0]); i++) {
        if (our_signal(tab[i].s, f, sigset)<0){
            TRACE(">>>>> our_signal failed on %s\n",tab[i].name);
            throw std::runtime_error("our_signal");
        }
    }
}


} // namespace

struct Bar
{
    ~Bar() {
        TRACE("~Bar");
    }
};

struct Foo
{
    ~Foo() {
        TRACE("~Foo");
    }
};

static int usage()
{
    std::cerr << "sigcore [sig|nosig] [abort|throw|rethrow]" << std::endl;
    return 1;
}

enum Mode {M_Abort, M_Throw, M_Rethrow};

static void bar(Mode m)
{
    Bar b;
    if (m == M_Abort) {
        abort();
    } else {
        throw std::logic_error("bar");
    }
}

static void foo(int level, Mode m)
{
    if (level < 20) {
        foo(level + 1, m);
        return;
    }
    Foo f;
    if (m == M_Rethrow) {
        try {
            bar(M_Throw);
        } catch (const std::exception& e) {
            TRACE("exception catched: [%s]", e.what());
            throw;
        }
    } else {
        bar(m);
    }
}

int main(int ac, char* av[])
{
    if (ac != 3) {
        return usage();
    }
    bool setSignal = false;
    if (strncmp("sig", av[1], 4) == 0) {
        setSignal = true;
    } else if (strncmp("nosig", av[1], 6) == 0) {
        setSignal = false;
    } else {
        TRACE("unknown option [%s]", av[1]);
        return usage();
    }
    Mode mode = M_Abort;
    if (strncmp("abort", av[2], 6) == 0) {
        mode = M_Abort;
    } else if (strncmp("throw", av[2], 6) == 0) {
        mode = M_Throw;
    } else if (strncmp("rethrow", av[2], 8) == 0) {
        mode = M_Rethrow;
    } else {
        TRACE("unknown option [%s]", av[2]);
        return usage();
    }
    TRACE("setSignal=%d mode=%d", setSignal, mode);
    if (setSignal) {
        set_signal(term3);
    }
    foo(0, mode);
    return 0;
}
