#include <string>
#include <vector>
#include <iostream>

using namespace std;

int solution(vector<int> a) {
    int answer = 0;
    int length = a.size();

    vector<int> beginMin(a.size() + 1, INT32_MAX);
    vector<int> endMin(a.size() + 1, INT32_MAX);
    for (int i = 0; i<length; ++i)
    {
        beginMin[i + 1] = min(beginMin[i], a[i]);
    }
    for (int i = length; i > 0; --i)
    {
        endMin[i - 1] = min(endMin[i], a[i-1]);
    }

    for (int i = 0; i < length; ++i)
    {
        const int curr = a[i];
        bool isGreaterLeft = curr > beginMin[i];
        bool isGreaterRight = curr > endMin[i];

        if (! (isGreaterLeft && isGreaterRight) )
        {
            ++answer;
        }
    }
    
    return answer;
}

#include <iostream>

int main()
{
    vector<int> a = { 1, 2 };
    // vector<int> a = {-16,27,65,-2,58,-92,-71,-68,-61,-33};

    cout << solution(a) << endl;

    return 0;
}

/*
    현재 수를 기준으로 좌우에서 가장 작은 수가 나보다 작은지 큰 지 비교
    좌우 둘다 작으면 불가능
*/