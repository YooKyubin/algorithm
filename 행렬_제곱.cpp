#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> operator*(vector<vector<int>>& a, vector<vector<int>>& b)
{
    int n = a.size();
    vector<vector<int>> ret(n, vector<int>(n));

    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            for (int k = 0; k<n; ++k)
            {
                ret[i][j] += (a[i][k] * b[k][j]);
                ret[i][j] %= 1000;
            }
        }
    }
    return ret;
}

vector<vector<int>> operator^(vector<vector<int>>& a, int64_t b)
{
    vector<vector<int>> ret;

    if (b == 1)
        return a;

    if (b % 2 == 0)
    {
        ret = a^(b/2);
        return ret * ret;
    }
    else
    {
        ret = a^(b-1);
        return ret * a;
    }
}

int main()
{
    int n;
    int64_t b;
    cin >> n >> b;
    vector<vector<int>> ans(n, vector<int>(n));
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            cin >> ans[i][j];
        }
    }

    ans = ans^b;

    for (int i=0; i<ans.size(); ++i)
    {
        for (int j=0; j<ans.size(); ++j)
        {
            cout << ans[i][j] % 1000 << " ";
        }
        cout << "\n";
    }
    return 0;
}