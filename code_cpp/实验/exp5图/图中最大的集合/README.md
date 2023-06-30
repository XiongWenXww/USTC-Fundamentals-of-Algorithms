### Description

在一张有向图G*G*中，你需要找出节点数最多的一个节点集合S，使得S中的任意两个节点A B至少满足“A可达B”或者“B可达A”中的一个。如果A到B有连边，B到C有连边，那么我们认为C对A是可达的，即A可达C



### Input

第一行为2个整数, N M, 分别代表节点个数、边的个数

接下来M*M*行, 每行一条边的信息, 表述为$U_i\ V_i$的形式, 表示一条从节点$U_i$到节点$V_i$的边

对于所有数据, 满足$1 \leq U_i \leq N, 1 \leq V_i \leq N$

40％的数据, $2 \leq N \leq 50, 0 \leq M \leq 500$

100％的数据, $2 \leq N \leq 5000, 0 \leq M \leq 10^5$



### Output

输出一个数字，表示满足上述条件的最大的集合包含的节点的个数



### Sample Input 1 

```
5 5
1 2
2 3
3 1
4 1
5 2
```



### Sample Output 1

```
4
```







思路：半连通分量，见书上22.5-7

![img](file:///C:\Users\Eiffel\Documents\Tencent Files\3273693574\Image\C2C\8938B7F76BE30882870FF5E7AF613ED1.png)