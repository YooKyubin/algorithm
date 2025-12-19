#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    
    for (int i = 0; i < 10001; ++i)
    {
        if (i % 2 == 0 || i % 5 == 0)
        {
            continue;
        }

        int n = i;
        
        if (cin.eof())
        {
            break;
        }

        int value = 0;
        int iterCnt = 1;
        while (true)
        {
            value = value * 10 + 1;
            value %= n;
            if (value == 0)
            {
                cout << iterCnt << "\n";
                break;
            }
            ++iterCnt;
        }
    }

    return 0;
}