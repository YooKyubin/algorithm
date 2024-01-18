#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

struct Vertex
{
	float x;
	float y;
};

struct Node
{
	int idx;
	float dist;

	//bool operator>(const Node& input)
	//{
	//	return this->dist > input.dist;
	//}
};

bool operator>(const Node& a, const Node& b)
{
	return a.dist > b.dist;
}

int n;
vector<Vertex> vertices;
vector<bool> visited;

float getDist(const Vertex& from, const Vertex& to)
{
	float dx = to.x - from.x;
	float dy = to.y - from.y;

	return sqrt(dx * dx + dy * dy);
}

int main()
{
	cin >> n;
	vertices.resize(n);
	visited.resize(n, false);
	for (int i = 0; i < n; ++i)
	{
		cin >> vertices[i].x;
		cin >> vertices[i].y;
	}

	priority_queue<Node, vector<Node>, greater<Node> > pq;
	pq.push({ 0, 0 });
	int MSTsize = 0;
	float totalDist = 0.0;

	while (!pq.empty())
	{
		int cur = pq.top().idx;
		float curDist = pq.top().dist;
		pq.pop();

		if (visited[cur])
			continue;

		++MSTsize;
		totalDist += curDist;
		visited[cur] = true;

		if (MSTsize == n)
			break;

		for (int i = 0; i < n; ++i)
		{
			if (visited[i])
				continue;

			float nDist = getDist(vertices[cur], vertices[i]);
			pq.push({ i, nDist });
		}
	}

	cout << fixed;
	cout.precision(2);

	cout << totalDist << endl;


	return 0;
}