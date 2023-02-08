#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <vector>
#include <queue>
using namespace std;
/*
LeetCode 207
不同于DFS的逆向生成拓扑序列，BFS属于正向生成拓扑序列，我们先生成一个邻接表，然后将邻接表中入度为0的顶点加入队列q中，加入序列会影响最后的拓扑序列，但不会影响判断图中是否有环。
然后，遍历队列头部元素，将其出队，并将其邻接表中的顶点的入度减1，若某一个顶点的入度变成0，将其入队。直到队空，判断我们遍历到的顶点数是否等于图的顶点数，是则图中无环。
*/
class Solution
{
    vector<vector<int>> Edges;//邻接表
    vector<int>indeg;//入度数组
public:
    bool canFinish(int numCourses, vector<vector<int>> &prerequisites)
    {
        int visit=0;
        queue<int> q;
        Edges.resize(numCourses);
        indeg.resize(numCourses);
        //生成邻接表
        for (auto &p : prerequisites){
            Edges[p[1]].push_back(p[0]);
            indeg[p[0]]++;
        }
        //将入度为0的顶点入队
        for(int i=0;i<numCourses;i++){
            if(indeg[i]==0)
                q.push(i);
        }
        //当队不空时，进行BFS
        while(!q.empty()){
            visit++;//遇到的顶点加1
            int start=q.front();
            q.pop();//队列第一个顶点出队
            //遍历这个顶点的邻接表，将其中的顶点的入度减1,遇到入度为0的顶点则将其入队
            for(auto &v:Edges[start]){
                indeg[v]--;
                if(indeg[v]==0)
                    q.push(v);
            }
        }
        return visit==numCourses;
    }
};
