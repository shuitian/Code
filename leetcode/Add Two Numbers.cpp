#include <iostream>
using namespace std;
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

// class Solution {
// public:
// 	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
// 		ListNode * l3 = new ListNode(0);
// 		ListNode * last_node = l3;
// 		ListNode * last_1;
// 		ListNode * last_2;
// 		int overflow = 0;
// 		while(l1 != NULL && l2 != NULL){
// 			ListNode *node = new ListNode(l1->val + l2->val + overflow);
// 			last_node->next = node;
// 			if(node->val >= 10){
// 				overflow = node->val / 10;
// 				node->val = node->val % 10;
// 			}else {
// 				overflow = 0;
// 			}
// 			l1 = l1->next;
// 			l2 = l2->next;
// 			last_1 = l1;
// 			last_2 = l2;
// 			last_node = node;
// 		}
// 		if(l1 == NULL){
// 			while(l2 != NULL){
// 				ListNode *node = new ListNode(l2->val + overflow);
// 				last_node->next = node;
// 				if(node->val >= 10){
// 					overflow = node->val / 10;
// 					node->val = node->val % 10;
// 				}else {
// 					overflow = 0;
// 				}
// 				l2 = l2->next;
// 				last_2 = l2;
// 				last_node = node;
// 			}
// 			if(overflow > 0){
// 				ListNode *node = new ListNode(overflow);
// 				last_node -> next = node;
// 			}
// 		}
// 		if(l2 == NULL){
// 			while(l1 != NULL){
// 				ListNode *node = new ListNode(l1->val + overflow);
// 				last_node->next = node;
// 				if(node->val >= 10){
// 					overflow = node->val / 10;
// 					node->val = node->val % 10;
// 				}else {
// 					overflow = 0;
// 				}
// 				l1 = l1->next;
// 				last_1 = l1;
// 				last_node = node;
// 			}
// 			if(overflow > 0){
// 				ListNode *node = new ListNode(overflow);
// 				last_node -> next = node;
// 			}
// 		}
// 		return l3->next;
// 	}
// };

class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode * l3 = l1;
		ListNode * last_1;
		ListNode * last_2;
		int overflow = 0;
		while(l1 != NULL && l2 != NULL){
			l1->val = l1->val + l2->val + overflow;
			if(l1->val >= 10){
				overflow = l1->val / 10;
				l1->val = l1->val % 10;
			}else {
				overflow = 0;
			}
			last_1 = l1;
			last_2 = l2;
			l1 = l1->next;
			l2 = l2->next;
		}
		if(l2 == NULL){
			while(l1 != NULL && overflow > 0){
				l1->val = l1->val + overflow;
				if(l1->val >= 10){
					overflow = l1->val / 10;
					l1->val = l1->val % 10;
				}else {
					overflow = 0;
					break;
				}
				last_1 = l1;
				l1 = l1->next;
			}
			if(overflow > 0){
				ListNode *node = new ListNode(overflow);
				last_1 -> next = node;
			}
		}
		if(l1 == NULL){
			if(l2 != NULL){
				last_1->next = l2;
			}
			while(l2 != NULL && overflow > 0){
				l2->val = l2->val + overflow;
				if(l2->val >= 10){
					overflow = l2->val / 10;
					l2->val = l2->val % 10;
				}else {
					overflow = 0;
					break;
				}
				last_2 = l2;
				l2 = l2->next;
			}
			if(overflow > 0){
				ListNode *node = new ListNode(overflow);
				last_2 -> next = node;
			}
		}	
		return l3;
	}
};

int main(int argc, char const *argv[])
{
	ListNode n1(1);
	ListNode n5(7);
	ListNode n2(9);
	ListNode n4(9);
	//n1.next = &n5;
	n2.next = &n4;
	Solution s;
	ListNode *n3 = s.addTwoNumbers(&n1,&n2);
	while(n3!=NULL){
		cout<<n3->val<<endl;
		n3 = n3->next;
	}
	return 0;
}
