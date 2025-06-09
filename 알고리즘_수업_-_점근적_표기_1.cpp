#include <iostream>

using namespace std;

int main()
{
    int a_1, a_0;
    cin >> a_1 >> a_0;
    int c;
    cin >> c;
    int n_0;
    cin >> n_0;

    int f = a_1 * n_0 + a_0;
    int cg = c * n_0;

    if (f <= cg && c >= a_1)
    {
        cout << 1 << endl;
    }
    else
        cout << 0 << endl;
        
    return 0;
}