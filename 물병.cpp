#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
    freopen("../../input.txt", "r", stdin);
    // freopen("../../output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, k;
    cin >> n >> k;

    int lastBit = 0;
    int cnt = 0;
    for (int i = 30; i >= 0; --i)
    {
        if (n & (1 << i))
        {
            ++cnt;

            if (cnt == k)
            {
                lastBit = i;
                break;
            }
        }
    }

    int mask = (1 << lastBit) - 1;
    int complement = -n; // 2's complement;
    int answer = complement & mask;
    cout << answer << endl;

    return 0;
}