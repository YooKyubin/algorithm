import sys
from collections import deque
sys.setrecursionlimit(10000)

n = int(sys.stdin.readline())
graph = [[] for _ in range(n+1)]
for _ in range(n):
  a, b = map(int, sys.stdin.readline().split())
  graph[a].append(b)
  graph[b].append(a)


cycle_node = []
visited = [False] * (n+1)
dist = [-1] * (n+1)

# 사이클을 찾았을 때 이전 노드들을 추적하며 사이클을 이루는 노드 탐색하기 위함
pre_node = [0] * (n+1)
# 사이클 찾기
def dfs(v):
  visited[v] = True
  for i in graph[v]:
    # cycle_node가 비어있다면 사이클을 아직 찾지 못한 상태
    if not(cycle_node):
      if not(visited[i]):
        pre_node[i] = v
        dfs(i)
      # 바로 이전에 탐색한 노드가 아닌 경우
      elif pre_node[v] != i:
        cycle_node.append(v)
        # 거꾸로 거슬러 올라가며 사이클에 해당하는 노드 경로 추적
        while v != i:
          cycle_node.append(pre_node[v])
          v = pre_node[v]
          
# 거리 계산
def bfs():
  q = deque(cycle_node)
  while q:
    v = q.popleft()
    for i in graph[v]:
      if dist[i] == -1:
        dist[i] = dist[v] + 1
        q.append(i)
  
dfs(1)
for i in cycle_node:
  dist[i] = 0
bfs()
print(*dist[1:])