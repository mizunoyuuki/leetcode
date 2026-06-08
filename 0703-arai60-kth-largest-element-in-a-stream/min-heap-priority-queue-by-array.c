typedef struct KthLargest KthLargest;

struct KthLargest {
	int k;
	int size;
	int *array;
};

KthLargest *init_priority_queue(int k, int numsSize){
	int *array = calloc(k, sizeof(int));
	KthLargest *kl = calloc(1, sizeof(KthLargest));
	kl->array = array;
	kl->size = 0;
	kl->k = k;

	return kl;
}

KthLargest *kthLargestCreate(int k, int *nums, int numsSize){
	KthLargest *kl = init_priority_queue(k, numsSize);

	for (int i = 0; i < numsSize; i++){
		kthLargestAdd(kl, nums[i]);
	}

	return kl;
}

void shift_up(KthLargest *obj){
	if (obj->size == 0) return;

	int c = obj->size - 1;
	int *array = obj->array;

	while(c >= 0){
		if (c == 0) break;

		int next = (c - 1)/2;
		if (array[next] > array[c]){
			int tmp = array[next];
			array[next] = array[c];
			array[c] = tmp;
			c = next;
		} else {
			break;
		}
	}

	return;
}

void shift_down(KthLargest *obj){
      int c = 0;
      int *array = obj->array;

      while(2*c+1 < obj->size){
          int smallest = c;
          int left = 2*c + 1;
          int right = 2*c + 2;

          if (array[left] < array[smallest])
              smallest = left;
          if (right < obj->size && array[right] < array[smallest])
              smallest = right;

          if (smallest == c) break;

          int tmp = array[c];
          array[c] = array[smallest];
          array[smallest] = tmp;

          c = smallest;
      }

      return;
  }


int kthLargestAdd(KthLargest *obj, int val){
	if (obj->size < obj->k){
		obj->array[obj->size] = val;
		obj->size += 1;
		shift_up(obj);
	} else {
		if (obj->array[0] > val) return obj->array[0];

		obj->array[0] = val;
		shift_down(obj);
	}

	return obj->array[0];
}

void kthLargestFree(KthLargest *obj){}
