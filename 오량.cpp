#include <iostream>
#include <vector>

using namespace std;

int main()
{
    freopen("../../input.txt", "r", stdin);
    freopen("../../output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    
    constexpr int MOD = 1e9 + 7;
    // constexpr int MOD = 1'000'000'000 + 7;
    
    vector<vector<int>> combination(2001);
    for (int i = 0; i <= 2000; ++i)
    {
        combination[i].assign(i + 1, 1);
        // combination[i][0] = 1;
        // combination[i][i] = 1;
        
        for (int j = 1; j < i; ++j)
        {
            combination[i][j] = ((long long)combination[i-1][j-1] + combination[i-1][j]) % MOD;
        }
    }

    int t;
    cin >> t;

    while(t--)
    {
        int n;
        cin >> n;

        vector<int> notes(n, 0);
        bool AllOne = true;
        for (int i = 0; i < n; ++i)
        {
            cin >> notes[i];

            AllOne &= notes[i] == 1;
        }
        if (AllOne)
        {
            cout << 1 << "\n";
        }
        else
        {
            int left = n;
            long long numCase = 1;
            for (int i = 0; i < n; ++i)
            {
                int numNote = notes[i];
    
                numCase *= combination[left][numNote];
                numCase %= MOD;
                left -= numNote;
            }
    
            cout << numCase << "\n";
        }
        
    }

    return 0;
}