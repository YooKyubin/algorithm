#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// 상 하 우 좌
vector<pair<int, int>> direction { {0, 0}, {-1, 0}, {1, 0}, {0, 1}, {0, -1} };
int r, c, m;
vector<vector<struct Shark*>> board;

struct Shark
{
    Shark() {}
    ~Shark() {}

    int x;
    int y;
    int speed;
    int dir;
    int size;

    void setShark()
    {
        if (board[x][y] != nullptr)
            if (board[x][y]->size > this->size)
                return;

        board[x][y] = this;
    }

    void move()
    {
        int max; // 1,2 : row가 최대움직일 거리 // 

        if ( dir < 3) // 1, 2
        {
            max = r;
            speed = speed % ((max-1)*2); // speed가 클때 굳이 모두 계산할 필요없이 반복되는 부분을 줄인다
            int dist = speed;

            while (true)
            {
                int next =  x + direction[dir].first * dist;
                if (next >= max ) // 움직일 거리가 경계를 넘어가는 경우 dir = 2
                {
                    x = max-1;
                    dist = next - (max-1);
                    dir = 1;
                }
                else if (next < 0 ) // 움직일 거리가 경계를 넘어가는 경우 dir = 1
                {
                    x = 0;
                    dist = -next;
                    dir = 2;
                }
                else
                {
                    break;
                }
            }
            x = (x + direction[dir].first * dist);
        }
        else // 3, 4 
        {
            max = c;
            speed = speed % ((max-1)*2);
            int dist = speed;

            while (true)
            {
                int next =  y + direction[dir].second * dist;
                if (next >= max ) // 움직일 거리가 경계를 넘어가는 경우 dir = 3
                {
                    y = max-1;
                    dist = next - (max-1);
                    dir = 4;
                }
                else if (next < 0 ) // 움직일 거리가 경계를 넘어가는 경우 dir = 4
                {
                    y = 0;
                    dist = -next;
                    dir = 3;
                }
                else
                {
                    break;
                }
            }
            y = (y + direction[dir].second * dist);
        }
    }
};

int min(int a, int b) { return a < b ? a : b; }

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> r >> c >> m;
    board.assign(r, vector<Shark*>(c, nullptr));

    for (int i=0; i<m; ++i)
    {
        int x, y, s, d, z;
        cin >> x >> y >> s >> d >> z;
        Shark* sharkPtr = new Shark();
        sharkPtr->x = x-1;
        sharkPtr->y = y-1;
        sharkPtr->speed = s;
        sharkPtr->dir = d;
        sharkPtr->size = z;

        sharkPtr->setShark();
    }

    int cntSize = 0;
    for (int i=0; i<c; ++i)
    {
        // 낚시질
        for (int line = 0; line < r; ++line)
        {
            if (board[line][i] != nullptr)
            {
                cntSize += board[line][i]->size;
                // cout << line << ", " << i << ": " << board[line][i]->size << endl;
                board[line][i] = nullptr;
                break;
            }
        }

        // 상어 이동
        vector<Shark*> buffer;
        for (int x=0; x < r; ++x)
        {
            for (int y=0; y<c; ++y)
            {
                if (board[x][y])
                {
                    board[x][y]->move();
                    buffer.push_back(board[x][y]);
                }
                board[x][y] = nullptr;
            }
        }
    
        for (auto& shark : buffer)
        {
            shark->setShark();
        }
        
    }
    
    cout << cntSize << endl;
    return 0;
}