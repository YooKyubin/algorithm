#include <iostream>
#include <vector>
#include <array>
#include <queue>

using namespace std;

struct Result
{
	int win;
	int draw;
	int lose;
};

constexpr int numNations = 6;
constexpr int numGames = numNations * (numNations - 1) / 2;
constexpr array<pair<int, int>, numGames> GetGames()
{
	array<pair<int, int>, numGames> games{};
	int id = 0;
	for (int i = 0; i < numNations; ++i)
	{
		for (int j = i + 1; j < numNations; ++j)
		{
			games[id].first = i;
			games[id].second = j;
			++id;
		}
	}

	return games;
}

bool IsPossible(vector<Result>& results, int depth)
{
	if (depth == numGames)
	{
		for (Result& result : results)
		{
			bool possible = result.win == 0 && result.draw == 0 && result.lose == 0;

			if (possible == false)
			{
				return false;
			}
		}

		return true;
	}

	static constexpr auto games = GetGames();
	int src = games[depth].first;	
	int dst = games[depth].second;	
	bool possible = false;


	// win
	if (results[src].win > 0 && results[dst].lose > 0)
	{
		--results[src].win;
		--results[dst].lose;
		possible |= IsPossible(results, depth + 1);
		++results[src].win;
		++results[dst].lose;
	}

	// draw
	if (results[src].draw > 0 && results[dst].draw > 0)
	{
		--results[src].draw;
		--results[dst].draw;
		possible |= IsPossible(results, depth + 1);
		++results[src].draw;
		++results[dst].draw;
	}

	// lose
	if (results[src].lose > 0 && results[dst].win > 0)
	{
		--results[src].lose;
		--results[dst].win;
		possible |= IsPossible(results, depth + 1);
		++results[src].lose;
		++results[dst].win;
	}

	return possible;
}

int main()
{
	freopen("../../input.txt", "r", stdin);
	
	cin.tie(nullptr);
	ios_base::sync_with_stdio(false);

	for (int i = 0; i < 4; ++i)
	{
		vector<Result> results(6);
		for (int j = 0; j < 6; ++j)
		{
			int win, draw, lose;
			cin >> win >> draw >> lose;

			results[j] = Result{ win, draw, lose };
		}

		cout << (IsPossible(results, 0) ? 1 : 0) << " ";
	}
	cout << "\n";
	
	return 0;
}