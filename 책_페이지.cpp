#include <iostream>
#include <vector>

using namespace std;

vector<int> answer(10, 0);

void calc(int n, int digit)
{
    while (n > 0)
    {
        answer[n % 10] += digit;
        n = n / 10;
    }
}

void solve(int a, int b, int digit)
{
    while (a % 10 != 0 && a <= b)
    {
        calc(a, digit);
        ++a;
    }

    if (a > b)
        return;

    while (b % 10 != 9 && a <= b)
    {
        calc(b, digit);
        --b;
    }

    int temp = b/10 - a/10 + 1;
    for (int i=0; i<10; ++i)
    {
        answer[i] += temp * digit;
    }

    solve(a / 10, b / 10, digit * 10);

}

int main()
{
    // freopen("../../input.txt", "r", stdin);
    int n;
    cin >> n;

    solve (1, n, 1);
    
    for (int i=0; i < 10; ++i)
    {
        cout << answer[i] << " ";
    }
    cout << endl;
    return 0;
}