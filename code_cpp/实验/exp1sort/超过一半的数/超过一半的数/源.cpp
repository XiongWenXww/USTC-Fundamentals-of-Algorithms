//首先输入一个正整数TT，代表存在T组样例。
//接下来共TT组样例，每组样例中首先输入N，下一行N个正整数。
//在每组样例中你需要找到是否存在一个“超过一半的数”x（即存在x在这N个数中出现次数≥(N + 1) / 2），
//若存在这样的x请输出x，否则输出 - 1
#include<iostream>
#define N 20
#define MAX 1000000

using namespace std;

int check(const int* a, const int& value, const int& len) {
	int count = 0;
	for (int i = 0; i < len; ++i) {
		if (a[i] == value) {
			++count;
		}
	}

	if (count >= (len + 1) / 2) 
		return value;
	else 
		return -1;
}


int main() {
	int t, n;
	int result[N], a[MAX];

	cin >> t;
	
	for (int i = 0; i < t; ++i) {
		cin >> n;

		int times, value;

		cin >> a[0];
		value = a[0];
		times = 1;
		for (int j = 1; j < n; ++j) {
			cin >> a[j];

			if (times == 0) {
				value = a[j];
				times = 1;
			}
			else if (value != a[j]) 
				--times;
			else
				++times;

		}
		if (times != 0) {
			result[i] = check(a,value,n);
		}
		else {
			result[i] = -1;
		}
	}

	for (int i = 0; i < t; ++i) {
		cout << result[i] << endl;
	}
}