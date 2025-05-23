#include <string>
#include <vector>
#include <algorithm>

#include <iostream>

using namespace std;

bool CanSolveInTime(const vector<int>& diffs, const vector<int>& times, long long limit, long long level)
{
    int numPuzzles = diffs.size();
    long long timeElapsed = 0LL;
    for (int i=0; i < numPuzzles; ++i)
    {
        timeElapsed += (times[i-1] + times[i]) * max(0LL, diffs[i] - level);
        timeElapsed += times[i];
    }

    return timeElapsed <= limit;
}

int solution(vector<int> diffs, vector<int> times, long long limit) {
    int answer = 0;

    long long low = 0;
    long long high = 1e15 + 1;
    // long long high = 11;

    // lower boundary 구하기
    while (low + 1 < high)
    {
        long long mid = (low + high) >> 1;

        if (CanSolveInTime(diffs, times, limit, mid))
        {
            // 숙련도가 높다. -> 숙련도를 낮춰서 다시 학인
            high = mid;
        }   
        else
        {
            // 숙련도가 낮다. -> 숙련도를 높여서 다시 확인
            low = mid;
        }
    }

    answer = high;

    return answer;
}

int main()
{
    vector<int> diffs = 
        // {1, 5, 3};
        // {1, 328, 467, 209, 54};
        {1, 99999, 100000, 99995};
        vector<int> times = 
        // {2, 4, 7};
        // {2, 7, 1, 4, 3};
        {9999, 9001, 9999, 9001};
    long long limit = 3456789012;

    cout << solution(diffs, times, limit) << endl;

    return 0;
}