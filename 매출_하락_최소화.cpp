#include <string>
#include <vector>

#include <iostream>

using namespace std;

int ComputeIncludeMinSales
(
    int ID, 
    const vector<int>& sales,
    const vector<int>& childIDs, 
    const vector<int>& memoIncludeMinSales,
    const vector<int>& memoExcludeMinSales
)
{
    int minSales = sales[ID];

    for (int childID : childIDs)
    {
        // 팀장이 워크숍 가니까 팀원은 안가도 상관없음, 무조건 적은 수
        minSales += min(memoIncludeMinSales[childID], memoExcludeMinSales[childID]);
    }

    return minSales;
}

int ComputeExcludeMinSales
(
    int ID, 
    const vector<int>& sales,
    const vector<int>& childIDs, 
    const vector<int>& memoIncludeMinSales,
    const vector<int>& memoExcludeMinSales
)
{
    // 팀원이 없는데 나를 제외한다면 최소 판매액은 0 이다.
    if (childIDs.empty())
    {
        return 0;
    }

    int minSales = INT32_MAX;
    for (size_t i=0; i < childIDs.size(); ++i)
    {
        // 워크숍에 가는 팀원 ID
        const int includeChildID = childIDs[i];
        int sumChildSalse = 0;
        
        for (size_t j=0; j<childIDs.size(); ++j)
        {
            if (includeChildID == childIDs[j])
            {
                // 이 팀원(적어도 한명)은 반드시 워크숍 참여
                // 팀원이 워크숍에 갔을 때의 최소 비용
                sumChildSalse += memoIncludeMinSales[includeChildID];
            }
            else
            {
                // 다른 팀원들은 워크숍 가건말건 최소 비용
                int childID = childIDs[j];
                sumChildSalse += min(memoIncludeMinSales[childID], memoExcludeMinSales[childID]);
            }
        }

        minSales = min(sumChildSalse, minSales);
    }

    return minSales;
}

void ComputeMinSales
(
    int ID,
    const vector<int>& sales, 
    const vector<vector<int>>& graph, 
    vector<int>& memoIncludeMinSales, 
    vector<int>& memoExcludeMinSales
)
{
    // 이미 값을 구한적이 있으면 조기 리턴
    if (memoIncludeMinSales[ID] != -1)
    {
        return;
    }

    // 각 자식 노드들에 대해서 동일한 알고리즘 적용
    for (int childID : graph[ID])
    {
        ComputeMinSales(childID, sales, graph, memoIncludeMinSales, memoExcludeMinSales);
    }

    // 내가(팀장) 워크숍 갈때
    memoIncludeMinSales[ID] = 
        ComputeIncludeMinSales(ID, sales, graph[ID], memoIncludeMinSales, memoExcludeMinSales);

    // 내가(팀장) 워크숍을 가지 않을 때 -> 팀원 중 한명은 반드시 워크숍에 가야한다.
    memoExcludeMinSales[ID] = 
        ComputeExcludeMinSales(ID, sales, graph[ID], memoIncludeMinSales, memoExcludeMinSales);

}

int solution(vector<int> sales, vector<vector<int>> links) {
    int answer = 0;

    sales.insert(sales.begin(), 0);
    vector<vector<int>> graph(sales.size());
    // make graph
    for (auto& edge : links)
    {
        int from = edge[0];
        int to = edge[1];
        graph[from].push_back(to);
    }

    vector<int> memoIncludeMinSales(sales.size(), -1);
    vector<int> memoExcludeMinSales(sales.size(), -1);

    ComputeMinSales(1, sales, graph, memoIncludeMinSales, memoExcludeMinSales);

    answer = min(memoIncludeMinSales[1], memoExcludeMinSales[1]);
    return answer;
}

int main()
{

    vector<int> sales =
    // {14, 17, 15, 18, 19, 14, 13, 16, 28, 17};
    // {10, 10, 1, 1};
    // {5, 6, 5, 3, 4};
    {5, 6, 5, 1, 4};
    vector<vector<int>> links = 
    // {{10, 8}, {1, 9}, {9, 7}, {5, 4}, {1, 5}, {5, 10}, {10, 6}, {1, 3}, {10, 2}};
    // {{3,2}, {4,3}, {1,4}};
    // {{2,3}, {1,4}, {2,5}, {1,2}};
    {{2,3}, {1,4}, {2,5}, {1,2}};
    
    cout << solution(sales, links) << endl;

    return 0;
}