#include <unistd.h>
#include <sys/wait.h>
#include <iostream>

#include <string>
#include <stdexcept>
#include <map>
#include <boost/format.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/stream.hpp>

typedef boost::iostreams::stream<boost::iostreams::file_descriptor> fdstream;

void init_addr2line(const std::string& filename);

namespace
{
static std::string Addr2lineFilename;


class Addr2line
{
public:
    class Exception
        : public std::runtime_error
    {
    public:
        Exception(const std::string& msg) : std::runtime_error(msg) {}
        virtual ~Exception() throw() {}
    };
public:
    static Addr2line& instance()
    {
        static Addr2line* ptr = NULL;
        if (!ptr)
            ptr = new Addr2line(Addr2lineFilename);
        return *ptr;
    }
    std::string translateAddress(const std::string& addr)
    {
        (*stream_to_ptr_) << addr << std::endl;
        std::string res;
        getline((*stream_from_ptr_), res);
        return res;
    }
private:
    Addr2line(const std::string& filename)
    {
        int main_to_addr[2];
        if (pipe(main_to_addr) < 0)
            throw Exception("pipe failed");
        int addr_to_main[2];
        if (pipe(addr_to_main) < 0)
            throw Exception("pipe failed");
        pid_ = fork();
        if (pid_ == -1)
            throw Exception("fork call in run_wpipe");
        if (pid_ == 0) { // child "addr2line"
            execAddr2line(main_to_addr, addr_to_main, filename);
        } else { // parent
            prepareWriter(addr_to_main, main_to_addr);
        }
    }
    ~Addr2line()
    {
        while (wait((int *)0) != pid_);
    }
    void prepareWriter(int input_pipe[], int output_pipe[])
    {
        close(input_pipe[1]);
        close(output_pipe[0]);

        stream_from_ptr_.reset(new fdstream(input_pipe[0]));
        stream_to_ptr_.reset(new fdstream(output_pipe[1]));
    }
    void execAddr2line(int input_pipe[], int output_pipe[], const std::string& filename)
    {
        close(input_pipe[1]);
        close(output_pipe[0]);

        // stdin from main_to_addr
        dup2(input_pipe[0], 0);   // read side of the pipe
        close(input_pipe[0]);
        // stdout to addr_to_main
        dup2(output_pipe[1], 1);   // write side of the pipe
        close(output_pipe[1]);

        int res = execlp("/usr/bin/addr2line", "-C", "-e", filename.c_str(), NULL);
        if (res != 0)
            throw Exception("execlp failed");
        
        close(input_pipe[0]);
        close(output_pipe[1]);
        exit(0);
    }
    boost::scoped_ptr<fdstream> stream_to_ptr_;
    boost::scoped_ptr<fdstream> stream_from_ptr_;
    int pid_;
};
}

void init_addr2line(const std::string& filename)
{
    Addr2lineFilename = filename;
    Addr2line::instance();
}

std::string addr2line(const std::string& addr)
{
    typedef std::map<std::string, std::string> known_addr_t;
    static known_addr_t known_addrs;

    static bool flag = true;
    const int address = flag ? int(&init_addr2line) : int(&addr2line);
    flag = !flag;
    std::string addr2 = (boost::format("0x%x") % address).str();
    std::cout << addr2 << " : ";
    
    known_addr_t::const_iterator it = known_addrs.find(addr2);
    if (it != known_addrs.end())
        return it->second;

    std::string res = Addr2line::instance().translateAddress(addr2);
    known_addrs[addr2] = res;
    return res;
}


