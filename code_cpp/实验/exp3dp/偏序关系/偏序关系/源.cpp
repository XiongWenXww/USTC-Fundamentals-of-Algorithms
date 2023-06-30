/* 对于二维平面上的任意两点A(x1, y1), B(x2, y2)，定义偏序关系≤，表示x1≤x2且y1≤y2。
 现给定平面上的若干点，求最大的点的子集S使得集合中的任意两点之间均满足偏序关系≤，
 即对任意A,B ∈ S,A≤B或B≤A成立。只需要输出子集S的大小|S|。
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

// 无向图DAG，Point的孩子都为>=Point的节点，故Point的孩子的孩子仍为>=Point的节点，
// 故Point.depth=max(Point.child.depth+1)，for all child

typedef struct Point {
	int x, y;
	int depth;
	vector<Point*> child;
	// Point*是因为在一个Point里面改变其孩子，则其孩子也会跟着改变，因为放进来的是指针，否则是其他Point的拷贝
}Point;

bool compare(const Point& p1, const Point& p2) {
	if (p1.x == p2.x && p1.y == p2.y) {		// 若两个点相同，则返回false
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
				i.child.push_back(&j);	// 放入的是指针，故对孩子的改变可以真正改变其值，而非改变孩子的拷贝
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
