#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "ex19.h"

Object MonsterProto = {
    .init = Monster_init,
    .attack = Monster_attack
};

Object RoomProto = {
    .move = Room_move,
    .attack = Room_attack
};

Object MapProto = {
    .init = Map_init,
    .move = Map_move,
    .attack = Map_attack
};

int Map_init(void *self)
{
    assert(self != NULL);
    Map *map = self;

    // make some rooms for a small map
    Room *hall = NEW(Room, "The great Hall");
    Room *throne = NEW(Room, "The throne room");
    Room *arena = NEW(Room, "The arena, with the minotaur");
    Room *kitchen = NEW(Room, "Kitchen, you have the knife now");

    // put the bad guy in the arena
    arena->bad_guy = NEW(Monster, "The evil minotaur");

    // setup the map rooms
    hall->north = throne;

    throne->west = arena;
    throne->east = kitchen;
    throne->south = hall;

    arena->east = throne;
    kitchen->west = throne;

    // start the map and the character off in the hall
    map->start = hall;
    map->location = hall;

    return 1;
}

int main(int argc, char *argv[])
{
    srand(time(NULL));

    // make our map to work with
    Map *game = NEW(Map, "The Hall of the Minotaur.");

    printf("You enter the ");
    game->location->_(describe)(game->location);

    int count = argc - 1;
    int i = 0;
    char **command = argv + 1;

    for (i = 0; i < count; command++, i++) {
        char *command_char = &(*command)[0];
        if (!process_input(game, command_char)) return 0;
    }

    while (process_input(game, NULL)) {
    }

    return 0;
}
