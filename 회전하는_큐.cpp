#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int GetDistance(int n, int curr, int target, vector<bool>& isPopped)
{
    int countInc = 0;
    int cursor = curr;
    while (cursor != target)
    {
        if (!isPopped[cursor])
        {
            ++countInc;
        }
        ++cursor;
        cursor = cursor % n;
    }

    int countDec = 0;
    cursor = curr;
    while (cursor != target)
    {
        if (!isPopped[cursor])
        {
            ++countDec;
        }
        --cursor;
        cursor = (cursor + n ) % n;
    }

    return min(countInc, countDec);
}

int main()
{
    freopen("../../input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<bool> isPopped(n, false);
    int curr = 0;
    int answer = 0;
    for (int i = 0; i < m; ++i)
    {
        int target;
        cin >> target;
        --target;

        int temp = GetDistance(n, curr, target, isPopped);
        answer += temp;
        isPopped[target] = true;
        curr = (target + 1) % n;
        while (isPopped[curr] && curr != target)
        {
            curr = (curr + 1) % n;
        }
        // cout << "curr: " << curr << ", temp: " << temp << endl;
    }

    cout << answer << endl;

    return 0;
}
