#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int n;
vector<vector<int>> A;
vector<vector<int>> board;
vector<vector<bool>> boundary;
int total = 0;

int min(int a, int b) { return a < b ? a : b; }

bool checkBoundary(int x, int y, int d1, int d2)
{
    bool ret = true;

    // ret &= d1 >= 1;
    // ret &= d2 >= 1;

    // ret &= x < x + d1 + d2; // x <= 0
    ret &= x + d1 + d2 < n;

    ret &= 0 <= y - d1;
    ret &= y + d2 < n;

    return ret;
}

void setBoundary(int x, int y, int d1, int d2)
{
    boundary.assign(n, vector<bool>(n, false));
    for (int i=0; i<= d1; ++i)
    {
        boundary[x + i][y - i] = true;
        boundary[x + d2 + i][y + d2 - i] = true;
    }

    for (int i=0; i<= d2; ++i)
    {
        boundary[x + i][y + i] = true;
        boundary[x + d1 + i][y - d1 + i] = true;
    }
}

int cal (int x, int y, int d1, int d2)
{
    vector<int> population(5, 0);

    setBoundary(x, y, d1, d2);

    board.assign(n, vector<int>(n, 5));
    // 1구역
    for (int i=0; i < x + d1; ++i)
    {
        for (int j=0; j <= y; ++j)
        {
            if (boundary[i][j])
                break;

            population[0] += A[i][j];
            board[i][j] = 1;
        }
    }

    // 2구역
    for (int i=0; i <= x+d2; ++i)
    {
        for (int j=n-1; j > y; --j)
        {
            if (boundary[i][j])
                break;

            population[1] += A[i][j];
            board[i][j] = 2;
        }
    }

    // 3 구역
    for (int i=x+d1; i < n; ++i)
    {
        for (int j=0; j < y - d1 + d2; ++j)
        {
            if (boundary[i][j])
                break;

            population[2] += A[i][j];
            board[i][j] = 3;
        }
    }

    // 4 구역
    for (int i=x+d2+1; i<n; ++i)
    {
        for (int j=n-1; j >= y - d1 + d2; --j)
        {
            if (boundary[i][j])
                break;

            population[3] += A[i][j];
            board[i][j] = 4;
        }
    }

    population[4] = total;
    for (int i=0; i<4; ++i)
        population[4] -= population[i];

    sort(population.begin(), population.end());
    return population.back() - population.front();
}

int main()
{
    freopen("../../input.txt", "r", stdin);
    
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n;
    A.resize(n, vector<int>(n));
    board.resize(n, vector<int>(n,5));
    boundary.resize(n, vector<bool>(n, false));
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            cin >> A[i][j];
            total += A[i][j];
        }
    }

    int minVal = INT32_MAX;
    for (int i=0; i<n; ++i)
    {
        for (int j=0; j<n; ++j)
        {
            for (int d1=1; d1<n; ++d1)
            {
                for (int d2=1; d2<n; ++d2)
                {
                    if (!checkBoundary(i, j, d1, d2))
                        continue;

                    minVal = min(minVal, cal(i, j, d1, d2));
                }
            }
        }
    }

    cout << minVal << endl;
    return 0;
}