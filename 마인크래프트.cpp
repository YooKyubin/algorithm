#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, m, b;
    cin >> n >> m >> b;

    vector<vector<int>> heights(n, vector<int>(m, 0));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            cin >> heights[i][j];
        }
    }
    
    int maxHeight = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j< m; ++j)
        {
            maxHeight = max(maxHeight, heights[i][j]);
        }
    }

    vector<int> times(maxHeight + 1, 0);
    vector<bool> validate(maxHeight + 1, false);
    for (int i = maxHeight; i >= 0; --i)
    {
        int tempB = b;
        for (auto& line : heights)
        {
            for (int height : line)
            {
                if ( i < height )
                {
                    int interval = height - i;
                    tempB += interval;
                    times[i] += 2 * interval;
                }
                else if (i > height)
                {
                    int interval = i - height;
                    tempB -= interval;
                    times[i] += 1 * interval;
                }
            }
        }

        if (tempB >= 0)
        {
            validate[i] = true;
        }
    }

    int minTime = INT32_MAX;
    int minTimeHeight = 0;
    for (int i = 0; i <= maxHeight; ++i)
    {
        if (validate[i])
        {
            if (minTime >= times[i])
            {
                minTime = times[i];
                minTimeHeight = i;
            }
        }
    }
    cout << minTime << " " << minTimeHeight << endl;

    return 0;
}