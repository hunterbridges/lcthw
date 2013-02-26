#include <stdio.h>

int main(int argc, char *argv[])
{
    int numbers[4] = {0};
    char name[4] = {'a', 'a', 'a', '\0'};

    // first, print them out raw
    printf("numbers: %d %d %d %d\n",
            numbers[0], numbers[1],
            numbers[2], numbers[3]);

    printf("name each %c %c %c %c\n",
            name[0], name[1],
            name[2], name[3]);

    printf("name: %s\n", name);

    // setup the numbers
    numbers[0] = 'a';
    numbers[1] = 'b';
    numbers[2] = 'c';
    numbers[3] = 'd';

    // setup the name
    name[0] = 'Z';
    name[1] = 'e';
    name[2] = 'd';
    name[3] = '\0';

    // then print them out initialized
    printf("numbers: %d %d %d %d\n",
            numbers[0], numbers[1],
            numbers[2], numbers[3]);

    printf("name each: %c %c %c %c\n",
            name[0], name[1],
            name[2], name[3]);

    // print the name like a string
    printf("name: %s\n", name);

    // another way to use name
    char *another = "Zed";

    printf("another: %s\n", another);

    printf("another each: %c %c %c %c\n",
            another[0], another[1],
            another[2], another[3]);

    // crazy hack
    int crazy_hack = 0;
    crazy_hack = 'Z' << 8 * 3;
    crazy_hack |= 'e' << 8 * 2;
    crazy_hack |= 'd' << 8 * 1;
    crazy_hack |= '\0' << 8 * 0;

    printf("crazy hack: %c %c %c %c\n",
            crazy_hack >> 8 * 3,
            crazy_hack >> 8 * 2,
            crazy_hack >> 8 * 1,
            crazy_hack >> 0);

    return 0;
}
