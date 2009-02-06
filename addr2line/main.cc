
#include <string>
#include <iostream>

void init_addr2line(const std::string& filename);
std::string addr2line(const std::string& addr);

#if 0
int main(int ac, char* av[])
{
    using namespace std;
    if (ac != 3) {
        cout << "usage: " << av[0] << " file addr" << endl;
        return 1;
    }
    init_addr2line(av[1]);
    cout << addr2line(av[2]) << endl;
    return 0;
}
#else // 0
int main(int ac, char* av[])
{
    using namespace std;
    //init_addr2line("/home/nonstop/work/sirena/sirenalibs/serverlib/testapp");
    init_addr2line(av[0]);
    cout << addr2line("0x817369a") << endl;
    cout << addr2line("0x81a3add") << endl;
    cout << addr2line("0x81a3add") << endl;
    cout << addr2line("0x81a3add") << endl;
    cout << addr2line("0x81a3add") << endl;
//    cout << addr2line("0x81b3fcb") << endl;
//    cout << addr2line("0xb7428e1d") << endl;
//    cout << addr2line("0xb739f50d") << endl;
    cout << addr2line("0x817369a") << endl;
    cout << addr2line("0x817369a") << endl;
    cout << addr2line("0x817369a") << endl;
    return 0;
}
#endif // 0
