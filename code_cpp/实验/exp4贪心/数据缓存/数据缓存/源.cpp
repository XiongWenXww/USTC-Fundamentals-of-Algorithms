#include<iostream>
#include<unordered_map>
#include<algorithm>
#include<vector>
#include<climits>

using namespace std;

typedef int addr;
typedef int nextSequence;
typedef int lastSequence;

typedef pair<addr, nextSequence> addrAndNext;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, k;
	int i;

	cin >> n >> k;

	vector<addrAndNext> visitAddr(n);
	unordered_map<addr, lastSequence> lastUsed;

	

	for (i = 0; i < n; ++i) {
		cin >> visitAddr[i].first;
		visitAddr[i].second = INT_MAX;

		auto t = lastUsed.find(visitAddr[i].first);
		if (t != lastUsed.end()) {		// ��i������ĵ�ַ���ǵ�һ�γ���
			visitAddr[t->second].second = i;		// ���´˵�ַ����һ�γ��ֵ����
			t->second = i;		// ���µ�ǰ�˵�ַ���һ��ʹ�õ����
		}
		else {
			lastUsed[visitAddr[i].first] = i;
		}
	}

	unordered_map<addr,nextSequence> cache;
	int miss = 0;
	i = 0;
	// ��ʼ��,��cache����
	while (cache.size() < k && i < n) {
		auto t = cache.find(visitAddr[i].first);
		if (t != cache.end()) {		// ����
			t->second = visitAddr[i].second;
		}
		else {
			++miss;
			cache.insert(visitAddr[i]);
		}
		++i;
	}

	for (; i < n; ++i) {
		auto t = cache.find(visitAddr[i].first);

		if (t != cache.end()) {
			t->second = visitAddr[i].second;
		}
		else {
			++miss;
			int maxNextSeq = -1;
			int addr;
			for (auto b = cache.begin(); b != cache.end(); ++b) {
				if (b->second > maxNextSeq) {
					maxNextSeq = b->second;
					addr = b->first;
				}
			}
			cache.erase(addr);
			cache.insert(visitAddr[i]);
		}
	}
	cout<<miss<<endl;
}