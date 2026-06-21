#include <stdio.h>
#include <stdlib.h>

#define CHANK 20

typedef struct Record Record;
struct Record {
    int amount;
    int order_id;
};

int cmp(const void *a, const void *b) {
    const Record *x = a;
    const Record *y = b;
    return (x->amount > y->amount) - (x->amount < y->amount);
}

int create_runs(const char *input_path) {
    FILE *in = fopen(input_path, "r");
    if (in == NULL) { perror("fopen input"); exit(1); }

    Record *buf = malloc(CHANK * sizeof(Record));
    int run_no = 0;

    while (1) {
        int count = 0;
        while (count < CHANK && fscanf(in, "%d %d", &buf[count].amount, &buf[count].order_id) == 2) {
            count++;
        }
        if (count == 0) break;

        qsort(buf, count, sizeof(Record), cmp);

        char name[64];
        snprintf(name, sizeof(name), "run_%d.txt", run_no);
        FILE *out = fopen(name, "w");
        if (out == NULL) { perror("fopen run (write)"); exit(1); }
        for (int i = 0; i < count; i++) {
            fprintf(out, "%d %d\n", buf[i].amount, buf[i].order_id);
        }
        fclose(out);

        run_no++;
    }

    free(buf);
    fclose(in);
    return run_no;
}

void merge_runs(int k, const char *output_path) {
    FILE *out = fopen(output_path, "w");
    if (out == NULL) { perror("fopen output"); exit(1); }

    FILE   **fps   = malloc(k * sizeof(*fps));
    Record  *head  = malloc(k * sizeof(*head));
    int     *alive = malloc(k * sizeof(*alive));

    for (int i = 0; i < k; i++) {
        char name[64];
        snprintf(name, sizeof(name), "run_%d.txt", i);
        fps[i] = fopen(name, "r");
        if (fps[i] == NULL) { perror("fopen run (read)"); exit(1); }

        if (fscanf(fps[i], "%d %d", &head[i].amount, &head[i].order_id) == 2)
            alive[i] = 1;
        else
            alive[i] = 0;
    }

    while (1) {
        int best = -1;
        for (int i = 0; i < k; i++) {
            if (!alive[i]) continue;
            if (best == -1 || head[i].amount < head[best].amount) best = i;
        }
        if (best == -1) break;

        fprintf(out, "%d %d\n", head[best].amount, head[best].order_id);

        if (fscanf(fps[best], "%d %d", &head[best].amount, &head[best].order_id) != 2)
            alive[best] = 0;
    }

    for (int i = 0; i < k; i++) fclose(fps[i]);
    free(fps); free(head); free(alive);
    fclose(out);
}

int main() {
    int k = create_runs("input.txt");

    merge_runs(k, "output.txt");

    return 0;
}
