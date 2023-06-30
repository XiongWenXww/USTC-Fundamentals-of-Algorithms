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
	//���캯���������ն�
	MinHeap(int sz = DefaultSize)
	{
		maxHeapSize = (DefaultSize < sz) ? sz : DefaultSize;
		heap = new T[maxHeapSize];
		currentSize = 0;
	}

	//���캯��ͨ��һ�����齨����
	MinHeap(T arr[], int n)
	{
		maxHeapSize = (DefaultSize < n) ? n : DefaultSize;
		heap = new T[maxHeapSize];
		for (int i = 0; i < n; i++)
		{
			heap[i] = arr[i];
		}
		currentSize = n;
		int currentPos = (currentSize - 2) / 2;	//���������λ��:����֧���
		while (currentPos >= 0)	//�Ե������������γɶ�
		{
			siftDowm(currentPos, currentSize - 1);	//�ֲ����������»�����
			currentPos--;	//����ǰ��һ����֧���
		}
	}

	//��x���뵽��С����
	bool Insert(const T& x)
	{
		if (currentSize == maxHeapSize)
		{
			cout << "Heap Full!" << endl;
			return false;
		}
		heap[currentSize] = x;	//����
		siftUp(currentSize);	//���ϵ���
		currentSize++;	//�Ѽ���+1
		return true;
	}

	bool RemoveMin(T& x)
	{
		if (!currentSize)
		{
			cout << "Heap Empty!" << endl;
			return false;
		}
		x = heap[0];	//������СԪ��
		heap[0] = heap[currentSize - 1];	//���Ԫ����������
		currentSize--;
		siftDowm(0, currentSize - 1);	//�������µ���Ϊ��
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

	//��С�ѵ��»������㷨
	void siftDowm(int start, int end)	//��start��end�»�������Ϊ��С��
	{
		int cur = start;
		int min_child = 2 * cur + 1;	//�ȼ�max_child��cur������Ůλ��
		T temp = heap[cur];
		while (min_child <= end)
		{
			if (min_child<end && heap[min_child]>heap[min_child + 1])	//�ҵ����Һ�������С��һ��
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

	//��С�ѵ��ϻ������㷨
	void siftUp(int start)	//��start��0�ϻ�������Ϊ��С��
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
		heap[cur] = temp;	//�ط�temp���ݴ��Ԫ��
	}
private:	//�����С����Ԫ�ص�����
	T* heap;
	int currentSize;	//��С���е�ǰԪ�ظ���
	int maxHeapSize;	//��С���������Ԫ�ظ���
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

	MinHeap<task> waitingTask;	// ���������
	int index = 0, timer = 1;
	int totalTime = 0, timeMin;
	task* t;
	task tmp;

	while (index < n || !waitingTask.isEmpty()) {	// index<n��ʾ��������δ����
		if (index < n) {
			while (index < n && T[index].startTime == timer) {
				waitingTask.Insert(T[index]);
				++index;
			}
			if (index < n && T[index].startTime > timer) {
				if (waitingTask.isEmpty()) {
					timer = T[index].startTime;		// ��ʱû����������Ҳû�й��������
				}
				else {
					t = waitingTask.top();
					timeMin = min(t->exeutionTime, T[index].startTime - timer);

					totalTime += timeMin * waitingTask.size();

					timer += timeMin;
					t->exeutionTime -= timeMin;
					//ִ��ʣ��ʱ�������µ��Ǹ�����ִ�д�����һ����λʱ��
					// ���ڴ������ʣ��ʱ����С���ʼ�С�˴������ʣ��ʱ�䣬��������Ϊʣ��ʱ����С��

					if (t->exeutionTime == 0) {
						waitingTask.RemoveMin(tmp);
					}
				}
				continue;
			}
		}
		// ִ�е��˴���Ϊindex>=n
		if (!waitingTask.isEmpty()) {
			t = waitingTask.top();
			totalTime += t->exeutionTime * waitingTask.size();
			waitingTask.RemoveMin(tmp);	//������remove����totalTime����Ϊsize���С
			timer += tmp.exeutionTime;
			
		}
	}

	cout << totalTime << endl;

}