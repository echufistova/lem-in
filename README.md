# lem-in
An ant farm with numbers of ants, rooms and rooms links is given. The goal of the project is to find the best possible ways to direct ants to the end room.

At the beginning of the game, all the ants are in the room ##start. The goal is to bring them to the room ##end with as few turns as possible. Each room can only contain one ant at a time. (except at ##start and ##end which can contain as many ants as necessary.)

- ##start signals the ant farm’s entrance and ##end its exit.
- At each turn you will only display the ants that moved.
- At each turn you can move each ant only once and through a tube (the room at the receiving end must be empty).

Format of the output:
Lx-y Lz-w Lr-o
where x, z, r represents the ants’ numbers (going from 1 to number_of_ants) and y, w, o represents the rooms’ names.

Example of valid map:
2 
1 0 2
##start
0 2 0
##end
4 2 6
2 4 2
3 4 4
0-1
0-2
2-3
3-4
4-1

Output of this map:
L1-1
L1-4 L2-1
L2-4

Error management is present.

To check the work of the project you need to compile it. In the root of repository write "make" in your terminal, press Enter and then exe named "lem-in" will be created. In the diectory to_test you can generate a test map for the ant farm like this "./generator --flow-one" or write "./generator --help" to see other options. To start write: " ../lem-in < test" in the terminal, where test is the file that contains generated map.
