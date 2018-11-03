/* Play noughts and crosses (tic-tac-toe) between two human players. */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

//-----------------------------------------------------------------------------
// Setting up types and constants.  Don't change this section.

// Constants for player X, player O, and neither N.
enum player { X, O, N };
typedef enum player player;

// Constants to represent validity checking.
enum validity { Unchecked, BadFormat, BadLetter, BadDigit, BadCell, OK };
typedef enum validity validity;

// A game object contains the current state of a game: the number of moves made,
// the player whose turn it is next, and the grid with each cell recording which
// player owns it.
struct game {
    int moves;
    player next;
    player grid[3][3];
};
typedef struct game game;

//-----------------------------------------------------------------------------
// Functions providing the logic of the game.  Develop these.

// Initialize a game, with the given player to move first.
void newGame(game *g, player first) {
	g -> moves = 0;
	g -> next = first;
	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			g -> grid[i][j] = N;
	return;
}

// Convert the letter in a valid move string such as "b2" into a row index.
int row(char *text) {

	int r = text[0] - 'a';
	return r;

    return -1;
}

// Convert the digit in a valid move string such as "b2" into a column index.
int col(char *text) {

	int c = text[1] - '1';
	return c;

    return -1;
}

// Check whether a move string typed in by the user such as "b2" is valid, and
// the corresponding cell is available.  Return a validity code.
validity valid(game *g, char *text) {
	if(strlen(text) != 2)
		return BadFormat;
	if(text[0] < 'a' || text[0] > 'c')
		return BadLetter;
	if(text[1] < '1' || text[1] > '3')
		return BadDigit;

	int r = row(text), c = col(text);
	if(g -> grid[r][c] != N)
		return BadCell;

    return OK;
}

// Make a move at the given valid position.
void move(game *g, int r, int c) {
	g -> grid[r][c] = g -> next;

	g -> moves++;

	if(g -> next == X)
		g -> next = O;
	else
		g -> next = X;
	return;
}

// Check if the given line is a winning one, and return the winning player.
player line(player p0, player p1, player p2) {
	if(p0 == p1 && p1 == p2)
		return p0;
    return N;
}

// Check whether a player has won, and return the winning player.
player win(game *g) {

	// Lines
	if(line(g -> grid[0][0], g -> grid[0][1], g -> grid[0][2]) != N)
		return g -> grid[0][0];
	if(line(g -> grid[1][0], g -> grid[1][1], g -> grid[1][2]) != N)
		return g -> grid[1][0];
	if(line(g -> grid[2][0], g -> grid[2][1], g -> grid[2][2]) != N)
		return g -> grid[2][0];

	// Cols
	if(line(g -> grid[0][0], g -> grid[1][0], g -> grid[2][0]) != N)
		return g ->grid[0][0];
	if(line(g -> grid[0][1], g -> grid[1][1], g -> grid[2][1]) != N)
		return g -> grid[0][1];
	if(line(g -> grid[0][2], g -> grid[1][2], g -> grid[2][2]) != N)
		return g -> grid[0][2];

	// Diags
	if(line(g -> grid[0][0], g -> grid[1][1], g -> grid[2][2]) != N)
		return g -> grid[0][0];
	if(line(g -> grid[0][2], g -> grid[1][1], g -> grid[2][0]) != N)
		return g -> grid[0][2];

    return N;
}

// Check whether the game has ended in a draw.
bool draw(game *g) {
	if(g -> moves == 9)
		return true;
    return false;
}

//-----------------------------------------------------------------------------
// Playing the game: Don't change this section until after submitting.

// Convert a player constant into a character for printing.
char show(player c) {
    return (c == X) ? 'X' : (c == O) ? 'O' : '-';
}

// Print a validity error message.
void printInvalid(validity v) {
    if (v == BadFormat) printf("Type a letter and a digit");
    else if (v == BadLetter) printf("Type a letter a, b or c");
    else if (v == BadDigit) printf("Type a digit 1, 2 or 3");
    else if (v == BadCell) printf("Choose an empty cell");
    printf("\n");
}

// Display the grid.
void display(game *g) {
    printf("  123\n");
    char abc[4] = "abc";
	for(int i = 0; i < 3; i++){
        printf("%c ", abc[i]);
	 	for(int j = 0; j < 3; j++)
	 		printf("%c", show(g -> grid[i][j]));
	 	printf("\n");
	}
}

// Ask the current player for their move, putting it into the given array.
// Ask repeatedly until the user types in a valid move.
void ask(game *g, char text[100]) {
    printf("Player %c enter a move: ", show(g -> next));
	char ch[20];
    fgets(ch, 20, stdin);
    ch[2] = '\0';
	while(valid(g, ch) != OK){
		printf("Please enter a valid move: ");
		fgets(ch, 20, stdin);
        ch[2] = '\0';
	}
    
    char r = row(ch);
    char c = col(ch);

    move(g, r, c);
    return;
}

// Play the game interactively between two human players who take turns.
void play(char player) {
	game gamedata;
    game *g = &gamedata;
    enum player winner = win(g);
    char moves[100] = "";
	newGame(g, player);
    display(g);
    while(g -> moves < 9){
        ask(g, moves);
        display(g);
        winner = win(g);
        if(winner != N)
            break;
    }
    if(draw(g))
        printf("The game is a draw!\n");
    else
        printf("The winner is %c!\n", show(winner));
    return;
}

//-----------------------------------------------------------------------------
// Testing and running: Don't change this section.

void test(){

}

// Run the program with no args to carry out the tests, or with one arg (the
// player to go first) to play the game.
int main(int n, char *args[n]) {
    if (n == 1) test();
    else if (n == 2 && strcmp(args[1],"X") == 0) play(X);
    else if (n == 2 && strcmp(args[1],"O") == 0) play(O);
    else {
        fprintf(stderr, "Use: ./oxotree  OR  ./oxotree X  OR  ./oxotree O\n");
        exit(1);
    }
    return 0;
}
