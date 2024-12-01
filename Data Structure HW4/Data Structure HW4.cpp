#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

// 定義二元樹節點結構
struct TreeNode {
    int val;               // 節點的值
    TreeNode* left;        // 指向左子樹的指標
    TreeNode* right;       // 指向右子樹的指標
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 將數值插入到二元搜尋樹（Binary Search Tree, BST）
TreeNode* insertBST(TreeNode* root, int val) {
    if (!root) // 如果當前節點為空，建立新節點
        return new TreeNode(val);
    if (val < root->val) // 如果輸入值小於當前節點值，插入左子樹
        root->left = insertBST(root->left, val);
    else // 如果輸入值大於或等於當前節點值，插入右子樹
        root->right = insertBST(root->right, val);
    return root; // 返回更新後的樹根
}

// 以樹狀結構輸出二元樹
void printTree(TreeNode* root, int space = 0, int height = 10) {
    if (!root) return; // 如果節點為空，直接返回
    space += height; // 增加縮排空間
    printTree(root->right, space); // 先輸出右子樹
    cout << endl;
    for (int i = height; i < space; i++) // 繪製空格
        cout << " ";
    cout << root->val << "\n"; // 輸出當前節點值
    printTree(root->left, space); // 最後輸出左子樹
}

// 以層序遍歷的方式將 BST 轉換成陣列表示
void bstToArray(TreeNode* root, vector<int>& arr) {
    if (!root) return; // 如果樹為空，直接返回
    queue<TreeNode*> q; // 使用佇列進行層序遍歷
    q.push(root);
    while (!q.empty()) {
        TreeNode* node = q.front();
        q.pop();
        arr.push_back(node->val); // 將當前節點值加入陣列
        if (node->left) q.push(node->left); // 如果有左子樹，加入佇列
        if (node->right) q.push(node->right); // 如果有右子樹，加入佇列
    }
}

// 將輸入陣列轉換成 Max-Heap
void buildMaxHeap(vector<int>& heap) {
    int n = heap.size();
    // 從最後一個非葉節點開始調整堆
    for (int i = n / 2 - 1; i >= 0; i--) {
        int parent = i; // 當前父節點索引
        while (parent < n) {
            int left = 2 * parent + 1; // 左子節點索引
            int right = 2 * parent + 2; // 右子節點索引
            int largest = parent; // 初始化最大值為父節點

            // 比較左子節點
            if (left < n && heap[left] > heap[largest])
                largest = left;

            // 比較右子節點
            if (right < n && heap[right] > heap[largest])
                largest = right;

            // 如果需要交換，則進行交換並繼續調整
            if (largest != parent) {
                swap(heap[parent], heap[largest]);
                parent = largest; // 更新父節點索引
            }
            else break; // 如果沒有需要交換，跳出
        }
    }
}

// 以樹狀結構輸出 Max-Heap
void printHeap(const vector<int>& heap, int index = 0, int space = 0, int height = 10) {
    if (index >= heap.size()) return; // 如果索引超出範圍，直接返回
    space += height; // 增加縮排空間
    printHeap(heap, 2 * index + 2, space); // 先輸出右子節點
    cout << endl;
    for (int i = height; i < space; i++) // 繪製空格
        cout << " ";
    cout << heap[index] << "\n"; // 輸出當前節點值
    printHeap(heap, 2 * index + 1, space); // 最後輸出左子節點
}

int main() {
    TreeNode* bstRoot = nullptr; // 初始化 BST 根節點為空
    vector<int> heap; // 初始化陣列用於存儲 Max-Heap

    cout << "請輸入一組整數值（輸入-1結束）: ";
    int val;
    while (cin >> val && val != -1) { // 讀取使用者輸入，直到輸入 -1
        bstRoot = insertBST(bstRoot, val); // 將數值插入 BST
        heap.push_back(val); // 同時將數值加入堆陣列
    }

    // 建立 Max-Heap
    buildMaxHeap(heap);

    // 以陣列表示輸出 BST
    vector<int> bstArray;
    bstToArray(bstRoot, bstArray);
    cout << "\nBST（陣列表示）: ";
    for (int v : bstArray) cout << v << " ";
    cout << endl;

    // 以樹狀表示輸出 BST
    cout << "\nBST（樹狀表示）:\n";
    printTree(bstRoot);

    // 以陣列表示輸出 Max-Heap
    cout << "\nMax-Heap（陣列表示）: ";
    for (int v : heap) cout << v << " ";
    cout << endl;

    // 以樹狀表示輸出 Max-Heap
    cout << "\nMax-Heap（樹狀表示）:\n";
    printHeap(heap);

    return 0;
}
