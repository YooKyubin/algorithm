#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int w, h;
vector<vector<int>> sandCastle;
vector<pair<int, int>> buffer;
vector<pair<int, int>> dir { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
int cnt = 0;

bool OOB(int x, int y)
{
    return x < 0 || x >= h || y < 0 || y >= w;
}

void bfs()
{
    queue<pair<int, int>> q;
    for (auto i : buffer)
        q.push(i);

    buffer.clear();

    while(!q.empty())
    {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        for (auto d : dir)
        {
            int nx = d.first + x;
            int ny = d.second + y;

            if (OOB(nx, ny))
                continue;

            --sandCastle[nx][ny];
            if (sandCastle[nx][ny] == 0)
                buffer.push_back({nx, ny});

        }
    }
}

int main() 
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> h >> w;
    sandCastle.resize(h);
    for (int i=0; i<h; ++i)
    {
        sandCastle[i].reserve(w);
        string input;
        cin >> input;
        for (auto c : input)
        {
            if (c == '.')
                sandCastle[i].push_back(0);
            else
                sandCastle[i].push_back(c - '0');
        }
    }

    for (int i=0; i < h; ++i)
    {
        for (int j=0; j <w; ++j)
        {
            if (sandCastle[i][j] == 0)
                buffer.push_back({i, j});
        }
    }

    while (true)
    {
        bfs();
        if (buffer.size() == 0)
            break;
        ++cnt;
    }
    
    cout << cnt << endl;

    return 0;
}