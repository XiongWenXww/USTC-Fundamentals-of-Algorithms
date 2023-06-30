//����������������N��T
//����������һ��ֻ���������ҳ���ΪN���ַ���������Ҫ���ַ�����T�ָ�����ɾ��T��
//��ʣ���ַ�����Ϊ���֣��������ֽ��д�С��������������
//���ַ���ת��Ϊ���ֵĹ����У���Ҫȥ��ǰ��0�����ַ���ȫΪ0������0��
//������
//"
//8 1
//01210213
//"
//���ȴ��ַ�����01210213�����޳�"1"����Ϊ��0 2 02 3��������С��������Ľ��Ϊ��0 2 2 3��

#include<iostream>
#define N 1000

using namespace std;

void countSort(int* A, int* B, const int& len) {
	int C[10];

	for (int i = 0; i < 10; ++i)
		C[i] = 0;
	for (int i = 1; i <= len; ++i)
		++C[A[i]];
	for (int i = 1; i < 10; ++i)
		C[i] = C[i] + C[i - 1];
	for (int i = len; i > 0; --i) {
		B[C[A[i]]] = A[i];
		--C[A[i]];
	}
}

int main() {
	char  c;
	int A[N], B[N];
	int n, t;

	cin >> n >> t;

	int k = 0;	// �����г�ȥt�ĸ���
	
	for (int i = 1; i <= n; ++i) {
		cin >> c;
		if (c - '0' != t) {
			++k;
			A[k] = c - '0';
		}
	}

	int i = 1;
	while (i <= k && A[i] == 0) {
		++i;
	}
	if (i > k) {
		cout << '0' << endl;
	}
	else {
		for (int j = i; j <= k; ++j) {
			B[j - i + 1] = A[j];
		}

		k = k - i + 1;
		countSort(B, A, k);
		string s(2 * k - 1, '0');
		for (int i = 1; i < k; ++i) {

			s[2 * i - 2] = '0' + A[i];
			s[2 * i - 1] = ' ';
		}
		s[2 * k - 2] = '0' + A[k];
		cout << s << endl;
		/*for (int i = 1; i <= k; ++i) {

			cout << char('0' + A[i]) << ' ';
		}
		cout << endl;*/
	}

	
}

//#include<iostream>
//#define N 10000
//
//using namespace std;
//
//void countSort(int* A, int* B,const int& len) {
//	int C[10];
//
//	for (int i = 0; i < 10; ++i)
//		C[i] = 0;
//	for (int i = 1; i <= len; ++i)
//		++C[A[i]];
//	for (int i = 1; i < 10; ++i)
//		C[i] = C[i] + C[i - 1];
//	for (int i = len; i > 0; --i) {
//		B[C[A[i]]] = A[i];
//		--C[A[i]];
//	}
//}
//
//int main() {
//	char  c;
//	int A[N], B[N];
//	int n, t;
//
//	cin >> n >> t;
//	
//	int k = 0;	// �����г�ȥt�ĸ���
//
//	cin >> c;
//	if (c != '0' && c - '0' != t) {
//		++k;
//		A[k] = c - '0';
//	}
//	for (int i = 2; i <= n; ++i) {
//		cin >> c;
//		if (c - '0' != t) {
//			++k;
//			A[k] = c - '0';
//		}
//	}
//
//	countSort(A, B, k);
//
//	for (int i = 1; i <= k; ++i) {
//		cout << B[i] << ' ';
//	}
//	cout << endl;
//
//
//	if (B[1] != 0) {
//		string s(2 * k - 1, '0');
//		for (int i = 1; i < k; ++i) {
//
//			s[2 * i - 2] = '0' + B[i];
//			s[2 * i - 1] = ' ';
//		}
//		s[2 * k - 2] = '0' + B[k];
//		cout << s << endl;
//	}
//	else {
//		string s(2 * k - 3, '0');
//		for (int i = 1; i < k - 1; ++i) {
//			s[2 * i - 2] = '0' + B[i+1];
//			s[2 * i - 1] = ' ';
//		}
//		s[2 * k - 4] = '0' + B[k];
//		cout << s << endl;
//	}
//}

//#include<iostream>
//#define N 10000
//
//using namespace std;
//
//void countSort(int* A, int* B, const int& len) {
//	int C[10];
//
//	for (int i = 0; i < 10; ++i)
//		C[i] = 0;
//	for (int i = 1; i <= len; ++i)
//		++C[A[i]];
//	for (int i = 1; i < 10; ++i)
//		C[i] = C[i] + C[i - 1];
//	for (int i = len; i > 0; --i) {
//		B[C[A[i]]] = A[i];
//		--C[A[i]];
//	}
//}
//
//int main() {
//	char  c;
//	int A[N], B[N];
//	int n, t;
//
//	cin >> n >> t;
//
//	int k = 0;	// �����г�ȥt�ͳ�ȥt��ǰ��0�ĸ���
//	int num = 0;
//	cin >> c;
//	++num;
//	if (c == '0' + t) {
//		bool flag = true;
//		while (num < n && flag && cin >> c) {
//			if (c != '0' + t) {
//				flag = false;
//				if (c != '0') {		// ����ǰ�� 0
//					++k;
//					A[k] = c - '0';
//				}
//			}
//			num = num + 1;
//		}
//	}
//	else {
//		++k;
//		A[k] = c - '0';
//	}
//
//	if (num < n) {
//		for (; num < n; ++num) {
//			cin >> c;
//			if (k != 0 || c != '0') {
//				if (c - '0' != t) {
//					++k;
//					A[k] = c - '0';
//				}
//			}
//			
//		}
//	}
//	
//	countSort(A, B, k);
//
//
//	/*string s(2 * k - 1, '0');
//	for (int i = 1; i < k; ++i) {
//
//		s[2 * i - 2] = '0' + B[i];
//		s[2 * i - 1] = ' ';
//	}
//	s[2 * k - 2] = '0' + B[k];
//	cout << s << endl;*/
//	for (int i = 1; i < k; ++i) {
//		cout << B[i] << ' ';
//	}
//	cout << B[k] << endl;
//
//}