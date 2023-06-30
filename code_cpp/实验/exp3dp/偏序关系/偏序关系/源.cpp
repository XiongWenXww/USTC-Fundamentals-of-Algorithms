/* ���ڶ�άƽ���ϵ���������A(x1, y1), B(x2, y2)������ƫ���ϵ�ܣ���ʾx1��x2��y1��y2��
 �ָ���ƽ���ϵ����ɵ㣬�����ĵ���Ӽ�Sʹ�ü����е���������֮�������ƫ���ϵ�ܣ�
 ��������A,B �� S,A��B��B��A������ֻ��Ҫ����Ӽ�S�Ĵ�С|S|��
input:
5
0 1
1 4
2 5
3 3
4 2
output:
3
//{(0,1), (1,4), (2,5)}
*/
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

// ����ͼDAG��Point�ĺ��Ӷ�Ϊ>=Point�Ľڵ㣬��Point�ĺ��ӵĺ�����Ϊ>=Point�Ľڵ㣬
// ��Point.depth=max(Point.child.depth+1)��for all child

typedef struct Point {
	int x, y;
	int depth;
	vector<Point*> child;
	// Point*����Ϊ��һ��Point����ı��亢�ӣ����亢��Ҳ����Ÿı䣬��Ϊ�Ž�������ָ�룬����������Point�Ŀ���
}Point;

bool compare(const Point& p1, const Point& p2) {
	if (p1.x == p2.x && p1.y == p2.y) {		// ����������ͬ���򷵻�false
		return false;
	}
	else if (p1.x <= p2.x && p1.y <= p2.y) {
		return true;
	}
	else {
		return false;
	}
}

int findMaxDepth(Point& p) {
	if (p.child.size() == 0) {
		p.depth = 1;
	}
	for (auto&& c : p.child) {
		if (c->depth == -1) {
			findMaxDepth(*c);
		}
		if (c->depth + 1 > p.depth) {
			p.depth = c->depth + 1;
		}
	}
	return p.depth;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n, maxdepth = -1;

	cin >> n;

	vector<Point> points{ vector<Point>(n) };

	for (auto&& p : points) {
		cin >> p.x >> p.y;
		p.depth = -1;
	}

	for (auto&& i : points) {
		for (auto&& j : points) {
			if (compare(i, j)) {	// i.x<=j.x , i.y<=j.y
				i.child.push_back(&j);	// �������ָ�룬�ʶԺ��ӵĸı���������ı���ֵ�����Ǹı亢�ӵĿ���
			}
		}
	}

	int tmp;
	for (auto&& p : points) {
		tmp = findMaxDepth(p);
		if (tmp > maxdepth) {
			maxdepth = tmp;
		}
	}

	cout << maxdepth << endl;
	
}
