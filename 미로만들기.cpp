#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

struct Coord
{
    Coord(int x, int y)
    : x(x)
    , y(y)
    {}

    bool OOB(int n)
    {
        return x < 0 || x >= n || y < 0 || y >= n;
    }

    Coord operator+(const Coord& other) const
    {
        return Coord(x + other.x, y + other.y);
    }

    int x;
    int y;
};

static const vector<Coord> dirs = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

struct Compare
{
    typedef pair<Coord, int> T;
    bool operator()(const T& src, const T& dst)
    {
        return src.second > dst.second; 
    }
};

int main()
{
    freopen("../../input.txt", "r", stdin);
    freopen("../../output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    vector<string> whiteRoom(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> whiteRoom[i];
    }

    priority_queue<pair<Coord,int>, vector<pair<Coord, int>>, Compare> pq;
    vector<vector<int>> dist(n, vector<int>(n, INT32_MAX));

    pq.push({ Coord(0, 0), 0 }); 
    dist[0][0] = 0;

    while(!pq.empty())
    {
        Coord curr = pq.top().first;
        int currWeight = pq.top().second;
        pq.pop();

        for (auto& dir : dirs)
        {
            Coord next = curr + dir;
            
            if (next.OOB(n))
            {
                continue;
            }
            
            int nextWeight = currWeight + (whiteRoom[next.x][next.y] == '0' ? 1 : 0);
            if (dist[next.x][next.y] <= nextWeight)
            {
                continue;
            }

            dist[next.x][next.y] = nextWeight;
            pq.push({next, nextWeight});
        }
    }

    for (auto& line : dist)
    {
        for (auto& i : line)
        {
            cout << i << " ";
        }
        cout << endl;
    }
    cout << dist[n-1][n-1] << endl;

    return 0;
}