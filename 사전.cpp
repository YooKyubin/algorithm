#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string FindString(int n, int m, int k, const vector<vector<long long>>& pascalTriangle)
{
    int numA = n;
    int numZ = m;
    string answer;
    answer.reserve(n + m);
    for (int i = 0; i < n + m; ++i)
    {
        if (numA == 0 || numZ == 0)
        {
            break;;
        }

        int boundary = pascalTriangle[numA + numZ - 1][numA - 1];
        if (k <= boundary)
        {
            answer.push_back('a');
            --numA;
        }
        else
        {
            answer.push_back('z');
            k -= boundary;
            --numZ;
        }
    }

    for (int i = 0; i < numA; ++i)
    {
        answer.push_back('a');
    }
    for (int i = 0; i < numZ; ++i)
    {
        answer.push_back('z');
    }

    return answer;
}

int main()
{
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, m, k;
    cin >> n >> m >> k;

    constexpr long long MAX_K = 1000'000'000;

    vector<vector<long long>> pascalTriangle;
    pascalTriangle.push_back({1});
    pascalTriangle.push_back({1, 1});
    for (int i = 2; i <= n + m; ++i)
    {
        vector<long long> coef(i + 1, 1);
        for (int j = 1; j < i; ++j)
        {
            coef[j] = pascalTriangle[i-1][j-1] + pascalTriangle[i-1][j];
            coef[j] = min(coef[j], MAX_K);
        }
        pascalTriangle.push_back(coef);
    }

    if (pascalTriangle[n + m][n] < k)
    {
        cout << -1 << endl;
    }
    else
    {
        cout << FindString(n, m, k, pascalTriangle) << endl;
    }

    return 0;
}
