#include <iostream>
#include <vector>

using namespace std;

int W(int a, int b, int c)
{
    static int memo[21][21][21] {};

    if (a <= 0 || b <= 0 || c <= 0)
    {
        return memo[0][0][0] = 1;
    }

    if (a > 20 || b > 20 || c > 20)
    {
        return memo[20][20][20] = W(20, 20, 20);
    }

    if (memo[a][b][c] != 0)
    {
        return memo[a][b][c];
    }

    if (a < b && b < c)
    {
        int cache = memo[a][b][c] = W(a, b, c-1) + W(a, b-1, c-1) - W(a, b-1, c);
        return cache; 
    }

    return memo[a][b][c] = W(a-1, b, c) + W(a-1, b-1, c) + W(a-1, b, c-1) - W(a-1, b-1, c-1);
}

int main()
{
    freopen("../../input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int a, b, c;
    while (true)
    {
        cin >> a >> b >> c;

        if (a == -1 && b == -1 && c == -1)
        {
            break;
        }

        int result = W(a, b, c);
        printf("w(%d, %d, %d) = %d\n", a, b, c, result);
    }

    return 0;
}
