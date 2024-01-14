#include <iostream>
#include <vector>

using namespace std;

struct Rec
{
	int x1;
	int y1;
	int x2;
	int y2;
};

int n;
vector<Rec> points;
vector<int> parent;

bool isOverlapped(int i, int j)
{
	const Rec& a = points[i];
	const Rec& b = points[j];

	if (b.y2 > a.y2 && a.x2 < b.x2 && a.y1 > b.y1 && b.x1 < a.x1)
		return false;
	if (a.y2 > b.y2 && b.x2 < a.x2 && b.y1 > a.y1 && b.x1 > a.x1)
		return false;

	if (b.y1 > a.y2 || b.x1 > a.x2 || a.y1 > b.y2 || b.x2 < a.x1)
		return false;

	return true;
}

int find(int x)
{
	if (parent[x] == x)
		return x;

	return parent[x] = find(parent[x]);
}

void merge(int x, int y)
{
	x = find(x);
	y = find(y);
	parent[x] = y;
}

int main()
{
	cin >> n;
	points.resize(n+1);
	parent.resize(n+1, 0); // parent[0] = 0;
	points[0] = { 0, 0, 0, 0 }; // 원점
	for (int i = 1; i <= n; ++i)
	{
		int a, b, c, d;
		cin >> a >> b >> c >> d;

		points[i] = { a, b, c, d };
		parent[i] = i;
	}

	for (int i = 0; i <= n; ++i)
	{
		for (int j = i+1; j <= n; ++j)
		{
			if (isOverlapped(i, j))
			{
				merge(i, j);
			}
		}
	}

	vector<bool> visited(n + 1, false);
	for (int i = 0; i <= n; ++i)
	{
		visited[ find(i) ] = true;
	}

	int cnt = 0;
	for (int i = 0; i <= n; ++i)
	{
		if (visited[i])
			++cnt;
	}

	cout << cnt-1 << endl;


	return 0;
}