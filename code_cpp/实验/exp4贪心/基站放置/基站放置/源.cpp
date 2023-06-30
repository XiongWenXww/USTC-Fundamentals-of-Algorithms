#include<iostream>
#include<algorithm>

using namespace std;
#define N 1000

int partition(int* A, const int& p, const int& r) {
	int x = A[r];
	int i = p - 1;
	for (int j = p; j <= r - 1; ++j) {
		if (A[j] <= x) {
			++i;
			swap(A[i], A[j]);
		}
	}
	swap(A[i + 1], A[r]);
	return i + 1;
}

int randomPartition(int* A, const int& p, const int& r) {
	int k = rand() % (r - p + 1) + p;
	swap(A[r], A[k]);
	return partition(A, p, r);
}

void quickSort(int* A, const int& p, const int& r) {
	if (p < r) {
		int q = randomPartition(A, p, r);
		quickSort(A, p, q - 1);
		quickSort(A, q + 1, r);
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, r;
	int A[N];

	cin >> n >> r;

	for (int i = 1; i <= n; ++i)
		cin >> A[i];

	quickSort(A, 1, n);
	
	int i = 1;
	int middle, first;
	int num = 0;

	while (i <= n) {
		first = A[i];
		while (i <= n && A[i] - first <=  r) {
			++i;
		}
		middle = A[i - 1];
		while (i <= n && A[i] - middle <= r) {
			++i;
		}
		
		++num;
	}
	cout << num << endl;
}