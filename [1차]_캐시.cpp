#include <string>
#include <vector>
#include <list>
#include <algorithm>

#include <iostream>

using namespace std;

string TransformStringLower(const string& str)
{
    string lowerString = str;
    std::transform(
        lowerString.begin(), 
        lowerString.end(), 
        lowerString.begin(),
        ::tolower);

    return lowerString;
}

bool FindInCache(list<string>& cache, const string& city, int cacheSize)
{
    for (auto iter = cache.begin(); iter != cache.end(); ++iter)
    {
        // cache hit
        if (city == *iter)
        {
            cache.erase(iter);
            cache.push_back(city);
            return true;
        }
    }

    // cache miss
    cache.push_back(city);
    if (cache.size() > cacheSize)
    {
        cache.pop_front();
    }
    return false;
}

int solution(int cacheSize, vector<string> cities) {
    int answer = 0;

    list<string> cache;

    for (const string& city : cities)
    {
        string cityLowerString = TransformStringLower(city);
        
        if (FindInCache(cache, cityLowerString, cacheSize))
        {
            answer += 1;
        }
        else
        {
            answer += 5;
        }
    }

    return answer;
}

int main()
{
    int cacheSize = 2;
    vector<string> cities = 
    { 
        "Jeju", "Pangyo", "NewYork", "newyork"
    };
    cout << solution(cacheSize, cities) << endl; 

    return 0;
}