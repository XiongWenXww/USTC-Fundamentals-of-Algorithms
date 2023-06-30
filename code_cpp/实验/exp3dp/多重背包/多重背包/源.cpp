// 相对于Knapcask问题，多了每个对每个item的数量的限制

// hint:由于对于S[i][w]，任意j<i，S[j][w]都不会消耗第i个item的数量，故在原来的问题
// 上加上了应该取多少个第i个item而已
#include<iostream>
#include<algorithm>
#include<climits>

#define N 200
#define W 10000

using namespace std;

int w[N + 1];
int v[N + 1];
int num[N + 1];

int S[N + 1][W + 1];	// s[i][w]:在不超过容量w的条件，从item 1,2,...,i中选出的最大的价值

int dp(const int& n, const int& wei, const int& min_wei) {
	int k;
	for (int i = w[1]; i <= n; ++i) {
		k = min(num[1], i / w[1]);		// 由于i和w[1]均为整数，故此处i / w[1]已经自动向下取整了
		S[1][i] = k * v[1];
	}

	int max, tmp;
	for (int i = 2; i <= n; ++i) {
		for (int j = min_wei; j <= wei; ++j) {		// 背包容量 w 小于min_wei时，S[i][w]为0，故不需考虑
			k = min(num[i], j / w[i]);
			max = -1;

			for (int x = 0; x <= k; ++x) {
				tmp = S[i - 1][j - x * w[i]] + x * v[i];
				if (tmp > max) {
					max = tmp;
				}
			}
			S[i][j] = max;
		}
	}
	return S[n][wei];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, wei;
	int min_wei = INT_MAX;

	cin >> n >> wei;

	for (int i = 1; i <= n; ++i) {
		cin >> w[i] >> v[i] >> num[i];
		if (w[i] < min_wei) {
			min_wei = w[i];
		}
	}

	cout << dp(n, wei, min_wei) << endl;


}
/* 奇怪的思路，也没过，例子过了
#include<iostream>
#include<algorithm>
#include<climits>
#define N 200
#define W 10000

using namespace std;

// 从1开始存储
int w[N+1];
int v[N+1];
struct itemsNum{
	int num[N+1];
}remain_num[N + 1][W + 1];
// remain_num[i][w]:对应于s[i][w]中最优策略中各个物品的剩余数量

// solution
int s[N+1][W+1];	// s[i][w]:在不超过容量w的条件，从item 1,2,...,i中选出的最大的价值

int dp(const int& n,const int& wei,const int& min_wei) {
	int tmp, k;
	int max, choice_num;

	for (int j = w[1]; j <= wei; ++j) {
		k =min(remain_num[1][j].num[1], j / w[1]);	// 由于j和w[1]均为整数，故此处j / w[1]已经自动向下取整了
		s[1][j] = k * v[1];
		remain_num[1][j].num[1] = remain_num[1][j].num[1] - k;
	}
	

	for (int i = 2; i <= n; ++i) {
		for (int j = min_wei; j <= wei; ++j) {	// 背包容量 w 小于min_wei时，s[i][w]为0，故不需考虑
			if ( j >= w[i]) {
				max = -1;
				k = 0;
				int tmp2 = j / w[i];
				while (true) {
					// 选第i个item的数目不能超过剩余数目和背包容量为j时只装第i个item的最大能装下的数目
					if (k > tmp2 || k > remain_num[i][j - k * w[i]].num[i]) {
						break;
					}
					tmp = s[i - 1][j - k * w[i]] + k * v[i];
					if (tmp > max) {
						max = tmp;
						choice_num = k;
					}
					++k;
				}
				
				s[i][j] = max;
				for (k = 1; k < i; ++k) {
					remain_num[i][j].num[k] = remain_num[i][j].num[k];
				}
				remain_num[i][j].num[i] = remain_num[i][j].num[i] - choice_num;
			}
			else {
				s[i][j] = s[i - 1][j];
				for (int k = 1; k <= i; ++k) {
					remain_num[i][j].num[k] = remain_num[i][j].num[k];
				}
			}
		}
	}
	return s[n][wei];
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, wei;
	int min_wei = INT_MAX;

	cin >> n >> wei;

	int num;

	for (int i = 1; i <= n; ++i) {
		cin >> w[i] >> v[i] >> num;
		if (w[i] < min_wei) {
			min_wei = w[i];		// 背包容量 w 小于min_wei时，s[i][w]为0
		}
		
		for (int j = 1; j <= wei; ++j) {
			for (int k = 1; k <= n; ++k) {
				remain_num[k][j].num[i] = num;
			}
		}
	}
	cout << dp(n, wei, min_wei) << endl;

	

}*/