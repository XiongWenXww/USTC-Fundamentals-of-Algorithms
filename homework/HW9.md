# HW9



1. **我们怎样才能使用 Floyd-Warshall 算法的输出来检测权重为负值的环路？** 

   若图中有负环，假设节点 i 为负值环路中的一个节点，在循环中会更新节点 i 到自身的距离，对于大于负值环路中的所有节点序号k，会使得 $d_{ii}^k$ 为负值。

   

2. **假定在一个权重函数为 W 的有向图图 G 上运行 Johnson 算法。证明：如果图 G 包含一条权重为 0 的环路 c，那么对于环路 c 上的每条边 (u, v)，$\hat{w}(u,v)=0$**

   由于重新赋值不会改变环路的权重，故重新赋值后此环路的权重仍为0，又由于重新赋值后每条边的权重为非负权重，故对于环路 c 上的每条边 (u, v)，有$\hat{w}(u,v)=0$。

   

3.  **(最大流的更新) 设 G = (V,E) 是一个源结点为 s 汇结点为 t 的流网络，其容量全部为整数值。假定我们已经给定 G 的一个最大流。** 

   **a. 如果将单条边 (u, v) ∈ E 的容量增加 1 个单位，请给出一个 O(V +E) 时间的算法来对最大流进行更新。** 

   **b. 如果将单条边 (u, v) ∈ E 的容量减少 1 个单位，请给出一个 O(V +E) 时间的算法来对最大流进行更新。**
   
   a.用BFS或DFS来找在残存网络中是否还存在从源节点 s 到汇节点 t 的路径，若存在，由于容量全部为整数，则将此条路径的流量增加1，否则不做任何修改。
   
   b. 计算一遍残存网络，若出现负值，则说明最大流所依赖的边包含（u,v）且流过此条边的流刚好为这条边的容量，此时利用BFS或DFS找到包含边(u,v)的一条路径，由于容量全部为整数，故将此条路径的流量减少1，若残存网络的边没有出现负值，则(u,v)容量减少1个单位对这个最大流无影响，故不作修改。