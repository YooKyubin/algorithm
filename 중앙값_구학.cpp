#include <iostream>
#include <vector>
#include <queue>

using namespace std;

using MinHeap = priority_queue<int, vector<int>, greater<int>>;
using MaxHeap = priority_queue<int, vector<int>, less<int>>;

void Print(int input, const MaxHeap& maxHeap, const MinHeap& minHeap)
{
	cout << "input: " << input << endl;
	cout << "maxHeap top: ";
	if (maxHeap.empty())
	{
		cout << "EMPTY";
	}
	else
	{
		cout << maxHeap.top();
	}
	cout << "\tmaxHeap size: " << maxHeap.size() << endl;
	cout << "minHeap top: ";
	if (minHeap.empty())
	{
		cout << "EMPTY";
	}
	else
	{
		cout << minHeap.top();
	}
	cout << "\tminHeap size: " << minHeap.size() << endl;
	cout << endl;
}

void Solve()
{
	int n;
	cin >> n;

	MinHeap minHeap;
	MaxHeap maxHeap;

	vector<int> outputs;
	for (int i = 0; i < n; ++i)
	{
		int input;
		cin >> input;

		if (minHeap.empty() || input > minHeap.top())
		{
			minHeap.push(input);
		}
		else
		{
			maxHeap.push(input);
		}

		if (minHeap.size() < maxHeap.size())
		{
			int temp = maxHeap.top();
			maxHeap.pop();
			minHeap.push(temp);
		}
		else if (minHeap.size() > maxHeap.size() + 1)
		{
			int temp = minHeap.top();
			minHeap.pop();
			maxHeap.push(temp);
		}

		// Print(input, maxHeap, minHeap);

		if (i % 2 == 0)
		{
			outputs.push_back(minHeap.top());
		}
	}

	cout << outputs.size() << "\n";
	for (size_t i = 0; i < outputs.size(); ++i)
	{
		cout << outputs[i] << " ";
		if ((i + 1) % 10 == 0 && (i + 1) < outputs.size())
		{
			cout << "\n";
		}
	}
	cout << "\n";
}

int main()
{
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);

	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	int t;
	cin >> t;
	while (t--)
	{
		Solve();
	}

	return 0;
}