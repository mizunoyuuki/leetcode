bool is_start(char s){
    return s == '(' || s == '[' || s == '{';
}

bool is_end(char s){
    return s == ')' || s== ']' || s== '}';
}

int push(char *stack, int sp, char s){
    sp++;
    stack[sp] = s;
    return sp;
}

int pop(char *stack, int sp, char s){
    char expected = (s == ')') ? '(' : (s == ']') ? '[' : '{';
    if (stack[sp] == expected){
        --sp;
        return sp;
    } else {
        return -1;
    }
}

bool isValid(char* s) {
    int i= 0;
    char *stack = calloc(10000, sizeof(char));
    int sp = 0; 
    while(s[i]){
        if (is_start(s[i])){
            sp = push(stack, sp, s[i]);
        } else if (is_end(s[i])){
            sp = pop(stack, sp, s[i]);
            if (sp == -1) return false;
        }
        i++;
    }
    return sp == 0;
}
