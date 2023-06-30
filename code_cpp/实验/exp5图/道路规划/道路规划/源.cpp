#include<iostream>
#include<algorithm>
#include<climits>
#include<vector>
#include<unordered_map>
#define N 100000

using namespace std;
// ע�⣺����Ҫ��������������������vector<unordered_map<int, int>>�ķ�ʽ���洢��
// ���ⲻҪ��ͨ��u��v���ٷ���Ȩ�أ���ʹ���жԱߵ��ظ���ֵ������kruskal�㷨�У��ж�
// �ߵ����򣬹�ֻ��Ҫ������ı�ֱ�ӷ���洢�ߵ������м��ɣ�����Աߵı���Ҳ�Ǵ�Ȩֵ
// ��С�ı߿�ʼ��������ֻ������һ���������ƺϲ�������ֵ�����ϲ�����Ϊnʱ�˳�ѭ�����ɣ�
// ��������������������洢�ߣ�����������ظ��ı߽��и��£�������������ʱ�临�Ӷ�

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