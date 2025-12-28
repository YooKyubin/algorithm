#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

int main()
{
    freopen("../../input.txt", "r", stdin);
    // freopen("../../output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<pair<int, int>> meetings(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> meetings[i].first >> meetings[i].second;
    }
    sort(meetings.begin(), meetings.end(), [](auto &src, auto &dst) -> bool 
    {
        if (src.first == dst.first)
        {
            return src.second < dst.second;
        }
        return src.first < dst.first;
    });

    priority_queue<int, vector<int>, greater<int>> meetingEnd;
    meetingEnd.push(meetings.front().second);

    for (int i = 1; i < n; ++i)
    {
        const pair<int, int>& currMeet = meetings[i];

        if (currMeet.first >= meetingEnd.top())
        {
            meetingEnd.pop();
        }
        meetingEnd.push(currMeet.second);
    }

    cout << meetingEnd.size() << endl;

    return 0;
}