#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <stack>
#include <vector>
using namespace std;
/*LeetCode 207
我们使用一个visit数组来记录节点搜索的状态，0表示未搜索，1表示搜索中，2表示搜索完成，用一个全局变量valid来表示图中是否存在环。对于每一个没有搜索过的顶点，我们对它进行深度优先搜索
搜索其每一个邻接顶点。若搜索过程中搜到一个正在搜索的顶点，则说明图中存在环。若想要输出拓扑序列，则只需增加一个栈，在每一个点搜索完成时加入栈。将全部顶点出栈得到一个拓扑序列
*/
class Solution
{
    vector<vector<int>> Edges;//邻接表
    vector<int> visit;//状态数组
    //stack<int> sequence;用一个栈来保存拓扑序列，本题不需要
    bool valid = true;//是否存在环，false表示是
    void dfs(int start)
    {
        visit[start] = 1;//将当前节点状态设置为正在搜索
        for (auto &p : Edges[start])//搜索其每一个邻接顶点
        {
            if (visit[p] == 0)//如果邻接顶点未搜索则进行搜索
            {
                dfs(p);
                if (!valid)//若邻接顶点搜索过程中发现环，则直接返回
                    return;
            }
            else if (visit[p] == 1)//若搜到一个正在搜索的顶点则说明遇到环，直接返回
            {
                valid = false;
                return;
            }
        }
        //sequence.push(start);//将搜索完成的顶点入栈
        visit[start]=2;//本顶点搜索完成
    }

public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        Edges.resize(numCourses);
        visit.resize(numCourses);
        //建立邻接表
        for (auto &p : prerequisites)
            Edges[p[1]].push_back(p[0]);
        //搜索每一个未搜索的顶点
        for (int i = 0; i < numCourses && valid; i++)
        {
            if (visit[i] == 0)
                dfs(i);
        }
        return valid;
    }
};
int main()
{
    int i, m, n;
    cin >> m >> n;
    vector<vector<int>> edges(m, vector<int>(2));
    for (i = 0; i < m; i++)
        cin >> edges[i][0] >> edges[i][1];
    Solution s;
    int res = s.canFinish(n, edges);
    cout << res << endl;
    return 0;
}
