/*
LeetCode 399.除法求值
*/
#include <bits/stdc++.h>
#include <iostream>
using namespace std;
class Solution
{
    //路径压缩及查找根节点
    int find(vector<int> &nums, vector<double> &weights, int x)
    {
        if (x != nums[x])//如果当前节点有父节点
        {
            int father = find(nums, weights, nums[x]);//递归查找根节点
            weights[x] = weights[x] * weights[nums[x]];//将查找路径上节点的权重加到当前节点上，然后当前节点直接连接到根节点实现路径压缩
            nums[x] = father;//将当前节点的父节点修改成查找到的父亲节点
        }
        return nums[x];//返回当前节点的父节点
    }
    //两个集合归并,由于路径压缩的存在，保证了两个节点查找之后，集合的高度都是2，不需要按秩归并
    void merge(vector<int> &nums, vector<double> &weights, int x, int y, double val)
    {
        int fx = find(nums, weights, x);//查找x的父节点
        int fy = find(nums, weights, y);//查找y的父节点
        nums[fx] = fy;//将x的父节点连接到y的父节点上
        /*在本题中，x,y之间的权重表示的含义为y/x的值，存储在weights[x]中
        假设x与fx之间的权重为wx,y与fy的权重为wy，val为x与y的权重，那么我们将fx连接到fy之后，可以得到x->fx->fy和x->y->fy两条路径
        那么fy与x之间的权重是一定的，假设fx与fy之间的权重为wfx，我们可以得到一个等式x*wx*wfx=val*wy,那么wfx=val*wy/wx
        */
        weights[fx] = val * weights[y] / weights[x];
    }

public:
    vector<double> calcEquation(vector<vector<string>> &equations, vector<double> &values, vector<vector<string>> &queries)
    {
        unordered_map<string, int> dict;
        int nvals = 0;
        // 将字符串映射成数字
        for (auto &e : equations)
        {
            if (dict.find(e[0]) == dict.end())
                dict[e[0]] = nvals++;
            if (dict.find(e[1]) == dict.end())
                dict[e[1]] = nvals++;
        }
        int n = equations.size();
        // 建立并查集,每个节点初始都看出一个单独的集合，权重都设为1.0
        vector<int> nums(nvals);
        vector<double> weights(nvals);
        for (int i = 0; i < nvals; i++)
        {
            nums[i] = i;
            weights[i] = 1.0;
        }
        // 以两个集合合并的方式向集合中添加元素
        for (int i = 0; i < n; i++)
        {
            int va = dict[equations[i][0]];
            int vb = dict[equations[i][1]];
            merge(nums, weights, va, vb, values[i]);
        }
        vector<double> ret;
        //根据需求进行查询
        for (auto &q : queries)
        {
            double ans = -1.0;//设初始解都是-1.0
            auto it1 = dict.find(q[0]), it2 = dict.find(q[1]);//先查找两个字符串映射的数字
            if (it1 != dict.end() && it2 != dict.end())//如果其中一个没有映射，则解直接是-1.0
            {
                int va = it1->second, vb = it2->second;//取出两个映射后的数字
                int fa = find(nums, weights, va), fb = find(nums, weights, vb);//查找两个数字是否是在同一个集合当中
                if (fa == fb)//如果是，则weights数组中存储的即为当前节点到根节点的权重，当前查询的解即为weights[va]/weights[vb]
                    ans = weights[va] / weights[vb];
            }
            ret.push_back(ans);
        }
        return ret;
    }
};
int main()
{
    int i, j, m, n;
    cin >> m >> n;
    vector<vector<string>> equations(m, vector<string>(2));
    vector<double> values(m);
    vector<vector<string>> queries(n, vector<string>(2));
    for (i = 0; i < m; i++)
        cin >> equations[i][0] >> equations[i][1];
    for (i = 0; i < m; i++)
        cin >> values[i];
    for (int i = 0; i < n; i++)
        cin >> queries[i][0] >> queries[i][1];
    Solution s;
    vector<double> ret = s.calcEquation(equations, values, queries);
    return 0;
}
