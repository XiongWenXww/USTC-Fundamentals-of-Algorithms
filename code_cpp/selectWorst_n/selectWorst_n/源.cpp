#include <iostream>
#include <math.h>
#define N 1000
#define M 100

using namespace std;

int medians[N / 5 + 1];

//此处的排序数组从0开始存储元素

void insertSort(int* A, const int& p, const int& r) {
	for (int i = p + 1; i <= r; ++i) {
		int tmp = A[i];
		int j;
		for (j = i - 1; j >= p && tmp < A[j]; --j) {
			A[j + 1] = A[j];
		}
		A[j + 1] = tmp;
	}
}

int partition(int* A, const int& p, const int& r, const int& v) {
	int i;
	for (i = p; i <= r; ++i) {
		if (A[i] == v) {
			break;
		}
	}
	swap(A[i], A[r]);

	i = p - 1;
	for (int j = p; j < r; ++j) {
		if (A[j] < v) {
			++i;
			swap(A[i], A[j]);
		}
	}
	swap(A[i + 1], A[r]);
	return i + 1;
}

int select(int* A, const int& p, const int& r, const int& k) {
	if (p == r) {
		return A[p];
	}
	int num = ceil((double(r) - p + 1) / 5);	// 子数组的数量
	if (num > 1) {
		for (int i = 0; i < num - 1; ++i) {
			insertSort(A, p + 5 * i, p + 5 * i + 4);
		}
		insertSort(A, p + 5 * (num - 1), r);	// 对最后一个可能个数不足5个的子数组进行插入排序
	}
	else {	//注意要对较小的数组进行处理，不然会一直递归导致栈溢出
		insertSort(A, p, r);
		return A[p + k - 1];
	}

	/*for (int i = p; i <= r; ++i) {
		cout << A[i] << ' ';
	}
	cout << endl;*/

	for (int i = 0; i < num - 1; ++i) {
		medians[i] = A[p + 5 * i + 2];
	}

	int lastNum = r - p + 1 - 5 * (num - 1);	// 最后一个子数组中所含元素的个数
	medians[num - 1] = A[p + 5 * (num - 1) + lastNum / 2];

	/*for (int i = 0; i < num; ++i) {
		cout << medians[i] << ' ';
	}
	cout << endl;*/

	int mid = select(medians, 0, num - 1, (num + 1) / 2);	// 递归找出中位数的中位数
	/*cout << "mid:" << mid << endl;*/

	int q = partition(A, p, r, mid);
	/*cout << "partition:" << endl;
	for (int i = p; i <= r; ++i) {
		cout << A[i] << ' ';
	}
	cout << endl;*/

	int m = q - p + 1;
	/*cout << "m:" << m << " q:" << q << " p:" << p << endl;*/
	if (m == k) {
		return A[q];
	}
	else if (k < m) {
		return select(A, p, q - 1, k);
	}
	else {
		return select(A, q + 1, r, k - m);
	}
}

int main() {
	int n, k, m;
	int A[N], result[M];

	cin >> m;
	for (int j = 0; j < m; ++j) {
		cin >> n >> k;

		for (int i = 0; i < n; ++i) {
			cin >> A[i];
		}
		result[j] = select(A, 0, n - 1, k);

	}
	for (int i = 0; i < m; ++i) {
		cout << result[i] << endl;
	}
}