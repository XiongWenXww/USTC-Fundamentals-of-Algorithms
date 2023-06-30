#include<iostream>
#include<algorithm>
#define N 200

using namespace std;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	cin >> n >> m;

	int clothes[N];
	for (int i = 0; i < n; ++i) {
		cin >> clothes[i];
	}
	sort(clothes, clothes + n);

	/*for (int i = 0; i < n; ++i) {
		cout << clothes[i] << ' ';
	}
	cout << endl;*/

	// ���ַ�
	int left = 0, right = clothes[n - 1] - clothes[0];
	int mid, num;
	int lastClothes;
	int clothesNum = n - m;

	while (left <= right) {
		mid = (left + right) / 2;
		lastClothes = clothes[0];
		num = 1;		// ��ǰ�¼����·�������

		for (int i = 1; i < n; ++i) {
			if (clothes[i] - lastClothes >= mid) {	// ��i���·�����һ���·��ļ�����mid
				lastClothes = clothes[i];	// �ѵ�i���·��ҵ��¼���
				++num;
			}
		}

		// num=clothesNumʱ����һ�������Ž⣬����d���ܸ���
		// �����벻���ٴ��ˣ�left=mid+1�󣬻���Ϊ�¼��ϵ��·�������,right��һֱright=mid-1
		// ���right=left,mid=right�����¼��ϵ��·����ǲ�����,right=mid-1=left-1����ʱrightΪ���Ž�
		// �����뻹���ٴ�һ����left=mid+1ֱ�����벻���ٴ󣬾ͱ������һ������������Ӧ���������right������mid
		if (num >= clothesNum) {		// �¼��ϵ��·�̫���ˣ����������·��ļ��
			left = mid + 1;
		}
		else if (num < clothesNum) {
			right = mid - 1;
		}

	}

	cout << right << endl;
}





















//#include<iostream>
//#include<algorithm>
//#include<climits>
//#include<vector>
//#include<list>
//#define N 200
//
//using namespace std;
//
//list<int>::iterator findMin(list<int>& dist) {
//	int minValue = INT_MAX;
//	vector<list<int>::iterator> minIndex;
//
//	for (auto b = dist.begin(); b != dist.end(); ++b) {
//		if (*b == minValue) {
//			minIndex.push_back(b);
//		}
//		else if (*b < minValue) {
//			minValue = *b;
//			vector<list<int>::iterator>().swap(minIndex);
//			minIndex.push_back(b);
//		}
//	}
//
//	minValue = INT_MAX;
//
//	list<int>::iterator iter, tmp;
//	int presValue;
//	// �Ӷ����Сֵ�ҵ��Ǹ�����������С���Ǹ�
//	for (auto index : minIndex) {
//		if (index == dist.begin()) {
//			tmp = index;
//			++tmp;
//			presValue = *(tmp);
//		}
//		else if (index == (--dist.end())) {
//			tmp = index;
//			--tmp;
//			presValue = *(tmp);
//		}
//		else {
//			auto l = index;
//			--l;
//			auto r = index;
//			++r;
//			presValue = min(*l, *r);
//		}
//		
//		if (presValue < minValue) {
//			minValue = presValue;
//			iter = index;
//		}
//	}
//
//
//	return iter;
//}
//
//void deleteMin(list<int>& dist, list<int>::iterator& index) {
//	list<int>::iterator l, r;
//	if (index == dist.begin()) {
//		r = index;
//		++r;
//		*r = *r + *index;
//		dist.erase(index);
//	}
//	else if (index == (--dist.end())) {
//		l = index;
//		--l;
//		*l = *l + *index;
//		dist.erase(index);
//	}
//	else {
//		l = index;
//		--l;
//		r = index;
//		++r;
//		if (*l <= *r) {
//			*l = *l + *index;
//		}
//		else {
//			*r = *r + *index;
//		}
//		dist.erase(index);
//	}
//}
//
//
//int main() {
//	ios::sync_with_stdio(false);
//	cin.tie(0);
//
//	int n, m;
//	cin >> n >> m;
//
//	int clothes[N];
//
//	for (int i = 0; i < n; ++i) {
//		cin >> clothes[i];
//	}
//	sort(clothes, clothes + n);
//
//	list<int> dist;
//	for (int i = 0; i < n - 1; ++i) {
//		dist.push_back(clothes[i + 1] - clothes[i]);
//	}
//
//	for (int i = 0; i < m; ++i) {
//		auto index = findMin(dist);
//		deleteMin(dist, index);
//	}
//	
//	
//	auto index = findMin(dist);
//	cout << *index << endl;
//	
//}