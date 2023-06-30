#include<iostream>
#define N 10000

using namespace std;

//int random(const int& min, const int& max) {
//	srand((unsigned)time(NULL));
//	return rand() % (max - min + 1) + min;
//}

void exchange(int& m, int& n) {
	int tmp = m;
	m = n;
	n = tmp;
}

int Partition(int* A, const int& p, const int& r) {
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

int randomPartition(int* A, const int& p, const int& r) {
	//int k = random(p, r);	比较费时间
	int k = rand() % (r - p + 1) + p;
	exchange(A[k], A[r]);
	return Partition(A, p, r);
}

void quickSort(int* A,const int& p,const int& r) {
	if (p < r) {
		int k = randomPartition(A, p, r);
		quickSort(A, p, k - 1);
		quickSort(A, k + 1, r);
	}
}

int main() {
	int A[N];
	int n;

	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> A[i];
	}
	quickSort(A, 0, n - 1);
	for (int i = 0; i < n; ++i) {
		cout << A[i] << ' ';
	}
	cout << endl;
}