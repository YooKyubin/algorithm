#include <string>
#include <vector>
#include <queue>

#include <iostream>

using namespace std;

#define _MAX_NUM (100 * 100)
#define MAX_NUM _MAX_NUM

struct Position
{
    Position() = default;
    Position(int _x, int _y)
        : x(_x)
        , y(_y)
    {}
    int x;
    int y;

    Position operator+(const Position& other) const
    {
        return Position(x + other.x, y + other.y);
    }

    bool operator==(const Position& other) const
    {
        return (x == other.x) && (y == other.y);
    }
};

const vector<Position> dirs { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

int ComputeStepCount(const Position& from, const Position& to, const vector<string>& maps)
{
    const int height = maps.size();
    const int width = maps[0].size();

    queue<Position> BfsQueue;
    vector<vector<int>> stepCountTable(height);
    for (auto& line : stepCountTable)
    {
        line.assign(width, MAX_NUM);
    }

    BfsQueue.push( from );
    stepCountTable[from.x][from.y] = 0;

    while (false == BfsQueue.empty())
    {
        Position curPos = BfsQueue.front();
        int curStepCount = stepCountTable[curPos.x][curPos.y];
        BfsQueue.pop();

        for (const Position& dir : dirs)
        {
            Position nextPos = curPos + dir;
            int x = nextPos.x;
            int y = nextPos.y;
            int nextStepCount = curStepCount + 1;

            bool isOutOfBoudary = x < 0 || x >= height || y < 0 || y >= width;
            if (isOutOfBoudary)
            {
                continue;
            }

            bool isBlocked = ('X' == maps[x][y]);
            bool isVisited = stepCountTable[x][y] <= nextStepCount;
            if (isBlocked || isVisited)
            {
                continue;
            }

            if (nextPos == to)
            {
                return nextStepCount;
            }

            BfsQueue.push( nextPos );
            stepCountTable[x][y] = nextStepCount;
        }
    }

    return -1;
}

int solution(vector<string> maps) {
    int answer = 0;

    Position startPos;
    Position leverPos;
    Position exitPos;

    // 위치 뽑기
    for (size_t i=0; i<maps.size(); ++i)
    {
        for (size_t j = 0; j < maps[i].size(); ++j)
        {
            switch (maps[i][j])
            {
            case 'S':
                startPos = Position(i, j);
                break;

            case 'L':
                leverPos = Position(i, j);
            break;

            case 'E':
                exitPos = Position(i, j);
            break;
            }
        }
    }

    // start -> lever 이동 계산
    int startToLeverCount = ComputeStepCount(startPos, leverPos, maps);
    if (-1 == startToLeverCount)
        return -1;

    int leverToExitCount = ComputeStepCount(leverPos, exitPos, maps);
    if (-1 == leverToExitCount)
        return -1;

    answer = startToLeverCount + leverToExitCount;
    return answer;
}

int main()
{
    vector<string> maps = 
        {"LOOXS","OOOOX","OOOOO","OOOOO","EOOOO"};
    cout << solution(maps) << endl;

    return 0;
}