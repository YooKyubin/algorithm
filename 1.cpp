#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    
    while (true)
    {
        int n;
        cin >> n;
        if (cin.eof())
        {
            break;
        }

        int value = 0;
        int iterCnt = 1;
        while (true)
        {
            value = value * 10 + 1;
            value = value % n;
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