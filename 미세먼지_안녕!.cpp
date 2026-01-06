#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Coord
{
    int x;
    int y;

    Coord operator+(const Coord& other) const
    {
        return { x + other.x, y + other.y };
    }

    bool OOB(int r, int c)
    {
        return x < 0 || x >= r || y < 0 ||y >= c;
    }
};

const static vector<Coord> dirs = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

vector<vector<int>> Spread(int r, int c, const vector<vector<int>>& room, int cleaner)
{
    vector<vector<int>> spreaded(r, vector<int>(c, 0));

    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            if (room[i][j] <= 0)
            {
                continue;
            }

            Coord curr{i, j};
            int cnt = 0;
            int spreadAmount = room[i][j] / 5;
            for (auto& dir : dirs)
            {
                Coord next = curr + dir; 

                if (next.OOB(r,c))
                {
                    continue;
                }

                if (room[next.x][next.y] == -1)
                {
                    continue;
                }

                ++cnt;
                spreaded[next.x][next.y] += spreadAmount;
            }
            spreaded[i][j] += room[i][j] - spreadAmount * cnt;
        }
    }

    spreaded[cleaner][0] = -1;
    spreaded[cleaner + 1][0] = -1;

    return spreaded;
}

vector<vector<int>> Circulate(int r, int c, const vector<vector<int>>& room, int cleaner)
{
    // vector<vector<int>> circulatedRoom(r, vector<int>(c, 0));
    auto circulatedRoom = room;

    int upper = cleaner;
    for (int i = upper-1; i >= 1; --i)
    {
        circulatedRoom[i][0] = room[i-1][0];
    }
    for (int i = 0; i < c-1; ++i)
    {
        circulatedRoom[0][i] = room[0][i+1];
    }
    for (int i = 0; i < upper; ++i)
    {
        circulatedRoom[i][c-1] = room[i+1][c-1];
    }
    for (int i = c-1; i >= 1; --i)
    {
        circulatedRoom[upper][i] = room[upper][i-1];
    }

    int lower = cleaner + 1;
    for (int i = lower+1; i < r -1; ++i)
    {
        circulatedRoom[i][0] = room[i+1][0];
    }
    for (int i = 0; i < c-1; ++i)
    {
        circulatedRoom[r-1][i] = room[r-1][i+1];
    }
    for (int i = r-1; i >= lower; --i)
    {
        circulatedRoom[i][c-1] = room[i-1][c-1];
    }
    for (int i = c-1; i >= 1; --i)
    {
        circulatedRoom[lower][i] = room[lower][i-1];
    }

    circulatedRoom[cleaner][1] = 0;
    circulatedRoom[cleaner + 1][1] = 0;

    circulatedRoom[cleaner][0] = -1;
    circulatedRoom[cleaner + 1][0] = -1;

    return circulatedRoom;
}

int main()
{
    freopen("../../input.txt", "r", stdin);
    // freopen("../../output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);
    
    int r, c, t;
    cin >> r >> c >> t;

    vector<vector<int>> room(r, vector<int>(c));
    for (int i = 0; i < r; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            cin >> room[i][j];
        }
    }

    int cleaner = 0;
    for (int i = 0; i < r; ++i)
    {
        if (room[i][0] == -1)
        {
            cleaner = i;
            break;
        }
    }
    
    while (t--)
    {
        room = Spread(r, c, room, cleaner);
        room = Circulate(r, c, room, cleaner);
    }

    int answer = 0;
    for (auto& line : room)
    {
        for (int i : line)
        {
            answer += i;
        }
    }
    answer += 2;
    cout << answer << endl;

    return 0;
}