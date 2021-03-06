# 第2章 初出毛庐初级篇

## 2.1 最基础的“穷竭搜索”

* POJ 2386 Lake Counting

有一个大小为N\*M的园子，雨后有积水，八连通的积水被认为是连在一起的。求共有多少个连通域。

典型的DFS或BFS或并查集求连通域。

## 2.2 一直往前！贪心法

2.2.2 区间调度问题

有n个区间，在不重叠的前提下，选择尽可能多的区间。

如果将这些区间看做区间内发生的事情，那么要做更多的事情的话，要优先选择结束时间更早的事情来做，以便为剩下的事情留出更多的时间。即按照右端点从小到大给区间排序，右端点相同的，左端点较大的在前（其实在前在后对于这个题目的结果没有影响）。 然后按照排序后的结果选择区间即可。

2.2.3 字典序最小问题

* POJ 3617 Best Cow Line

给定长度为N的字符串S，构造一个相同长度的字符串T，初始时T为空。反复进行如下两个操作：1从S的头部删除一个字符，加到T的尾部；2从S的尾部删除一个字符，加到T的尾部。目标是让T的字典序尽可能小。

如果S两侧的字符不同，显然，选择字符较小的添加到T即可。如果相同的话，需要进一步判断，即比较S的字符串和反转字符串的字典序，在T后添加较小者。

2.2.4 其他题目


* POJ 3069 Saruman's Army

直线上n个点。点i的位置是Xi。从n个点中选择若干个，给它们加上标记。对每一个点，其距离为R以内的区域里必须有带有标记的点（其本身有标记，可以认为与其相距为0的地方有一个带标记的点）。在满足这个条件的情况下，希望可以给尽可能少的点添加标记。请问至少给多少个点添加标记？

将所有节点从小到大排序，对于第一个点，在R的半径内必须有被标记的点，选择半径内最大的点标记，然后在标记点右侧R范围内的点出队。然后继续选择队列中第一个点重复该步骤即可。

* **POJ 3253 Fence Repair**

长度为L的木板，切割为N段，长度分别为L1-LN，每次切割的开销为模板的长度。问如何选择切割顺序，使总的开销最小。

可以把这个问题反过来思考，把不同的小段合并成一个整段，然后合并的成本是两端的长度之和，合并的次数是一定的。

典型的哈夫曼编码树，用优先级队列实现。

## 2.3 记录结果再利用的“动态规划”

* 01背包问题变形

n个重量和价值分别为Wi、Vi的物品。从这些物品中挑选总重量不超过W的物品，求所有挑选方案中价值总和的最大值。`1<=n<=100;1<=Wi<=10^7;1<=Vi<=100;1<=W<=10^9`

显然，本题和背包问题的区别在于重量的区间过大，如果仍按照01背包的`dp[i][j]`表示容量为j的背包在0-i物品中所能达到的最大价值，则会超出空间复杂度的要求。

价值的范围不大，可以改变DP的对象。`dp[i][j]`表示不超过j的价值量的背包在0-i物品中所能达到的最小重量。则状态转移方程为`dp[i][j]=min{dp[i][j-1],dp[i-1][j-v[i]]+w[i]}`。初始条件`dp[0][0]`=0,`dp[0][j]`=inf，注意这里的`dp[0][j]`是参与运算的，不能设置为0x3fffffff，设置为0x0fffffff足够大即可。最红的答案就在`dp[n][j]`;=W的j的最大值。

* 多重部分和问题

有n个不同大小的数字ai，每种各mi个。判断是否可以从这些数字中选出若干使他们的和恰好为K。

不同的定义对复杂度有影响。先看第一种定义`dp[i][j]:=用前i个数字是否能加成j`，为了用前i个数字加和成j，也就需要能用i-1中数字加和成`j,j-ai,j-2*ai,……,j-mi*ai`中的任一种。可以有如下的递推关系`dp[i][j]=(0<=k<=mi且k*ai<=j时存在使dp[i][j-k*ai]为真的k)`。复杂度为 $O(K*\sum{mi})$ ,**一般用dp求bool结果的话会有不少浪费，同样的复杂度通常能获得更多的信息**。

在这个问题中，我们不光求出能否得到目标的和数，同时把得到时ai这个数还剩下多少个可以使用计算出来。

`dp[i][j]:=用前i个数字加成j时第i中数字最多能剩余多少个(不能加和得到i的情况下为-1)`

按照上述递归关系，如果前i-1个数加和能得到j的话，第i个数就可以留下mi个。此外，前i种数加和出j-ai时第i种数还剩下k(k>0)的话，用这i种数加和到j时第i种数剩下k-1个。

这样，只需要看最终是否满足`dp[n][K]>=0`就可以知道答案了。复杂度`O(nK)`

* 最长上升子序列

`dp[i]表示长度为i+1的上升子序列中末尾元素的最小值(不存在的话就是inf)`

```cpp
int dp[MAXN];
void solve(){
    fill(dp,dp+n,inf);
    for(int i=0;i<n;i++){
        *lower_bound(dp,dp+n,a[i])=a[i];//lowerbound表示大于等于e的最小值
    }
    printf("%d\n",lower_bound(dp,dp+n,inf)-dp);
}
```

* 划分数

有n个无区别的物品，将他们划分成不超过m组，称为n的m划分，求出划分方法数模M的余数。`1<=m<=n<=1000;2<=M<=10000`

**DP不仅对于求解最有问题有效，对于各种排列组合的个数、概率或者期望之类的计算同样很有用**。

定义`dp[i][j]=j的i划分的总数`，考虑n的m划分{ai}( $\sum{ai}=n$ )，如果对于每个i都有ai>0，那么{ai-1}就对应n-m的m划分。另外，如果存在ai=0，那么这就对应了n的m-1划分。所以递推公式如下：`dp[i][j]=dp[i][j-1]+dp[i-1][j]`。

* 多重集组合数

有n种物品，第i中物品有ai个。不同种类的物品可以互相区分但相互种类的无法区分。从这些物品中取出m个的话，有多少种取法？求出方案数模M的余数。

定义`dp[i][j]:=前i种物品中取出j个的组合总数`，有递推公式`dp[i][j]=dp[i][j-1]+dp[i-1][j]-dp[i-1][j-1-ai]`.

## 2.4 加工并存储数据的数据结构

* POJ 2431 Expedition

需要驾驶卡车行驶L单位距离。最开始时，卡车上有P单位的汽油。卡车每开1单位距离消耗1单位汽油。如果在途中车上的汽油耗尽，卡车无法继续前进，因为无法到达终点。在途中一共有N个加油站。第i个加油站在距离起点Ai单位距离的地方，最多可以给卡车加Bi单位汽油。假设卡车的燃料的容量是无限大的，无论加多少油都没有问题。那么请问卡车能否到达终点，如果可以，最少需要加多少次油？

转化一下思考方式。在卡车开往终点的途中，只有在加油站才可以加油。但是，如果认为“在到达加油站i时，就获得了一次在以后任何时候都可以加Bi单位汽油的权利”。而在之后需要加油时，就认为是在之前的加油站加的油即可。

由此可以建立油量的优先级队列。

* POJ 1182 食物链

有N只动物，分别编号为1-N。所有动物都属于ABC中的其中一类。已知A吃B、B吃C、C吃A。按顺序给出下面的两种信息共K条。第一种：x和y属于同一类。第二种：x吃y。

然而这些信息可能会出错。有可能有的信息和之前给出的信息矛盾，也有的信息可能给出的x和y不在1-N的范围内。求在K条信息中有多少条是不正确的。计算过程中将忽略此类错误信息。

## 2.5 它们其实都是“图”

* POJ 3255 Roadblocks

某街区共有R条道路、N个路口。道路可以双向通行。问1号路口到N号路口的次短路长度是多少？次短路指的是比最短路长度长的次短的路径。同一条边可以经过多次。`1<=N<=5000;1<=R<=100000`

对Dijkstra算法进行稍微改进就行了。到某个顶点v的次短路要么是到其他某个顶点u的最短路加上u-v的边，要么是到u的次短路再加上u-v的边，因此，所需要求得就是到所有顶点的最短路和次短路。因此，对于每个顶点，我们记录的不仅仅是最短距离，还有次短距离。

* POJ 3723 conscription

需要征募女兵N人，男兵M人。每征募一个人需要花费10000美元。但是如果已经征募的人中有一些关系亲密的人，那么可以少花一些钱。给出若干的男女之间的1-9999之间的亲密度关系，征募每个人的费用是10000-（已经征募的人中和自己的亲密度的最大值）。要求通过适当的征募顺序使得征募所有人所需的费用更小。

把这个问题转化为求解无向图中的最大权森林问题。最大权森林问题可以通过把所有边权取反之后用最小生成树的算法求解。

* POJ 3169 Layout

n头牛编号为1到n，按照编号的顺序排成一列，每两头牛的之间的距离 >= 0。这些牛的距离存在着一些约束关系：1.有ml组（u, v, w）的约束关系，表示牛[u]和牛[v]之间的距离必须 <= w。2.有md组（u, v, w）的约束关系，表示牛[u]和牛[v]之间的距离必须 >= w。问如果这n头无法排成队伍，则输出-1，如果牛[1]和牛[n]的距离可以无限远，则输出-2，否则则输出牛[1]和牛[n]之间的最大距离。

记第i号牛的位置是d[i]，存在三类不等式。d[i]<=d[i+1];d[AL]+DL>=d[BL];d[AD]+DD<=d[BD]。

这些不等式的特点是所有的式子两边都只出现了一个变量。实际上图中的最短路问题也可以用这样的形式表示出来。记从起点s出发，到各个定点v的最短距离是d[v]。因此，对于每条权值为w的边e(v,u)，有d[v]+w>=d[u]成立。

将本题的三个不等式都用该形式表示出来，引入边长为0的边和负权边，采用bellman-ford算法求解最短路径问题。

## 2.6 数学问题中的解题窍门

* 辗转相除法
* 扩展欧几里得算法：一定存在整数对(x,y)使得ax+by=gcd(a,b)，并用同样的算法求得。
* 素数筛法
* 快速幂

## 2.7 一起来挑战GCJ题目

* Minimum Scalar Product
* Bribe the Prisoners
* Millionaire

