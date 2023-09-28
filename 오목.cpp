// 어디 내놓긴 부끄러운 코드
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> board(19, vector<int>(19, 0));
vector<pair<int, int>> dir { {1, -1}};

bool OOB(int x, int y)
{
    return x < 0 || x >= 19 || y < 0 || y >= 19;
}

int main() 
{
    vector<pair<int, pair<int, int>>> answer;

    for (int i=0; i<19; ++i)
    {
        for (int j=0; j<19; ++j)
        {
            cin >> board[i][j];
        }
    }

    for (int i=0; i<19; ++i) // 가로
    {
        int cnt = 1;
        int pre = 0;
        for (int j=0; j<19; ++j)
        {
            if (board[i][j] == 0)
            {
                pre = 0;
                cnt = 1;
                continue;
            }

            if (board[i][j] == pre)
            {
                ++cnt;

                if (cnt == 5)
                    answer.push_back({pre, {i, j-4}});
                if (cnt == 6)
                    answer.pop_back();
            }
            else
            {
                cnt = 1;
                pre = board[i][j];
            }
        }
    }

    for (int j=0; j<19; ++j) // 세로
    {
        int cnt = 1;
        int pre = 0;
        for (int i=0; i<19; ++i)
        {
            if (board[i][j] == 0)
            {
                pre = 0;
                cnt = 1;
                continue;
            }

            if (board[i][j] == pre)
            {
                ++cnt;

                if (cnt == 5)
                    answer.push_back({pre, {i-4, j}});
                if (cnt == 6)
                    answer.pop_back();
            }
            else
            {
                cnt = 1;
                pre = board[i][j];
            }
        }
    }

    for (int i=0; i<19; ++i) // 하단 삼각형
    {
        int cnt = 1;
        int pre = 0;
        for (int j=i; j<19; ++j) 
        {
            int x = j;
            int y = j-i;
            if (board[x][y] == 0)
            {
                pre = 0;
                cnt = 1;
                continue;
            }

            if (board[x][y] == pre)
            {
                ++cnt;

                if (cnt == 5)
                    answer.push_back({pre, {x-4, y-4}});
                if (cnt == 6)
                    answer.pop_back();
            }
            else
            {
                cnt = 1;
                pre = board[x][y];
            }
        }
    }

    for (int i=0; i<19; ++i) // 상단 삼각형
    {
        int cnt = 1;
        int pre = 0;
        for (int j=i; j<19; ++j) 
        {
            int x = j-i;
            int y = j;
            if (board[x][y] == 0)
            {
                pre = 0;
                cnt = 1;
                continue;
            }

            if (board[x][y] == pre)
            {
                ++cnt;

                if (cnt == 5)
                    answer.push_back({pre, {x-4, y-4}});
                if (cnt == 6)
                    answer.pop_back();
            }
            else
            {
                cnt = 1;
                pre = board[x][y];
            }
        }
    }
    
    for (int i=0; i<19; ++i)
    {
        int x = 0;
        int y = i;
        int pre = 0;
        int cnt = 1;
        while(!OOB(x, y))
        {
            if (board[x][y] == 0)
            {
                pre = 0;
                cnt = 1;
            }

            if (board[x][y] == pre)
            {
                ++cnt;

                if (cnt == 5)
                    answer.push_back({pre, {x, y}});
                if (cnt == 6)
                    answer.pop_back();
            }
            else
            {
                cnt = 1;
                pre = board[x][y];
            }

            x += dir[0].first;
            y += dir[0].second;
        }
    }

    for (int i=0; i<19; ++i)
    {
        int x = 18;
        int y = i;
        int pre = 0;
        int cnt = 1;
        while(!OOB(x, y))
        {
            if (board[x][y] == 0)
            {
                pre = 0;
                cnt = 1;
            }

            if (board[x][y] == pre)
            {
                ++cnt;

                if (cnt == 5)
                    answer.push_back({pre, {x, y}});
                if (cnt == 6)
                    answer.pop_back();
            }
            else
            {
                cnt = 1;
                pre = board[x][y];
            }

            x += dir[0].first;
            y += dir[0].second;
        }
    }

    if (answer.size() == 0)
    {
        cout << 0 << endl;
    }
    else
    {
        cout << answer[0].first << endl;
        cout << answer[0].second.first+1 << " " << answer[0].second.second+1 << endl;
    }
    return 0;
}