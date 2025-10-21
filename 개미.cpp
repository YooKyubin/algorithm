#include <iostream>
#include <vector>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);   

    int w, h;
    cin >> w >> h;
    int p, q;
    cin >> p >>q;
    int t;
    cin >> t;

    int tX = t + p;
    int tY = t + q;

    int offsetX = tX % (2 * w);
    int offsetY = tY % (2 * h);

    if (offsetX > w)
    {
        offsetX = 2 * w - offsetX;
    }
    if (offsetY > h)
    {
        offsetY = 2 * h - offsetY;
    }

    cout << offsetX << " " << offsetY << endl;

    return 0;
}