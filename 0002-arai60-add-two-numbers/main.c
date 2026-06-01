typedef struct ListNode ListNode;

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
	/* ListNodeのまま足し算を行い、桁あがりを実装する*/

	ListNode *cur_l1 = l1;
	ListNode *cur_l2 = l2;

	ListNode dummy;
	dummy.next = NULL;
	ListNode *tail = &dummy;
	int carry_flag = 0;
	int val = 0;

	while(cur_l1 != NULL || cur_l2 != NULL || carry_flag != 0){
		if (cur_l1 != NULL && cur_l2 != NULL){
			val = carry_flag ? cur_l1->val + cur_l2->val + carry_flag : cur_l1->val + cur_l2->val;
		} else if (cur_l1 == NULL && cur_l2 != NULL){
			val = carry_flag ? cur_l2->val + carry_flag : cur_l2->val;
		} else if (cur_l1 != NULL && cur_l2 == NULL){
			val = carry_flag ? cur_l1->val + carry_flag : cur_l1->val;
		} else if (cur_l1 == NULL && cur_l2 == NULL && carry_flag){
			val = carry_flag;
			carry_flag = 0;
		}

		if (val > 9){
			val = val - 10;
			carry_flag = 1;
		} else if ((cur_l1 != NULL || cur_l2 != NULL) && carry_flag != 0){
			carry_flag = 0;
		}

		ListNode *cur = calloc(1, sizeof(ListNode));
		cur->val = val;
		cur->next = NULL;
		tail->next = cur;
		tail = tail->next;

		if(cur_l1 != NULL) cur_l1 = cur_l1->next;
		if(cur_l2 != NULL) cur_l2 = cur_l2->next;
	}

	return dummy.next;
}
