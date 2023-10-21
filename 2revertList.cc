#include <iostream>

struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x): val(x), next(nullptr) {}
};

ListNode* revert(ListNode *node){
    ListNode *prev , *cur, *nxt; 
    prev = nullptr;
    cur = node;
    nxt = node;

    while(cur){
        nxt = cur->next;
        cur->next = prev;
        prev = nxt;
        nxt = cur;
    }
    return prev;
}