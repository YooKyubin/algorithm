#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// 19 : 03

int main()
{
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<pair<int, int>> lectures(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> lectures[i].first >> lectures[i].second;
    }

    sort(lectures.begin(), lectures.end());
    priority_queue<int, vector<int>, greater<int>> pq;

    for (auto& curr : lectures)
    {
        if (pq.empty())
        {
            pq.push(curr.second);
            continue;
        }

        int closeEndTime = pq.top();
        if (closeEndTime <= curr.first)
        {
            pq.pop();
        }
        pq.push(curr.second);
    }

    cout << pq.size() << endl;

    return 0;
}