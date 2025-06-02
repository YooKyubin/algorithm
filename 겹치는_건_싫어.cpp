#include <iostream>
#include <vector>

using namespace std;

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    freopen("input.txt", "r", stdin);

    int n;
    int k;
    cin >> n >> k;
    vector<int> numbers(n);

    for (int i=0; i<n; ++i)
    {
        cin >> numbers[i];
    }

    int beginIndex = 0;
    int endIndex = 0;
    int maxLength = 0;

    vector<int> numDuplications(100'001, 0);

    while (endIndex < n)
    {
        int endNum = numbers[endIndex];
        ++numDuplications[endNum];

        while (numDuplications[endNum] > k)
        {
            int beginNum = numbers[beginIndex];
            --numDuplications[beginNum];
            ++beginIndex;
        }
        
        maxLength = max(maxLength, endIndex - beginIndex + 1);
        
        ++endIndex;
    }

    cout << maxLength << endl;

    return 0;
}