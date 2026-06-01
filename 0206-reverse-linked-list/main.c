typedef struct ListNode ListNode;

struct ListNode* reverseList(struct ListNode* head){
	if (!head) return NULL;
    
    ListNode *tmp;
	ListNode *tmp1;
	ListNode *result = head;
	ListNode *cur = result->next;
	result->next = NULL;

	while(cur){
		tmp1 = result;
		result = cur;
		tmp = cur->next;
		result->next = tmp1;
		cur = tmp;

	}

	return result;
}
