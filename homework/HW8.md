1. **给定 G = (V,E) 是一带权重且没有权重为负值的环路的有向图，对于所有的结点 v ∈ V，从源结点 s 到结点 v 之间的最短路径中，包含边的条数的最大值为 m。请对算法 BELLMAN-FORD 进行简单修改，可以让其在 m+1 遍松弛操作之后终止，即使 m 不是事先知道的一个数值。**

   用一个数组记录每次循环中每个节点的v.d值，若在本轮循环中发现所有节点的v.d值较上一轮均不变，则跳出循环，算法结束。

   

2. **请举出一个包含负权重的有向图，使得 Dijkstra 算法在其上运行时将产生不正确的结果。为什么在有负权重的情况下，这一定理的证明不成立?** 

   <img src="file:///C:\Users\Eiffel\Documents\Tencent Files\3273693574\Image\C2C\590DE243C4B9D394387910A18025DEF1.png" width = "250" height = "250">

   Dijkstra将认为s到u的最短路径长度为2而不是1。

   <img src="file:///C:\Users\Eiffel\Documents\Tencent Files\3273693574\Image\C2C\A754D58959E133DECA80EB655CAEC158.png" height="250" width="350">

   假设x、y为s->u的最短路径上的节点，且s、x已经进入集合S中，则对x的邻居进行松弛后，有$d.y=\delta(s,y)$，但由于有负边的存在，此时$\delta(s,y)\leq \delta(s,u)$不一定能满足，也就是说$d.y\leq d.u$不一定能成立，故定理的证明不成立。

   

3. **Floyd-Warshall 算法的空间需求为 Θ(n^3^ ) , 因为要计算 $d_{ij}^{k}$ , 其中 i, j, k = 1,2,...,n。请证明下面所列出的去掉所有上标的算法是正确的，从而将 Floyd-Warshall 算法的空间需求降低到 Θ(n^2^ )。**

   ```
   Floyd-Warshall’(W)
   1: n = W.rows
   2: D = W
   3: for k = 1 to n do
   4: 	 for i = 1 to n do
   5: 		for j = 1 to n do
   6: 			dij = min(dij,dik +dkj)
   7: return D
   ```

   对于所需空间为O(n^3^)的Floyd-Warshall算法，每次对$d_{ij}^{k}=min(d_{ij}^{k-1}，d_{ik}^{k-1}+d_{kj}^{k-1})$进行更新，最外层为第 k 次的计算只依赖于第 k-1 次的计算，在这次计算中，$d_{ij}^{k-1}、d_{ij}^{k-1}、d_{ij}^{k-1}$的值是未改变的，改变的只是$d_{ij}^{k}$，由于对于外层循环为第 k 次的循环，在这次大循环中，k是固定不变的，i、j是变化的，当且仅当 i 或 j 等于 k 在本次大循环中更新的 dij 会被使用来更新其他的 dij ，而对于 i=k（j=k同理)，有$d_{kj}=min(d_{kj},d_{kk}+d_{kj})=d_{kj}$，即实际上 dij 的值并未发生改变。并且我们所需的结果为$d_{ij}^n$，即中间的结果是不需要的，故可以去掉上标来进行计算。