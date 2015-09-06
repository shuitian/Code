/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
#include <iostream>
#include <stdio.h>
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};
class Solution {
public:
    void deleteNode(ListNode* node) {
        while(node->next!=NULL){
        	node->val = node->next->val;
        	if(node->next->next == NULL){
        		node->next = NULL;
        	}else {
        		node = node->next;
        	}
        }

    }
};

void show(ListNode* node){
	while(node!=NULL){
		printf("%d",node->val);
		node = node->next;
	}
}

int main(int argc, char const *argv[])
{
	Solution *s = new Solution();
	ListNode n1(1);
	ListNode n2(2);
	ListNode n3(3);
	ListNode n4(4);
	n1.next = &n2;
	n2.next = &n3;
	n3.next = &n4;
	show(&n1);
	s->deleteNode(&n3);
	show(&n1);
	return 0;
}