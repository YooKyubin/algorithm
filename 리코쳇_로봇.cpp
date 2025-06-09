#include <string>
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

struct Coord
{
    Coord() = default;
    Coord(int _x, int _y)
        : x(_x)
        , y(_y)
    {}

    int x = 0;
    int y = 0;

    Coord operator+(const Coord& other)
    {
        return Coord{ x + other.x, y + other.y };
    }
    bool operator==(const Coord& other)
    {
        return x == other.x && y == other.y;
    }
    bool CheckOutOfBoundary(int h, int w)
    {
        return x < 0 || x >= h || y < 0 || y >= w;
    }
};

static const vector<Coord> dirs = { {0,1}, {1,0}, {-1, 0}, {0, -1} };

Coord Find(char target, const vector<string>& board)
{
    const int height = board.size();
    const int width = board.back().size();
    for (int i=0; i< height; ++i)
    {
        for (int j=0; j<width; ++j)
        {
            if (board[i][j] == target)
            {
                return Coord{i , j};
            }
        }
    }
    return Coord();
}

int solution(vector<string> board) {
    int answer = -1;

    const int height = board.size();
    const int width = board.back().size();

    Coord start = Find('R', board);
    Coord goal = Find('G', board);

    queue<pair<Coord, int> > q;
    vector<vector<vector<int>>> isVisited; //[height][width][dir]
    isVisited.assign(height, vector<vector<int>>(width, vector<int>(4, -1)));

    q.emplace(start, 0);
    isVisited[start.x][start.y] = {0, 0, 0, 0};

    while (!q.empty())
    {
        Coord curr = q.front().first;
        int currDist = q.front().second;
        q.pop();

        if (curr == goal)
        {
            if (answer == -1)
            {
                answer = currDist;
            }
        }

        for (int i=0; i<4; ++i)
        {
            const Coord& dir = dirs[i];

            Coord next = curr;
            while (true)
            {
                Coord test = next + dir;

                // 보드 경계 밖이라면
                if (test.CheckOutOfBoundary(height, width))
                {
                    break;
                }

                // 막힌 길이면
                if (board[test.x][test.y] == 'D')
                {
                    break;
                }

                // 이미 간 적이 있으면
                bool isFirstAccess = isVisited[test.x][test.y][i] == -1;
                bool isExistFasterWay = isVisited[test.x][test.y][i] <= currDist + 1;
                if (!isFirstAccess && isExistFasterWay)
                {
                    // 이 방향으로 갈 필요조차 없음
                    next = curr;
                    break;
                }

                next = test;
                isVisited[next.x][next.y][i] = currDist + 1;
            }
            // 움직이지 않았으면
            if (next == curr)
            {
                continue;
            }

            if (next == goal)
            {   
                int a= 0;
                ++a;
            }
            q.emplace(next, currDist + 1);
        }
    }

    return answer;
}

// #include <iostream>

int main()
{
    vector<string> board = 
        { 
            ".....GR", 
            "D......", 
            "D......", 
            "......D", 
            ".D.D..." 
        };
    cout <<solution(board) << endl;
    return 0;
}