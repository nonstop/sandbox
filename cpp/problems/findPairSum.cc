#include <iostream>
#include <vector>
#include <stdlib.h>
#include <map>

using namespace std;

void findPairSum(int n, const vector<int>& array)
{
    map<int, int> vals;
    for (int i = 0, end = array.size(); i < end; ++i) {
        vals[array[i]] = i;
    }
    for (int i = 0, end = array.size(); i < end; ++i) {
        map<int, int>::const_iterator it(vals.find(n - array[i]));
        if (it != vals.end()) {
            cout << "found sum for " << n << " : " << array[i] << " " << it->first << endl;
            return;
        }
    }

}

int main(int ac, char* av[])
{
    if (ac < 4) {
        return -1;
    }
    vector<int> array;
    for (int i = 2; i < ac; ++i) {
        array.push_back(atoi(av[i]));
    }
    findPairSum(atoi(av[1]), array);
    return 0;
}
