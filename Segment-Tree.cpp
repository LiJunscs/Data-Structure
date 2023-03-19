#include<iostream>
#include<vector>
/*LeetCode 307. 区域和检索 - 数组可修改
*/
using namespace std;
struct Node {
	int l, r, val;
	Node():l(0), r(0), val(0) {}
};
class NumArray {
	vector<Node> tree;//使用数组存储线段树的节点，节点个数是4*n,n是数组的长度
  //递归建树
	void build(int x, int l, int r, vector<int>& nums) {
    //将区间端点赋值给当前节点,递归的最小区间为单个数，将数组中的该位置的值赋给节点
		tree[x].l = l;
		tree[x].r = r;
		if (l == r) {
			tree[x].val = nums[l];
			return;
		}
    //递归创建左右子树的区间，左子树的区间为[0,mid],右子树区间为[mid+1,n-1]
		int mid = (l + r) / 2;
		build(x * 2, l, mid, nums);
		build(x * 2 + 1, mid + 1, r, nums);
    //每个节点的值根据不同的题型设置,本题为区间和，则节点的值为左右子树的值相加，如果是最大值则是左右子树的值取最大值
		tree[x].val = tree[x * 2].val + tree[x * 2 + 1].val;
	}
  //修改数组某个位置的数
	void change(int x, int pos, int val) {
    //如果当前节点是单个数的区间，即区间左右相等且等于需要修改的位置则直接修改
		if (tree[x].l == tree[x].r && tree[x].l == pos) {
			tree[x].val = val;
			return;
		}
    //求出区间中点，判断区间中点与需要修改位置的关系，递归
		int mid = (tree[x].l + tree[x].r) / 2;
		if (mid >= pos)
			change(x * 2, pos, val);
		else change(x * 2 + 1, pos, val);
		tree[x].val = tree[x * 2].val + tree[x * 2 + 1].val;
	}
  //求出某个区间的值
	int query(int x, int l, int r) {
    //判断当前区间范围和所求范围是否相同，相同则直接返回
		if (tree[x].l == l && tree[x].r == r)
			return tree[x].val;
    //求出区间中点，判断区间中点与所求区间的关系
		int mid = (tree[x].l + tree[x].r) / 2;
    //如果所求区间右端点小于等于区间中点，即在当前区间的左子树
		if (r <= mid)
			return query(x * 2, l, r);
    //如果所求区间的左端点大于中点，则所求区间在当前区间的右子树
		else if (mid + 1 <= l)
			return query(x * 2 + 1, l, r);
    //如果所求区间分开在中点左右两边，则分别递归左右子树，再对两个递归结果求值
		else return query(x * 2, l, mid) + query(x * 2 + 1, mid + 1, r);
	}
public:
  //构造函数,数组从1开始存储线段树节点
	NumArray(vector<int>& nums) {
		int n = nums.size();
		tree.resize(4 * n + 1);
		build(1, 0, n - 1, nums);
	}
  //修改数组某个位置的值
	void update(int index, int val) {
		change(1, index, val);
	}
  //求某个区间的和
	int sumRange(int left, int right) {
		return query(1, left, right);
	}
};
int main() {
	int n;
	cin >> n;
	vector<int>nums(n);
	for (int i = 0;i < n;i++)
		cin >> nums[i];
	NumArray obj(nums);
	obj.update(0, 3);
	int sum = obj.sumRange(1, 1);
	cout << sum << endl;
	sum = obj.sumRange(0, 1);
	cout << sum << endl;
	obj.update(1, -3);
	sum = obj.sumRange(0, 1);
	cout << sum << endl;
	return 0;
}
