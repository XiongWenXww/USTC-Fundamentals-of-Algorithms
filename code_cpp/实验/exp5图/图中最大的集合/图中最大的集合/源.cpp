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
vector<pair<int, int>> finish;		// pair��first�Žڵ����ţ�second�Žڵ���ɴ����ʱ��
int color[N], parent[N];
int belongScc[N];
// �±����1��ʼ������ݣ�finish���⣨finishû�г�ʼ����

struct scc {
	int num;	// ��ʼ��Ϊǿ��ͨ�����нڵ�ĸ���������ͨ����ͬ��ǿ��ͨ����ֱ�ӵı߽��и���
	int smcNum;		//semi_connected�������Ⱦ�����ǿ��ͨ��������ǿ��ͨ������������ɵİ���ͨ���������Ľڵ��������
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
			//	++sccNum; �˴�����Ҫ++sccNum����Ϊ�����������RDFS_VISIT����RDFS_VISIT������һ��ʼ���Ѿ�ִ����++sccNum
			RDFS_VISIT(adj, aSccNum, sccSeq);
		}
		if (belongScc[adj] && belongScc[adj] != sccSeq) {
			// ��һ���ڵ����ڵ���ͨ�����͵�ǰ�ڵ����ڵ���ͨ��������ͬһ����ͨ����
			sccEdge[belongScc[adj]].aSccEdge.push_back(sccSeq);
		}
	}
}

// ����ǿ��ͨ�����ĸ���
int RDFS() {
	for (int i = 1; i <= n; ++i) {
		color[i] = white;
	}

	int sccSeq = 0;		// ǿ��ͨ�����ڵ�����
	sort(finish.begin(), finish.end(), compare);	// ���Ӵ�С��˳�����򣬹�compare��ƽ���õĲ�̫һ��

	/*cout << "************sorted finish time(first is seq,second is time):" << endl;
	for (auto&& f : finish) {
		cout << f.first << ' ' << f.second << endl;
	}*/

	for (auto&& f : finish) {
		int aSccNum = 0;		// һ��ǿ��ͨ�����������ڵ�ĸ���
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