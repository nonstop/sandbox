//  shared memory needs it
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>           /* For O_* constants */
#include <errno.h>

#include <iostream>

using namespace std;
const char* sm_name = "/shared memory name";

void firstTime(int fd)
{
    cout << "first time" << endl;
    write(fd, "123\n", 4);
}

void notFirst()
{
    int fdShMem = shm_open(sm_name, O_RDONLY, 0);
    char buff[40];
    int len = read(fdShMem, buff, 40);
    buff[len] = 0;
    cout << "[" << buff << "]" << endl;
    close(fdShMem);
}

int main(int ac, char* av[])
{
    cout << "starting " << av[0] << endl;
    
    cout << "checking for shared:" << endl;
    
    int fdShMem = shm_open(sm_name, O_RDWR | O_CREAT | O_EXCL, S_IRWXU);
    if (fdShMem < 0)
    {
        int err = errno;
        if (errno == EEXIST)
            notFirst();
        else
        {
            cerr << "Error occured: " << strerror(err) << endl;
            return -1;
        }
    }
    else
    {
        firstTime(fdShMem);
        close(fdShMem);
    }

    cout << "finishing " << av[0] << endl;
    return 0;
}


