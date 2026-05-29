bool isPalindrome(int x) {
    if (x < 0) return false;
    if (x == 0) return true;

    char str[15] = {0};
    int quotient = x;
    int length = 0;

    while (quotient != 0) {
        str[length] = (quotient % 10) + '0';
        quotient = quotient / 10;
        length++;
    }

    for (int i = 0; i < length / 2; i++) {
        if (str[i] != str[length - 1 - i]) {
            return false;
        }
    }

    return true;
}
