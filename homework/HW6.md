1. **假定我们对一个数据结构执行一个由 n 个操作组成的操作序列，当 i 严格为 2 的幂时，第 i 个操作 的代价为 i，否则代价为 1.** 

   **（1）使用聚合分析确定每个操作的摊还代价。**

   **（2）使用核算法确定每个 操作的摊还代价。**

   **（3）使用势能法确定每个操作的摊还代价。** 

   (1) 对于n个操作，其中为2的幂的操作共有$\lfloor lg n \rfloor +1$个，故总摊还代价为
   $$
   \begin{align*}\label{1}
   & \sum_{i=0}^{\lfloor lg n \rfloor }2^i+\sum_{i=1}^{n-\lfloor lg n \rfloor -1}1 \\
   & =\frac{1\times(1-2^{\lfloor lg n \rfloor+1})}{1-2}+n-\lfloor lg n \rfloor -1 \\
   & =2^{\lfloor lg n \rfloor+1}-1+n-\lfloor lg n \rfloor -1 \\
   & \leq 2n+n-2-lg n	\\
   & =3n-lg n \\
   & =O(n)
   & \end{align*}
   $$
   故每个操作的摊还代价为O(1)

   

   (2) 赋予每个操作的摊还代价为3，则对于第2^k-1^+1到第2^k^-1个操作来说，这些操作的所多付的信用为

   ​												(3-1)(2^k^-1-(2^k-1^+1)+1)=2(2^k-1^-1)=2^k^-2 

   对于第2^k^个操作，已经付了3个信用，加上之前多付的信用，总共付的信用为2^k^-2+3=2^k^+1>2^k^，大于第2^k^次操作本来应该付的代价。由于故每个操作的摊还代价为O(1)

   

   (3) 定义势函数 $\Phi(D_i)=2i-2^{\lfloor \lg i \rfloor+1},\Phi(D_0)=0$

   对于任意 i ，有$\Phi(D_i)=2i-2^{\lfloor \lg i \rfloor+1}=2(i-2^{\lfloor \lg i \rfloor})\geq 2(i-2^{\lg i})=0=\Phi(D_0)$

   则对于 i 不是2的幂，有$\lfloor \lg i \rfloor=\lfloor \lg i-1 \rfloor$，故摊还代价 
   $$
   \begin{align*}\label{5}
   & \hat {c_i}=c_i+\Phi(D_i)-\Phi(D_{i-1}) \\
   & =1+2i-2^{\lfloor \lg i \rfloor+1}-(2(i-1)-2^{\lfloor \lg i-1 \rfloor+1}) \\
   &=1+2=3
   \end{align*}
   $$
   

   对于 i 是2的幂，有$\lg i=\lfloor \lg i \rfloor=\lfloor \lg i-1 \rfloor+1,2^{\lfloor \lg i \rfloor}=i$，故摊还代价 
   $$
   \begin{align*}\label{6}
   & \hat {c_i}=c_i+\Phi(D_i)-\Phi(D_{i-1})\\
   & =i+2i-2^{\lfloor \lg i \rfloor+1}-(2(i-1)-2^{\lfloor \lg i-1 \rfloor+1}) \\
   & =i+2-2^{\lfloor \lg i \rfloor+1}+2^{\lfloor \lg i-1 \rfloor+1} \\
   & =i+2-2i+i=2
   \end{align*}
   $$
   故每个操作的摊还代价为O(1)

   

2. **V.Pan 发现一种方法，可以用 132464 次乘法操作完成 68×68 的矩阵相乘，发现另一种方法，可以用 143664 次乘法操作完成 70×70 的矩阵相乘，还发现一种方法，可以用 155424 次乘法操作完成 72×72 的矩阵乘法。当用于矩阵乘法的分治算法时，上述哪种方法会得到最佳的渐近运行时间？与 Strassen 算法相比，性能如何？**

   对于用 132464 次乘法操作完成 68×68 的矩阵相乘，有 $\lg_{68}132464=2.795128$

   对于用 143664 次乘法操作完成 70×70 的矩阵相乘，有 $\lg_{70}143664=2.795123$

   对于用 155424 次乘法操作完成 72×72 的矩阵乘法，有 $\lg_{72}155424=2.795147$

   而Strassen算法的时间复杂度为$O(n^{\lg 7})=O(n^{2.807355})$，故用 143664 次乘法操作完成 70×70 的矩阵相乘会得到最佳的渐进运行时间，与 Strassen 算法相比，这些算法性能更好一些。

   

3. ![image-20211123211255273](C:\Users\Eiffel\AppData\Roaming\Typora\typora-user-images\image-20211123211255273.png)

a.
$$
\begin{align*}\label{8}
& y_{k_1,k_2,...,k_d} \\
& =\sum_{j_1=0}^{n_1-1}\sum_{j_2=0}^{n_2-1}...\sum_{j_d=0}^{n_d-1}a_{j_1,j_2,...,j_d}w_{n_1}^{j_1k_1}w_{n_2}^{j_2k_2}...w_{n_d}^{j_dk_d} \\
& =\sum_{j_d=0}^{n_d-1}...\sum_{j_2=0}^{n_2-1}\sum_{j_1=0}^{n_1-1}a_{j_1,j_2,...,j_d}w_{n_1}^{j_1k_1}w_{n_2}^{j_2k_2}...w_{n_d}^{j_dk_d} \\
& =\sum_{j_d=0}^{n_d-1}...\sum_{j_2=0}^{n_2-1}(\sum_{j_1=0}^{n_1-1}a_{j_1,j_2,...,j_d}w_{n_1}^{j_1k_1})w_{n_2}^{j_2k_2}...w_{n_d}^{j_dk_d} \\
& =\sum_{j_d=0}^{n_d-1}...\sum_{j_2=0}^{n_2-1}a_{j_2,...,j_d}w_{n_2}^{j_2k_2}...w_{n_d}^{j_dk_d} \\
& =\sum_{j_d=0}^{n_d-1}...\sum_{j_3=0}^{n_3-1}(\sum_{j_1=0}^{n_2-1}a_{j_2,...,j_d}w_{n_2}^{j_2k_2})w_{n_3}^{j_3k_3}...w_{n_d}^{j_dk_d} \\
& = \space......
\end{align*}
$$
先计算括号里面的，总共需计算$n_2 \cdot n_3\cdot...\cdot n_d=n/n_1$次，也就是沿着第一维计算$n/n_1$个独立的一维DFT，再把这个结果作为输入，继续计算第二维的DFT，对于每个第一维的结果要计算$n/n_1n_2$次，故总共要计算$n/n_2$个。每次计算出结果，都可以减小一维，直到问题解决，也就是到第n维。



b.对于上述等式，由于求和号之间相互独立，故可以互换次序，故可以交换先后计算维度的次序。



c.

计算每一个维度的时间都是$O(n_i\lg n_i)$，故计算一个d维的DFT的总时间为
$$
\begin{align*}\label{7}
& total=\sum_{i=1}^{d}O(n_i \lg n_i)=O(\sum_{i=1}^{d}n_i \lg n_i)\leq O(\lg n\sum_{i=1}^{d}n_i)=O(n\lg n)
\end{align*}
$$
故总时间为O(nlgn)，与d无关
