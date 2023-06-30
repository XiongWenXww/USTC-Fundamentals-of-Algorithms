#include<iostream>
#include<algorithm>
#include<unordered_map>
#include<vector>
#include<climits>
#define N 100000
#define M 1000000
#define MAX 1000
using namespace std;

struct edge {
	int u, v;
	int w;
}edges[M];

int dis[N + 1];

bool Relax(const edge& e) {
	int u = e.u;
	int v = e.v;
	int w = e.w;
	if (dis[u] + w < dis[v]) {
		dis[v] = dis[u] + w;
		return true;
	}
	return false;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m, s, t;
	cin >> n >> m >> s >> t;

	int u, v, w;
	// ���������ظ��ı߲�ͬ��Ȩ�ز���Ӱ�죬���������Ȩ�ؽϴ��򲻻�relax��
	// ���������Ȩ�ؽ�С������ٴ�relax������Сֵ
	for (int i = 0; i < m; ++i) {
		cin >> u >> v >> w;
		edges[i] = { u,v,w };
	}

	for (int i = 1; i <= n; ++i) {
		dis[i] = MAX;		// �˴�������INT_MAX������INT_MAX������һ����������Ϊ�������޷�relax
	}
	dis[s] = 0;

	// �����Ż���Bellman-Ford�㷨
	for (int i = 1; i <= n - 1; ++i) {
		bool unchanged = true;
		for (int j = 0; j < m; ++j) {
			if (Relax(edges[j])) {
				unchanged = false;
			}
		}
		if (unchanged) {
			break;
		}
	}

	cout << dis[t] << endl;
}