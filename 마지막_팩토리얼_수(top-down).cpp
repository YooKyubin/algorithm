#include <iostream>
#include <cmath>

using namespace std;

int getQPac(int n)
{
    switch(n)
    {
        case 0:
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 6;
        case 4:
            return 4;

        default:
            int q= n / 5;
            int qtime5 = q * 5;

            int ret = getQPac(q) * pow(2, q%4);
            for (int i=qtime5+1; i <= n; ++i)
            {
                ret *= i % 10;
            }
            return ret % 10;
    }
}

int main()
{
    int n;
    cin >> n;

    int answer = getQPac(n);

    cout << answer << endl;
    return 0;
}