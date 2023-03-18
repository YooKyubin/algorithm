#include <iostream>
#include <cstring>

using namespace std;

int n, m;
int *ptr; //root
int *depth; //rank


int find(int x){
    if (ptr[x] == x){
        return x;
    }
    else {
        return ptr[x] = find(ptr[x]);
    }
}

void merge(int a, int b){
    a = find(a);
    b = find(b);

    if (a == b) return;

    if (depth[a] > depth[b]){
        ptr[b] = a;
    }
    else if(depth[a] < depth[b]){
        ptr[a] = b;
    }
    else{
        ptr[a] = b;
        depth[b]++;
    }
}

int main() {
    scanf("%d %d", &n, &m);
    ptr = (int*)malloc( sizeof(int) * n+1 );
    depth = (int*)malloc( sizeof(int) * n+1 );
    memset(depth, 0, sizeof(int) * n+1 );
    for(int i=0; i<=n; i++){
        ptr[i] = i;
    }

    for (int i =0; i < m; i++){
        int op, a, b;
        // cin >> op >> a >> b;
        scanf("%d %d %d", &op, &a, &b);
        switch(op){
            case 0:
                merge(a, b);
                break;

            case 1:
                if (find(a) == find(b)) printf("YES\n");
                else printf("NO\n");
                break;
        }
    }

    free(ptr);
    return 0;
}