// �����Knapcask���⣬����ÿ����ÿ��item������������

// hint:���ڶ���S[i][w]������j<i��S[j][w]���������ĵ�i��item������������ԭ��������
// �ϼ�����Ӧ��ȡ���ٸ���i��item����
#include<iostream>
#include<algorithm>
#include<climits>

#define N 200
#define W 10000

using namespace std;

int w[N + 1];
int v[N + 1];
int num[N + 1];

int S[N + 1][W + 1];	// s[i][w]:�ڲ���������w����������item 1,2,...,i��ѡ�������ļ�ֵ

int dp(const int& n, const int& wei, const int& min_wei) {
	int k;
	for (int i = w[1]; i <= n; ++i) {
		k = min(num[1], i / w[1]);		// ����i��w[1]��Ϊ�������ʴ˴�i / w[1]�Ѿ��Զ�����ȡ����
		S[1][i] = k * v[1];
	}

	int max, tmp;
	for (int i = 2; i <= n; ++i) {
		for (int j = min_wei; j <= wei; ++j) {		// �������� w С��min_weiʱ��S[i][w]Ϊ0���ʲ��迼��
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
/* ��ֵ�˼·��Ҳû�������ӹ���
#include<iostream>
#include<algorithm>
#include<climits>
#define N 200
#define W 10000

using namespace std;

// ��1��ʼ�洢
int w[N+1];
int v[N+1];
struct itemsNum{
	int num[N+1];
}remain_num[N + 1][W + 1];
// remain_num[i][w]:��Ӧ��s[i][w]�����Ų����и�����Ʒ��ʣ������

// solution
int s[N+1][W+1];	// s[i][w]:�ڲ���������w����������item 1,2,...,i��ѡ�������ļ�ֵ

int dp(const int& n,const int& wei,const int& min_wei) {
	int tmp, k;
	int max, choice_num;

	for (int j = w[1]; j <= wei; ++j) {
		k =min(remain_num[1][j].num[1], j / w[1]);	// ����j��w[1]��Ϊ�������ʴ˴�j / w[1]�Ѿ��Զ�����ȡ����
		s[1][j] = k * v[1];
		remain_num[1][j].num[1] = remain_num[1][j].num[1] - k;
	}
	

	for (int i = 2; i <= n; ++i) {
		for (int j = min_wei; j <= wei; ++j) {	// �������� w С��min_weiʱ��s[i][w]Ϊ0���ʲ��迼��
			if ( j >= w[i]) {
				max = -1;
				k = 0;
				int tmp2 = j / w[i];
				while (true) {
					// ѡ��i��item����Ŀ���ܳ���ʣ����Ŀ�ͱ�������Ϊjʱֻװ��i��item�������װ�µ���Ŀ
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
			min_wei = w[i];		// �������� w С��min_weiʱ��s[i][w]Ϊ0
		}
		
		for (int j = 1; j <= wei; ++j) {
			for (int k = 1; k <= n; ++k) {
				remain_num[k][j].num[i] = num;
			}
		}
	}
	cout << dp(n, wei, min_wei) << endl;

	

}*/