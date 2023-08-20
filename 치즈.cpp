#include <iostream>
#include <vector>
#include <queue>

#define x first
#define y second

using namespace std;

int w, h;
vector<vector<int>> plate;
vector<pair<int, int>> buffer;
vector<pair<int, int>> dir { {0,1}, {1,0}, {-1, 0}, {0, -1} };

bool OOB(int x, int y) { return x < 0 || x >= h || y < 0 || y >= w; }

void find()
{
    queue<pair<int, int>> q;
    vector<vector<bool>> visited(h, vector<bool>(w, false));
    int cnt = 1;
    q.push({0, 0});
    visited[0][0] = true;

    while(!q.empty())
    {
        pair<int, int> cur = q.front();
        q.pop();

        for (int i=0; i<4; ++i)
        {
            int nx = cur.x + dir[i].x;
            int ny = cur.y + dir[i].y;

            if (OOB(nx, ny) || visited[nx][ny])
                continue;

            if (plate[nx][ny] == 0)
                q.push({nx, ny});

            else
                buffer.push_back({nx, ny});
            
            visited[nx][ny] = true;
        }
    }

}

int melt()
{
    for (auto pos : buffer)
        plate[pos.x][pos.y] = 0;

    return buffer.size();
}

bool checkEnd()
{
    for (int i=0; i<h; ++i)
    {
        for (int j=0; j<w; ++j)
        {
            if (plate[i][j] == 1)
                return false;
        }
    }

    return true;
}

int main()
{
    cin >> h >> w;
    plate.assign(h, vector<int>(w));
    for (int i=0; i<h; ++i)
    {
        for (int j=0; j<w; ++j)
        {
            cin >> plate[i][j];
        }
    }
    
    int time = 0;
    int last;
    while(!checkEnd())
    {
        find();

        last = melt();

        buffer.clear();
        ++time;
    }

    cout << time << endl;
    cout << last << endl;
    return 0;
}

/*
아니 이거 끝인지 아닌지 확인하는 작업에서 시간 줄이려고 했는데 굳이 그럴 필요가 없는게 속상하네
반례 :
5 5
0 0 0 0 0
0 1 1 0 0
0 1 0 1 0
0 1 1 1 0
0 0 0 0 0
*/