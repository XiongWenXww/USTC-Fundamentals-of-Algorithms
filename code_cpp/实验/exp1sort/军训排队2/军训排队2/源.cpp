#include<iostream>
#include<map>
#include<vector>

using namespace std;

int fun(vector<string>& vec, const int& k) {
	map<string, int> name_count;

	int count = 0;
	int n = vec.size(), r;

	// 初始化map
	for (int i = 0; i < k; ++i) {
		++name_count[vec[i]];
	}
	if (name_count.size() == k) {
		++count;
	}

	for (int l = 0; l < n - k + 1; ++l) {
		r = l + k - 1;
		map<string, int> tmp(name_count);
		
		while (r < n - 1) {
			++r;
			
			++tmp[vec[r]];

			if (tmp.size() == k) {
				++count;
			}
			else if (tmp.size() > k) {
				break;
			}
		}

		r = l + k - 1;	// 通过上面的while循环，r的值可能已经改变

		// 滑动窗口，更新num的值
		if (r < n - 1) {
			if (name_count[vec[l]] == 1) {
				name_count.erase(vec[l]);
			}
			else {
				--name_count[vec[l]];
			}
			++name_count[vec[r + 1]];
			if (name_count.size() == k) {
				++count;
			}
		}

	}
	return count;
}

int main() {
	int n, k;
	vector<string> vec;
	string name;

	cin >> n >> k;
	for (int i = 0; i < n; ++i) {
		cin >> name;
		vec.push_back(name);
	}

	cout << fun(vec, k) << endl;
}