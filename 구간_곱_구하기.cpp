#include <iostream>
#include <vector>
#include <cmath>

#define MOD 1'000'000'007

using namespace std;

int n, m, k;
int height;
int treeSize;
vector<uint64_t> arr;
vector<int> tree;

int init(int idx, int start, int end)
{
    if (start == end)
        return tree[idx] = arr[start];
    
    int mid = (start + end) / 2;
    tree[idx] = (uint64_t)init(idx*2 + 1, start, mid) * init(idx*2 + 2, mid + 1, end) % MOD;
    return tree[idx] ;
}

int getMul(pair<int, int> range, int idx, int start, int end)
{
    if (end < range.first || range.second < start)
        return 1;
    
    if (range.first <= start && end <= range.second)
        return tree[idx];
    
    int mid = (start + end) / 2;
    return (uint64_t)getMul(range, idx*2 + 1, start, mid) * getMul(range, idx*2 + 2, mid+1, end) % MOD;
}

int update(int num, int target, int idx, int start, int end)
{
    // if (start == end && target == start)
    //     return tree[idx] = num;

    if (target < start || end < target) // 반드시 이 조건 먼저 확인
        return tree[idx];

    if (start == end)
        return tree[idx] = num;

    int mid = (start + end) / 2;
    return tree[idx] = (uint64_t)update(num, target, idx*2 + 1, start, mid) * update(num, target, idx*2 + 2, mid+1, end) % MOD;
}

int main()
{
    cin.tie(0);
    ios_base::sync_with_stdio(false);

    cin >> n >> m >> k;
    arr.resize(n);
    height = ceil(log2(n));
    treeSize = (1 << (height+1) )-1;
    tree.resize(treeSize, 0);
    for (int i=0; i<n; ++i)
    {
        cin >> arr[i];
    }

    init(0, 0, n-1);

    for (int i=0; i< m+k; ++i)
    {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 1)
        {
            update(c, b-1, 0, 0, n-1);
        }
        else
        {
            cout << getMul({b-1, c-1}, 0, 0, n-1) << "\n";
        }
    }

    return 0;
}