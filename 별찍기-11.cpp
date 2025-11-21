#include <iostream>
#include <vector>
#include <string>

using namespace std;

void Draw(vector<string>& canvas, int cascade, int x, int y)
{
    if (cascade == 3)
    {
        canvas[x][y] = '*';

        canvas[x + 1][y - 1] = '*';
        canvas[x + 1][y + 1] = '*';
        
        for (int i = 0; i < 5; ++i)
        {
            canvas[x + 2][y + i - 2] = '*';
        }
     
        return;
    }

    int nextCascade = cascade / 2;

    vector<int> nx = { x, x + nextCascade, x + nextCascade };
    vector<int> ny = { y, y - nextCascade, y + nextCascade };
    
    for (int i = 0; i < 3; ++i)
    {
        Draw(canvas, nextCascade, nx[i], ny[i]);
    }
}

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    // 3, 6, 12, 24, 48,
    // 1, 2, 4, 8, 16

    int height = n;
    int width = n * 2 - 1;

    vector<string> canvas(height, string(width, ' '));

    Draw(canvas, n, 0, width / 2);


    for (auto& line : canvas)
    {
        cout << line << "\n";
    }

    return 0;
}