/*ダミーノードのいい点*/

struct ListNode* deleteDuplicatee(struct ListNode* head){
	// 先頭の重複を先に処理しないといけない。(特殊ケース)
	while (head != NULL && head->next != NULL && head->val == head->next->val){
		int val = head->val;
		while (head != NULL && head->val == val){
			head = head->next;
		}
	}

	if (head == NULL) return NULL;

	ListNode *cur = head;

	while (cur->next){
		ListNode *next = cur->next;
		if (next->next != NULL && next->val == next->next->val){
			int val = next->val;
			while (next!=NULL && next->val == val){
				next = next->next;
			}
			cur->next = next;
		} else {
			cur = cur->next;
		}
	}

	return head;
}
