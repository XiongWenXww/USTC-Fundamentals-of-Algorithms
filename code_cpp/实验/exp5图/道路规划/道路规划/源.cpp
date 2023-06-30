#include<iostream>
#include<algorithm>
#include<climits>
#include<vector>
#include<unordered_map>
#define N 100000

using namespace std;
// 注意：不需要另外可以用类似与数组或vector<unordered_map<int, int>>的方式来存储边
// 此题不要求通过u、v快速访问权重，即使会有对边的重复赋值，但在kruskal算法中，有对
// 边的排序，故只需要将输入的边直接放入存储边的容器中即可，后面对边的遍历也是从权值
// 较小的边开始遍历，故只需设置一个用来控制合并次数的值，当合并次数为n时退出循环即可，
// 若用数组或其他容器来存储边，方便对输入重复的边进行更新，但这样增加了时间复杂度

int parent[N + 1];

struct edge {
	int u, v;
	int w;
};

bool Compare(const edge& e1, const edge& e2) {
	return e1.w < e2.w;
}

int FindSet(int u) {
	if (u != parent[u]) {
		parent[u] = FindSet(parent[u]);
	}
	return parent[u];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	vector<edge> edges;

	int u, v, w;

	for (int i = 1; i <= m; ++i) {
		cin >> u >> v >> w;
		edges.push_back({ u,v,w });
	}

	sort(edges.begin(), edges.end(), Compare);

	for (int i = 1; i <= n; ++i) {
		parent[i] = i;
	}

	int i = 0;
	int totalCost = 0;
	for (auto&& iter : edges) {
		int set1 = FindSet(iter.u);
		int set2 = FindSet(iter.v);
		if (set1 != set2) {
			parent[set2] = set1;
			totalCost += iter.w;

			++i;
			if (i >= n) {
				break;
			}
		}
	}
	cout << totalCost << endl;
}