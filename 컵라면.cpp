#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

struct Problem
{
    int deadline;
    int price;
};

void PushHeap(vector<int>& heap, int value)
{
    heap.push_back(value);
    push_heap(heap.begin(), heap.end(), greater<int>());
}

void PopHeap(vector<int>& heap)
{
    pop_heap(heap.begin(), heap.end(), greater<int>());
    heap.pop_back();
}

int main()
{
    freopen("../../input.txt", "r", stdin);
    // freopen("../../output.txt", "w", stdout);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);

    int n;
    cin >> n;

    // <deadline, price>
    vector<Problem> problems(n);
    for (int i = 0;i < n; ++i)
    {
        cin >> problems[i].deadline >> problems[i].price;
    }
    sort(problems.begin(), problems.end(), [](auto& src, auto& dst)->bool
    {
        if (src.deadline == dst.deadline)
        {
            return src.price > dst.price;
        }
        return src.deadline < dst.deadline;
    });

    vector<int> priceByDay;
    // priority_queue<int, vector<int>, less<int>> priceByDay;
    priceByDay.reserve(n);

    for (const Problem& problem : problems)
    {
        if (priceByDay.size() < problem.deadline)
        {
            PushHeap(priceByDay, problem.price);
        }
        else
        {
            if (problem.price > priceByDay.front())
            {
                PopHeap(priceByDay);
                PushHeap(priceByDay, problem.price);
            }
        }
    }

    int totalPrice = 0;
    for (int i : priceByDay)
    {
        totalPrice += i;
    }

    cout << totalPrice << endl;

    return 0;
}

// https://www.acmicpc.net/board/view/97635