#include <iostream>

using namespace std;

struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x):val(x),next(nullptr) {}
};

ListNode* revert(ListNode *list){
    ListNode *prev, *cur, *nxt;
    prev = nullptr;
    cur = list;
    nxt = list;
    while(cur){
        nxt = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nxt;
    }
    return prev;
}

void reorderedList(ListNode *list){
    ListNode *slow = list, *fast = list;
    while(fast->next && fast->next->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    ListNode *p2 = slow->next, *p1 = list;
    ListNode *dummy = new ListNode(-1), *p = dummy;
    slow->next = nullptr;                                   //断链
    p2 = revert(p2);
    while(p1){
        p->next = p1;
        p1 = p1->next;
        p = p->next;
        p->next = p2;
        if(p2){
            p2 = p2->next;
            p = p->next;
        }
    }
    list = dummy->next;

};

int main(){
    ListNode* head = new ListNode(1);
	ListNode* node1 = new ListNode(2);
	ListNode* node2 = new ListNode(3);
	ListNode* node3 = new ListNode(4);
	ListNode* node4 = new ListNode(5);
	ListNode* node5 = new ListNode(6);

	head->next = node1;
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = node5;
	node5->next = nullptr;


	reorderedList(head);
	while (head != nullptr) {
		cout << head->val << endl;
		head = head->next;
	}

	return 0;
}