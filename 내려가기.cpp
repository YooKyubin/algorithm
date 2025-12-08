#include <vector>
#include <iostream>
#include <array>
#include <algorithm>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<array<int, 3>> numbers(n); 
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            cin >> numbers[i][j];
        }
    }

    vector<int> maxDP(3, 0);
    vector<int> maxNextDP(3, 0);

    for (int i = 0; i < 3; ++i)
    {
        maxDP[i] = numbers[0][i];
    }

    for (int i = 1; i < n; ++i)
    {
        maxNextDP[0] = numbers[i][0] + max(maxDP[0], maxDP[1]);
        maxNextDP[1] = numbers[i][1] + max(max(maxDP[0], maxDP[1]), maxDP[2]);
        maxNextDP[2] = numbers[i][2] + max(maxDP[1], maxDP[2]);

        swap(maxDP, maxNextDP);
    }

    vector<int> minDP(3, 0);
    vector<int> minNextDP(3, 0);
    for (int i = 0; i < 3; ++i)
    {
        minDP[i] = numbers[0][i];
    }

    for (int i = 1; i < n; ++i)
    {
        minNextDP[0] = numbers[i][0] + min(minDP[0], minDP[1]);
        minNextDP[1] = numbers[i][1] + min(min(minDP[0], minDP[1]), minDP[2]);
        minNextDP[2] = numbers[i][2] + min(minDP[1], minDP[2]);

        swap(minDP, minNextDP);
    }

    cout << *max_element(maxDP.begin(), maxDP.end()) << " ";
    cout << *min_element(minDP.begin(), minDP.end()) << endl;

    return 0;
}