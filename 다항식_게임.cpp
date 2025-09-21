#include <iostream>
#include <vector>

using namespace std;

int main()
{
    freopen("../../input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int testcase = 0;
    cin >> testcase;

    const int length = 20;
    int maxCoef = (length * (length + 1)) / 2;

    vector<vector<long long>> coefs;
    coefs.reserve(21);
    coefs.push_back({1});
    coefs.push_back({1, 1});


    for (size_t i = 2; i <= length; ++i)
    {
        int lastLength = coefs.back().size();
        vector<long long> coef( lastLength + i, 0 );
        for (int j = 0; j <= i; ++j)
        {
            for (size_t k = 0; k < lastLength; ++k)
            {
                coef[j + k] += coefs.back()[k]; 
            }
        }
        coefs.push_back(coef);
    }

    while (testcase--)
    {
        int k, n;
        cin >> k >> n;

        cout << coefs[k][n] << "\n";
    }

    return 0;
}