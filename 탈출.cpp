#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

struct Coord
{
    Coord() = default;
    Coord(int x, int y)
    : x(x)
    , y(y)
    {
    }

    Coord operator+(const Coord& other) const
    {
        return Coord(x + other.x, y + other.y);
    }

    bool OOB(const vector<string>& board)
    {
        int r = board.size();
        int c = board[0].size();

        return x < 0 || x >= r || y < 0 || y >= c;
    }
 
    int x;
    int y;
};

const static vector<Coord> dirs = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };

queue<Coord> MoveWater(
        queue<Coord>& waterBound, 
        const vector<string> board, 
        vector<vector<bool>>& waterVisited)
{
    queue<Coord> nextWaterBound;

    while (!waterBound.empty())
    {
        Coord curr= waterBound.front();
        waterBound.pop();

        for (const Coord& dir : dirs)
        {
            Coord next = curr + dir;

            if (next.OOB(board))
            {
                continue;
            }

            if (waterVisited[next.x][next.y])
            {
                continue;
            }

            char nextBlock = board[next.x][next.y];
            if (nextBlock == '.' || nextBlock == 'S')
            {   
                waterVisited[next.x][next.y] = true;
                nextWaterBound.push(next);
            }
        }
    }

    return nextWaterBound;
}

void Print(vector<vector<int>> dist, vector<vector<bool>> waterVisited)
{
    cout << "distance: \n";
    for (auto& line : dist)
    {
        for (int i : line)
        {
            cout << i << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    cout << "water visited: \n";
    for (auto& line : waterVisited)
    {
        for (bool i : line)
        {
            cout << i << " ";
        }
        cout << endl;
    }
}

queue<Coord> MoveHedgeHog(
        queue<Coord>& q, 
        const vector<string> board,
        vector<vector<int>>& dist,
        vector<vector<bool>>& waterVisited)
{
    queue<Coord> nextQ;

    while(!q.empty())
    {        
        Coord curr = q.front();
        q.pop();


        if (waterVisited[curr.x][curr.y])
        {
            continue;
        }
        
        for (const Coord& dir : dirs)
        {
            Coord next = curr + dir;
            
            if (next.OOB(board))
            {
                continue;
            }
            
            if (dist[next.x][next.y] <= dist[curr.x][curr.y] + 1)
            {
                continue;
            }
            
            if (waterVisited[next.x][next.y])
            {
                continue;
            }
            
            if (board[next.x][next.y] == '.' || board[next.x][next.y] == 'D')
            {
                dist[next.x][next.y] = dist[curr.x][curr.y] + 1;
                nextQ.push(next);
            }
        }
    }

    return nextQ;
}

int main()
{
    // freopen("output.txt", "w", stdout);
    freopen("input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int r, c;
    cin >> r >> c;
    vector<string> board(r);
    for (int i = 0; i < r; ++i)
    {
        cin >> board[i];
    }

    Coord start;
    Coord destination;
    queue<Coord> waterBound;
    vector<vector<bool>> waterVisited(r, vector<bool>(c, false));

    for (int i = 0; i < r; ++i)
    {
        for (int j = 0 ; j < c; ++j)
        {
            char info = board[i][j];
            switch(info)
            {
                case 'D':
                    destination = Coord(i, j);
                break;
                case 'S':
                    start = Coord(i, j);
                break;
                case '*':
                    waterBound.push(Coord(i, j));
                    waterVisited[i][j] = true;
                break;
            }
        }
    }

    queue<Coord> q;
    q.push(start);
    vector<vector<int>> dist(r, vector<int>(c, r * c));
    dist[start.x][start.y] = 0;

    while(!q.empty())
    {
        q = MoveHedgeHog(q, board, dist, waterVisited);
        waterBound = MoveWater(waterBound, board, waterVisited);
    }
    
    int answer = dist[destination.x][destination.y];
    if (answer == r * c)
    {
        cout << "KAKTUS" << endl;
    }
    else
    {
        cout << dist[destination.x][destination.y] << endl;
    }



    return 0;
}