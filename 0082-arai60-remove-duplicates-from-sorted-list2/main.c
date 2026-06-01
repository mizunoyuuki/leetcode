typedef struct ListNode ListNode;

struct ListNode* deleteDuplicates(struct ListNode *head){
	if (head == NULL) return NULL;
	if (head->next == NULL) return head;

	ListNode dummy;
	dummy.next = NULL;
	ListNode *tail = &dummy;
	ListNode *cur = head;

	while(cur){
		ListNode *next = cur->next;
		if (next != NULL && cur->val == next->val){
			while(next != NULL && cur->val == next->val){
				next = next->next;
			}
			cur = next;
		} else {
			tail->next = cur;
			tail = tail->next;
			cur = cur->next;
		}
	}
	tail->next = NULL;

	return dummy.next;
}
