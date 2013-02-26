#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc == 1) {
        printf("ERROR: You need at least one argument.\n");
        // this is how you abort a program
        return 1;
    }

    int w = 0;
    for (w = 1; w < argc; w++) {
        int i = 0;
        char letter = '\0';
        for (i = 0, letter = argv[w][i];
             argv[w][i] != '\0';
             i++, letter = argv[w][i]) {
            if (letter <= 'Z') {
                letter += 'a' - 'A';
            }

            switch(letter) {
                case 'a':
                    printf("%d: 'A'\n", i);
                    break;

                case 'e':
                    printf("%d: 'E'\n", i);
                    break;

                case 'i':
                    printf("%d: 'I'\n", i);
                    break;

                case 'o':
                    printf("%d: 'O'\n", i);
                    break;

                case 'u':
                    printf("%d: 'U'\n", i);
                    break;

                case 'y':
                    if (i > 2) {
                        // it's only sometimes Y
                        printf("%d: 'Y'\n", i);
                        break;
                    }
                    // Fallthrough

                default:
                    printf("%d: %c is not a vowel\n", i, letter);
            }
        }
        printf("\n");
    }

    return 0;
}
