#include <string>
#include <vector>
#include <map>
#include <set>
#include <iostream>

using namespace std;

struct Coord
{
	int x;
	int y;

	Coord operator+(const Coord& other) const
	{
		return { x + other.x, y + other.y };
	}

	bool OOB() const
	{
		return x < -5 || x > 5 || y < -5 || y > 5;
	}

	bool operator<(const Coord& other) const
	{
		if (x == other.x)
		{
			return y < other.y;
		}
		return x < other.x;
	}
};

pair<Coord, Coord> MakeEdge(Coord src, Coord dst)
{
	if (src < dst)
	{
		swap(src, dst);
	}
	return { src, dst };
}

int solution(string dirs) {
	int answer = 0;

	map<char, Coord> move = {
		{ 'L', Coord{  0, -1 } },
		{ 'R', Coord{  0,  1 } },
		{ 'U', Coord{ -1,  0 } },
		{ 'D', Coord{  1,  0 } },
	};

	set<pair<Coord, Coord>> edges;
	Coord curr{ 0, 0 };

	for (const char dir : dirs)
	{
		Coord next = curr + move[dir];
		if (next.OOB())
		{
			continue;
		}

		edges.insert(MakeEdge(curr, next));

		curr = next;
	}
	answer = static_cast<int>(edges.size());

	return answer;
}

int main()
{
	freopen("../../input.txt", "r", stdin);

	string dirs;
	cin >> dirs;

	cout << solution(dirs) << endl;

	return 0;
}