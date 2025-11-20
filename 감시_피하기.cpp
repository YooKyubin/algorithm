#include <iostream>
#include <vector>
#include <set>

using namespace std;

// 15:03

struct Coord
{
    Coord(int x, int y)
    : x(x)
    , y(y)
    {}

    int x;
    int y;

    bool OOB(int n ) const
    {
        return x < 0 || x >= n || y < 0 || y >= n;
    }

    Coord operator+(const Coord& other) const
    {
        return Coord(x + other.x, y + other.y);
    }

    bool operator<(const Coord& other) const
    {
        if (x == other.x)
        {
            return y < other.y;
        }
        return x < other.x;
    }
};

const vector<Coord> dirs = 
{
    Coord(0, 1),
    Coord(0, -1),
    Coord(1, 0),
    Coord(-1, 0),
};

bool CanHide(
        vector<Coord>& obstacles, 
        const vector<vector<char>>& board, 
        vector<Coord> teachers)
{
    vector<vector<char>> testBoard = board;
    for (auto& obstacle : obstacles)
    {
        testBoard[obstacle.x][obstacle.y] = 'O';
    }

    for (const Coord& teacher : teachers)
    {
        for (const Coord& dir : dirs)
        {
            Coord curr = teacher;
            while (true)
            {   
                curr = curr + dir;

                if (curr.OOB(board.size()))
                {
                    break;
                }

                if (testBoard[curr.x][curr.y] == 'O')
                {
                    break;
                }

                if (testBoard[curr.x][curr.y] == 'S')
                {
                    // cout << "look student" << endl;
                    return false;
                }
            }
        }
    }

    return true;
}

bool Combination(
        int curr, 
        const vector<Coord>& candidates, 
        vector<Coord>& obstacles, 
        const vector<vector<char>> board,
        vector<Coord> teachers)
{
    if (obstacles.size() == 3)
    {
        return CanHide(obstacles, board, teachers);
    }

    bool result = false;
    for (int i = curr + 1; i < candidates.size(); ++i)
    {
        obstacles.push_back(candidates[i]);
        result |= Combination(i, candidates, obstacles, board, teachers);
        obstacles.pop_back();
    }

    return result;
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<vector<char>> board(n, vector<char>(n));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            cin >> board[i][j];
        }
    }

    vector<Coord> teachers;
    vector<Coord> students;
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (board[i][j] == 'T')
            {
                teachers.push_back(Coord(i, j));
            }
            else if (board[i][j] == 'S')
            {
                students.push_back(Coord(i, j));
            }
        }
    }

    set<Coord> candidates;
    for (const Coord& teacher : teachers)
    {
        for (const Coord& dir : dirs)
        {
            Coord curr = teacher;
            bool canLookStudent = false;
            while (true)
            {   
                curr = curr + dir;

                if (curr.OOB(n))
                {
                    break;
                }

                if (board[curr.x][curr.y] == 'S')
                {
                    canLookStudent = true;
                    break;
                }

                candidates.insert(curr);
            }
        }
    }

    vector<Coord> vecCandidate;
    vecCandidate.reserve(candidates.size());
    for (auto& coord : candidates)
    {
        vecCandidate.push_back(coord);
    }

    vector<Coord> obstacles;
    if (Combination(-1, vecCandidate, obstacles, board, teachers))
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }

    return 0;
}