#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n, L;
vector<vector<int>> board;

bool checkRoad(const vector<int>& road, vector<bool>& ramp)
{
    int pre = 0;
    int cnt = 1;
    bool ret = true;
    for (int i=0; i<n-1; ++i)
    {
        int cur = road[i];
        int next = road[i+1];
        bool placeable = false;

        if (pre == cur)
            ++cnt;
        else
            cnt = 1;

        if (cnt >= L)
        {
            for (int j=i; j > i-L; --j)
            {
                if (ramp[j])
                {
                    placeable = false;
                    break;
                }
                placeable = true;
            }
        }

        if (next - cur > 1)
        {
            ret = false;
            break;
        }
        else if (next - cur == 1)
        {
            if (!placeable)
            {
                ret = false;
                break;
            }
            else
            {
                for(int j = i; j > i - L; --j)
                {
                    ramp[j] = true;
                }
            }
        }

        pre = cur;
    }

    return ret;
}

int main()
{
    // freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> L;
    board.resize(n, vector<int>(n));
    for (int i=0; i<n; ++i)
    {
        for(int j=0; j<n; ++j)
        {
            cin >> board[i][j];
        }
    }


    int cnt = 0;
    for (int i=0; i<n; ++i)
    {
        vector<int> row = board[i];
        vector<bool> ramp(n, false);

        bool result = checkRoad(row, ramp);
        reverse(row.begin(), row.end());
        reverse(ramp.begin(), ramp.end());
        result = result && checkRoad(row, ramp);

        if (result)
        {
            // cout << "row : " << i << endl;
            ++cnt;
        }
    }

    for (int i=0; i<n; ++i)
    {
        vector<int> col(n);
        for (int j=0; j<n; ++j)
        {
            col[j] = board[j][i];
        }
        vector<bool> ramp(n, false);

        bool result = checkRoad(col, ramp);
        reverse(col.begin(), col.end());
        reverse(ramp.begin(), ramp.end());
        result = result && checkRoad(col, ramp);

        if (result)
        {
            // cout << "col : " << i << endl;
            ++cnt;
        }
    }

    cout << cnt << endl;

    return 0;
}