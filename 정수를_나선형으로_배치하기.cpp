#include <string>
#include <vector>

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

    Coord operator+(const Coord& other) const
    {
        return Coord(x + other.x, y + other.y);
    }

    bool IsOutOfBoundary(int n) const
    {
        return x < 0 || x >= n || y < 0 || y >= n;
    }
};

void FillWithDFS(int n, vector<vector<int>>& answer, const Coord& curPosition, int depth, int dirIndex)
{
    static const vector<Coord> dirs {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    answer[curPosition.x][curPosition.y] = depth;

    for (int i=0; i<4; ++i)
    {
        int nextDirIndex = (dirIndex + i) % 4;
        const Coord& dir = dirs[nextDirIndex];
        const Coord nextPosition = curPosition + dir;
        

        if (nextPosition.IsOutOfBoundary(n))
        {
            continue;
        }

        bool isVisited = 0 != answer[nextPosition.x][nextPosition.y];
        if (isVisited)
        {
            continue;
        }

        FillWithDFS(n, answer, nextPosition, depth + 1, nextDirIndex);
    }
}

vector<vector<int>> solution(int n) {
    vector<vector<int>> answer;

    answer.assign(n, vector<int>(n, 0));

    const Coord startPosition(0, 0);
    int depth = 1;
    int dirIndex = 0;
    FillWithDFS(n, answer, startPosition, depth, dirIndex);

    return answer;
}

void PrintArr(const vector<vector<int>>& answer)
{
    for (auto& line : answer)
    {
        for (int i : line)
        {
            cout << i << "\t";
        }
        cout << endl;
    }

    cout << "================" << endl;
}

int main()
{       
    PrintArr(solution(4));

    PrintArr(solution(5));
    return 0;
}