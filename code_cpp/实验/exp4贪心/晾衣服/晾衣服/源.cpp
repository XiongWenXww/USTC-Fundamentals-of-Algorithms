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

	// 二分法
	int left = 0, right = clothes[n - 1] - clothes[0];
	int mid, num;
	int lastClothes;
	int clothesNum = n - m;

	while (left <= right) {
		mid = (left + right) / 2;
		lastClothes = clothes[0];
		num = 1;		// 当前衣架上衣服的数量

		for (int i = 1; i < n; ++i) {
			if (clothes[i] - lastClothes >= mid) {	// 第i件衣服与上一件衣服的间距大于mid
				lastClothes = clothes[i];	// 把第i件衣服挂到衣架上
				++num;
			}
		}

		// num=clothesNum时，不一定是最优解，距离d可能更大
		// 若距离不能再大了，left=mid+1后，会因为衣架上的衣服不够多,right会一直right=mid-1
		// 最后right=left,mid=right发现衣架上的衣服还是不够多,right=mid-1=left-1，此时right为最优解
		// 若距离还能再大一点则left=mid+1直到距离不能再大，就变成了上一种情况，故最后应该输出的是right而不是mid
		if (num >= clothesNum) {		// 衣架上的衣服太多了，可以增大衣服的间距
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
//	// 从多个最小值找到那个左右两边最小的那个
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