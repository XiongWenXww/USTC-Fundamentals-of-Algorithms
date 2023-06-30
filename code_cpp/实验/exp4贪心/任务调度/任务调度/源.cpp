#include<iostream>
#include<algorithm>
#define N 1000

using namespace std;

struct task {
	int startTime;
	int exeutionTime;

	bool operator<(const task& t)const {
		return exeutionTime < t.exeutionTime;
	}
	bool operator>(const task& t)const {
		return exeutionTime > t.exeutionTime;
	}
	bool operator<=(const task& t)const {
		return exeutionTime <= t.exeutionTime;
	}
	bool operator>=(const task& t)const {
		return exeutionTime >= t.exeutionTime;
	}

	
}T[N];

ostream& operator<<(ostream& os,const task& t) {
	os << t.startTime << ' ' << t.exeutionTime << endl;
	return os;
}

const int DefaultSize = 1000;

template<typename T>
class MinHeap
{
public:
	//构造函数：建立空堆
	MinHeap(int sz = DefaultSize)
	{
		maxHeapSize = (DefaultSize < sz) ? sz : DefaultSize;
		heap = new T[maxHeapSize];
		currentSize = 0;
	}

	//构造函数通过一个数组建立堆
	MinHeap(T arr[], int n)
	{
		maxHeapSize = (DefaultSize < n) ? n : DefaultSize;
		heap = new T[maxHeapSize];
		for (int i = 0; i < n; i++)
		{
			heap[i] = arr[i];
		}
		currentSize = n;
		int currentPos = (currentSize - 2) / 2;	//找最初调整位置:最后分支结点
		while (currentPos >= 0)	//自底向上逐步扩大形成堆
		{
			siftDowm(currentPos, currentSize - 1);	//局部自上向下下滑调整
			currentPos--;	//再向前换一个分支结点
		}
	}

	//将x插入到最小堆中
	bool Insert(const T& x)
	{
		if (currentSize == maxHeapSize)
		{
			cout << "Heap Full!" << endl;
			return false;
		}
		heap[currentSize] = x;	//插入
		siftUp(currentSize);	//向上调整
		currentSize++;	//堆计数+1
		return true;
	}

	bool RemoveMin(T& x)
	{
		if (!currentSize)
		{
			cout << "Heap Empty!" << endl;
			return false;
		}
		x = heap[0];	//返回最小元素
		heap[0] = heap[currentSize - 1];	//最后元素填补到根结点
		currentSize--;
		siftDowm(0, currentSize - 1);	//自上向下调整为堆
		return true;
	}

	int size() {
		return currentSize;
	}

	T *top() {
		return &heap[0];
	}

	bool isEmpty() {
		return currentSize == 0;
	}

	void output()
	{
		for (int i = 0; i < currentSize; i++)
		{
			cout << heap[i];
		}
		cout << endl;
	}
protected:

	//最小堆的下滑调整算法
	void siftDowm(int start, int end)	//从start到end下滑调整成为最小堆
	{
		int cur = start;
		int min_child = 2 * cur + 1;	//先记max_child是cur的左子女位置
		T temp = heap[cur];
		while (min_child <= end)
		{
			if (min_child<end && heap[min_child]>heap[min_child + 1])	//找到左右孩子中最小的一个
				min_child++;

			if (temp <= heap[min_child])
				break;
			else
			{
				heap[cur] = heap[min_child];
				cur = min_child;
				min_child = 2 * min_child + 1;
			}
		}
		heap[cur] = temp;
	}

	//最小堆的上滑调整算法
	void siftUp(int start)	//从start到0上滑调整成为最小堆
	{
		int cur = start;
		int parent = (cur - 1) / 2;
		T temp = heap[cur];
		while (cur > 0)
		{
			if (heap[parent] <= temp)
				break;
			else
			{
				heap[cur] = heap[parent];
				cur = parent;
				parent = (parent - 1) / 2;
			}
		}
		heap[cur] = temp;	//回放temp中暂存的元素
	}
private:	//存放最小堆中元素的数组
	T* heap;
	int currentSize;	//最小堆中当前元素个数
	int maxHeapSize;	//最小堆最多允许元素个数
};



bool compare(const task& t1, const task& t2) {
	return t1.startTime < t2.startTime;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0);

	int n;
	cin >> n;

	for (int i = 0; i < n; ++i) {
		cin >> T[i].startTime >> T[i].exeutionTime;
	}
	sort(T, T + n,compare);

	

	/*cout << "**************" << endl;
	for (int i = 0; i < n; ++i) {
		cout << T[i];
	}*/

	MinHeap<task> waitingTask;	// 挂起的任务
	int index = 0, timer = 1;
	int totalTime = 0, timeMin;
	task* t;
	task tmp;

	while (index < n || !waitingTask.isEmpty()) {	// index<n表示还有任务未到来
		if (index < n) {
			while (index < n && T[index].startTime == timer) {
				waitingTask.Insert(T[index]);
				++index;
			}
			if (index < n && T[index].startTime > timer) {
				if (waitingTask.isEmpty()) {
					timer = T[index].startTime;		// 此时没有任务到来且也没有挂起的任务
				}
				else {
					t = waitingTask.top();
					timeMin = min(t->exeutionTime, T[index].startTime - timer);

					totalTime += timeMin * waitingTask.size();

					timer += timeMin;
					t->exeutionTime -= timeMin;
					//执行剩余时间中最下的那个任务，执行此任务一个单位时间
					// 由于此任务的剩余时间最小，故减小了此任务的剩余时间，此任务仍为剩余时间最小的

					if (t->exeutionTime == 0) {
						waitingTask.RemoveMin(tmp);
					}
				}
				continue;
			}
		}
		// 执行到此处均为index>=n
		if (!waitingTask.isEmpty()) {
			t = waitingTask.top();
			totalTime += t->exeutionTime * waitingTask.size();
			waitingTask.RemoveMin(tmp);	//不能先remove再求totalTime，因为size会变小
			timer += tmp.exeutionTime;
			
		}
	}

	cout << totalTime << endl;

}