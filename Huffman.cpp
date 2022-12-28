#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<vector>
#include<map>
#include<string>
using namespace std;
typedef struct {
	int parent;
	int lchild;
	int rchild;
	char val;
	int weight;
}TreeNode;
typedef struct {
	int index;
	int weight;
}weighted_char;
typedef struct {
	weighted_char* nums;
	int size;
}MinHeap;
MinHeap* H;
void create_huffmanTree(vector<TreeNode>&);
void init(int);
void insert(int,int);
int get_min();
map<char, string>huffman_encode(vector<TreeNode>);
string encode(map<char, string>, string);
int main() {
	vector<TreeNode>huffman;
	map<char, string>code_set;
	int i, n, fre = 0;
	string s, encode_string;
	cin >> n;
	init(2 * n - 1);
	for (i = 1; i <= n; i++) {
		TreeNode node;
		node.parent = 0;
		node.lchild = 0;
		node.rchild = 0;
		getchar();
		scanf("%c%d", &node.val, &node.weight);
		huffman.push_back(node);
		insert(i,node.weight);
	}
	create_huffmanTree(huffman);
	code_set = huffman_encode(huffman);
	cout << "请输入原字符串" << endl;
	getchar();
	getline(cin, s);
	encode_string = encode(code_set, s);
	cout << "译码后的字符串为:  " << encode_string << endl;
	return 0;
}
//建立哈夫曼树
void create_huffmanTree(vector<TreeNode>& huffman) {
	int min = 0, sec = 0, sum = 0,n = huffman.size(), m = 2 * n - 1, i = 0;
	huffman.resize(m);
	for (i = n; i < m; i++) {
		min = get_min();
		sec = get_min();
		huffman[min - 1].parent = i;
		huffman[sec - 1].parent = i;
		huffman[i].lchild = min - 1;
		huffman[i].rchild = sec - 1;
		sum = huffman[min - 1].weight + huffman[sec - 1].weight;
		huffman[i].weight = sum;
		insert(i + 1,sum);
	}
}
//根据哈夫曼树构造哈夫曼编码
void DFS(vector<TreeNode>huffman, int index, string s, map<char,string>&code_set) {
	if (huffman[index].lchild == 0 && huffman[index].rchild == 0) {
		code_set.insert({ huffman[index].val,s });
		return;
	}
	DFS(huffman, huffman[index].lchild, s + '0', code_set);
	DFS(huffman, huffman[index].rchild, s + '1', code_set);
}
map<char,string> huffman_encode(vector<TreeNode> huffman) {
	int n = huffman.size(), index = n - 1;
	map<char, string> code_set;
	string s;
	DFS(huffman, index, s, code_set);
	return code_set;
}
//根据哈夫曼编码对输入的字符串进行编码
string encode(map<char, string>code_set, string s) {
	string decode_string;
	for (auto p : s) {
		auto q = code_set.find(p);
		decode_string += q->second;
		decode_string += ' ';
	}
	return decode_string;
}
//最小堆及其操作
void init(int maxsize) {
	H = (MinHeap*)malloc(sizeof(MinHeap));
	H->nums = (weighted_char*)malloc(sizeof(weighted_char) * (maxsize + 1));
	H->size = 0;
	H->nums[0].index = 0;
	H->nums[0].weight = 0;
}
void insert(int index, int weight) {
	int i;
	H->size++;
	for (i = H->size; H->nums[i / 2].weight > weight; i /= 2)
		H->nums[i] = H->nums[i / 2];
	H->nums[i].index = index;
	H->nums[i].weight = weight;
}
int get_min() {
	int parent = 0, child = 0, minItem = 0;
	weighted_char tmp;
	if (H->size <= 0)
		return 0;
	minItem = H->nums[1].index;
	tmp = H->nums[H->size--];
	for (parent = 1; parent * 2 <= H->size; parent = child) {
		child = parent * 2;
		if (child<H->size && H->nums[child].weight > H->nums[child + 1].weight)
			child++;
		if (tmp.weight < H->nums[child].weight)
			break;
		else H->nums[parent] = H->nums[child];
	}
	H->nums[parent] = tmp;
	return minItem;
}
