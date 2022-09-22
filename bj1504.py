#특정한 최단 경로

import sys
from collections import deque

#https://www.acmicpc.net/board/view/85172 INF 설정하는 방법
INF = int(1e7)
n, e = map(int, sys.stdin.readline().split())
graph = [[] for _ in range(n+1)]
for _ in range(e):
    a, b, c = map(int, sys.stdin.readline().split())
    graph[a].append((b,c))
    graph[b].append((a,c))

#경유지
v1, v2 = map(int, sys.stdin.readline().split())

# 끊긴 경로가 없는지 검사
def bfs():
    visited = [False] * (n+1)
    q = deque()
    q.append(1)
    visited[1] = True
    while q:
        v = q.popleft()
        for i, d in graph[v]:
            if not(visited[i]):
                q.append(i)
                visited[i] = True

    if visited[v1] and visited[v2] and visited[n]:
        return True
    else:
        return False


def dijkstra(start):
    dist = [INF] * (n+1)
    visited = [False] * (n+1)
    dist[start] = 0
    #visited[start] = True
    
    for _ in range(n):
        v = min(list(range(1,n+1)), key = lambda x: dist[x] if not(visited[x]) else INF)
        visited[v] = True
        for i, d in graph[v]:
            dist[i] = min(dist[i], dist[v] + d)
    
    return dist


# 1 -> v1, v1 -> v2, v2 -> n
# 1 -> v2, v2 -> v1, v1 -> n
if bfs():
    dist_1 = dijkstra(1)
    dist_v1 =  dijkstra(v1)
    dist_v2 = dijkstra(v2)
    print(min(dist_1[v1] + dist_v1[v2] + dist_v2[n], dist_1[v2] + dist_v2[v1] + dist_v1[n]))
else:
    print(-1)