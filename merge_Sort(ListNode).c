/*
LeetCode 148,排序链表，要求时间复杂度O(nlogn)
进阶版要求空间复杂度O(1)
*/
//双指针归并
struct ListNode *merge(struct ListNode *head1, struct ListNode *head2)
{
    struct ListNode *dummy = (struct ListNode *)malloc(sizeof(struct ListNode));
    struct ListNode *tmp1 = head1, *tmp2 = head2, *cur = dummy;
    // 双指针归并
    while (tmp1 && tmp2)
    {
        if (tmp1->val <= tmp2->val)
        {
            cur->next = tmp1;
            tmp1 = tmp1->next;
        }
        else
        {
            cur->next = tmp2;
            tmp2 = tmp2->next;
        }
        cur = cur->next;
    }
    if (tmp1)
        cur->next = tmp1;
    if (tmp2)
        cur->next = tmp2;
    cur = dummy->next;
    free(dummy);
    return cur;
}
//自顶向下归并排序，时间复杂度O(nlogn),空间复杂度O(logn),为栈使用的空间
struct ListNode
{
    int val;
    struct ListNode *next;
};
struct ListNode *mergeSort(struct ListNode *, struct ListNode *);
struct ListNode *merge(struct ListNode *, struct ListNode *);
struct ListNode *sortList(struct ListNode *head)
{
    return mergeSort(head, NULL);
}
struct ListNode *mergeSort(struct ListNode *head, struct ListNode *tail)
{
    // 空节点处理
    if (head == NULL)
        return NULL;
    // 递归到只剩下一个节点时，直接返回（由于链表的特性，所以当head->next=tail时就只剩一个节点
    if (head->next == tail)
    {
        head->next = NULL;
        return head;
    }
    // 使用快慢指针找到链表的中心
    struct ListNode *fast = head, *slow = head;
    while (fast != tail)
    {
        // 快指针一次走两步，注意空节点判断
        fast = fast->next;
        if (fast!=tail)
            fast = fast->next;
        // 慢指针一次走一步
        slow = slow->next;
    }
    struct ListNode *mid = slow;
    return merge(mergeSort(head, mid), mergeSort(mid, tail));
}
//自底向上归并排序
//时间复杂度O(nlogn),空间复杂度O(1)
struct ListNode *sortList(struct ListNode *head)
{
    if (head == NULL)
        return NULL;
    int len = 0;
    struct ListNode *node = head;
    // 计算链表的长度
    while (node)
    {
        len++;
        node = node->next;
    }
    struct ListNode *dummy = (struct ListNode *)malloc(sizeof(struct ListNode));
    dummy->next = head;
    for (int subLen = 1; subLen < len; subLen *= 2)
    {
        struct ListNode *pre = dummy, *cur = dummy->next;
        while (cur)
        {
            // 寻找subLen个节点为链表1
            struct ListNode *head1 = cur;
            for (int i = 1; i < subLen && cur->next; i++)
                cur = cur->next;
            struct ListNode *head2 = cur->next;
            cur->next = NULL;
            cur = head2;
            // 寻找下一组subLen个节点为链表2，允许节点个数不足
            for (int i = 1; i < subLen && cur && cur->next; i++)
                cur = cur->next;
            //保存后续的节点
            struct ListNode *next = NULL;
            if (cur)
            {
                next = cur->next;
                cur->next = NULL;
            }
            //保存归并完成的节点
            struct ListNode *mergedNode = merge(head1, head2);
            //将归并完成的节点连接到前面的节点
            pre->next = mergedNode;
            //找到已经归并部分的最后一个节点，作为下一次归并的前驱节点
            while (pre->next)
                pre = pre->next;
            //cur变成后续未归并部分
            cur = next;
        }
    }
    //释放空间，避免野指针
    node=dummy->next;
    free(dummy);
    return node;
}
