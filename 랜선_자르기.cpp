#include <iostream>
#include <vector>

using namespace std;

int CountLANs(const vector<int>& lengths, long long requiredLength)
{
    int numSplitedLANs = 0;
    for (int length : lengths)
    {
        numSplitedLANs += length / requiredLength;
    }

    return numSplitedLANs;
}

int main()
{
    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int numLAN;
    int numRequiredLAN;
    cin >> numLAN >> numRequiredLAN;

    vector<int> lengths(numLAN);
    for (int i=0; i<numLAN; ++i)
    {
        cin >> lengths[i];
    }

    long long low = 0;
    long long high = 1'000'0000'000 + 1;
    while (low + 1 < high)
    {
        long long mid = (low + high) >> 1;

        if (CountLANs(lengths, mid) < numRequiredLAN)
        {
            high = mid;   
        }
        else
        {
            low = mid;
        }
    }
    cout << low << endl;
    return 0;
}

/*
    low |<--- M+1, M+1, M+1, M, M, M-1, M-1, --->| high
    ( M = numRequiredLAN )
    
    CountLANs(lengths, mid) < numRequiredLAN 인 경우에
    - CountLANs의 결과는 M-1 이라 할 수 있다.
    - high를 이동시켜 범위를 좁힌다.

    CountLANs(lengths, mid) > numRequiredLAN 인 경우에
    - CountLANs의 결과는 M+1 이라 할 수 있다.
    - low를 이동시켜 범위를 좁힌다.
    
    CountLANs(lengths, mid) == numRequiredLAN 인 경우에
    - low를 이동시켜 범위를 좁힌다.

*/