#include <iostream>
#include <vector>

using namespace std;

int main()
{
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, d, k, c;
    cin >> n >> d >> k >> c;

    vector<int> susiIDs(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> susiIDs[i];
    }

    vector<int> eatCount(d + 1, 0);
    ++eatCount[c];
    
    // init
    int answer = 1;
    for (int i = 0; i < k; ++i)
    {
        int susiID = susiIDs[i];
        
        if (eatCount[susiID] == 0)
        {
            ++answer;
        }
        ++eatCount[susiID];
    }

    // loop
    int maxAnswer = answer;
    for (int i = 0; i < n; ++i)
    {


        int leftSusiID = susiIDs[i];
        int rightSusiID = susiIDs[(i + k) % n];

        --eatCount[leftSusiID];
        if (eatCount[leftSusiID] == 0)
        {
            --answer;
        }

        if (eatCount[rightSusiID] == 0)
        {
            ++answer;
        }
        ++eatCount[rightSusiID];

        maxAnswer = max(maxAnswer, answer);
    }

    cout << maxAnswer << endl;

    return 0;
}