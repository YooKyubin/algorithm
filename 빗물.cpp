#include <iostream>
#include <vector>

using namespace std;

int h, w;
vector<vector<bool>> blocks;

int main()
{
    // freopen("../../input.txt", "r", stdin);
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> h >> w;
    blocks.resize(h, vector<bool>(w, false));

    for (int i=0; i<w; ++i)
    {
        int height;
        cin >> height;

        for (int j=0; j<height; ++j)
        {
            blocks[j][i] = true;
        }   
    }

    int totalCapacity = 0;
    for (int i=0; i<h; ++i)
    {
        bool leftBlock = false;
        int blankAfterLeftBlock = 0;
        for (int j=0; j<w; ++j)
        {
            if (leftBlock)
            {
                
                if (blocks[i][j])
                {
                    totalCapacity += blankAfterLeftBlock;
                    blankAfterLeftBlock = 0;
                }
                else
                {
                    ++blankAfterLeftBlock;
                }
            }
            else
            {
                if (blocks[i][j])
                {
                    leftBlock = true;
                }
            }
        }
    }

    cout << totalCapacity << endl;
    return 0;

}