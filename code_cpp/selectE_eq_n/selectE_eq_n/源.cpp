#include <iostream>
#define N 100000

using namespace std;

int random(const int& min, const int& max) {
	srand((unsigned)time(NULL));	// 用时间作为随机生成器的种子
	return rand() % (max - min + 1) + min;
}

void exchange(int& m, int& n) {
	int tmp = m;
	m = n;
	n = tmp;
}

int partition(int* A, int p, int r) {
	int x = A[r];
	int i = p - 1;
	for (int j = p; j < r; ++j) {
		if (A[j] <= x) {
			++i;
			exchange(A[i], A[j]);
		}
	}
	exchange(A[i + 1], A[r]);
	return i + 1;
}

void print(int* A, int r) {
	for (int i = 0; i <= r; ++i) {
		cout << A[i] << ' ';
	}
	cout << endl;
}

int randomPartition(int* A, int p, int r) {
	int i = random(p, r);
	exchange(A[i], A[r]);
	return partition(A, p, r);
}

int randomSelect(int* A, int p, int r, int i) {
	if (p == r) {
		return A[p];
	}
	int q = randomPartition(A, p, r);

	int k = q - p + 1;
	if (i == k) {
		return A[q];
	}
	else if (i < k) {
		return randomSelect(A, p, q - 1, i);
	}
	else {
		return randomSelect(A, q + 1, r, i - k);
	}
}

int main() {
	int n, k;
	cin >> n >> k;
	int A[N];
	for (int i = 1; i <= n; ++i) {
		cin >> A[i];
	}
	cout << randomSelect(A, 0, n-1, k) << endl;
	return 0;
}