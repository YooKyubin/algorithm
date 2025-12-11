#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

class SegmentTree
{
public:
    SegmentTree(const vector<int>& array)
    : arraySize(static_cast<int>(array.size()))
    {
        int height = ceil(log2(arraySize)) + 1;
        int treeSize = 1 << height; // (2 ^ height);

        m_value.assign(treeSize, INF);

        Init(1, arraySize, 1, array);
    }

    int Query(int rangeStart, int rangeEnd)
    {
        return Query({rangeStart, rangeEnd}, 1, arraySize, 1);
    }


private:
    int Init(int start, int end, int treeID, const vector<int>& array)
    {
        if (start == end)
        {
            return m_value[treeID] = array[start-1];
        }

        int mid = (start + end) >> 1;

        int left  = Init(start,   mid, treeID * 2,     array);
        int right = Init(mid + 1, end, treeID * 2 + 1, array);

        return m_value[treeID] = min(left, right);
    }

    int Query(pair<int, int> range, int start, int end, int treeID)
    {
        // 범위가 완전히 벗어남
        if (end < range.first || start > range.second)
        {
            return INF;
        }

        // 완전 겹침, 포함, range <- start ~ end
        if (range.first <= start && end <= range.second)
        {
            return m_value[treeID];
        }

        // 일부 겹침
        int mid = (start + end) >> 1;
        int leftSub  = Query(range, start,   mid, treeID * 2    );
        int rightSub = Query(range, mid + 1, end, treeID * 2 + 1);
        return min(leftSub, rightSub);
    }

private:
    int arraySize;
    vector<int> m_value;

    static constexpr int INF = 1'000'000'000 + 1;
};

int main()
{
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;

    vector<int> nums(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> nums[i];
    }

    SegmentTree tree(nums);

    for (int i = 0; i < m; ++i)
    {
        int rangeStart, rangeEnd;
        cin >> rangeStart >> rangeEnd;

        cout << tree.Query(rangeStart, rangeEnd) << "\n";
    }

    return 0;
}