#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>

using namespace std;

vector<int> solution(vector<string> gems) {
    vector<int> answer;

    map<string, int> currGems;
    for (string& gem : gems)
    {
        currGems[gem] = 0;
    }

    int left = 0;
    int right = 0;
    int numCurrGems = 0;
    vector<pair<int, int>> results;

    while (right <= gems.size())
    {
        // 범위 내의 보석들이 모든 보석을 포함하는지 확인
        if (numCurrGems !=  currGems.size())
        {
            if (right >= gems.size())
            {
                break;
            }
            
            const string& gem = gems[right];
            if (currGems[gem] == 0)
            {
                ++numCurrGems;
            }
            ++currGems[gem];

            ++right;
        }
        else
        {   
            const string& gem = gems[left];
            --currGems[gem];
            if (currGems[gem] == 0)
            {
                --numCurrGems;
            }

            results.push_back({right - 1 - left, left});
            // cout << left << ", " << right - 1 << endl;
            
            ++left;
        }
    }

    sort(results.begin(), results.end());
    const pair<int, int>& minLength = results.front();
    answer.push_back(minLength.second + 1);
    answer.push_back(minLength.second + minLength.first +1);
    return answer;
}