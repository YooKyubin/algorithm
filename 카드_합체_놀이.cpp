#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main()
{
    freopen("../../input.txt", "r", stdin);

    cin.tie(nullptr);
    ios_base::sync_with_stdio(false);


    int n, m;
    cin >> n >> m;
    vector<long long> cards(n);
    for (int i = 0; i< n; ++i)
    {
        cin >> cards[i];
    }
    make_heap(cards.begin(), cards.end(), greater<long long>());

    for (int i = 0; i < m; ++i)
    {
        pop_heap(cards.begin(), cards.end(), greater<long long>());
        long long src = cards.back();
        cards.pop_back(); 

        pop_heap(cards.begin(), cards.end(), greater<long long>());
        long long dst = cards.back();
        cards.pop_back(); 

        cards.push_back(src + dst);
        push_heap(cards.begin(), cards.end(), greater<long long>());
        cards.push_back(src + dst);
        push_heap(cards.begin(), cards.end(), greater<long long>());
    }

    long long sum = 0;
    for (long long i : cards)
    {
        sum += i;
    }

    cout << sum << endl;

    return 0;
}
