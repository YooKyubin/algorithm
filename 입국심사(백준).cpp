#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

bool CanPassAll(int m, long long time, const vector<int>& durations)
{
    long long numProcessed = 0;

    for (int duration : durations)
    {
        numProcessed += time / duration;
        if (numProcessed >= m)
        {
            return true;
        }
    }

    return false;
}

int main()
{
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    vector<int> durations(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> durations[i];
    }

    long long low = 0;
    long long high = (long long)(*max_element(durations.begin(),durations.end())) * m + 1;

    while (low + 1 < high)
    {
        long long mid = (low + high) >> 1;

        // m-1 m-1 m-1 m m m m+1 m+1
        if (CanPassAll(m, mid, durations))
        {
            high = mid;
        }
        else
        {
            low = mid;
        }
    }

    cout << high << endl;

    return 0;
}
