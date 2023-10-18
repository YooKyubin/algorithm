#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

struct Pos
{
    int x;
    int y;

    bool operator==(Pos input)
    {
        return x == input.x && y == input.y;
    }
    bool operator!=(Pos input)
    {
        return !(x == input.x && y == input.y);
    }
    Pos operator+(Pos input)
    {
        Pos ret;
        ret.x = x + input.x;
        ret.y = y + input.y;
        return ret;
    }
    Pos operator-(Pos input)
    {
        Pos ret;
        ret.x = x - input.x;
        ret.y = y - input.y;
        return ret;
    }
};

int n, m;
vector<vector<char>> board;
vector<Pos> dir { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
Pos red;
Pos blue;
Pos goal;

bool min(int a, int b) { return a < b ? a : b; }
int abs(int a) { return a > 0 ? a : -a; }

void Input()
{
    cin >> n >> m;
    board.resize(n, vector<char>(m));
    for (int i=0; i<n; ++i)
    {
        string line;
        cin >> line;
        for (int j=0; j<m; ++j)
        {
            board[i][j] = line[j];

            switch(line[j])
            {
                case 'R':
                    red = {i, j};
                    break;
                case 'B':
                    blue = {i, j};
                    break;
                case 'O':
                    goal = {i, j};
                    break;
                default:
                    break;
            }
        }
    }
}

int bfs()
{
    struct Params
    {
        Pos r;
        Pos b;
        int cnt;
    };

    queue<Params> q;
    q.push({red, blue, 0});
    int answer = -1;
    // vector<vector<bool>> redVisited(n, vector<bool>(m, false));
    // vector<vector<bool>> blueVisited(n, vector<bool>(m, false));
    bool visited[10][10][10][10];
    memset(visited, false, sizeof(visited));

    while(!q.empty())
    {
        Pos curRed = q.front().r;
        Pos curBlue = q.front().b;
        int curCnt = q.front().cnt;
        q.pop();

        if (curCnt > 10)
        {
            answer = -1;
            break;
        }

        if (curRed == goal && curBlue != goal)
        {
            answer = curCnt;
            break;
        }

        for (auto d : dir)
        {
            Pos nRed = curRed;
            Pos nBlue = curBlue;
            int redMove = 0;
            int blueMove = 0;
            
            while (true)
            {
                if (board[nRed.x][nRed.y] == '#')
                {
                    nRed = nRed - d;
                    break;
                }

                if (nRed == goal)
                    break;

                nRed = nRed + d;
                ++redMove;
            }

            while (true)
            {
                if (board[nBlue.x][nBlue.y] == '#')
                {
                    nBlue = nBlue - d;
                    break;
                }

                if (nBlue == goal)
                    break;

                nBlue = nBlue + d;
                ++blueMove;
            }

            if (blueMove == 0 && redMove == 0)
                continue;


            if (nRed != goal && nRed == nBlue) // 현재 위치가 구멍이라면 두 구슬이 같은 위치일 수 있음
            {
                if (blueMove > redMove)
                    nBlue = nBlue - d;
                else
                    nRed = nRed - d;
            }

            // if (blueVisited[nBlue.x][nBlue.y] && redVisited[nRed.x][nRed.y])
            //     continue;

            if (visited[nBlue.x][nBlue.y][nRed.x][nRed.y])
                continue;

            visited[nBlue.x][nBlue.y][nRed.x][nRed.y] = true;
            // blueVisited[nBlue.x][nBlue.y] = true;
            // redVisited[nRed.x][nRed.y] = true;

            q.push({nRed, nBlue, curCnt+1});
        }
    }

    return answer;
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    Input();

    cout << bfs() << endl;
    return 0;
}

/*
visited가 없다면 4^10 = 2^20 = 1048576 의 연산량이 발생한다.


아주 훌륭한 반례
8 8
########
#.####.#
#...#B##
#.##.R.#
######.#
##.##O.#
###.##.#
########

ans : 7

출처: https://www.acmicpc.net/board/view/76729
*/