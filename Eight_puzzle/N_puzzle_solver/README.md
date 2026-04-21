# N Puzzle Solver

N puzzle sover program revisit.
It was three years ago when I was in my first year of college, ...(TODO)

## The Target

The board is big (17x17 puzzle is approximate $289! / 2$, which is roughly $10^{590}$ states. For context, the observable universe only has about $10^{80}$ atoms.)

So it's nearly impossible to find an **optimal** solution, but can we find a **suboptimal** solution? That is, can we find a solution that is good enough (less moves) and in a reasonable time (as fast as possible)?

## Idea

- Compress board state, to reduce memory usage.
- Hash table (using flat array, also a dynamic array): for fast state search, and check if a state is visited before.
- Heap: as a priority queue, to start search with the smallest heuristic value
- Hybrid heuristic function: Manhatan distance, ...(Not decided yet)
- Fringe Reduction: solve top row and left column first, shrink the board size down

### Storing Board State

Use **64-bit Zobrist hashing** to compress the board state. Moving a piece contains only **4 XOR** operations. Comparing board is also fast as it's just 64-bit integer comparison.

<!-- To avoid collision, we also store the exact values in the board. -->

<!-- But use `int board[17][17]` to represent the board consumes too much memory, so we compress it, use only the minimal bits that fits the number. For example, the largest number in 13x13 puzzle is `13*13-1 = 168`, and `168` fits in `uint8_t`, so we don't need to use `int board[13][13]`, we can use `uint8_t board[13][13]` or `uint8_t board[169]`. -->

<!-- As for 17x17 puzzle, we can use `uint16_t` as the type, it would waste some memory, but it's fast than bit-packing the number into the `uint64_t` variable use bit-shifting and masking to extract the value. -->

I want to know if this state is met before, so I use Zobrist hashing to it and get a hash value.
How do I quickly search if the hash value is presented? I use a hash map to store the hash value.
I also want to know the parent of current state, so there's a parent_idx field in BoardMetadata, but index in hash table might change once it resizes, so I use another array to store the data, and store the index of the data in that array to the hash table.

### Searching

- Strategy
    - Use **Fringe Method**, solve top row and left column first, so the board size reduces

- Lock map
    - Indicates that a tile is solve, and can't be moved.

- Hash table
    - Use `hash table (flat dynamic array)`, with `linear probing` when collides. This stores the visited states' hash values, no need to store the whole board.
    - Also uses as a tree, we can backtrace until the root to find the moves we made.
    - Separate the data and hash table, data store in a dynamic array, hash table stores the index of data in that array, so resize the hash table won't affect the route for backtrace.
    - Cleared when a tile is solved.

- Bucket queue
    - Store the states to be expanded, need to store the whold board
    - Cleared when a tile is solved.

- Search method
    - **Weighted A-star**
MD = manhatan distance
f = h + g
h = MD(target tile, destination) * 100 + MD(blank tile, target tile)
g = moves made
(TODO)

## TODO

1. Handle all the situations if solving row/col tiles in the ascending order of their heuristic value
2. Remove Arena allocator, find another way so that the program won't fail if the arena capacity is not large enough
    - Make bucket queue have max limit? If exceed, drop the node or remove the worst one?
    - Or, Don't store the board, track to the root to construct the board?

## References

- [Zobrist Hashing](https://ithelp.ithome.com.tw/articles/10364171)
- [A* Variants](https://www.movingai.com/astar-var.html)
- [Bucket queue](https://en.wikipedia.org/wiki/Bucket_queue)
- [Xorshift](https://en.wikipedia.org/wiki/Xorshift)
- [Kociemba](https://kociemba.org/#fifteen)