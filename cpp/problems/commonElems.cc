#include <iostream>
#include <vector>
#include <map>

using namespace std;

static void findCommon(const vector<vector<int> >& arrays)
{
    const size_t arraysSz(arrays.size());
    map<int, vector<int> > elems;
    for (size_t i = 0; i < arraysSz; ++i) {
        for (size_t j = 0, end_j = arrays[i].size(); j < end_j; ++j) {
            const int elem(arrays[i][j]);
            map<int, vector<int> >::iterator it = elems.find(elem);
            if (it != elems.end()) {
                it->second[i] = 1;
            } else {
                elems[elem] = vector<int>(arraysSz, 0);
                elems[elem][i] = 1;
            }
        }
    }
    cout << "common elems are:";
    const vector<int> match(arraysSz, 1);
    for (map<int, vector<int> >::const_iterator cit = elems.begin(); cit != elems.end(); ++cit) {
        if (cit->second == match) {
            cout << ' ' << cit->first;
        }
    }
    cout << endl;
}

int main()
{
    vector<int> ar1 = {1, 2, 3, 4, 5, 6},
        ar2 = {2, 4, 6, 8},
        ar3 = {3, 4, 5},
        ar4 = {6, 7, 5, 4, 3, 5};

    vector<vector<int> > arrays;
    arrays.push_back(ar1);
    arrays.push_back(ar2);
    arrays.push_back(ar3);
    arrays.push_back(ar4);
    findCommon(arrays);
    return 0;
}
