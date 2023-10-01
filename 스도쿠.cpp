#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;

int sudoku[9][9];
bool row[9][10];
bool col[9][10];
bool square[3][3][10];

bool dfs(int idx)
{
    if (idx == 9*9)
        return true;

    int x = idx / 9;
    int y = idx % 9;

    if (sudoku[x][y] != 0)
        return dfs(idx+1);
    
    for (int i=1; i<10; ++i)
    {
        if (row[x][i] || col[y][i] || square[x/3][y/3][i])
            continue;

        row[x][i] = true;
        col[y][i] = true;
        square[x/3][y/3][i] = true;

        sudoku[x][y] = i;
        if (dfs(idx+1))
        {
            return true;
        }
        sudoku[x][y] = 0;
        
        row[x][i] = false;
        col[y][i] = false;
        square[x/3][y/3][i] = false;
    }

    return false;
    
}

int main()
{
    memset(row, false, sizeof(row));
    memset(col, false, sizeof(col));
    memset(square, false, sizeof(square));

    for (int i=0; i<9; ++i)
    {
        string input;
        cin >> input;
        for (int j=0; j<9; ++j)
        {
            int val = (int)input[j] - '0';
            sudoku[i][j] = val;

            row[i][val] = true;
            col[j][val] = true;
            square[i/3][j/3][val] = true;
        }
    }
    
    dfs(0);

    for (int i=0; i<9; ++i)
    {
        for (int j=0; j<9; ++j)
        {
            cout << sudoku[i][j];
        }
        cout << endl;
    } 
    return 0;
}