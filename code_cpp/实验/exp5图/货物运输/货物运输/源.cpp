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

// n��ʾ���������v��ʾ����
void DFS_VISIT(int n, int v) {
	color[v] = gray;
	for (int i = 1; i <= n; ++i) {
		if (residualNet[v][i] && color[i] == white) {	// ������ھӵĻ�
			parent[i] = v;
			DFS_VISIT(n, i);
		}
	}
	color[v] = black;
}

// n��ʾ�������
void DFS(int n,int s) {
	for (int i = 1; i <= n; ++i) {
		parent[i] = -1;
		color[i] = white;
	}

	DFS_VISIT(n, s);
	for (int i = 1; i <= n; ++i) {		// �������ж���
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
		// �˴�����Ӳ���ȡ���
		weight[u][v] += w;
		residualNet[u][v] += w;
	}

	

	vector<edge> path;
	int minFlow;
	DFS(n, s);
	
	while (FindPath(s, t, path, minFlow)) {
		for (auto&& edg : path) {
			// �����ǲ���ͼ�еıߣ��д������(u,v)�߾���С��(v,u)�߾�������Ϊ��u��v����������
			residualNet[edg.u][edg.v] -= minFlow;
			residualNet[edg.v][edg.u] += minFlow;
		}
		DFS(n, s);
	}

	int flow = 0;
	for (int i = 1; i <= n; ++i) {
		if (weight[s][i]) {		// ��s���ھ�
			flow += weight[s][i] - residualNet[s][i];
		}
	}
	cout << flow << endl;

	
}