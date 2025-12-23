#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    constexpr int div = 15746;

    int n;
    cin >> n;

    vector<int> solutions(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> solutions[i];
    }
    sort(solutions.begin(), solutions.end());

    int left = 0;
    int right = n-1;
    int ph = solutions[left] + solutions[right];

    int captureLeft = left;
    int captureRight = right;
    int minAbsPH = abs(ph);

    while (left + 1 < right)
    {
        if (ph > 0)
        {
            ph -= solutions[right];
            --right;
            ph += solutions[right];
        }
        else if (ph < 0)
        {
            ph -= solutions[left];
            ++left;
            ph += solutions[left];
        }
        else
        {
            break;
        }

        if (minAbsPH > abs(ph))
        {
            captureLeft = left;
            captureRight = right;
            minAbsPH = abs(ph);
        }
    }

    cout << solutions[captureLeft] << " " << solutions[captureRight] << endl;

    return 0;
}