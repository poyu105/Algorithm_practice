/*
* 此為霍夫曼演算法
輸入:
從標準輸入（standard input）輸入以下的字符與出現頻率資料：
a:16
b:5
c:12
d:17
e:10
f:25
輸出:
從標準輸出（standard output）印出字符的霍夫曼編碼：
a:00
b:1110
c:110
d:01
e:1111
f:10
*/
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;
//自訂節點結構
struct Node
{
	char symbol; //輸入的字符
	int frequency; //每個字符出現的頻率
	Node* left; //左節點
	Node* right; //右節點
	string code; //霍夫曼編碼
	Node(char s=' ', int f=0) : symbol(s), frequency(f), left(nullptr), right(nullptr), code("") {}
};
//使用selection_sort排序節點
void selection_sort(Node nodes[], int size) {
	for (int i = 0; i < size - 1; i++) {
		int minIndex = i; //假設目前最小頻率index為i
		for (int j = i+1; j < size; j++) {
			if (nodes[j].frequency < nodes[minIndex].frequency) {
				//如果當前(j)frequency小於最小(minIndex)frequency則替換minIndex值
				minIndex = j;
			}
		}
		//將最小元素和當前元素交換
		if (minIndex != i) {
			Node temp = nodes[i];
			nodes[i] = nodes[minIndex];
			nodes[minIndex] = temp;
		}
	}
}
//建立二元編碼樹
Node* bottom_up(Node nodes[], int size) {
	//總共會執行n-1次
	while (size>1) {
		selection_sort(nodes, size); //首先排序節點

		Node* parent = new Node(' ', nodes[0].frequency + nodes[1].frequency); //new一個父節點，頻率是nodes[0]頻率+nodes[1]頻率
		parent->left = new Node(nodes[0]); //父節點的左節點指向node[0]位址 (使用new的方法避免在nodes[0] = *parent;執行時左指標指向空)
		parent->right = new Node(nodes[1]); //父節點的右節點指向node[1]位址 

		nodes[0] = *parent; //將第一個節點位置換成parent
		nodes[1] = nodes[size-1]; //將第二個節點位置換成最後一個元素
		size--;

	}
	return &nodes[0]; //回傳根節點
}
//生成編碼
void generateHuffmanCode(Node* node, string str, vector<Node*>& nodes) {
	if (!node) {
		return;
	}
	
	//如果是葉節點，則將編碼存入map
	if (!node->left && !node->right) {
		node->code = str;
		nodes.push_back(node);
		return;
	}

	generateHuffmanCode(node->left, str + "0", nodes); //左指標為'0'
	generateHuffmanCode(node->right, str + "1", nodes); //右指標為'1'
}
// 按照 frequency 排序
bool compareNode(Node* a, Node* b) {
	return a->symbol < b->symbol;
}
int main() {
	Node nodes[6];
	string input; //讀取資料輸入
	
	//依序輸入字符與對應的頻率
	for (int i = 0; i < 6; i++) {
		getline(cin, input); //一次讀取整行
		stringstream ss(input);
		ss >> nodes[i].symbol; //字符串第一個符號存入nodes[i].symbol
		ss.ignore(1, ':'); //字符串往右移一個字符並忽略":"
		ss >> nodes[i].frequency; //讀取頻率
	}

	//根節點
	Node* root = bottom_up(nodes, size(nodes));

	//儲存經過編碼的節點
	vector<Node*> code_nodes;

	//生成霍夫曼編碼
	generateHuffmanCode(root, "", code_nodes);

	// 排序 code_nodes 按照頻率由小到大
	sort(code_nodes.begin(), code_nodes.end(), compareNode);

	// 輸出結果
	for (Node* node : code_nodes) {
		cout << node->symbol << ":" << node->code << endl;
	}
}