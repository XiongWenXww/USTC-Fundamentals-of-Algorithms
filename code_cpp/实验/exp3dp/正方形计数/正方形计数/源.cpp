#include<iostream>
#include<algorithm>
#include<map>
#define N 200

using namespace std;

enum { intact, broken };

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, m;
	int A[N][N], count[N][N];
	int num = 0;


	cin >> n >> m;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> A[i][j];
			count[i][j] = -1;	// ��(i,j)Ϊ���ϽǶ������������εĸ���
		}
	}

	int maxCount;
	int maxLen;
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			if (A[i][j] == broken)
				continue;

			int len = 0;	// len��ָ��(i,j)Ϊ���ϽǶ������������ε���߳�
			// ��̬�滮
			if (i > 1 && count[i - 1][j] > 1)
				len = count[i - 1][j] - 1;
			if (j > 1 && count[i][j - 1] > 1)
				len = max(count[i][j - 1] - 1, len);

			bool isContinue = true;
			maxLen = min(n - i + 1, m - j + 1); // ����(i,j)Ϊ���ϽǶ���������ε���߳�
			for (; isContinue && len <= maxLen; ++len) {
				// ���ڱ߳�Ϊlen������£��������Ƿ��������
				for (int k = 0; k < len; ++k) {
					if (A[i + len - 1][j + k] == broken || A[i + k][j + len - 1] == broken) {
						--len;
						isContinue = false;
						// break; ֻ������һ��ѭ��
					}
				}
			}
			--len;		// ѭ����--len������forѭ����len��������1
			count[i][j] = len;
			num = num + count[i][j];
		}
	}

	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= m; ++j) {
			cout << count[i][j] << ' ';
		}
		cout << endl;
	}

	cout << num << endl;

}
