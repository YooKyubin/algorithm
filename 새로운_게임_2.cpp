#include <iostream>
#include <vector>

#define MAXCNT 1000

using namespace std;

struct ChessPiece
{
    int x;
    int y;
    int z;
    int d;
};

vector<vector<int>> board;
vector<vector<int>> heightMap;
vector<vector<vector<int>>> space;
vector<ChessPiece> chessPieces;
vector<pair<int, int>> dir { {0, 1}, {0, -1}, {-1, 0}, {1, 0} };
int n, k;

bool OOB(int x, int y)
{
    return x < 0 || x >= n || y < 0 || y >= n;
}

void Turn(int it, bool& endCondition)
{
    ChessPiece& cur = chessPieces[it];
    int nx = cur.x + dir[cur.d].first;
    int ny = cur.y + dir[cur.d].second;


    vector<int> temp;
    int interval = heightMap[cur.x][cur.y] - cur.z;
    for (int it = 0; it < interval; ++it)
    {
        temp.push_back(space[cur.x][cur.y].back());
        space[cur.x][cur.y].pop_back();
        --heightMap[cur.x][cur.y];
    }

    if (OOB(nx, ny) || board[nx][ny] == 2) // board의 index 범위를 벗어난 경우를 최우선 처리해야함
    {
        // change dir
        cur.d % 2 == 0 ? ++cur.d : --cur.d; 
        nx = cur.x + dir[cur.d].first;
        ny = cur.y + dir[cur.d].second;
    }

    if (OOB(nx, ny) || board[nx][ny] == 2)
    {
        while(!temp.empty())
        {
            int t = temp.back();
            space[cur.x][cur.y].push_back(t);
            // chessPieces[t].x = cur.x;
            // chessPieces[t].y = cur.y;
            // chessPieces[t].z = heightMap[cur.x][cur.y];
            temp.pop_back();
            ++heightMap[cur.x][cur.y];
        }
    }

    else if (board[nx][ny] == 0)
    {
        while(!temp.empty())
        {
            int t = temp.back();
            space[nx][ny].push_back(t);
            chessPieces[t].x = nx;
            chessPieces[t].y = ny;
            chessPieces[t].z = heightMap[nx][ny];
            temp.pop_back();
            ++heightMap[nx][ny];
        }
    }

    else if (board[nx][ny] == 1)
    {
        for (int t : temp)
        {
            space[nx][ny].push_back(t);
            chessPieces[t].x = nx;
            chessPieces[t].y = ny;
            chessPieces[t].z = heightMap[nx][ny];
            ++heightMap[nx][ny];
        }
    }

    if (!OOB(nx,ny))
        if (heightMap[nx][ny] >= 4)
            endCondition = true;
}

void Input()
{
    cin >> n >> k;
    board.assign(n, vector<int>(n));
    heightMap.assign(n, vector<int>(n, 0));
    space.assign(n, vector<vector<int>>(n, vector<int>()));
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            cin >> board[i][j];
        }
    }
    
    chessPieces.reserve(k);
    for (int i=0; i<k; ++i)
    {
        int x, y, d;
        cin >> x >> y >> d;
        --x; --y; --d;
        chessPieces.push_back({x, y, 0, d});
        space[x][y].push_back(i);
        ++heightMap[x][y];
    }
}

int main()
{
    Input();
    
    int cnt = 0;
    bool endCondition = false;
    while (cnt <= MAXCNT)
    {
        for (int i=0; i<k; ++i)
        {
            Turn(i, endCondition);
        }
        ++cnt;

        if (endCondition)
            break;
    }

    if (cnt > MAXCNT)
        cnt = -1;
    cout << cnt << endl;
    return 0;
}