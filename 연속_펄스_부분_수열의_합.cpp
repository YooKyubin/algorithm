#include <string>
#include <vector>
#include <iostream>
using namespace std;

long long GetDPMax(vector<int>& sequence)
{
    long long acc = 0;
    long long dpMax = INT64_MIN;

    for (int i=0; i<sequence.size(); ++i)
    {
        acc = max(acc + sequence[i], (long long)sequence[i]);
        dpMax = max(acc, dpMax);
    }
    return dpMax;
}

long long solution(vector<int> sequence) {
    long long answer = 0;
    
    vector<int> pluxSequence[2];
    for (size_t i =0; i<sequence.size(); ++i)
    {
        int signedNum = (i % 2 ? 1 : -1) * sequence[i];
        pluxSequence[0].push_back(signedNum);
        pluxSequence[1].push_back(signedNum * -1);
    }

    long long src = GetDPMax(pluxSequence[0]);
    long long dst = GetDPMax(pluxSequence[1]);

    answer = max(src, dst);
    return answer;
}

int main()
{
    vector<int> a = {2, 3, -6, 1, 3, -1, 2, 4};
    cout << solution(a) << endl;

    return 0;
}