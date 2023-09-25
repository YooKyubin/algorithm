#include <iostream>
#include <vector>

using namespace std;

int n;
vector<vector<bool>> board;
vector<bool> incr;
vector<bool> decr;
int odd = 0;
int even = 0;
// int answer[2] = {0, 0};

int max(int a, int b) { return a > b ? a : b; }

void dfs(int x, int y, int cnt, bool isOdd)
{
    if (y >= n)
    {
        x += 1;
        if(y % 2 == 0) y = 1;
        else y = 0;
    }
    if (x >= n)
    {
        // answer[isOdd] = max(answer[isOdd], cnt);
        int& answer = isOdd ? odd : even;
        answer = max(answer, cnt);
        return;
    }

    if (board[x][y] && !incr[x + y] && !decr[x - y + n-1])
    {
        incr[x+y] = true;
        decr[x-y+n-1] = true;
        dfs(x, y+2, cnt+1, isOdd);
        incr[x+y] = false;
        decr[x-y+n-1] = false;
    }

    dfs(x, y+2, cnt, isOdd);
}

int main()
{
    cin >> n;
    board = vector(n, vector<bool>(n, false));
    incr = vector<bool>(n*2, false);
    decr = vector<bool>(n*2, false);
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; ++j)
        {
            bool temp;
            cin >> temp;
            board[i][j] = temp;
        }
    }

    dfs(0, 0, 0, false);
    dfs(0, 1, 0, true);
    
    cout << odd + even << endl;
    return 0;
}