#include<iostream>
#include<algorithm>
#include<queue>
#include<climits>
#define N 500

using namespace std;
enum { white = 1, gray, black };

int weight[N + 1][N + 1];
int residualNet[N + 1][N + 1];
int parent[N + 1];
int color[N + 1];

struct edge {
	int u, v;
	//int w;
};

// n表示顶点个数，v表示顶点
void DFS_VISIT(int n, int v) {
	color[v] = gray;
	for (int i = 1; i <= n; ++i) {
		if (residualNet[v][i] && color[i] == white) {	// 如果是邻居的话
			parent[i] = v;
			DFS_VISIT(n, i);
		}
	}
	color[v] = black;
}

// n表示顶点个数
void DFS(int n,int s) {
	for (int i = 1; i <= n; ++i) {
		parent[i] = -1;
		color[i] = white;
	}

	DFS_VISIT(n, s);
	for (int i = 1; i <= n; ++i) {		// 对于所有顶点
		if (color[i] == white) {
			DFS_VISIT(n, i);
		}
	}
}

bool FindPath(const int& s, const int& t,vector<edge>& path,int& minFlow) {
	int tmp = t;
	minFlow = INT_MAX;
	vector<edge>().swap(path);

	int u, v, w;
	while (parent[tmp] > 0&&tmp!=s) {
		u = parent[tmp];
		w = residualNet[parent[tmp]][tmp];
		path.push_back({ u,tmp});
		if (w < minFlow) {
			minFlow = w;
		}

		tmp = parent[tmp];
	}
	if (tmp == s)
		return true;
	else
		return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	
	int n, m, s, t;
	cin >> n >> m >> s >> t;

	int u, v, w;
	for (int i = 0; i < m; ++i) {
		cin >> u >> v >> w;
		// 此处是相加不是取最大
		weight[u][v] += w;
		residualNet[u][v] += w;
	}

	

	vector<edge> path;
	int minFlow;
	DFS(n, s);
	
	while (FindPath(s, t, path, minFlow)) {
		for (auto&& edg : path) {
			// 不管是不是图中的边，残存网络的(u,v)边均减小，(v,u)边均增大，因为从u到v的流增大了
			residualNet[edg.u][edg.v] -= minFlow;
			residualNet[edg.v][edg.u] += minFlow;
		}
		DFS(n, s);
	}

	int flow = 0;
	for (int i = 1; i <= n; ++i) {
		if (weight[s][i]) {		// 是s的邻居
			flow += weight[s][i] - residualNet[s][i];
		}
	}
	cout << flow << endl;

	
}