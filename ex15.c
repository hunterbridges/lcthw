#include <stdio.h>

void first_way(char **names, int *ages, int max_offset) {
    // first way of using indexing
    int i = 0;
    for (i = 0; i < max_offset; i++) {
        printf("%s has %d years alive.\n",
                names[i], ages[i]);
    }

    printf("---\n");
}

void second_way(char **names, int *ages, int max_offset) {
    // setup the pointers to the start of the arrays
    int i = 0;
    int *cur_age = ages;
    char **cur_name = names;

    // second way using pointers
    for (i = 0; i < max_offset; i++) {
        printf("%s is %d years old.\n",
                *(cur_name+i), *(cur_age+i));
        printf("%d == %ld ?\n",
                i,
                ((cur_name + i) - (names)));
    }

    printf("---\n");

}

void third_way(char **names, int *ages, int max_offset) {
    // third way, pointers are just arrays
    int i = 0;
    int *cur_age = ages;
    char **cur_name = names;

    for (i = 0; i < max_offset; i++) {
        printf("%s is %d years old again.\n",
                cur_name[i], cur_age[i]);
    }

    printf("---\n");
}

void fourth_way(char **names, int *ages, int max_offset) {
    int *cur_age = ages;
    char **cur_name = names;

    for (cur_name = names, cur_age = ages;
            (cur_age - ages) < max_offset;
            cur_name++, cur_age++)
    {
        printf("%s lived %d years so far.\n",
                *cur_name, *cur_age);
    }

}

int main(int argc, char *argv[])
{
    // create two arrays we care about
    int ages[] = {23, 43, 12, 89, 2};
    char **names = (argv + 1);

    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    if (argc - 1 > count) {
        printf("Too many args!");
        return 1;
    }

    int the_max = 0;
    for (i = 0; i < argc - 1 && i < count; i++) {
        the_max++;
    }

    first_way(names, ages, the_max);
    second_way(names, ages, the_max);
    third_way(names, ages, the_max);
    fourth_way(names, ages, the_max);

    return 0;
}
