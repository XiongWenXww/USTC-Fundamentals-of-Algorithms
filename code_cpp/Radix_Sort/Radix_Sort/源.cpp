#include <iostream>

// 最大位数为3，最大个数为5
const int d = 3, m = 5;

using namespace std;

// 将数组的每一位分别放在数组中，不够的补0
void digitArray(int* a, int digit[m][d]) {
	int t, t1, t2;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < d; ++j) {
			t = d - j;	// t 表示当前所求的位数是第几位，当j=0时，实际上为最高位
			t1 = pow(10, t);	// t1 用来对数字进行求模运算
			t2 = pow(10, t - 1);	// t2 用来对求模后的数进行取余
			digit[i][j] = a[i] % t1 / t2;
		}
	}
}

// 将各个位数的数字组装成一个完整的数，如 1 3 4组装为134
void assembleDigits(int* a, int digit[m][d]) {
	int base;

	for (int i = 0; i < m; ++i) {
		a[i] = 0;   // 数组a中原来存放着原来需排序的元素
		base = 1;
		for (int j = d - 1; j >= 0; --j) {
			a[i] = a[i] + digit[i][j] * base;
			base = base * 10;
		}
	}
}

// 对数组A的第dd列进行排序
void countSort(int A[m][d], int B[m][d], int dd) {
	int C[19];
	int index;

	for (int i = 0; i < 19; ++i) {
		C[i] = 0;
	}
	for (int i = 0; i < m; ++i) {
		++C[A[i][dd] + 9];	// 可能有负数，故整体向右偏移9个单位
	}

	for (int i = 1; i < 19; ++i) {
		C[i] = C[i] + C[i - 1];
	}


	for (int i = m - 1; i >= 0; --i) {
		index = C[A[i][dd] + 9] - 1;
		--C[A[i][dd] + 9];
		for (int j = 0; j < d; ++j) {
			B[index][j] = A[i][j];
		}
	}


}



void radixSort(int* a) {
	int digit[m][d], B[m][d];
	digitArray(a, digit);

	int k;
	for (k = d - 1; k >= 1; k = k - 2) {
		countSort(digit, B, k);
		// B中存放的是按digit的第k列排好序了的数组，下一次的排序是对数组B中第k-1列的排序

		countSort(B, digit, k - 1);
		// digit中存放的是按B的第k-1列排好序了的数组，下一次的排序是对数组digit中第k-2列的排序
	}
	// 可能总排序的次数为奇数次
	if (k == 0) {
		countSort(digit, B, k);
	}

	assembleDigits(a, B);
}
union Myunion {
	int a;
	int* p;
	
};

int main() {
	Myunion u;
	u.a = 1000;
	int* p;
	p = u.p;
	*p = 10000000;
	cout << u.p << endl;
	

	/*int a[5] = { 89,145,-4,0,123 };
	
	radixSort(a);

	cout << "排好序的数组为:";
	for (int i = 0; i < m; ++i) {
		cout << a[i] << ' ';
	}
	cout << endl;*/
}
