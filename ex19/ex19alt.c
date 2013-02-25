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

    Room *field = NEW(Room, "Hyrule field");

    Room *drawbridge = NEW(Room, "Castle drawbridge");
    field->north = drawbridge;
    drawbridge->south = field;

    Room *pots = NEW(Room, "Room with a bunch of pots in it");
    drawbridge->east = pots;
    pots->west = drawbridge;
    Monster *pot = NEW(Monster, "A pot");
    pot->hit_points = 1;
    pots->bad_guy = pot;

    Room *market = NEW(Room, "Hyrule castle market");
    drawbridge->north = market;
    market->south = drawbridge;

    Room *outside_tot = NEW(Room, "Outside the Temple of Time");
    market->east = outside_tot;
    outside_tot->west = market;

    Room *temple = NEW(Room, "The Temple of Time");
    outside_tot->east = temple;
    temple->west = outside_tot;

    Room *courtyard = NEW(Room, "Outside Ganondorf's castle");
    market->north = courtyard;
    courtyard->south = market;

    Room *castle = NEW(Room, "Ganondorf's castle");
    courtyard->north = castle;
    castle->south = courtyard;
    Monster *ganondorf = NEW(Monster, "Ganondorf");
    ganondorf->hit_points = 20;
    castle->bad_guy = ganondorf;

    map->start = field;
    map->location = field;

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
