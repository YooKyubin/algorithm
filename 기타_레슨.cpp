#include <iostream>
#include <vector>

using namespace std;

#define _MAX_LECTURE_DURATION (100'000 * 10'000)
#define MAX_LECTURE_DURATION _MAX_LECTURE_DURATION

int CountRequiredBluRays(const vector<int>& lectureDurations, long long bluRaySize)
{
    int numRequiredBluRays = 0;
    long long durationAcc = 0LL;
    for (int duration : lectureDurations)
    {
        durationAcc += duration;

        if (durationAcc > bluRaySize)
        {
            ++numRequiredBluRays;
            durationAcc = duration;
        }
    }
    ++numRequiredBluRays;

    return numRequiredBluRays;
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    int numLectures;
    int numBluRays;
    cin >> numLectures >> numBluRays;

    vector<int> lectureDurations(numLectures);
    int maxLectureDuration = 0;
    for (int i = 0; i < numLectures; ++i)
    {
        cin >> lectureDurations[i];
        maxLectureDuration = max(maxLectureDuration, lectureDurations[i]);
    }
    

    long long low = maxLectureDuration - 1LL;
    long long high = MAX_LECTURE_DURATION + 1LL;

    while (low + 1LL < high)
    {
        long long mid = (low + high) >> 1;

        // lower boundary 찾기
        if (CountRequiredBluRays(lectureDurations, mid) <= numBluRays)
        {
            high = mid;
        }
        else
        {
            low = mid;
        }
    }
    cout << high << endl;


    return 0;
}