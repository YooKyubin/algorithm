#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void FindCyle(const vector<int>& arr, int curr, int root, vector<int>& cycle)
{
	cycle.push_back(curr);

	int next = arr[curr];
	if (next == root)
	{
		return;
	}

	FindCyle(arr, next, root, cycle);
}

// visited < depth, root >
void FindNext(const vector<int>& arr, int curr, vector<pair<int, int>>& visited, int depth, int root, vector<int>& cycle)
{
	if (depth == arr.size())
	{
		return;
	}

	visited[curr].first = depth;
	visited[curr].second = root;

	int next = arr[curr];
	if (visited[next].first != 0)
	{
		if (visited[next].second == root)
		{
			FindCyle(arr, next, next, cycle);
		}
		return;
	}

	FindNext(arr, next, visited, depth + 1, root, cycle);
}


int main()
{
	freopen("../../input.txt", "r", stdin);
	
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	int n;
	cin >> n;
	vector<int> arr(n + 1);
	for (int i = 1; i <= n; ++i)
	{
		cin >> arr[i];
	}

	int answer = 0;
	vector<pair<int, int>> visited(n + 1, {0, 0});
	vector<int> cycle;
	cycle.reserve(n);
	for (int i = 1; i <=n; ++i)
	{
		if (visited[i].first != 0)
		{
			continue;
		}

		FindNext(arr, i, visited, 1, i, cycle);
	}
	sort(cycle.begin(), cycle.end());

	cout << cycle.size() << "\n";
	for (int i : cycle)
	{
		cout << i << "\n";
	}

	return 0;
}