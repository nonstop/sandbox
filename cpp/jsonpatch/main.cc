#include <iostream>
#include <fstream>
#include <iomanip>
#include <optional>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

std::string readFile(const char* path)
{
    std::ifstream f(path, std::ios::in | std::ios::binary);
    const auto sz = std::filesystem::file_size(path);
    std::string res(sz, '\0');
    f.read(res.data(), sz);
    return res;
}

template<typename D>
int diffSize(const D& d)
{
    std::stringstream ss;
    ss << d;
    return ss.str().size();
}

int main(int ac, char* av[])
{
    if (ac == 3) {
        std::string s1 = readFile(av[1]);
        std::string s2 = readFile(av[2]);
        const auto json1 = json::parse(s1);
        const auto json2 = json::parse(s2);
        const auto d = json::diff(json1, json2);
        std::cout << "sz=" << s1.size() << ' ' << std::setw(2) << json1 << std::endl;
        std::cout << "sz=" << s2.size() << ' ' << std::setw(2) << json2 << std::endl;
        std::cout << "sz=" << diffSize(d) << ' ' << std::setw(2) << d << std::endl;
        return 0;
    }
    if (ac == 2) {
        std::ifstream f(av[1], std::ios::in);
        int objSz = 0, diffSz = 0;
        int l = 0;
        std::string s;
        std::optional<decltype(json::parse(s))> baseVer;
        int baseVerNum = 0;
        while (getline(f, s)) {
            ++l;
            if (s.empty()) {
                break;
            }
            objSz += s.size();
            if (!baseVer) {
                diffSz = objSz;
                baseVer = json::parse(s);
                baseVerNum = l;
                continue;
            }
            const auto ver = json::parse(s);
            const auto patch = json::diff(*baseVer, ver);
            json d;
            d["id"] = std::to_string(l);
            d["patch"] = patch;
            int szd = diffSize(d);
            int sz = s.size();
            if (3*szd > sz) {
                diffSz += sz;
                baseVer = ver;
                baseVerNum = l;
                fprintf(stdout, "%3d : sz=%d base\n", l, sz);
            } else {
                diffSz += szd;
                fprintf(stdout, "%3d : sz=%d diff [%d vs %d]=%d\n", l, sz, baseVerNum, l, szd);
            }
        }
        fprintf(stdout, "obj=%d diff=%d\n", objSz, diffSz);
        f.close();
    }
    return 1;
}

#if 0
v = basic version
nv = new version
szo = size of whole object for new version
szp = size of patch between v and nv
if szo > szp then
    set v to nv
else
    store patch
#endif //0
       //
