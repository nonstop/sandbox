#include <iostream>
#include <fstream>
#include <string>
#include <boost/filesystem/operations.hpp>
//#include <boost/filesystem/path.hpp>
//#include <boost/filesystem/fstream.hpp>

#define TRACE(val) std::cout << __FILE__ << ":" << __LINE__ << " " << #val << " [" << val << "]" << std::endl


using namespace std;
using namespace boost::filesystem;

int main(int ac, char* av[])
{
    std::string prefix = "/home/nonstop/tmp";
    std::string fileName = "fileName";
    std::string tmpDir = prefix + "/tmp";
    std::string readyDir = prefix + "/ready";

    TRACE(tmpDir);
    TRACE(readyDir);

    if (!exists(tmpDir))
        create_directory(tmpDir);
    if (!exists(readyDir))
        create_directory(readyDir);

    std::string tmpFile = tmpDir + "/" + fileName;
    std::string readyFile = readyDir + "/" + fileName;

    ofstream file(tmpFile.c_str());
    file << "tastes good!\n";
    file.close();
    
    if (exists(readyFile))
        remove(readyFile);

    copy_file(tmpFile, readyFile);
    remove(tmpFile);

    return 0;
}

