#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);

    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int testCase;
    cin >> testCase;

    while (testCase--)
    {
        int n, m;
        cin >> n >> m;
        
        vector<int> arrA(n);
        vector<int> arrB(m);
        for (int i = 0; i < n; ++i)
        {
            cin >> arrA[i];
        }
        for (int i = 0; i < m; ++i)
        {
            cin >> arrB[i];
        }
        sort(arrA.begin(), arrA.end());
        sort(arrB.begin(), arrB.end());

        int idA = 0;
        int idB = 0;

        // A -> B
        vector<int> numSmallers(n);
        while (true)
        {
            if (idA >= n)
            {
                break;
            }
            else if (idB >= m)
            {
                for (int i = idA; i < n; ++i)
                {
                    numSmallers[i] = m;
                }
                break;
            }

            bool canEat = arrA[idA] > arrB[idB];
            if( canEat )
            {   
                ++idB;
            }
            else
            {
                numSmallers[idA] = idB;
                ++idA;
            }
        }

        int numCase = 0;
        for (int i :numSmallers)
        {
            numCase += i;
        }
        cout << numCase << "\n";
    }

    return 0;
}