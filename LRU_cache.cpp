/*
LeetCode 146.LRU缓存
请你设计并实现一个满足  LRU (最近最少使用) 缓存 约束的数据结构。
实现 LRUCache 类：
LRUCache(int capacity) 以 正整数 作为容量 capacity 初始化 LRU 缓存
int get(int key) 如果关键字 key 存在于缓存中，则返回关键字的值，否则返回 -1 。
void put(int key, int value) 如果关键字 key 已经存在，则变更其数据值 value ；如果不存在，则向缓存中插入该组 key-value 。如果插入操作导致关键字数量超过 capacity ，则应该 逐出 最久未使用的关键字。
函数 get 和 put 必须以 O(1) 的平均时间复杂度运行。
*/
struct DLinkedNode {
    int key, value;
    DLinkedNode* prev;
    DLinkedNode* next;
    DLinkedNode(): key(0), value(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int _key, int _value): key(_key), value(_value), prev(nullptr), next(nullptr) {}
};
class LRUCache {
    DLinkedNode* head;
    DLinkedNode* tail;
    unordered_map<int,DLinkedNode*> cache;
    int size;
    int capacity;
public:
    LRUCache(int _capacity):capacity(_capacity),size(0) {
        head=new DLinkedNode;
        tail=new DLinkedNode;
        head->next=tail;
        tail->prev=head;
    }
    
    int get(int key) {
        if(!cache.count(key))
            return -1;
        DLinkedNode* cur=cache[key];
        moveTohead(cur);
        return cur->value;
    }
    
    void put(int key, int value) {
        if(!cache.count(key)){
            //如果当前没有存储key-value
            //申请一个新的节点，加入哈希表
            DLinkedNode* node= new DLinkedNode(key,value);
            cache[key]=node;
            //更新双向链表
            addTohead(node);
            size++;
            if(size>capacity){
                DLinkedNode* tmp=removeTail();
                cache.erase(tmp->key);
                size--;
                delete tmp;
            }
        }
        else{
            //如果哈希表中存储了key，则更新该节点
            DLinkedNode* tmp=cache[key];
            tmp->value=value;
            moveTohead(tmp);
        }
    }
    void addTohead(DLinkedNode* node){
        node->prev=head;
        node->next=head->next;
        head->next->prev=node;
        head->next=node;
    }
    void removeNode(DLinkedNode* node){
        node->prev->next=node->next;
        node->next->prev=node->prev;
    }
    void moveTohead(DLinkedNode* node){
        removeNode(node);
        addTohead(node);
    }
    DLinkedNode* removeTail(){
        DLinkedNode* tmp=tail->prev;
        removeNode(tmp);
        return tmp;
    }
};
