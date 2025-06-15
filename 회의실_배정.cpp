#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    // freopen("../../input.txt", "r", stdin);

    int n;
    cin >> n;

    vector<pair<int, int>> meetings(n);
    for (int i=0; i<n; ++i)
    {
        cin >> meetings[i].first >> meetings[i].second;
    }

    sort(meetings.begin(), meetings.end(), [](const pair<int, int>& src, const pair<int, int>& dst)->bool
        {
            if (src.second == dst.second)
            {
                return src.first < dst.first;
            }
            return src.second < dst.second;
        });


    int endTime = 0;
    int numUsableMeeting = 0;
    for (auto& meeting : meetings)
    {
        if (meeting.first >= endTime)
        {
            endTime = meeting.second;
            ++numUsableMeeting;
        }
    }

    cout << numUsableMeeting << endl;

    return 0;
}