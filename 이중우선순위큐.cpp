#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

void insert(string op, vector<int>& heap){
    int num = stoi(op);
    heap.push_back(num);
    cout << "push: " << heap.back() << endl;
    return;
}

void del(string op, vector<int>& heap) {
    if(!heap.empty()){
        if (op == "1"){
            make_heap(heap.begin(), heap.end(), less<int>()); 
            pop_heap(heap.begin(),heap.end(), [](int a, int b)->bool{return a < b;}); 
            cout << "1 pop: " << heap.back() << endl;
            heap.pop_back();
        }
        // else if (op == "1"){
        else{
            make_heap(heap.begin(), heap.end(), greater<int>()); 
            pop_heap(heap.begin(),heap.end(), [](int a, int b)->bool{return a > b;}); 
            cout << "-1 pop: " << heap.back() << endl;
            heap.pop_back();
        }
    }
    return;
}

vector<int> solution(vector<string> operations) {
    vector<int> heap;
    for (auto i: operations){
        if (i[0] == 'I'){
            insert( i.substr(2), heap );
        }
        else{
            del( i.substr(2), heap );
        }
    }
    if (heap.empty()){
        return {0, 0};
    }
    else{
        make_heap(heap.begin(), heap.end(), greater<int>());
        sort_heap(heap.begin(), heap.end(), greater<int>());
        vector<int> answer {heap.front(), heap.back()};
        return answer;
    }
}

int main() {
    // vector<string> test { "I 16", "I -5643", "D -1", "D 1", "D 1", "I 123", "D -1" };
    // vector<string> test { "I 16","I 15", "I 13", "D -1", "D 1" };
    vector<string> test { "I -45", "I 653", "D 1", "I -642", "I 45", "I 97", "D 1", "D -1", "I 333" };
    for (auto i: solution(test)){
        cout << i << " ";
    }
    cout << endl;
    return 0;
}