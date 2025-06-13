#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void Insert(vector<int>& heap, int value)
{
    heap.push_back(value);
    push_heap(heap.begin(), heap.end(), less<int>());
}

void PopMax(vector<int>& heap)
{
    pop_heap(heap.begin(), heap.end());
    heap.pop_back();
}

void PopMin(vector<int>& heap)
{
    make_heap(heap.begin(), heap.end(), greater<int>());

    pop_heap(heap.begin(), heap.end());
    heap.pop_back();

    make_heap(heap.begin(), heap.end(), less<int>());
}
#include <iostream>
void Print(const vector<int>& heap)
{
    for (auto i : heap)
    {
        cout << i << " ";
    }
    cout << endl;
}

vector<int> solution(vector<string> operations) {
    vector<int> answer;

    vector<int> heap;

    for (const string& operation : operations)
    {
        if (operation[0] == 'D')
        {
            if (heap.empty())
            {
                continue;
            }

            int value = stoi(operation.substr(1));

            if(value < 0)
            {
                PopMin(heap);
            }
            else
            {
                PopMax(heap);
            }
        }
        else
        {
            int value = stoi(operation.substr(1));
            Insert(heap, value);
        }

        Print(heap);
    }

    if (heap.empty())
    {
        answer.push_back(0);
        answer.push_back(0);
    }
    else
    {
        sort_heap(heap.begin(), heap.end());
        answer.push_back(heap.back());
        answer.push_back(heap.front());
    }

    return answer;
}

#include <iostream>

int main()
{
    vector<string> operations = 
    {"I -45", "I 653", "D 1", "I -642", "I 45", "I 97", "D 1", "D -1", "I 333"};

    for (int i : solution(operations))
    {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}