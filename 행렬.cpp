#include <iostream>
#include <vector>

using namespace std;

vector<vector<char>> GetInput(int n, int m)
{
    vector<vector<char>> matrix(n, vector<char>(m, false));
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            char input;
            cin >> input;
            matrix[i][j] = input;
        }
    }
    return matrix;
}

void Flip(vector<vector<char>>& src, int x, int y)
{
    for (int i = x; i - x < 3; ++i)
    {
        for (int j = y; j - y < 3; ++j)
        {
            src[i][j] = src[i][j] == '0' ? '1' : '0';
        }
    }
}

int GetFlipCount(int n, int m, vector<vector<char>>& src, vector<vector<char>>& dst)
{
    int answer = 0;
    for (int i = 0; i < n - 2 ; ++i)
    {
        for (int j = 0; j < m - 2; ++j)
        {
            if (src[i][j] != dst[i][j])
            {
                Flip(src, i, j);
                ++answer;
            }
        }
    }

    return answer;
}

int main()
{
    freopen("input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    vector<vector<char>> src = GetInput(n, m);
    vector<vector<char>> dst = GetInput(n, m);

    int answer = 0;
    if ( !(n < 3 || m < 3) )
    {
        answer = GetFlipCount(n, m, src, dst);
    }

    bool perfect = true;   
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < m; ++j)
        {
            if (src[i][j] != dst[i][j])
            {
                perfect = false;
            }
        }
    }

    if (perfect)
    {
        cout << answer << endl;
    }
    else
    {
        cout << -1 << endl;
    }
    
    return 0;
}