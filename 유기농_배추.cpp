#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Coord
{
    Coord() = default;
    Coord(int _x, int _y)
        : x(_x)
        , y(_y)
    {}

    int x;
    int y;

    bool Check_OutOfBoundary(int height, int width) const
    {
        return x < 0 || x >= height || y < 0 || y >= width;
    }

    Coord operator+(const Coord& other) const
    {
        return Coord{x + other.x, y + other.y};
    }
};

void FloodFill(vector<vector<bool>>& field, const int height, const int width, Coord start)
{
    static const vector<Coord> dirs = { {0,1}, {1, 0}, {0, -1}, {-1, 0}};

    queue<Coord> q;
    q.push(start);
    field[start.x][start.y] = false;

    while (!q.empty())
    {
        Coord curr = q.front();
        q.pop();
        
        for (auto& dir : dirs)
        {
            Coord next = dir + curr;

            if (next.Check_OutOfBoundary(height, width))
            {
                continue;
            }

            if (!field[next.x][next.y])
            {
                continue;
            }

            field[next.x][next.y] = false;
            q.push(next);
        }

    }
}

int solution(vector<vector<bool>>& field, const int height, const int width)
{       
    int answer = 0;
    for (int i=0; i<height; ++i)
    {
        for (int j=0; j<width; ++j)
        {
            if (field[i][j] == true)
            {
                ++answer;
                FloodFill(field, height, width, Coord{i, j});
            }
        }
    }

    return answer;
}

int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int numTestcase = 0;
    cin >> numTestcase;
    while (numTestcase--)
    {
        int width = 0;
        int height = 0;
        int k = 0;
        cin >> width >> height >> k;
        
        vector<vector<bool>> field(height, vector<bool>(width, false));
        for (int i=0; i<k; ++i)
        {
            int x, y;
            cin >> x >> y;

            field[y][x] = true;
        }

        cout << solution(field, height, width) << endl;
    }

    return 0;
}
