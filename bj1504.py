#특정한 최단 경로
import sys
from collections import deque

n, e = map(int, sys.stdin.readline().split())
graph = [[] for _ in range(n+1)]
for _ in range(e):
    a, b, c = map(int, sys.stdin.readline().split())
    graph[a].append((b,c))
    graph[b].append((a,c))

#경유지
v1, v2 = map(int, sys.stdin.readline().split())
def cal_dist(start, dp_n):
    q = deque()
    visited = [False] * (n+1)
    q.append(start)
    dp[dp_n][start] = 0
    visited[start] = True
    while q:
        v = q.popleft()
        for i, d in graph[v]:
            if not(visited[i]):
                dp[dp_n][i] = min(dp[dp_n][i], dp[dp_n][v] + d)
        # visited가 False인 dp값이 가장 작은 연결된 노드, dp값의 인덱스
        temp_distance = sys.maxsize
        next_node = 0
        new = False
        for i, d in graph[v]:
            if not(visited[i]):
                if temp_distance > dp[dp_n][i]:
                    new = True
                    next_node = i
                    temp_distance = dp[dp_n][i]
        if new:          
            q.append(next_node)
            visited[v] = True

# 1 -> v1, v1 -> v2, v2 -> n
# 1 -> v2, v2 -> v1, v1 -> n
dp = [[sys.maxsize] * (n+1) for _ in range(3)]

cal_dist(1, 0)
cal_dist(v1, 1)
cal_dist(v2, 2)

print(min(dp[0][v1] + dp[1][v2] + dp[2][n], dp[0][v2] + dp[2][v1] + dp[1][n]))