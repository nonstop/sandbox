#include <iostream>

using namespace std;

void printSquares(int n)
{
    if (n == 0) {
        cout << n << endl;
        return;
    }
    int sq = 0;
    cout << "0";
    for (int i = 1; i < n; ++i) {
        sq = (sq + i + (i - 1));
        cout << ' ' << sq;
    }
    cout << endl;
}

int main()
{
    int n = 0;
    cin >> n;
    printSquares(n);
    return 0;
}
