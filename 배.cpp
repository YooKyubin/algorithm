#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> CountWorkableCrane(int n, vector<int>& numWorks)
{
    vector<int> numCrane(n);
    int acc = 0;
    for (int i =0 ; i< n; ++i)
    {
        ++acc;
        if (0 != numWorks[i])
        {
            numCrane[i] = acc;
            acc = 0;    
        }
    }

    return numCrane;
}

void Move(int n, vector<int>& numWorks, vector<int>& cranes)
{
    for (int i = 0; i < n; ++i)
    {
        int result = numWorks[i] - cranes[i];
        if (result <= 0)
        {
            if (i + 1 < n)
            {
                numWorks[i + 1] += result;
            }
            numWorks[i] = 0;
        }
        else
        {
            numWorks[i] = result;
        }
    }
}

bool CheckIsEnd(vector<int>& numWorks)
{
    for (int i : numWorks)
    {
        if (i != 0)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    freopen("../../input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;
    vector<int> maxWeights(n, 0);
    vector<bool> moved(n, false);
    for (int& i : maxWeights)
    {
        cin >> i;
    }
    sort(maxWeights.begin(), maxWeights.end());
    
    bool isMovable = true;
    vector<int> numWorks(n, 0);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i)
    {
        int box;
        cin >> box;
        if (box > maxWeights.back())
        {
            isMovable = false;
            break;
        }

        for (int j = 0; j < n; ++j)
        {
            if (box <= maxWeights[j])
            {
                ++numWorks[j];
                break;
            }
        }
    }

    if (isMovable)
    {
        reverse(maxWeights.begin(), maxWeights.end());
        reverse(numWorks.begin(), numWorks.end());
    
        int answer = 0;
        while ( !CheckIsEnd(numWorks) )
        {
            vector<int> numThreads = CountWorkableCrane(n, numWorks);
            Move(n, numWorks, numThreads);
            ++answer;
        }
        cout << answer << endl;
    }
    else
    {
        cout << -1 << endl;
    }

    return 0;
}
