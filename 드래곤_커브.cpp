#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<pair<int, int>> dir { {1, 0}, {0, -1}, {-1, 0}, {0, 1} };

vector<vector<bool>> board(101, vector<bool>(101, false));

int countRectangle()
{
    int cnt = 0;
    for (int i=0; i<100; ++i)
    {
        for (int j=0; j<100; ++j)
        {
            if (board[i][j] && board[i][j+1] && board[i+1][j] && board[i+1][j+1])
                ++cnt;
        }
    }
    return cnt;
}
void CopyRotate(vector<pair<int, int>>& points)
{
    pair<int, int> endPoint = points.back();
    size_t length = points.size()-1;
    points.resize(points.size() + length);

    for (size_t i=0; i< length; ++i)
    {
        pair<int, int> p = points[i];
        int tpx = p.first - endPoint.first;
        int tpy = p.second - endPoint.second;

        int rpx = -tpy;
        int rpy = tpx;

        int rx = rpx + endPoint.first;
        int ry = rpy + endPoint.second;
        // points.push_back({rx, ry});
        points[points.size() - i - 1] = {rx, ry};
    }
}

void makeDragonCurve(int depth, int maxDepth, vector<pair<int, int>>& points)
{
    if (depth == maxDepth)
    {
        for (auto p : points)
        {
            board[p.first][p.second] = true;
        }
        return;
    }

    CopyRotate(points);
    makeDragonCurve(depth+1, maxDepth, points);
}

int main()
{
    freopen("../../input.txt", "r", stdin);

    int n;
    cin >> n;
    for (int i = 0; i < n; ++i)
    {
        int x, y, d, g;
        cin >> x >> y >> d >> g;
        vector<pair<int, int>> points;
        points.push_back({x, y});
        points.push_back({x + dir[d].first, y + dir[d].second});

        makeDragonCurve(0, g, points);

    }
    
    cout << countRectangle() << endl;
    // for (int i=0; i<10; ++i)
    // {
    //     for (int j=0; j<10; ++j)
    //     {
    //         cout << board[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    return 0;
}