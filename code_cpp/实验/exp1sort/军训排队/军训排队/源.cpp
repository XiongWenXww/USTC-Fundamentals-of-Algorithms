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

	int l = 0;
	while( l < n - k + 1) {
		r = l + k - 1;
		bool flag = false;
		if (name_count[vec[l]]>1) {
			flag = true;
		}
		
		int r2 = r;
		int num = 0;
		while (r2 < n - 1) {
			++r2;
			++name_count[vec[r2]];

			if (name_count.size() == k) {
				++count;
				++num;
			}
			else if (name_count.size() > k) {
				break;
			}
		}
		
		

		// 清除r—r2在map中存储的数据
		for (int i = r + 1; i <= r2; ++i) {
			if (name_count[vec[i]] == 1) {
				name_count.erase(vec[i]);
			}
			else
				--name_count[vec[i]];
		}
		

		/*if (flag) {
			count = count + num;
			if ((vec[l] == vec[r + 1]||name_count[vec[r+1]]==0) && name_count.size() == k) {
				++count;
			}
			l = l + 2;
			continue;
		}*/

		if (flag && r < n - 1) {

			count = count + num;
			if (name_count[vec[l]] == 1) {
				name_count.erase(vec[l]);
			}
			else {
				--name_count[vec[l]];
			}

			++name_count[vec[r + 1]];
			if (r < n - 2) {

				if (name_count[vec[l + 1]] == 1) {
					name_count.erase(vec[l + 1]);
				}
				else {
					--name_count[vec[l + 1]];
				}

				++name_count[vec[r + 2]];
				if (name_count.size() == k) {
					++count;
				}
			}
			l = l + 2;

			continue;

		}

		// 窗口滑动，更新相关的值
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
		
		++l;
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