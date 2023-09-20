#include <iostream>

using namespace std;

int64_t a, b, c;

int64_t pow(int64_t n)
{
    if (n==1)
        return a % c;

    int64_t temp = pow(n/2);

    if (n % 2 == 0)
        return (temp * temp) % c;
    else
        return (((temp * temp) % c) * a) % c;
}

int main()
{
    cin >> a >> b >> c;
    cout << pow(b) << endl;
    return 0;
}