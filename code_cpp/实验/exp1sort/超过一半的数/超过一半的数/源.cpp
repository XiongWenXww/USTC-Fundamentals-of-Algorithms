//��������һ��������TT���������T��������
//��������TT��������ÿ����������������N����һ��N����������
//��ÿ������������Ҫ�ҵ��Ƿ����һ��������һ�������x��������x����N�����г��ִ�����(N + 1) / 2����
//������������x�����x��������� - 1
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