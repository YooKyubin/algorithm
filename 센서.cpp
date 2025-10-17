#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    int k;
    cin >> k;

    vector<int> sensors(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> sensors[i];
    }
    sort(sensors.begin(), sensors.end());

    vector<int> intervals;
    intervals.reserve(n-1);
    for (int i = 0; i< n-1; ++i)
    {
        int src = sensors[i];
        int dst = sensors[i+1];
        intervals.push_back(dst - src);
    }
    sort(intervals.begin(), intervals.end(), greater<int>());

    int totalLength = sensors.back() - sensors.front();
    int sumIntervals = 0;

    for (int i = 0; i < min(k-1, n-1); ++i)
    {
        sumIntervals += intervals[i];
    }
    cout << totalLength - sumIntervals << endl;

    return 0;
}