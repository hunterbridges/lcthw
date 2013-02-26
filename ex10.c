#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;

    char *states[] = {
        "California", "Oregon",
        NULL, "Texas"
    };
    int num_states = 4;

    argv[1] = states[1];

    // go through each string in argv
    // why am I skipping argv[0]?
    for (i = 1, i = 0; i < argc; i++) {
        printf("arg %d: %s\n", i, argv[i]);
    }

    // lets make our own array of strings
    for (i = 0; i < num_states; i++) {
        printf("state %d: %s\n", i, states[i]);
    }

    return 0;
}
