#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

struct Coord
{
    int x;
    int y;

    static int Distance(const Coord& src, const Coord& dst)
    {
        return abs(src.x - dst.x) + abs(src.y - dst.y);
    }
};

bool Solve(const vector<Coord>& coords)
{
    static const int maxDist = 20 * 50;
    queue<int> q;
    vector<bool> visited( coords.size(), false );

    q.push(0);
    visited[0] = true;

    while (!q.empty())
    {
        int currID = q.front();
        Coord curr = coords[currID];
        q.pop();

        for (size_t i = 0; i < coords.size(); ++i)
        {
            if (currID == i)
            {
                continue;
            }

            if (visited[i])
            {
                continue;
            }

            Coord next = coords[i];
            if (Coord::Distance(next, curr) > 20 * 50)
            {
                continue;
            }

            visited[i] = true;
            q.push(i);
        }
    }

    return visited.back();
}

int main()
{
    freopen("../../input.txt", "r", stdin);
    // freopen("../../output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int t;
    cin >> t;
    while (t--)
    {
        int n;
        cin >> n;

        vector<Coord> coords(n + 2);
        for (int i = 0; i < n + 2; ++i)
        {
            cin >> coords[i].x >> coords[i].y;
        }

        cout << ( Solve(coords) ? "happy" : "sad" ) << "\n";
    }

    return 0;
}