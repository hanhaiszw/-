// 多骨诺米牌.cpp : Defines the entry point for the console application.
//
/*
题目描述：现有n块多骨诺米牌放在x轴上，每一块骨牌有一个所在的位置下标和高度，
         每一块骨牌都只会向x轴正方向倒下，
		 当处于x，高度为h的骨牌倒下，会压倒[x+1,x+h-1]内所有的骨牌。
		 对于每一块骨牌，求取这块骨牌推倒后，至多可以倒下多少骨牌？

输入： 输入第一行包含一个正整数n，表示多骨诺米牌的数量 n [1,10^5]
      接下来n行，每行包含两个正整数x,h,分别表示第i块骨牌的位置和高度
	  其中 x [-10^8,10^8]   h [2,10^8] ,保证不会有两块骨牌在同一位置

输出：对于每个测试数据输出一行，包含n个正整数，
     第i个数字表示如果推倒第i块骨牌，可以使得多少个骨牌倒下。
*/

#include "stdafx.h"
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main()
{
	int n;  //个数
	cin >> n;
	
	//多骨诺米牌
	struct pai {
		int high;  //高度
		int id;  //顺序  记录输入顺序
	};

	//坐标 高度
	map<int, pai> mp;
	for (int i = 0; i < n; i++) {
		int xVal, high;
		cin >> xVal;
		cin >> high;
		mp[xVal] = { high,i };
	}


	//存储的是id和直接压倒的牌
	vector<int> downV(n, 1);

	//求出直接压倒的数目  从后向前
	for (auto it = mp.rbegin(); it != mp.rend(); it++) {
		//存储下标  按牌的输入顺序
		int index = it->second.id;

		int xVal = it->first;
		int high = it->second.high;
		int down = xVal + high - 1;// 

		//从前向后查找
		auto j = it;
		while (j != mp.rbegin()) {
			--j;
			//说明压倒了
			if (down >= j->first) {
				//加上当前牌
				downV[index]++;   //flag1
				//找到被压倒的牌所能覆盖的最大范围，向前继续压
				int downTmp = j->first + j->second.high - 1;
				if (downTmp > down) {
					//down = downTmp;
					int index1 = j->second.id;
					//优化
					//如果当前被压倒的牌的覆盖范围大于down，
					//则直接加上当前被压牌的压倒牌数 减一减得是对当前牌的计数(flag1处)
					downV[index] += (downV[index1] - 1);
					break;
				}
			}
			else {
				//向后x坐标是递增的，压不倒当前，当然也压不倒后面
				break;
			}
		}

	}

	for (int i : downV) {
		cout << i << "   ";
	}

	//提交时需要删掉
	cout << endl;
	system("pause");

	return 0;
}


//测试用例
/*
例1：
输入：
1
16 5
输出：1

例2：
输入：
2
17 2
16 5
输出：1 2


例3：
输入：
4
16 5
20 5
10 10
18 2
输出：3 1 4 1 


例4：
输入：
6
16 5
20 5
10 10
18 2
23 7
19 2
输出：5 2 6 4 1 3



*/
