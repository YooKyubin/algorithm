#include <iostream>
#include <string>
#include <vector>

using namespace std;


void PrintTable(vector<vector<bool>>& table)
{
    for (auto& line : table)
    {
        for (bool b : line)
        {
            char boolean = b ? 'T' : 'F';
            cout << boolean << " ";
        }
        cout << endl;
    }
}

int solution(string s)
{
    int answer=0;
    int length = s.size();

    vector<vector<bool>> isPalindromeTable(length, vector<bool>(length, false));

    // 초기 값 채우기
    for (int i=0; i<length; ++i)
    {
        isPalindromeTable[i][i] = true;
    }
    for (int i = 0; i < length - 1; ++i)
    {
        isPalindromeTable[i][i + 1] = s[i] == s[i + 1];
    }

    // bottom-up 방식으로 표 채우기
    for (int interval = 2; interval < length; ++interval)
    {
        for (int i=0; i < length - interval; ++i)
        {
            int begin = i;
            int end = i + interval;
            
            bool isInnerPalinedrome = isPalindromeTable[begin + 1][end - 1];
            bool isSame = s[begin] == s[end];
            isPalindromeTable[begin][end] = isInnerPalinedrome && isSame;
        }
    }
    
    // 가장 긴 길이 구하기
    int maxLength = 0;
    for (int interval = 0; interval < length; ++interval)
    {
        for (int i=0; i < length - interval; ++i)
        {
            int begin = i;
            int end = i + interval;

            if (isPalindromeTable[begin][end])
            {
                maxLength = interval + 1;
            }
        }
    }
    
    answer = maxLength;
    return answer;
}

#include <iostream>

int main()
{
    string s = "aaa";

    cout << solution(s) << endl;
    return 0;
}