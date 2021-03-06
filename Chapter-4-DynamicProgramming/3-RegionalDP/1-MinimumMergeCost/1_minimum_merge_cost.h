#ifndef DYNAMICPROGRAMMING_REGIONDYNAMIC_MINIMUM_MERGE_COSE_H
#define DYNAMICPROGRAMMING_REGIONDYNAMIC_MINIMUM_MERGE_COSE_H 1
//最小合并代价
//minimum merge cost

//给定一个序列 例如5 1 2 3 7 4... 将其进行合并
//每次只能合并相邻的两个元素 合并之后成为一个新元素 其值为两数之和
//而合并的代价是两个元素之和 求一个合并的方案使代价总和最小
//题目原型为"最小代价树"

//对于序列s的从1到n这n个元素
//设sum[i][j]指代从i到j元素之和 设f[i][j]指代合并i到j的最小代价
//我们现在考虑最后一次合并:
//假设合并从1到i和从i+1到n这两堆元素
//从1到i的最小代价为f[1][i] 从i+1到n的最小代价为f[i+1][n]
//还需要加上sum[1][i]和sum[i+1][n] 
//所以最后一次合并f[1][n] = f[1][i] + f[i+1][n] + sum[1][i] + sum[i+1][n]
//只要枚举所有的i 其中1<i<n 就可以求出最后一步的最小代价
//由此递推回去 容易得出整个过程的状态转移方程是:
//f[i][j] = min( f[i][k] + f[k+1][j] + sum[i][k] + sum[k+1][j] )
//其中1<=i<k<j<=n
//初始条件: f[i][i]为0 其他都为INF 1<=i<=n
//即i到i的合并代价为0 其他代价为INF

#include <climits>
#include <algorithm>
#include <iostream>
using namespace std;
#ifndef MAX
#define MAX 60
#endif
#ifndef INF
#define INF INT_MAX
#endif

int minimum_merge_cost(int s[MAX], int n)
{
    //序列s的数量为n 范围是[1,n] 返回最小合并代价
	int f[MAX + 1][MAX + 1];
    int sum[MAX + 1][MAX + 1];
    //对于1<=i<=n f[i][i]=0 sum[i][i]=0
    //而对于1<=i!=j<=n f[i][j]=INF
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j) {
			//初始化
			f[i][j] = (i == j) ? 0 : INF;
			sum[i][j] = 0;
		}
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			for (int k = i; k <= j; ++k)
				//sum[i][j]存储序列i到j的元素之和
				sum[i][j] += s[k];
    //i范围是[1,n]
    for (int i = 1; i <= n; ++i)
        //j范围是[i+1,n]
        for (int j = i+1; j <= n; ++j)
            for (int k = i; k < j; ++k) {
                if (f[i][k] == INF || f[k+1][j] == INF)
                    continue;
				f[i][j] = min( f[i][j],
						f[i][k] + f[k+1][j] + sum[i][k] + sum[k+1][j] );
            }

	return f[1][n];
}

#endif
