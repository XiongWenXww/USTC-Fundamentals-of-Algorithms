#include <iostream>

// ���λ��Ϊ3��������Ϊ5
const int d = 3, m = 5;

using namespace std;

// �������ÿһλ�ֱ���������У������Ĳ�0
void digitArray(int* a, int digit[m][d]) {
	int t, t1, t2;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < d; ++j) {
			t = d - j;	// t ��ʾ��ǰ�����λ���ǵڼ�λ����j=0ʱ��ʵ����Ϊ���λ
			t1 = pow(10, t);	// t1 ���������ֽ�����ģ����
			t2 = pow(10, t - 1);	// t2 ��������ģ���������ȡ��
			digit[i][j] = a[i] % t1 / t2;
		}
	}
}

// ������λ����������װ��һ�������������� 1 3 4��װΪ134
void assembleDigits(int* a, int digit[m][d]) {
	int base;

	for (int i = 0; i < m; ++i) {
		a[i] = 0;   // ����a��ԭ�������ԭ���������Ԫ��
		base = 1;
		for (int j = d - 1; j >= 0; --j) {
			a[i] = a[i] + digit[i][j] * base;
			base = base * 10;
		}
	}
}

// ������A�ĵ�dd�н�������
void countSort(int A[m][d], int B[m][d], int dd) {
	int C[19];
	int index;

	for (int i = 0; i < 19; ++i) {
		C[i] = 0;
	}
	for (int i = 0; i < m; ++i) {
		++C[A[i][dd] + 9];	// �����и���������������ƫ��9����λ
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
		// B�д�ŵ��ǰ�digit�ĵ�k���ź����˵����飬��һ�ε������Ƕ�����B�е�k-1�е�����

		countSort(B, digit, k - 1);
		// digit�д�ŵ��ǰ�B�ĵ�k-1���ź����˵����飬��һ�ε������Ƕ�����digit�е�k-2�е�����
	}
	// ����������Ĵ���Ϊ������
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

	cout << "�ź��������Ϊ:";
	for (int i = 0; i < m; ++i) {
		cout << a[i] << ' ';
	}
	cout << endl;*/
}
