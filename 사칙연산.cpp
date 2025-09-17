#include <vector>
#include <string>
#include <iostream>

using namespace std;

vector<int> ConvertInteger(const vector<string>& arr)
{
    vector<int> nums;
    nums.reserve(arr.size());
    
    for (int i = 0; i < (int)arr.size(); ++i)
    {
        if (i % 2)
        {
            if (arr[i] == "+")
            {
                nums.push_back(1);
            }
            else
            {
                nums.push_back(-1);
            }
        }
        else
        {
            nums.push_back(stoi(arr[i]));
        }
    }
    
    return nums;
}

void PrintTable(const vector<vector<pair<int, int>>>& dpTable)
{
    for (auto line : dpTable)
    {
        for (const pair<int, int>& p : line)
        {
			cout << " { "<< p.first << ", " << p.second << " }  ";
        }
        cout << endl;
    }
}

int solution(vector<string> arr)
{
    int answer = -1;
    
    vector<int> nums = ConvertInteger(arr);
    
    size_t tableSize = nums.size() / 2 + 1;
    vector<vector<pair<int, int>>> dpTable(tableSize, vector<pair<int, int>>(tableSize));
    
    for (int i = 0; i < tableSize; ++i)
    {
        int num = nums[i * 2];
        dpTable[i][i] = { num, num };
    }
    for (int interval = 1; interval < tableSize; ++interval)
    {
        for (int start = 0; start + interval < tableSize; ++start)
        {
            int left = start;
            int right = start + interval;
            
            int minResult = INT32_MAX;
            int maxResult = INT32_MIN;
            
            for (int offset = 0; offset < interval; ++offset)
            {
                int mid = start + offset;
                // src = left ~ mid
                // dst = mid + 1 ~ right
                
                int sign = nums[(mid) * 2 + 1];
                
                int srcMin = dpTable[left][mid].first;
                int dstMin = min(
                    sign * dpTable[mid + 1][right].first,
                    sign * dpTable[mid + 1][right].second);
                
                int srcMax = dpTable[left][mid].second;
                int dstMax = max(
                    sign * dpTable[mid + 1][right].first,
                    sign * dpTable[mid + 1][right].second);
                
                minResult = min(minResult, srcMin + dstMin);
                maxResult = max(maxResult, srcMax + dstMax);
            }
            
            dpTable[left][right] = { minResult, maxResult };
        }
    }
    
    
    // PrintTable(dpTable);
    
    answer = dpTable.front().back().second;
    
    return answer;
}