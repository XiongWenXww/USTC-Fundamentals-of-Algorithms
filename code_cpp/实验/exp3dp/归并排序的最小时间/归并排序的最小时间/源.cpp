// ����ԱС����Ҫ��nn����������ϲ���һ������ĳ�ֹ����ϵ�ԭ��С��ֻ��ʹ��һ��ϵͳ
// ����Merge���������ڵ�����ϲ�Ϊһ�����顣
// Merge�����ϲ��������ȷֱ�Ϊn1, n2�������ʱ��Ϊn1 + n2
// �ָ���n������ĳ��ȣ�С����Ҫ�����С��Ҫ�ĺϲ�ʱ�䡣
// input:
// 5
// 68 34 41 55 71
// output: 613

// ע�⣺������̰�ģ���ÿ��ѡ����С�ģ��� 9 6 7 8��Ӧ��merge 9��6��7��8����������merge 6��7
#include<iostream>
#include<algorithm>
#include<climits>

#define N 200
#define MAX 10000

using namespace std;

int sum[N+1][N+1];		// sum[i][j]:��i�����鵽��j������ĳ���֮��,i<=j
int times[N+1][N+1];		// times[i][j]:�ϲ�i,i+1,...,j�������Сʱ��,i<=j

// ��sum�����ʼ��
void sumValue(const int* array,const int& len) {
	for (int i = 1; i <= len; ++i) {
		sum[i][i] = array[i];
		for (int j = i + 1; j <= len; ++j) {
			sum[i][j] = sum[i][j - 1] + array[j];
		}
	}
}

// times��sum��Ϊ����
void dp(const int& len) {
	int min, j;
	int tmp;

	for (int l = 2; l <= len; ++l) {
		for (int i = 1; i <= len - l + 1; ++i) {
			j = i + l - 1;
			min = INT_MAX;
			for (int k=i; k < j; ++k) {
				tmp = times[i][k] + times[k+1][j] + sum[i][k] + sum[k+1][j];
				// sum[i][k] + sum[k+1][j]Ϊ�ϲ���������������ʱ��
				if (tmp < min) {
					min = tmp;
				}
			}
			times[i][j] = min;
		}
	}
}

void print(const int a[N+1][N+1],int n) {
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			cout << a[i][j] << ' ';
		}
		cout << endl;
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, array[N+1];

	cin >> n;
	for (int i = 1; i <= n; ++i) {
		cin >> array[i];
	}

	sumValue(array, n);
	//print(sum,n);

	dp(n);
	//print(times, n);
	cout << times[1][n] << endl;
}