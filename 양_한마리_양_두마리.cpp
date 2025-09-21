#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Vec
{
    int x;
    int y;

    Vec operator+(const Vec& other) const
    {
        return { x + other.x, y + other.y };
    }
};

bool OOB(Vec coord, int h, int w)
{
    return coord.x < 0 || coord.x >= h || coord.y < 0 || coord.y >= w;
}

void FloodFill(Vec start, const vector<vector<char>>& board, vector<vector<bool>>& visited, int h, int w)
{
    const static vector<Vec> dirs = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

    queue<Vec> q;
    q.push(start); 
    visited[start.x][start.y];

    while(!q.empty())
    {
        Vec curr = q.front();
        q.pop();

        for (Vec d : dirs)
        {
            Vec next = curr + d;

            if (OOB(next, h, w))
            {
                continue;
            }

            if (visited[next.x][next.y])
            {
                continue;   
            }

            if (board[next.x][next.y] == '.')
            {
                continue;
            }

            q.push(next);
            visited[next.x][next.y] = true;
        }
    }
}

int solution(int h, int w, const vector<vector<char>>& board)
{
    int answer = 0;

    vector<vector<bool>> visited(h, vector<bool>(w, false));
    for (int i=0; i < h; ++i)
    {
        for (int j=0; j < w; ++j)
        {
            if (!visited[i][j] && board[i][j] == '#')
            {
                FloodFill({ i, j }, board, visited, h, w);
                ++answer;
            }
        }
    }

    return answer;
}

int main()
{
    freopen("../../input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int testcase = 0;
    cin >> testcase;

    while(testcase--)
    {
        int w, h;
        cin >> h >> w;

        vector<vector<char>> board(h, vector<char>(w));
        for (int i = 0; i< h; ++i)
        {
            for (int j = 0; j < w; ++j)
            {
                cin >> board[i][j];
            }
        }

        cout << solution(h, w, board) << "\n";
    }

    return 0;
}