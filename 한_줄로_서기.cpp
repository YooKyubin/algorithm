#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    vector<int> leftTallerCounts(n);
    for (int i=0; i<n; ++i)
    {
        cin >> leftTallerCounts[i];
    }

    vector<int> talls(n, 0);
    for (int i = 0; i < n; ++i)
    {
        const int tall = i + 1;
        int tallCount = 0;
        int leftTallerCount = leftTallerCounts[i];

        for (int j = 0; j < n; ++j)
        {
            bool isEmpty = 0 == talls[j];
            bool hasEnoughCount = tallCount == leftTallerCount;
            
            if (isEmpty && hasEnoughCount)
            {
                talls[j] = tall;
                break;
            }
            
            if (0 == talls[j])
            {
                ++tallCount;
            }
        }
    }

    for (int tall : talls)
    {
        cout << tall << " ";
    }
    cout << endl;

    return 0;
}