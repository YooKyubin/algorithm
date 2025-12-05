#include <vector>
#include <iostream>
#include <string>
#include <queue>

using namespace std;

struct Coord
{
    Coord(int x, int y)
    : x(x)
    , y(y)
    {
    }

    Coord operator+(const Coord& other) const
    {
        return Coord(x + other.x, y + other.y);
    }

    bool OOB(int n, int m)
    {
        return x < 0 || x >= n || y < 0 || y >= m;
    }

    int x;
    int y;
};

const static vector<Coord> dirs = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };

struct Node
{
    Node(int weight, Coord coord)
    : weight(weight)
    , coord(coord)
    {
    }

    int weight;
    Coord coord;

    bool operator>(const Node& other) const
    {
        return weight > other.weight;
    }
};

int main()
{
    // freopen("input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    swap(n, m);

    vector<string> miro(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> miro[i];
    }

    Coord start(0, 0);

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    vector<vector<int>> dist(n, vector<int>(m, n * m + 1));
    pq.push({0, start});
    dist[start.x][start.y] = 0;

    while (!pq.empty())
    {
        Coord curr = pq.top().coord;
        int currWeight = pq.top().weight;
        pq.pop();

        for (auto& dir : dirs)
        {
            Coord next = curr + dir;
            int nextWeight = currWeight;

            if (next.OOB(n, m))
            {
                continue;
            }

            if (miro[next.x][next.y] == '1')
            {
                ++nextWeight;
            }

            if (dist[next.x][next.y] <= nextWeight)
            {
                continue;
            }

            dist[next.x][next.y] = nextWeight;
            pq.push(Node(nextWeight, next));
        }
    }

    cout << dist[n-1][m-1] << endl;

    return 0;
}