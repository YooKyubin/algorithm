#include <iostream>
#include <vector>

using namespace std;

struct Fish
{
    pair<int, int> pos;
    int dir;
    bool isAlive = true;
};
int dedug = 0;

vector<pair<int, int>> direction { {-1, 0}, {-1, -1}, {0, -1}, {1, -1}, {1, 0}, {1, 1}, {0, 1}, {-1, 1} };

bool OOB(int x, int y)
{
    return x < 0 || x >= 4 || y < 0 || y >= 4;
}

int max(int a, int b) { return a > b ? a : b; }

void fishMove(vector<vector<int>>& bowl, vector<Fish>& fishes)
{
    for (int i=1; i<=16; ++i)
    {
        if (!fishes[i].isAlive)
            continue;

        pair<int, int> pos = fishes[i].pos;
        int dir = fishes[i].dir;

        int nx = pos.first + direction[dir].first;
        int ny = pos.second + direction[dir].second;
        while (OOB(nx, ny) || bowl[nx][ny] == 0)
        {
            dir = (dir + 1) % 8;

            nx = pos.first + direction[dir].first;
            ny = pos.second + direction[dir].second;
        }

        int temp = bowl[nx][ny];
        bowl[nx][ny] = i;
        fishes[i].pos = {nx, ny};
        fishes[i].dir = dir;

        bowl[pos.first][pos.second] = temp;
        if (temp != -1)
        {
            fishes[temp].pos = pos;
        }
    }
}

int getMaxFish(vector<vector<int>>& bowl, vector<Fish>& fishes)
{
    int dir = fishes[0].dir;
    pair<int, int> pos = fishes[0].pos;
    vector<pair<int, int>> nexts;
    int nx = pos.first + direction[dir].first;
    int ny = pos.second + direction[dir].second;
    while (!OOB(nx, ny))
    {
        nexts.push_back({nx, ny});

        nx += direction[dir].first;
        ny += direction[dir].second;
    }

    int maxFish = 0;
    for (auto next : nexts)
    {
        vector<vector<int>> nbowl = bowl;
        vector<Fish> nfishes = fishes;

        int die = bowl[next.first][next.second];
        if (die == -1)
            continue;

        nfishes[0] = fishes[die];
        nfishes[die].isAlive = false;
        nbowl[next.first][next.second] = 0;
        nbowl[pos.first][pos.second] = -1; // 기존 상어 위치에 죽은 물고기 넣기

        fishMove(nbowl, nfishes);

        maxFish = max(maxFish, getMaxFish(nbowl, nfishes) + die);
    }
    return maxFish;
}

int main() 
{
    vector<vector<int>> bowl(4, vector<int>(4));
    vector<Fish> fishes(17);
    for (int i=0; i<4; ++i)
    {
        for (int j=0; j<4; ++j)
        {
            int n, d;
            cin >> n >> d;
            bowl[i][j] = n;
            fishes[n] = {{i, j}, d-1};
        }
    }
    
    int first = bowl[0][0];
    bowl[0][0] = 0; // 0번은 상어
    fishes[0] = fishes[first];
    fishes[first].isAlive = false;
    
    fishMove(bowl, fishes);

    int answer = getMaxFish(bowl, fishes) + first;
    
    cout << answer << endl;
    return 0;
}

/*
번호가 작은 물고기부터 이동

상어는 물고기가 없는 칸으로 이동할 수 없다.
*/