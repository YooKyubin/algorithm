#include <iostream>

using namespace std;

struct node{
    int x;
    int y;
    int z;
};

void reduceNode(node n){
    if (n.x == 0){
        return;
    }
    n.x--;
    n.y = n.y-1;
    n.z -= 1;
    reduceNode(n);
    cout << n.x << " " << n.z << " " << n.z << endl;
}

int main(){
    node n;
    n.x = 5;
    n.y = 5;
    n.z = 5;
    reduceNode(n);
    return 0;
}