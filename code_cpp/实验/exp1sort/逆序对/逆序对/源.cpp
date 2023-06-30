#include <iostream>
#define N 1000
#define MOD 10000007

using namespace std;

int merge(int* A, int* B, int l, int r, int m) {
	int num = 0;
	int p = l, q = m + 1, k = l;
	while (p <= m && q <= r) {
		if (A[p] > A[q]) {
			num = num + m - p + 1;
			num = num % MOD;
			B[k++] = A[q];
			++q;
		}
		else {
			B[k++] = A[p];
			++p;
		}
	}
	while (p <= m) {
		B[k++] = A[p];
		++p;
	}
	while (q <= r) {
		B[k++] = A[q];
		++q;
	}
	for (int i = l; i <= r; ++i) {
		A[i] = B[i];
	}
	return num;
}

int mergeS(int* A, int* B, int l, int r) {
	if (l < r) {
		int m = (l + r - 1) / 2;
		return ((mergeS(A, B, l, m) + mergeS(A, B, m + 1, r) + merge(A, B, l, r, m)) % MOD);
	}
	else {
		return 0;
	}
}

int mergeSort(int* A, int len) {
	int B[N];
	return mergeS(A, B, 0, len - 1) % MOD;
}


int main() {
	int A[N];
	int n;

	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> A[i];
	}
	cout << mergeSort(A,n) << endl;
}