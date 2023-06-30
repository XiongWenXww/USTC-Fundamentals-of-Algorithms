#include<iostream>
#define N 10000

using namespace std;

void exchange(int& m, int& n) {
	int tmp = m;
	m = n;
	n = tmp;
}

void maxHeapify(int* A, const int& i,const int& len) {
	int max = i;
	int l = 2 * i, r = 2 * i + 1;
	if (l <= len && A[l] > A[i]) {
		max = l;
	}
	if (r <= len && A[r] > A[max]) {
		max = r;
	}
	if (i != max) {
		exchange(A[i], A[max]);
		maxHeapify(A, max, len);
	}
}

void buildMaxHeap(int* A, const int& len) {
	for (int i = len / 2; i >= 1; --i) {
		maxHeapify(A, i, len);
	}
}

void heapSort(int* A,int& len) {
	buildMaxHeap(A, len);
	for (int i = len; i >= 2; --i) {
		exchange(A[1], A[i]);
		len = len - 1;
		maxHeapify(A, 1, len);
	}
}

int main() {
	int n, len;
	int A[N];
	
	cin >> n;
	len = n;
	for (int i = 1; i <= n; ++i) {
		cin >> A[i];
	}
	heapSort(A, len);	// len传入函数后会改变，故不能直接传n，否则将改变n的值

	for (int i = 1; i <= n; ++i) {
		cout << A[i] << ' ';
	}
	cout << endl;
}