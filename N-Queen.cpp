#include <iostream>
#include <vector>

using namespace std;


int GetPermutation(int x, int y, 
                    vector<bool>& visited, 
                    vector<bool>& diagonalPositive, 
                    vector<bool>& diagonalNegative)
{
    int boardSize = visited.size();

    if (boardSize - 1 == x)
    {
        return 1;
    }

    int numPermutation = 0;
    for (int i = 0; i < boardSize; ++i)
    {
        int nx = x + 1;
        int ny = i;

        int positiveID = ny - nx + boardSize - 1;
        int negativeID = nx + ny;

        bool isVisited = visited[i];
        bool isDiagonalPositive = diagonalPositive[positiveID];
        bool isDiagonalNegative = diagonalNegative[negativeID];

        if ( !(isVisited || isDiagonalNegative || isDiagonalPositive) )
        {
            visited[i] = true;
            diagonalPositive[positiveID] = true;
            diagonalNegative[negativeID] = true;

            numPermutation += GetPermutation(nx, ny, visited, diagonalPositive, diagonalNegative);

            visited[i] = false;
            diagonalPositive[positiveID] = false;
            diagonalNegative[negativeID] = false;
        }
    }
    return numPermutation;
}

int main()
{
    freopen("input.txt", "r", stdin);

    int n;
    cin >> n;

    vector<bool> visited(n, false);
    // ex) n = 6;
    // "\", -5 ~ 5 y - x
    vector<bool> DiagonalPositive(n + n, false);
    // "/" 0 ~ 10, x + y
    vector<bool> DiagonalNegative(n + n, false);

    cout << GetPermutation(-1, 0, visited, DiagonalPositive, DiagonalNegative) << endl;


    // for(int i = 0; i<6; ++i)
    // {
    //     for (int j = 0; j < 6; ++j)
    //     {
    //         cout << "  " << i << "," << j << "  "; 
    //     }
    //     cout << endl;
    // }


    return 0;
}