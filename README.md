# Not So Deep Blue
A relatively basic chess engine in C++. It uses 64-bit "bitboards" to represent chessboard. Each
piece type and color has its own bitboard which represents the 64 squares of the chessboard. A set
bit indicates that the piece type occupies that square on the board, while 0 means its empty. The
board is a union of all the piece bitboards, which are disjoint sets (since no square can have more
than one piece on it at a time).

Searching for moves uses a modified version of the alpha-beta improvement to the minimax
algorithm. This algorithm checks different move trees from the given position, but it keeps an upper
and lower bound on the scores. By doing this, it can cut searches short if it comes across a move
that will refute the previous move. This results in a much faster search than the regular minimax
algorithm.

To evaluate positions, Not So Deep Blue only considers material for both sides. It adds up the
material weight for a piece multiplied by the number of that piece on the board for the side. It
does this for both sides, then subtracts black from white. If it's black's move, the score is
multiplied by -1.

## Usage

To build on a UNIX environment, run the following command in the terminal (from within the project
directory):
```
make
```
This will build the program and create the executable. You can use the executable along with any
UCI-compliant GUI program. I've used Arena during development. To load it into Arena, type `F11` to
bring up the Manage Engines window, then click New near the bottom of the window. From there you can
enter the info for the engine and then use it as you would any other.

## Future Improvements
- Better move ordering: currently this engine does a very simple ordering of captures based on the
  material weight of the captured piece compared to the capturing piece. I'd like to make the move
  ordering a bit more sophisticated so that it takes more factors into account.
- Improved move evaluation: the engine only uses material strength to evaluate each position. I plan
  to add more sophistication to this, such as some positional awareness and a score for things like
  mobility, passed pawns, king safety, etc.
- Transposition tables: while recursively searching positions, it's inevitable that the engine will
  encounter identical positions reached in different ways. A transposition table to store board
  positions would cut down on the amount of time each search takes, since instead of calculating the
  score again it could simply look into the table before evaluation.
- Hashing of positions: in order to use transposition tables, I would need to come up with a way to
  represent positions in a way that they could use used as keys in a table. The way that seems most
  common would be Zobrist hashing.
