// 程序员小明需要将nn个有序数组合并到一起，由于某种工程上的原因，小明只能使用一个系统
// 函数Merge将两个相邻的数组合并为一个数组。
// Merge函数合并两个长度分别为n1, n2的数组的时间为n1 + n2
// 现给定n个数组的长度，小明需要求出最小需要的合并时间。
// input:
// 5
// 68 34 41 55 71
// output: 613

// 注意：不能用贪心，即每次选择最小的！如 9 6 7 8，应先merge 9和6，7和8，而不是先merge 6和7
#include<iostream>
#include<algorithm>
#include<climits>

#define N 200
#define MAX 10000

using namespace std;

int sum[N+1][N+1];		// sum[i][j]:第i个数组到第j个数组的长度之和,i<=j
int times[N+1][N+1];		// times[i][j]:合并i,i+1,...,j所需的最小时间,i<=j

// 对sum数组初始化
void sumValue(const int* array,const int& len) {
	for (int i = 1; i <= len; ++i) {
		sum[i][i] = array[i];
		for (int j = i + 1; j <= len; ++j) {
			sum[i][j] = sum[i][j - 1] + array[j];
		}
	}
}

// times和sum均为方阵
void dp(const int& len) {
	int min, j;
	int tmp;

	for (int l = 2; l <= len; ++l) {
		for (int i = 1; i <= len - l + 1; ++i) {
			j = i + l - 1;
			min = INT_MAX;
			for (int k=i; k < j; ++k) {
				tmp = times[i][k] + times[k+1][j] + sum[i][k] + sum[k+1][j];
				// sum[i][k] + sum[k+1][j]为合并两个大数组所需时间
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