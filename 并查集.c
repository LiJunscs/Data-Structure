/*用结构体数组来表示集合，每个结构体含有自身的值和父亲节点的下标，根节点的父亲下标为-1
* 在进行并操作时，需要判断每个集合的大小，所以父亲下标负数代表根节点，其绝对值代表集合的元素个数
*/
typedef struct {
	int data;
	int parent;
}set;
//查找 某个元素属于哪个集合，返回根节点下标
#define MAXSIZE 1000
int find(set S[], int x) {
	int i;
	//先在集合S中找到x所在下标
	for (i = 0; i < MAXSIZE && S[i].data != x; i++);//多次查找的时间复杂度为O(N²),可能超时，可以使用映射函数将N的元素映射到0~N-1，实现直接数组下标存储
	//判断集合中是否含有该元素
	if (i >= MAXSIZE)
		return -1;
	//寻找根节点位置,DFS
	for (; S[i].parent > 0; i = S[i].parent);
	return i;
}
//两个集合并运算
void Union(set S[], int x1, int x2) {
	int root1, root2;
	//先在S中找到两个元素对应的根节点下标
	root1 = find(S, x1);
	root2 = find(S, x2);
	//如果两个元素所属同一个集合则不需要合并
	if (root1 == root2)
		return;
	//将小集合并到大集合中有利于后续操作的时间更短
	if (S[root1].parent <= S[root2].parent) {
		S[root1].parent += S[root2].parent;
		S[root2].parent = root1;
	}
	else {
		S[root2].parent += S[root1].parent;
		S[root1].parent = root2;
	}
}
//映射后的集合
int Find(int Set[], int x) {
	int i;
	for (i = x; i > 0; i = Set[i]);
	return i;
}
void Union2(int Set[], int x1, int x2) {
	int root1, root2;
	root1 = Find(Set, x1);
	root2 = Find(Set, x1);
	if (root1 == root2)
		return;
	//按秩归并，即按照树的高度或元素个数，将小的并到大的上去
	if (Set[root1] <= Set[root2]) {
		Set[root1] += Set[root2];
		Set[root2] = root1;
	}
	else {
		Set[root2] += Set[root1];
		Set[root1] = root2;
	}
}
//路径压缩，find的时候将找到的根节点变成每一轮循环节点的父节点
int Find2(int Set[], int x) {
	if (Set[x] < 0)
		return x;
	else return Set[x] = Find2(Set, Set[x]);
}