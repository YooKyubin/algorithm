#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int ConverStringToTime(const string& timeForamt)
{
    int timeMinute = 0;

    timeMinute += stoi(timeForamt.substr(0, 2)) * 60;
    timeMinute += stoi(timeForamt.substr(3, 2));

    return timeMinute;
}

string ConvertTimeToString(int timeMinute)
{
    string timeFormat;
    int hour = timeMinute / 60;
    if (hour < 10)
    {
        timeFormat = "0";
    }
    timeFormat += to_string(hour);
    timeFormat += ":";
    
    int minute = timeMinute % 60;
    if (minute < 10)
    {
        timeFormat += "0";
    }
    timeFormat += to_string(minute);

    return timeFormat;
}

string solution(int n, int t, int m, vector<string> timetable) {
    string answer = "";

    vector<int> times;
    times.reserve(timetable.size());
    for (const string& timeFormat : timetable)
    {
        times.push_back(ConverStringToTime(timeFormat));
    }
    sort(times.begin(), times.end());
    
    const int busStartTime = ConverStringToTime("09:00");

    int busTime = busStartTime;
    size_t crewIndex = 0;
    vector<int> numPassengers(n, 0);
    for (int i=0; i<n; ++i)
    {
        int& numPassenger = numPassengers[i];
        while (crewIndex + numPassenger < times.size())
        {
            // 탈 수 없는 조건
            bool isFull = numPassenger == m; // 승객이 최대 수용량 m 인지 확인
            bool isLate = times[crewIndex + numPassenger] > busTime; // 이번에 탈 승객이 온 시간이 버스가 온 뒤인지 확인

            if (isFull || isLate)
            {
                break;
            }

            ++numPassengers[i]; // 승객 태우기
        }
        crewIndex = crewIndex + numPassenger; // 아직 버스 못 탄 승객 중 가장 먼저 오는 사람
        busTime += t;
    }

    int latestTime = (n - 1) * t + busStartTime; // 마지막 배차시간
    if (numPassengers.back() >= m ) // 마지막 버스에 승객이 꽉 찾다면
    {
        // mix(버스 마지막 배차 시간, 마지막에 탄 승객의 시간 - 1분)
        latestTime = min(latestTime, times[crewIndex-1] - 1);
    }

    answer = ConvertTimeToString(latestTime);

    return answer;
}

#include <iostream>

int main()
{
    int n = 10;
    int t = 60;
    int m = 45;
    vector<string> timetable = 
    {
        "23:59","23:59", "23:59", "23:59", "23:59", "23:59", 
        "23:59", "23:59", "23:59", "23:59", "23:59", "23:59",
         "23:59", "23:59", "23:59", "23:59"
    };

    cout << solution(n, t, m, timetable) << endl;

    return 0;
}