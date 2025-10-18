#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Coord
{
    int x;
    int y;

    Coord operator+(const Coord& other) const
    {
        return { x + other.x, y + other.y };
    }
};

bool OOB(const Coord& coord, int n, int m)
{
    return coord.x < 0 || coord.x >= n || coord.y < 0 || coord.y >= m;
}

int CountPicture(
        Coord start,
        const vector<vector<bool>>& paper, 
        vector<vector<bool>>& visited, 
        int n, int m)
{
    static const vector<Coord> dirs = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

    int count = 0;

    queue<Coord> q;
    q.push(start);
    visited[start.x][start.y] = true;

    while(!q.empty())
    {
        Coord curr = q.front();
        q.pop();
        ++count;

        for (auto& dir : dirs)
        {
            Coord next = curr + dir;
            if (OOB(next, n, m)) 
            {
                continue;
            }

            if (false == paper[next.x][next.y])
            {
                continue;
            }

            if (visited[next.x][next.y])
            {
                continue;
            }

            q.push(next);
            visited[next.x][next.y] = true;
        }
    }
    return count;
}

int main()
{
    freopen("../../input.txt", "r", stdin);

    cin.tie(nullptr); 
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<vector<bool>> paper(n, vector<bool>(m, false));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            bool isPicture;
            cin >> isPicture;
            paper[i][j] = isPicture;
        }
    }

    vector<vector<bool>> visited(n, vector<bool>(m, false));
    vector<int> pictureSizes;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if(false == visited[i][j] && true == paper[i][j])
            {
                int size = CountPicture({i, j}, paper, visited, n, m);
                pictureSizes.push_back(size);
            }
        }
    }
    
    int numPicture = (int)pictureSizes.size();
    int maxSize = 0;
    if (numPicture > 0)
    {
        maxSize = *max_element(pictureSizes.begin(), pictureSizes.end());
    }
    cout << numPicture << endl;
    cout << maxSize << endl;

    return 0;
}
