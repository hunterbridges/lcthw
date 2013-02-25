#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "engine.h"

int Monster_attack(void *self, int damage)
{
    assert(self != NULL);
    Monster *monster = self;

    printf("You attack %s!\n", monster->_(description));

    monster->hit_points -= damage;

    if (monster->hit_points > 0) {
        printf("It is still alive.\n");
        return 0;
    } else {
        printf("It is dead!\n");
        return 1;
    }
}

int Monster_init(void *self)
{
    assert(self != NULL);
    Monster *monster = self;
    monster->hit_points = 10;
    return 1;
}

void *Room_move(void *self, Direction direction)
{
    assert(self != NULL);
    Room *room = self;
    Room *next = NULL;

    if (direction == NORTH && room->north) {
        printf("You go north, into:\n");
        next = room->north;
    } else if (direction == SOUTH && room->south) {
        printf("You go south, into:\n");
        next = room->south;
    } else if (direction == EAST && room->east) {
        printf("You go east, into:\n");
        next = room->east;
    } else if (direction == WEST && room->west) {
        printf("You go west, into:\n");
        next = room->west;
    } else {
        printf("You can't go that direction.");
        next = NULL;
    }

    if (next) {
        next->_(describe)(next);
    }

    return next;
}

int Room_attack(void *self, int damage)
{
    assert(self != NULL);
    Room *room = self;
    Monster *monster = room->bad_guy;

    if (monster) {
        monster->_(attack)(monster, damage);
        return 1;
    } else {
        printf("You flail in the air at nothing. Idiot.\n");
        return 0;
    }
}

void *Map_move(void *self, Direction direction)
{
    assert(self != NULL);
    Map *map = self;
    Room *location = map->location;
    Room *next = NULL;

    next = location->_(move)(location, direction);

    if (next) {
        map->location = next;
    }

    return next;
}

int Map_attack(void *self, int damage)
{
    assert(self != NULL);
    Map *map = self;
    Room *location = map->location;

    return location->_(attack)(location, damage);
}

int process_input(Map *game, char *command)
{
    assert(game != NULL);

    char ch = '\0';

    printf("\n> ");
    if (command) {
        ch = *command;
        printf("%c\n", ch);
    } else {
        ch = getchar();
        getchar(); // eat ENTER
    }

    int damage = rand() % 4;

    switch(ch) {
        case 'q':
            printf("Giving up? You suck.\n");
            return 0;
            break;

        case 'n':
            game->_(move)(game, NORTH);
            break;

        case 's':
            game->_(move)(game, SOUTH);
            break;

        case 'e':
            game->_(move)(game, EAST);
            break;

        case 'w':
            game->_(move)(game, WEST);
            break;

        case 'a':
            game->_(attack)(game, damage);
            break;

        case 'l':
            printf("You can go:\n");
            if (game->location->north) printf("NORTH\n");
            if (game->location->south) printf("SOUTH\n");
            if (game->location->east) printf("EAST\n");
            if (game->location->west) printf("WEST\n");
            break;

        default:
            printf("What?: %c\n", ch);
    }

    return 1;
}

