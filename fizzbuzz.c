#include <stdio.h>

int main(int argc, char *argv[]) {
    int i = 0;
    for (i = 1; i <= 100; i++) {
        int three = (i % 3 == 0);
        int five = (i % 5 == 0);

        if (five && three) printf("FizzBuzz\n");
        else if (three) printf("Fizz\n");
        else if (five) printf("Buzz\n");
        else printf("%d\n", i);
    }

    return 0;
}
