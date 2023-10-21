#include <iostream>

using namespace std;

struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x):val(x),next(nullptr) {}
};

ListNode *oddEvenList(ListNode *head){
    if(head == nullptr) return nullptr;

    ListNode *evenHead = head->next;
    ListNode *odd = head;
    ListNode *even = evenHead;

    while(even && even->next){
        odd->next = even->next;
        odd = odd->next;
        even->next = odd->next;
        even = even->next;
    }

    odd->next = evenHead;
    return head;
}
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


	ListNode *node =  oddEvenList(head);
	while (node != nullptr) {
		cout << node->val << endl;                  // 1 3 5 2 4 6
		node = node->next;
	}
    return 0;
}