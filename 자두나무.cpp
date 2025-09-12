#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    freopen("../../input.txt", "r", stdin);

    int t, w;
    cin >> t >> w;
    vector<int> numbers(t);
    for (int i=0; i<t; ++i)
    {
        cin >> numbers[i];
        --numbers[i];
    }

    vector<vector<vector<int>>> dpTable;
    dpTable.assign(t, vector<vector<int>>(w+1, vector<int>(2, 0)));

    dpTable[0][0][0] = numbers[0] == 0 ? 1 : 0;
    dpTable[0][0][1] = numbers[0] == 1 ? 1 : 0;
    for (int i=1; i<t; ++i)
    {
        dpTable[i][0][0] = dpTable[i-1][0][0] + ((numbers[i] == 0) ? 1 : 0);
        dpTable[i][0][1] = dpTable[i-1][0][1] + ((numbers[i] == 1) ? 1 : 0);
    }
    for (int i=1; i < w+1; ++i)
    {
        dpTable[0][i][0] = (numbers[i] == i) ? 1 : 0;
        dpTable[0][i][1] = 0;
    }

    for (int i = 1; i < t; ++i)
    {
        for (int j = 1; j < w+1; ++j)
        {
            for (int k=0; k < 2; ++k)
            {
                dpTable[i][j][k] = dpTable[i-1][j][k];
                if (numbers[i] == k)
                {
                    dpTable[i][j][k] += 1;
                }
                else
                {
                    dpTable[i][j][k] = max(dpTable[i-1][j][k], dpTable[i-1][j-1][(k + 1) % 2] + 1);
                }
            }
        }
    }

    // for (auto line : dpTable)
    // {
    //     for (auto p : line)
    //     {
    //         cout << "[" << p[0] << ", " << p[1] << "] " ;
    //     }
    //     cout << endl;
    // }


    int maxCount = 0;
    for (int i=0; i<w+1; ++i)
    {
        for (int j =  0; j < 2; ++j)
        {
            maxCount = max(maxCount, dpTable.back()[i][j]);
        }
    }
    cout <<  maxCount << endl;

    return 0;
}
/*
    dpTable[몇번째 자두인지][움직인 횟수][현재 나무위치]
*/