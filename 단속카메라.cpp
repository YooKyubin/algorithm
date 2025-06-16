#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> routes) {
    int answer = 0;
    
    sort(routes.begin(), routes.end(), [](const vector<int>& src, const vector<int>& dst)->bool
         {
             if (src[1] == dst[1])
             {
                 return src[0] < dst[0];
             }
             return src[1] < dst[1];
         });
        
    int end_time = -30000;
    for (const vector<int>& route : routes)
    {
        if (route[0] > end_time)
        {
            ++answer;
            end_time = route[1];
        }
    }
    
    return answer;
}
