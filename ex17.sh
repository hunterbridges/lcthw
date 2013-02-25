#!/bin/sh
set -ex

./ex17 testdb.dat c 8 512
./ex17 testdb.dat s 1 "Hunter Bridges" "hbridges@gmail.com" "San Francisco, CA"
./ex17 testdb.dat s 2 "Jeff Rafter" "jeffrafter@gmail.com" "Redlands, CA"
./ex17 testdb.dat s 3 "Mike Kavouras" "kavourasm@gmail.com" "New York, NY"
./ex17 testdb.dat s 4 "Levi Kennedy" "levicole@gmail.com" "San Francisco, CA"
./ex17 testdb.dat s 5 "Brandon Withrow" "buba447@gmail.com" "San Francisco, CA"
./ex17 testdb.dat s 6 "Willy Hardy" "wonkajh@gmail.com" "Raleigh, NC"
./ex17 testdb.dat g 1
./ex17 testdb.dat g 2
./ex17 testdb.dat g 3
./ex17 testdb.dat g 4
./ex17 testdb.dat g 5
./ex17 testdb.dat g 6
./ex17 testdb.dat l
./ex17 testdb.dat g 1
./ex17 testdb.dat g 2
./ex17 testdb.dat g 3
./ex17 testdb.dat l
./ex17 testdb.dat f "Brando"
./ex17 testdb.dat f "wonka"
./ex17 testdb.dat f "San"
./ex17 testdb.dat f "abcdefg"
rm -f testdb.dat
