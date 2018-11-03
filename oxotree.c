/* Play noughts and crosses (tic-tac-toe) between a human and a computer */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

//-----------------------------------------------------------------------------
// Setting up types and constants.

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

// Keep track of human and computer player
player human = N;
player comp = N;

//-----------------------------------------------------------------------------
// Functions providing the logic of the game.

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

// Convert indices into a valid move string
void indicesToMove(int r, int c, char *m){
    m[0] = r + 'a';
    m[1] = c + '1';
    m[2] = '\0';
    return;
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

void unmove(game *g, int r, int c){
    g -> grid[r][c] = N;

    g -> moves--;

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
// Minimax functions

// Return max number
int max(int a, int b){
    if (a > b)
        return a;
    return b;
}

// Return min number
int min(int a, int b){
    if (a > b)
        return b;
    return a;
}

int score(game *g){
    if (win(g) == comp)
        return 10 - g -> moves;
    else if (win(g) == human)
        return g -> moves - 10;
    else
        return 0;
}

// Minimax implementation: runs all possible games onwards from a given position
int minimax(game *g){
    if(win(g) != N || draw(g))
        return score(g);
    
    if(g -> next == comp){
        int scoremax = -100000;
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                if(g -> grid[i][j] == N){
                    move(g, i, j);
                    scoremax = max(scoremax, minimax(g));
                    unmove(g, i, j);
                }
        return scoremax;
    }
    else{
        int scoremin = 100000;
        for(int i = 0; i < 3; i++)
            for(int j = 0; j < 3; j++)
                if(g -> grid[i][j] == N){
                    move(g, i, j);
                    scoremin = min(scoremin, minimax(g));
                    unmove(g, i, j);
                }
        return scoremin;
    }
}

// Find the best possible move
void findMove(game *g, char *m){
    int r = -1, c = -1;
    int bestscore = -100000;

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(g -> grid[i][j] == N){
                move(g, i, j);
                int currentscore = minimax(g);
                unmove(g, i, j);

                if(currentscore > bestscore){
                    r = i;
                    c = j;
                    bestscore = currentscore;
                }
            }
    indicesToMove(r, c, m);
    return;
}

//-----------------------------------------------------------------------------
// Playing the game: Don't change this section until after submitting.

// Convert a player constant into a character for printing.
char show(player c) {
    return (c == X) ? 'X' : (c == O) ? 'O' : '-';
}

// Convert validity into string for printing
void errMessage(validity err, char *mess){
    switch(err){
        case BadFormat: strcpy(mess, "BadFormat"); break;
        case BadLetter: strcpy(mess, "BadLetter"); break;
        case BadDigit: strcpy(mess, "BadDigit"); break;
        case BadCell: strcpy(mess, "BadCell"); break;
    }
    return;
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

// Ask the player for their move, putting it into the given array.
// Ask repeatedly until the user types in a valid move.
void ask(game *g) {
    printf("Player %c enter a move: ", show(g -> next));
	char ch[200];
    fgets(ch, 200, stdin);
    ch[2] = '\0';
	while(valid(g, ch) != OK){
        validity error = valid(g, ch);
        char mess[10];
        errMessage(error, mess);
		printf("Please enter a valid move (%s. Correct format example is \"b2\"): ", mess);
		fgets(ch, 200, stdin);
        ch[2] = '\0';
	}
    
    int r = row(ch);
    int c = col(ch);

    move(g, r, c);
    return;
}

// Play the game interactively between a human and a computer who take turns.
void play(char player) {
	game gamedata;
    game *g = &gamedata;

    human = player;
    if(human == X)
        comp = O;
    else
        comp = X;

    enum player winner = win(g);

	newGame(g, X);
    display(g);

    while(g -> moves < 9){
        if(g -> next == human)
            ask(g);
        else{
            char m[3];
            findMove(g, m);

            printf("Player %c enter a move: ", show(g -> next));
            printf("%s\n", m);

            int r = row(m);
            int c = col(m);
            move(g, r, c);
        }
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
// Testing and running.

// Set up a game structure with given contents.  The grid is given as a string
// of the form "XO- -XO X-X", then the next player, then the number of moves.
// Work out the number of moves made and the player to move next.
void setup(game *g, char *grid) {
    int xs = 0, os = 0, moves = 0;
    for (int r=0; r<3; r++) {
        for (int c=0; c<3; c++) {
            char ch = grid[r*4 + c];
            if (ch == 'X') { g->grid[r][c] = X; xs++; moves++; }
            else if (ch == 'O') { g->grid[r][c] = O; os++; moves++; }
            else g->grid[r][c] = N;
        }
    }
    g->moves = moves;
    if (xs == os || xs == os - 1) g->next = X;
    else if (xs == os + 1) g->next = O;
    else printf("Setup problem\n");
}

// Test the score function
void testScores(game *g){
    human = X;
    comp = O;

    setup(g, "XXX OO- -OO");
    assert(score(g) < 0);

    setup(g, "OOO XX- -XX");
    assert(score(g) > 0);

    setup(g, "XOX OO- -XO");
    assert(score(g) == 0);
}

// Test the minimax function
void testMinimax(game *g){
    human = X;
    comp = O;

    setup(g, "XX- O-- -OO");
    assert(minimax(g) < 0);

    setup(g, "OO- X-- -XX");
    assert(minimax(g) > 0);
}

void testFindMove(game *g){
    human = X;
    comp = O;
    char m[3];

    setup(g, "X-- OO- X-O");
    findMove(g, m);
    assert(strcmp("a2", m) == 0);

    setup(g, "O-- XX- O-X");
    findMove(g, m);
    assert(strcmp("b3", m) == 0);
}

void test(){
    game *g = malloc(sizeof(game));
    testScores(g);
    testMinimax(g);
    testFindMove(g);
    free(g);
    printf("All tests passed.\n");
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
