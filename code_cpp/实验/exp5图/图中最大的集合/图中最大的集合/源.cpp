#include<iostream>
#include<algorithm>
#include<vector>
#define N 5001

using namespace std;

enum { white = 1, gray, black };

int n, m;
int timer = 0;
vector<vector<int>> edge(N);
vector<vector<int>> redge(N);
int d[N];
vector<pair<int, int>> finish;		// pair中first放节点的序号，second放节点完成处理的时间
int color[N], parent[N];
int belongScc[N];
// 下标均从1开始存放数据，finish除外（finish没有初始化）

struct scc {
	int num;	// 初始化为强连通分量中节点的个数，后面通过不同的强连通分量直接的边进行更新
	int smcNum;		//semi_connected：从最先经过的强连通分量到此强连通分量中所能组成的半连通分量包含的节点的最大个数
	vector<int> aSccEdge;
};

vector<scc> sccEdge(N);

bool compare(pair<int, int>& p1, pair<int, int>& p2) {
	return p1.second > p2.second;
}

void DFS_VISIT(int u) {
	++timer;
	d[u] = timer;
	color[u] = gray;
	for (auto&& adj : edge[u]) {
		if (color[adj] == white) {
			parent[adj] = u;
			DFS_VISIT(adj);
		}
	}
	++timer;
	finish.push_back({ u,timer });
	// f[u] = timer;
	color[u] = black;
}

void DFS() {
	for (int i = 1; i <= n; ++i) {
		color[i] = white;
	}

	timer = 0;
	for (int i = 1; i <= n; ++i) {
		if (color[i] == white) {
			DFS_VISIT(i);
		}
	}
}

void RDFS_VISIT(int u,int & aSccNum,const int& sccSeq) {
	color[u] = gray;
	belongScc[u] = sccSeq;
	++aSccNum;

	for (auto&& adj : redge[u]) {
		if (color[adj] == white) {
			//	++sccNum; 此处不需要++sccNum，因为接下来会调用RDFS_VISIT，而RDFS_VISIT函数中一开始就已经执行了++sccNum
			RDFS_VISIT(adj, aSccNum, sccSeq);
		}
		if (belongScc[adj] && belongScc[adj] != sccSeq) {
			// 另一个节点所在的联通分量和当前节点所在的连通分量不是同一个连通分量
			sccEdge[belongScc[adj]].aSccEdge.push_back(sccSeq);
		}
	}
}

// 返回强连通分量的个数
int RDFS() {
	for (int i = 1; i <= n; ++i) {
		color[i] = white;
	}

	int sccSeq = 0;		// 强连通分量节点的序号
	sort(finish.begin(), finish.end(), compare);	// 按从大到小的顺序排序，故compare和平常用的不太一样

	/*cout << "************sorted finish time(first is seq,second is time):" << endl;
	for (auto&& f : finish) {
		cout << f.first << ' ' << f.second << endl;
	}*/

	for (auto&& f : finish) {
		int aSccNum = 0;		// 一个强连通分量中所含节点的个数
		if (color[f.first] == white) {
			++sccSeq;
			RDFS_VISIT(f.first, aSccNum, sccSeq);
			sccEdge[sccSeq].num = aSccNum;
			sccEdge[sccSeq].smcNum = aSccNum;
		}
	}
	return sccSeq;
}

int FindScc() {
	DFS();

	/*cout << "***********start time:" << endl;
	for (int i = 1; i <= n; ++i) {
		cout << d[i] << ' ';
	}
	cout << endl;

	cout << "************finish time(first is seq,second is time):" << endl;
	for (auto&& f : finish) {
		cout << f.first << ' ' << f.second << endl;
	}*/

	return RDFS();
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	cin >> n >> m;

	int u, v;
	for (int i = 0; i < m; ++i) {
		cin >> u >> v;
		edge[u].push_back(v);
		redge[v].push_back(u);
	}

	int sccNum = FindScc();	
	int maxNum = -1;

	/*cout << "********************sccEdge:" << endl;
	for (int i = 1; i <= sccNum; ++i) {
		cout << "num: " << sccEdge[i].num << "  smcNum: " << sccEdge[i].smcNum << "          " << "adj: ";
		for (auto&& adj : sccEdge[i].aSccEdge) {
			cout << adj << ' ';
		}
		cout << endl;
	}*/


	for (int i = 1; i <= sccNum; ++i) {
		if (sccEdge[i].smcNum > maxNum)
			maxNum = sccEdge[i].smcNum;
		for (auto&& adj : sccEdge[i].aSccEdge) {
			sccEdge[adj].smcNum = max(sccEdge[adj].smcNum, sccEdge[adj].num + sccEdge[i].smcNum);
			if (sccEdge[adj].smcNum > maxNum) {
				maxNum = sccEdge[adj].smcNum;
			}
		}
	}

	cout << maxNum << endl;
}