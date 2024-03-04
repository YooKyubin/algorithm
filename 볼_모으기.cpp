#include <iostream>
#include <vector>

using namespace std;

int min(int a, int b) { return a < b ? a : b; }

int main()
{
    freopen("../../input.txt", "r", stdin);

    int n;
    int redCnt = 0;
    int blueCnt = 0;
    cin >> n;
    vector<char> balls(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> balls[i];
        if (balls[i] == 'R')
        {
            ++redCnt;
        }
        else
        {
            ++blueCnt;
        }
    }

    char front = balls.front();
    char back = balls.back();

    int blueRight = blueCnt;
    int blueLeft = blueCnt;
    int redRight = redCnt;
    int redLeft = redCnt;

    for(int i=1; i<n; ++i)
    {
        if (front != balls[i])
        {
            if (front == 'R')
                redRight -= i;
            else
                blueRight -= i;

            break;
        }
    }

    for (int i=n-2; i>=0; --i)
    {
        if (back != balls[i])
        {
            if (back == 'R')
                redLeft -= n-1-i;
            else
                blueLeft -= n-1-i;

            break;
        }
    }

    cout << min( min(blueRight, redRight), min(blueLeft, redLeft) ) << endl;
    return 0;
}