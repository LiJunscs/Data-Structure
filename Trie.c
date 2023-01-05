#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
typedef struct Trie
{
    struct Trie *children[26]; // 字符前缀
    bool isEnd;                // 是否是一个单词的结尾
} Trie;
Trie *trieCreate()
{
    Trie *ret = (Trie *)malloc(sizeof(Trie));
    memset(ret->children, 0, sizeof(ret->children)); // 初始创建的字典树节点没有前缀字符，全部孩子节点设为空
    ret->isEnd = false;
    return ret;
}
// 向字典树中插入单词
void trieInsert(Trie *obj, char *word)
{
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        int ch = word[i] - 'a';        // 根据单词中的每一个字符寻找它是否在字典树的子树中
        if (obj->children[ch] == NULL) // 如果不是则创建新的节点
            obj->children[ch] = trieCreate();
        obj = obj->children[ch]; // 如果是则继续往下寻找，直到末尾
    }
    obj->isEnd = true; // 找到末尾空节点创建新的节点后，将这个节点设为一个单词的结尾标志
}
// 搜索某个单词是否在字典树中
bool trieSearch(Trie *obj, char *word)
{
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        int ch = word[i] - 'a';        // 根据单词的每一个字符，依次寻找
        if (obj->children[ch] == NULL) // 如果某一个字符没有找到，则直接返回false
            return false;
        obj = obj->children[ch]; // 当前字符找到了则继续往下找
    }
    return obj->isEnd; // 如果找完全部字符且找到末尾的话则返回true,虽然这个末尾可能是另一个字符串的字符，但是在插入时会将给位置设置为结束标识
}
// 查找某个前缀是否在字典树中
bool trieStartWith(Trie *obj, char *prefix)
{
    int len = strlen(prefix);
    for (int i = 0; i < len; i++)
    {
        int ch = prefix[i] - 'a';
        if (obj->children[ch] == NULL)
            return false;
        obj = obj->children[ch];
    }
    return true; // 当前缀的字符寻找完时，直接返回true；
}
void trieFree(Trie *obj)
{
    for (int i = 0; i < 26; i++)
    {
        if (obj->children[i])
            trieFree(obj->children[i]);
    }
    free(obj);
}
int main()
{
    Trie *obj;
    char order[10] = "\0";
    obj = trieCreate();
    scanf("%s", order);
    while (strcmp(order, "end") != 0)
    {
        if (strcmp(order, "insert") == 0)
        {
            char word[10] = "\0";
            scanf("%s", word);
            trieInsert(obj, word);
        }
        if (strcmp(order, "search") == 0)
        {
            char word[10] = "\0";
            scanf("%s", word);
            bool res = trieSearch(obj, word);
            printf("%s", res ? "True\n" : "False\n");
        }
        if (strcmp(order, "startWith") == 0)
        {
            char word[10] = "\0";
            scanf("%s", word);
            bool res = trieStartWith(obj, word);
            printf("%s", res ? "True\n" : "False\n");
        }
        scanf("%s", order);
    }
    trieFree(obj);
    return 0;
}