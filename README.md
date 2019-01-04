# Oxotree

“oxotree.c” is a modified version of “oxo.c”. Instead of a noughts and crosses game between two players, it is a noughts and crosses game between a human player and the computer.

The program is run with “./oxotree X” or “./oxotree O”,  so that the human player chooses whether they want to go first or second. X always goes first. The player has to input the coordinates of the cell they want to play.

The computer player uses a game tree to decide what the best move is.  The scoring function is based on the winning player and the game depth, so the computer ends a game as fast as possible. The computer always plays a perfect game (it either always wins, or ends in a draw). The function to find the best move makes use of a minimax algorithm. Every possible outcome is calculated each time the computer choses a new move.

Testing of the additional functions is done with “./oxotree”, however, the fact that the computer runs through all the remaining possible games before deciding on the best move makes it particularly unpredictable.

Resources used:

Game tree: https://en.wikipedia.org/wiki/Game_tree

Minimax algorithm: https://en.wikipedia.org/wiki/Minimax
