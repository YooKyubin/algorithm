#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Snake
{
    vector<pair<int, int>> body = {{0,0}};
    int head = 0;
    int tail = 0;
    int d = 0; // right
};

vector<pair<int, int>> dir { { 0, 1 }, {-1, 0 }, { 0,-1 }, { 1, 0 } }; //ccw

int n, k, l;
vector<vector<int>> board;
vector<pair<int, int>> command;

bool OOB(int x, int y)
{
    return x < 0 || x >= n || y < 0 || y >= n;
}

void Print(int t)
{
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            cout << board[i][j] << " ";
        }

        if (i == n-1)
            cout << t;

        cout << endl;
    }
    cout << endl;
}

int main()
{
    freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n;
    board.resize(n, vector<int>(n,0));

    cin >> k;
    for (int i=0; i<k; ++i)
    {
        int x, y;
        cin >> x >> y;
        board[x-1][y-1] = 1;
    }

    cin >> l;
    for (int i=0; i<l; ++i)
    {
        int x;
        char c;
        cin >> x >> c;
        if (c == 'L')
        {
            command.push_back({x, 1});
        }
        else
        {
            command.push_back({x, 3});
        }

    }

    int time = 0;
    int commandIdx = 0;
    Snake snake;
    snake.body.reserve(10000);
    board[0][0] = 2;
    while (true)
    {
        if (commandIdx < l && command[commandIdx].first == time)
        {
            snake.d += command[commandIdx].second;
            snake.d = snake.d % 4;
            ++commandIdx;
        }

        // move
        int nx = snake.body.back().first + dir[snake.d].first;
        int ny = snake.body.back().second + dir[snake.d].second;

        snake.body.push_back({nx, ny});
        snake.head += 1;

        ++time;

        if (OOB(nx, ny))
        {
            break;
        }

        if (board[nx][ny] == 2)
        {
            break;
        }

        if (board[nx][ny] == 0)
        {
            pair<int, int> tailPos = snake.body[snake.tail];
            board[tailPos.first][tailPos.second] = 0;
            snake.tail += 1;
        }

        board[nx][ny] = 2;

        // Print(time);
    }

    cout << time << endl;

    return 0;
}