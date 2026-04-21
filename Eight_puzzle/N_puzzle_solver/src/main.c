#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define DA_IMPLEMENTATION
#include <da.h>

#define ARENA_IMPLEMENTATION
#include <arena.h>

#ifndef typeof
#define typeof __typeof__
#endif
#define STB_DS_IMPLEMENTATION
#include <stb_ds.h>

#define NDEBUG

#ifndef NDEBUG
    #define ASSERT(cond) \
        do { \
            if (!(cond)) { \
                fprintf(stderr, "%s:%d: ASSERT FAILED: %s\n", __FILE__, __LINE__, #cond); \
                exit(1); \
            } \
        } while(0)

    #define LOGF(fmt, ...) \
        do { \
            fprintf(stdout, "%s:%d: LOG: " fmt "\n", \
                    __FILE__, __LINE__, ##__VA_ARGS__); \
        } while(0)

    #define LOG_BOARD(board) \
        do { \
            printf("%s:%d: LOG_BOARD: \n", __FILE__, __LINE__); \
            for (size_t i = 0; i < board_size; i++) { \
                for (size_t j = 0; j < board_size; j++) { \
                    printf("%3d ", board.tiles[i*board_size + j]); \
                } \
                printf("\n"); \
            } \
            printf("\n"); \
        } while(0)

    #define DEBUG() do { fprintf(stdout, "%s:%d: DEBUG\n", __FILE__, __LINE__); } while(0)
#else
    #define ASSERT(cond) do { (void)(cond); } while(0)
    #define LOGF(fmt, ...) do { (void)(fmt); } while(0)
    #define LOG_BOARD(board) do { (void)(board); } while(0)
    #define DEBUG(board) do { } while(0)
#endif

#define TODO(message) do { fprintf(stderr, "%s:%d: TODO: %s\n", __FILE__, __LINE__, message); exit(1); } while(0)
#define UNREACHABLE(message) do { fprintf(stderr, "%s:%d: UNREACHABLE: %s\n", __FILE__, __LINE__, message); exit(1); } while(0)

typedef enum {
    M_UP    = 0,
    M_DOWN  = 1,
    M_LEFT  = 2,
    M_RIGHT = 3,
    __MOVE_TYPES_COUNT,
} MoveType;

typedef struct {
    MoveType *items;
    size_t count;
    size_t capacity;
} MoveTypeDa;

/* 64-bit Random Number Generator */
#define INIT_PRNG_STATE 0xDEADBEEF69421337ULL
typedef struct {
    uint64_t a;
} XorShift64State;

uint64_t xorshift64(XorShift64State *state);

/* Hash value (Zobrist Hashing) */
typedef struct {
    uint64_t l, r;
} HashValue;

HashValue **zobrist_hash_table_init(XorShift64State *prng_state, size_t positions, size_t tiles);
void zobrist_hash_table_destroy(HashValue **hv, size_t positions, size_t tiles);
static inline void xor_hash(HashValue *current, HashValue update);
HashValue zobrist_hash(const HashValue **zobrist_table, uint16_t *tiles);
HashValue zobrist_hash_update(const HashValue **zobrist_table, HashValue hv, uint16_t *tiles, size_t src, size_t dst);

/* Hash Map (See stb_ds.h) */
typedef struct {
    HashValue key;
    int value;
} HashTable;

int hash_table_get(HashTable **ht, HashValue hv);
void hash_table_put(HashTable **ht, HashValue hv, int value);

/* Board */
typedef struct {
    HashValue hash_value;
    MoveType move_made; /* The move do we made to get current state */
    int parent_idx; /* -1 if it has no parent (root state) */
} BoardMetadata;

typedef struct {
    BoardMetadata metadata;
    uint16_t *tiles; /* Whole board (suggest using arena allocator to allocate memory) */
    size_t blank_idx; /* Blank tile position */
} Board;

/* Memory pool for visited/explored states */
typedef struct {
    BoardMetadata *items;
    size_t count;
    size_t capacity;
} ExploredState;

void explored_states_insert(ExploredState *es, BoardMetadata new_item);
void explored_states_clear(ExploredState *es);

/* Bucket Queue */
typedef struct {
    Board board;
    int g_cost; /* Moves we made until this state */
} SearchNode;

SearchNode search_node_new(Board board, int g_cost);

typedef struct {
    SearchNode *items;
    size_t count;
    size_t capacity;
} Bucket;

void bucket_clear(Bucket *bucket);

#define MAX_F_VALUE (1<<16) // TODO: Enough?
typedef struct {
    Bucket buckets[MAX_F_VALUE];
    size_t current_min_f;
    size_t total_count;
} BucketQueue;

void bucket_queue_insert(BucketQueue *bq, SearchNode sn, size_t f_cost);
SearchNode bucket_queue_pop(BucketQueue *bq);
void bucket_queue_clear(BucketQueue *bq);
bool bucket_queue_is_empty(BucketQueue *bq);
void bucket_queue_destory(BucketQueue *bq);

/* Solver Context */
typedef struct {
    Arena arena;
    ExploredState es;
    HashTable *ht;
    BucketQueue bq;
    bool *lock_map;

    XorShift64State prng_state;
    HashValue **zobrist_table; /* zobrist_table[position][tile] */
    size_t zobrist_table_positions;
    size_t zobrist_table_tiles;

    MoveTypeDa solution_path;

    uint16_t cur_target_tile;
    size_t cur_target_idx;
    size_t cur_dst_idx;
    Board cur_board;
} SolverContext;

void solver_context_init(SolverContext *ctx);
void solver_context_free(SolverContext *ctx);

/* Global Variables */
size_t board_size;
size_t board_size_square;
// size_t board_width;
// size_t board_height;
Board goal_board;
MoveTypeDa temp_stack = {0};
// const size_t ARENA_CAPACITY = 1024 * 1024 * 512 * 1LLU; /* 512MB */
const size_t ARENA_CAPACITY = (1<<30);
const MoveType SPECIAL_MOVE_ROW_CW[]  = { M_UP, M_UP, M_RIGHT, M_DOWN, M_LEFT, M_DOWN, M_RIGHT, M_UP, M_UP, M_LEFT, M_DOWN }; /* Special moves for row, clockwise */
const MoveType SPECIAL_MOVE_ROW_CCW[] = { M_UP, M_UP, M_LEFT, M_DOWN, M_RIGHT, M_DOWN, M_LEFT, M_UP, M_UP, M_RIGHT, M_DOWN }; /* Special moves for row, counterclockwise */
const MoveType SPECIAL_MOVE_COL_CW[]  = { M_LEFT, M_LEFT, M_UP, M_RIGHT, M_DOWN, M_RIGHT, M_UP, M_LEFT, M_LEFT, M_DOWN, M_RIGHT }; /* Special moves for col, clockwise */
const MoveType SPECIAL_MOVE_COL_CCW[] = { M_LEFT, M_LEFT, M_DOWN, M_RIGHT, M_UP, M_RIGHT, M_DOWN, M_LEFT, M_LEFT, M_UP, M_RIGHT }; /* Special moves for col, counterclockwise */

/* Function Prototypes */
void *alloc_new_tiles(SolverContext *ctx);
void get_board_size(FILE *stream);
Board get_root_state(SolverContext *ctx, FILE *stream);
size_t find_tile_index_in_board(Board board, size_t target);
size_t find_tile_index_in_goal(size_t target);
size_t manhattan_distance_of_two_tiles(size_t src, size_t dst);
size_t heuristic_of_row(Board board, size_t target_row, size_t start_col);
size_t heuristic_of_col(Board board, size_t target_col, size_t start_row);
size_t heuristic_function(Board board, size_t target, size_t dst);
size_t f_cost_function(SearchNode sn, size_t target_idx, size_t dst_idx);
bool is_locked(bool *lock_map, size_t idx);
void lock_tile(bool *lock_map, size_t idx);
void unlock_tile(bool *lock_map, size_t idx);
int is_move_valid(Board board, MoveType move); /* -1 if move is not valid, else return dst idx */

void solve_puzzle(SolverContext *ctx);
void solve_top_left_tile(SolverContext *ctx, size_t top_row_of_remaining_board);
void solve_top_row(SolverContext *ctx, size_t top_row_of_remaining_board);
void solve_left_column(SolverContext *ctx, size_t top_row_of_remaining_board);
void solve_tile(SolverContext *ctx, bool lock_it);
void weighted_a_star(SolverContext *ctx);
void expand_node(SolverContext *ctx, SearchNode sn);
void move_tile_and_update_board_info(SolverContext *ctx, Board *board, MoveType move);
void output_solution(FILE *stream, SolverContext *ctx);
void extract_path(SolverContext *ctx, HashValue target_hash);
void apply_and_record_move(SolverContext *ctx, MoveType move);

void execute_special_moves(SolverContext *ctx, const MoveType *moves, size_t count);
void special_move_for_row_clockwise(SolverContext *ctx);
void special_move_for_row_counterclockwise(SolverContext *ctx);
void special_move_for_col_clockwise(SolverContext *ctx);
void special_move_for_col_counterclockwise(SolverContext *ctx);

/* Function implementations */
uint64_t xorshift64(XorShift64State *state)
{
	uint64_t x = state->a;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	return state->a = x;
}

HashValue **zobrist_hash_table_init(XorShift64State *prng_state, size_t positions, size_t tiles)
{
    HashValue **t = malloc(sizeof(HashValue) * positions);
    for (size_t i = 0; i < positions; i++) {
        t[i] = malloc(sizeof(HashValue) * tiles);
        for (size_t j = 0; j < tiles; j++) {
            t[i][j].l = xorshift64(prng_state);
            t[i][j].r = xorshift64(prng_state);
        }
    }
    return t;
}

void zobrist_hash_table_destroy(HashValue **hv, size_t positions, size_t tiles)
{
    (void)tiles; /* Unused variable */
    for (size_t i = 0; i < positions; i++)
        free(hv[i]);
    free(hv);
}

static inline void xor_hash(HashValue *current, HashValue update)
{
    current->l ^= update.l;
    current->r ^= update.r;
}

HashValue zobrist_hash(const HashValue **zobrist_table, uint16_t *tiles)
{
    HashValue hv = {0};
    for (size_t i = 0; i < board_size_square; i++) {
        xor_hash(&hv, zobrist_table[i][tiles[i]]);
    }
    return hv;
}

HashValue zobrist_hash_update(const HashValue **zobrist_table, HashValue hv, uint16_t *tiles, size_t src, size_t dst)
{
    xor_hash(&hv, zobrist_table[src][tiles[src]]);
    xor_hash(&hv, zobrist_table[dst][tiles[dst]]);
    xor_hash(&hv, zobrist_table[src][tiles[dst]]);
    xor_hash(&hv, zobrist_table[dst][tiles[src]]);
    return hv;
}

int hash_table_get(HashTable **ht, HashValue hv)
{
    return hmgeti(*ht, hv);
}

void hash_table_put(HashTable **ht, HashValue hv, int value)
{
    hmput(*ht, hv, value);
}

void explored_states_insert(ExploredState *es, BoardMetadata new_item)
{
    da_append(es, new_item);
}

void explored_states_clear(ExploredState *es)
{
    es->count = 0;
}

SearchNode search_node_new(Board board, int g_cost)
{
    return (SearchNode){
        .board  = board,
        .g_cost = g_cost,
    };
}

void bucket_clear(Bucket *bucket)
{
    bucket->count = 0;
}

void bucket_queue_insert(BucketQueue *bq, SearchNode sn, size_t f_cost)
{
    ASSERT(f_cost < MAX_F_VALUE);

    da_append(&bq->buckets[f_cost], sn);
    if (f_cost < bq->current_min_f) {
        bq->current_min_f = f_cost;
    }
    bq->total_count++;
}

SearchNode bucket_queue_pop(BucketQueue *bq)
{
    ASSERT(bq->current_min_f < MAX_F_VALUE);

    for (; bq->current_min_f < MAX_F_VALUE; bq->current_min_f++) {
        if (bq->buckets[bq->current_min_f].count > 0)
            return da_pop(&bq->buckets[bq->current_min_f]);
    }
    UNREACHABLE("bucket_queue_pop, bucket queue is empty");
}

void bucket_queue_clear(BucketQueue *bq)
{
    for (int i = bq->current_min_f; i < MAX_F_VALUE; i++) {
        bq->total_count -= bq->buckets[i].count;
        bq->buckets[i].count = 0;

        if (bq->total_count == 0)
            break;
    }
    bq->current_min_f = MAX_F_VALUE;
}

bool bucket_queue_is_empty(BucketQueue *bq)
{
    return bq->total_count == 0;
}

void bucket_queue_destory(BucketQueue *bq)
{
    for (int i = 0; i < MAX_F_VALUE; i++) {
        if (bq->buckets[i].items != NULL) {
            da_free(bq->buckets[i]);
        }
    }
}

void solver_context_init(SolverContext *ctx)
{
    ctx->arena = arena_new(ARENA_CAPACITY);
    ctx->es = (ExploredState){0};
    ctx->ht = NULL;
    ctx->bq = (BucketQueue){0};
    ctx->lock_map = NULL;

    ctx->prng_state = (XorShift64State){0};
    ctx->zobrist_table = NULL;
    ctx->zobrist_table_positions = 0;
    ctx->zobrist_table_tiles = 0;

    ctx->solution_path = (MoveTypeDa){0};

    explored_states_clear(&ctx->es);
    bucket_queue_clear(&ctx->bq);
    arena_reset(&ctx->arena);
}

void solver_context_free(SolverContext *ctx)
{
    arena_destroy(ctx->arena);
    da_free(ctx->es);
    hmfree(ctx->ht);
    bucket_queue_destory(&ctx->bq);
    free(ctx->lock_map);

    da_free(ctx->solution_path);

    zobrist_hash_table_destroy(ctx->zobrist_table, ctx->zobrist_table_positions, ctx->zobrist_table_tiles);
}

void *alloc_new_tiles(SolverContext *ctx)
{
    return arena_alloc(&ctx->arena, sizeof(uint16_t) * board_size_square);
}

void get_board_size(FILE *stream)
{
    /* Read board size */
#ifdef _WIN32
    fscanf(stream, "%d", &board_size);
#else
    fscanf(stream, "%zu", &board_size);
#endif
    board_size_square = board_size * board_size;
}

Board get_root_state(SolverContext *ctx, FILE *stream)
{
    /* Allocate space for board and read initial state */
    uint16_t *tiles = alloc_new_tiles(ctx);
    uint16_t blank_idx;
    for (size_t i = 0; i < board_size_square; i++) {
        fscanf(stream, "%hu", &tiles[i]);
        if (tiles[i] == 0)
            blank_idx = i;
    }

    Board board = {
        .metadata = {
            .hash_value = zobrist_hash((const HashValue **)ctx->zobrist_table, tiles),
            .move_made  = __MOVE_TYPES_COUNT,
            .parent_idx = -1,
        },
        .tiles     = tiles,
        .blank_idx = blank_idx,
    };

    return board;
}

size_t find_tile_index_in_board(Board board, size_t target)
{
    /* Find target tile position (index) in board */
    for (size_t i = 0; i < board_size_square; i++)
        if (board.tiles[i] == target)
            return i;
    UNREACHABLE("find_tile_index_in_board");
}

size_t find_tile_index_in_goal(size_t target)
{
    return find_tile_index_in_board(goal_board, target);
}

size_t manhattan_distance_of_two_tiles(size_t src, size_t dst)
{
    // size_t src_r = src / board_height;
    // size_t src_c = src % board_width;
    // size_t dst_r = dst / board_height;
    // size_t dst_c = dst % board_width;
    // return abs(dst_r - src_r) + abs(dst_c - src_c);
    return abs((int)(dst / board_size) - (int)(src / board_size))
         + abs((int)(dst % board_size) - (int)(src % board_size));
}

size_t heuristic_of_row(Board board, size_t target_row, size_t start_col)
{
    int value = 0;
    int pre = target_row * board_size;
    for (size_t i = start_col; i < board_size; i++) {
        value += heuristic_function(board, find_tile_index_in_board(board, goal_board.tiles[pre + i]), pre + i);
    }
    return value;
}

size_t heuristic_of_col(Board board, size_t target_col, size_t start_row)
{
    int value = 0;
    for (size_t i = start_row; i < board_size; i++) {
        int pre = i * board_size;
        value += heuristic_function(board, find_tile_index_in_board(board, goal_board.tiles[pre + target_col]), pre + target_col);
    }
    return value;
}

size_t heuristic_function(Board board, size_t target_idx, size_t dst_idx)
{
    const int H_WEIGHT = 10;

    /* h = MD(target tile pos, destination) * weight + MD(blank tile pos, target tile pos) */
    int md_target_to_dst = manhattan_distance_of_two_tiles(target_idx, dst_idx);
    int md_blank_to_target = manhattan_distance_of_two_tiles(board.blank_idx, target_idx);
    int blank_penalty = (md_blank_to_target > 1) ? (md_blank_to_target - 1) : 0;

    return (md_target_to_dst * H_WEIGHT) + blank_penalty;
}

size_t f_cost_function(SearchNode sn, size_t target_idx, size_t dst_idx)
{
    return heuristic_function(sn.board, target_idx, dst_idx) + sn.g_cost;
}

void solve_puzzle(SolverContext *ctx)
{
    size_t current_size = board_size;

    while (current_size > 2) {
        size_t x = board_size - current_size; /* Top row of remaining board */
        size_t y = x + 1;

        /* Solve top-left corner tile first */
        solve_top_left_tile(ctx, x);
        // LOG_BOARD(ctx->cur_board);

        size_t top_row_heuristic = heuristic_of_row(ctx->cur_board, x, y);
        size_t left_col_heuristic = heuristic_of_col(ctx->cur_board, x, y);
        // LOGF("%ld, %ld", top_row_heuristic, left_col_heuristic);

        /* Then solve row and column */
        if (top_row_heuristic < left_col_heuristic) {
            solve_top_row(ctx, x);
            solve_left_column(ctx, x);
        } else {
            solve_left_column(ctx, x);
            solve_top_row(ctx, x);
        }
        current_size--;
    }

    solve_top_left_tile(ctx, board_size - current_size);
    // LOG_BOARD(ctx->cur_board);

    if (ctx->cur_board.blank_idx == board_size_square - 2)
        apply_and_record_move(ctx, M_RIGHT);
    else
        apply_and_record_move(ctx, M_DOWN);
}

void solve_top_left_tile(SolverContext *ctx, size_t top_row_of_remaining_board)
{
    ctx->cur_dst_idx = top_row_of_remaining_board * board_size + top_row_of_remaining_board;
    ctx->cur_target_idx = find_tile_index_in_board(ctx->cur_board, goal_board.tiles[ctx->cur_dst_idx]);
    ctx->cur_target_tile = ctx->cur_board.tiles[ctx->cur_target_idx];

    // LOGF("ctx->cur_dst_idx: %ld", ctx->cur_dst_idx);
    // LOGF("ctx->cur_target_idx: %ld", ctx->cur_target_idx);
    // LOGF("ctx->cur_target_tile: %hu", ctx->cur_target_tile);

    if (ctx->cur_target_idx == ctx->cur_dst_idx) {
        lock_tile(ctx->lock_map, ctx->cur_dst_idx);
        return;
    }

    solve_tile(ctx, true);
}

// TODO: Handle all the situations
void solve_top_row(SolverContext *ctx, size_t top_row_of_remaining_board)
{
    // FIXME: Separate the Slot structure and logic
    size_t x = top_row_of_remaining_board;
    size_t y = top_row_of_remaining_board + 1;

    const size_t slot_cap = board_size - y;
    size_t slot_count = 0;
    struct Slot {
        size_t idx;
        size_t h_cost;
    } slots[slot_cap];

    memset(slots, 0, sizeof(struct Slot) * slot_cap);

    for (; y < board_size; y++) {
        size_t dst_idx = x * board_size + y;
        size_t target_idx = find_tile_index_in_board(ctx->cur_board, goal_board.tiles[dst_idx]);
        size_t h = heuristic_function(ctx->cur_board, target_idx, dst_idx);

        size_t i = slot_count;
        slots[i].idx = dst_idx;
        slots[i].h_cost = h;
        // struct Slot tmp = slots[i];
        // for (; i > 0; i--) {
        //     if (h < slots[i-1].h_cost) {
        //         slots[i] = slots[i-1];
        //     } else {
        //         break;
        //     }
        // }
        // slots[i] = tmp;
        slot_count++;
    }

    for (size_t i = 0; i < slot_cap; i++) {
        ctx->cur_dst_idx = slots[i].idx;
        ctx->cur_target_idx = find_tile_index_in_board(ctx->cur_board, goal_board.tiles[ctx->cur_dst_idx]);
        ctx->cur_target_tile = ctx->cur_board.tiles[ctx->cur_target_idx];

        if (ctx->cur_target_idx == ctx->cur_dst_idx) {
            lock_tile(ctx->lock_map, ctx->cur_dst_idx);
            continue;
        }

        /* Special cases
         *
         * 1. dst neighbors are locked
         *   row = [locked, dst, locked, ...]
         * 2. dst left neighbor is locked and dst is on the board edge
         *   row = [locked, ..., locked, dst]
         * 3. dst neighbors are locked and target's neighbors are also locked
         *   row = [locked, dst, locked, target, locked]
         * 4. dst neighbors are locked and target's left neighbor is locked and target is on the board edge
         *   row = [locked, dst, locked, locked, target]
         * 5. blank tile in the same row, and target is beside the blank tile
         *
         * Idea:
         * 1. If target in the target row, move target out
         * 2. (TODO)
         */
        if (is_locked(ctx->lock_map, ctx->cur_dst_idx - 1) && (ctx->cur_dst_idx % board_size == board_size - 1 || is_locked(ctx->lock_map, ctx->cur_dst_idx + 1))) {
            if (ctx->cur_board.blank_idx == ctx->cur_dst_idx && ctx->cur_board.tiles[ctx->cur_dst_idx + board_size] == ctx->cur_target_tile) {
                solve_tile(ctx, true);
                // LOG_BOARD(ctx->cur_board);
            } else {
                ctx->cur_dst_idx += board_size;
                solve_tile(ctx, true);
                if (ctx->cur_dst_idx % board_size == board_size - 1)
                    special_move_for_row_counterclockwise(ctx);
                else
                    special_move_for_row_clockwise(ctx);
                lock_tile(ctx->lock_map, ctx->cur_dst_idx - board_size);
                // LOG_BOARD(ctx->cur_board);
            }
        } else {
            solve_tile(ctx, true);
            // LOG_BOARD(ctx->cur_board);
        }
    }
}

void solve_left_column(SolverContext *ctx, size_t top_row_of_remaining_board)
{
    size_t x = top_row_of_remaining_board;
    size_t y = top_row_of_remaining_board + 1;

    const size_t slot_cap = board_size - y;
    size_t slot_count = 0;
    struct Slot {
        size_t idx;
        size_t h_cost;
    } slots[slot_cap];

    memset(slots, 0, sizeof(struct Slot) * slot_cap);

    for (; y < board_size; y++) {
        size_t dst_idx = y * board_size + x;
        size_t target_idx = find_tile_index_in_board(ctx->cur_board, goal_board.tiles[dst_idx]);
        size_t h = heuristic_function(ctx->cur_board, target_idx, dst_idx);

        size_t i = slot_count;
        slots[i].idx = dst_idx;
        slots[i].h_cost = h;
        // struct Slot tmp = slots[i];
        // for (; i > 0; i--) {
        //     if (h < slots[i-1].h_cost) {
        //         slots[i] = slots[i-1];
        //     } else {
        //         break;
        //     }
        // }
        // slots[i] = tmp;
        slot_count++;
    }

    for (size_t i = 0; i < slot_cap; i++) {
        ctx->cur_dst_idx = slots[i].idx;
        ctx->cur_target_idx = find_tile_index_in_board(ctx->cur_board, goal_board.tiles[ctx->cur_dst_idx]);
        ctx->cur_target_tile = ctx->cur_board.tiles[ctx->cur_target_idx];

        if (ctx->cur_target_idx == ctx->cur_dst_idx) {
            lock_tile(ctx->lock_map, ctx->cur_dst_idx);
            continue;
        }

        /* Check special case */
        if (is_locked(ctx->lock_map, ctx->cur_dst_idx - board_size) && (ctx->cur_dst_idx / board_size == board_size - 1 || is_locked(ctx->lock_map, ctx->cur_dst_idx + board_size))) {
            if (ctx->cur_board.blank_idx == ctx->cur_dst_idx && ctx->cur_board.tiles[ctx->cur_dst_idx + 1] == ctx->cur_target_tile) {
                solve_tile(ctx, true);
            } else {
                ctx->cur_dst_idx += 1;
                solve_tile(ctx, true);
                if (ctx->cur_dst_idx / board_size == board_size - 1)
                    special_move_for_col_clockwise(ctx);
                else
                    special_move_for_col_counterclockwise(ctx);
                lock_tile(ctx->lock_map, ctx->cur_dst_idx - 1);
            }
        } else {
            solve_tile(ctx, true);
        }
    }
}

void solve_tile(SolverContext *ctx, bool lock_it)
{
    // LOGF("%ld, %hu", ctx->cur_dst_idx, ctx->cur_target_tile);
    weighted_a_star(ctx);
    if (lock_it)
        lock_tile(ctx->lock_map, ctx->cur_dst_idx);
}

void weighted_a_star(SolverContext *ctx)
{
    /* Clear hash table, queue, explored states array and arena */
    hmfree(ctx->ht);
    bucket_queue_clear(&ctx->bq);
    explored_states_clear(&ctx->es);
    arena_reset(&ctx->arena); /* Since the bucket queue is cleared, the arena can be reset for reuse */

    /* Push start state to queue */
    Board tmp_board = {
        .metadata  = {
            .hash_value = ctx->cur_board.metadata.hash_value,
            .move_made = ctx->cur_board.metadata.move_made,
            .parent_idx = -1,
        },
        .tiles     = alloc_new_tiles(ctx),
        .blank_idx = ctx->cur_board.blank_idx,
    };
    memcpy(tmp_board.tiles, ctx->cur_board.tiles, sizeof(uint16_t) * board_size_square);


    SearchNode sn = search_node_new(tmp_board, 0); /* 0 g cost, to start over */
    bucket_queue_insert(&ctx->bq, sn, f_cost_function(sn, ctx->cur_target_idx, ctx->cur_dst_idx));

    while (!bucket_queue_is_empty(&ctx->bq)) {
        /* Get next search node with smallest f cost */
        sn = bucket_queue_pop(&ctx->bq);

        /* Insert to ExploredState and hash table */
        explored_states_insert(&ctx->es, sn.board.metadata);
        hash_table_put(&ctx->ht, sn.board.metadata.hash_value, ctx->es.count-1);

        /* Target reaches destination */
        if (sn.board.tiles[ctx->cur_dst_idx] == ctx->cur_target_tile) {
            extract_path(ctx, sn.board.metadata.hash_value);
            return;
        }

        /* Expand and insert to queue (this function does nothing to ctx->cur_board, so ctx->cur_board remains the same after expand) */
        expand_node(ctx, sn);
    }
}

bool is_locked(bool *lock_map, size_t idx)
{
    ASSERT(idx < board_size_square);
    return lock_map[idx];
}

void lock_tile(bool *lock_map, size_t idx)
{
    ASSERT(idx < board_size_square);
    lock_map[idx] = true;
}

void unlock_tile(bool *lock_map, size_t idx)
{
    ASSERT(idx < board_size_square);
    lock_map[idx] = false;
}

int is_move_valid(Board board, MoveType move)
{
    int src = board.blank_idx;
    int dst;

    switch (move) {
    case M_UP:
        dst = src - board_size;
        if (dst >= 0)
            return dst;
        break;
    case M_DOWN:
        dst = src + board_size;
        if (dst < (int)board_size_square)
            return dst;
        break;
    case M_LEFT:
        dst = src - 1;
        if (dst >= 0 && dst % board_size != board_size-1)
            return dst;
        break;
    case M_RIGHT:
        dst = src + 1;
        if (dst < (int)board_size_square && dst % board_size != 0)
            return dst;
        break;
    default:
        UNREACHABLE("is_move_valid default branch, invalid move");
        break;
    }
    return -1;
}

void move_tile_and_update_board_info(SolverContext *ctx, Board *board, MoveType move)
{
    ASSERT(board != NULL);

    int src = board->blank_idx;
    int dst = is_move_valid(*board, move);
    if (dst != -1) {
        uint16_t tmp = board->tiles[src];
        board->tiles[src] = board->tiles[dst];
        board->tiles[dst] = tmp;

        /* Update blank tile index */
        board->blank_idx = dst;

        /* Update metadata */
        board->metadata.parent_idx = hash_table_get(&ctx->ht, board->metadata.hash_value);
        board->metadata.hash_value = zobrist_hash_update((const HashValue **)ctx->zobrist_table, board->metadata.hash_value, board->tiles, src, dst);
        board->metadata.move_made = move;
    }
}

void expand_node(SolverContext *ctx, SearchNode sn)
{
    for (MoveType move = M_UP; move < __MOVE_TYPES_COUNT; move++) {
        int dst = is_move_valid(sn.board, move);
        if (dst == -1)
            continue;

        Board tmp_board = {
            .metadata  = sn.board.metadata,
            .tiles     = alloc_new_tiles(ctx),
            .blank_idx = sn.board.blank_idx,
        };
        memcpy(tmp_board.tiles, sn.board.tiles, sizeof(uint16_t) * board_size_square);

        if (dst != -1 && !is_locked(ctx->lock_map, dst)) {
            /* Move the tile */
            move_tile_and_update_board_info(ctx, &tmp_board, move);

            /* Insert new state if not searched before (not in hash table) */
            if (hash_table_get(&ctx->ht, tmp_board.metadata.hash_value) == -1) {
                SearchNode tmp_sn = search_node_new(tmp_board, sn.g_cost + 1);
                size_t target_idx = find_tile_index_in_board(tmp_board, ctx->cur_target_tile);
                bucket_queue_insert(&ctx->bq, tmp_sn, f_cost_function(tmp_sn, target_idx, ctx->cur_dst_idx));
            }
        }
    }
}

void output_solution(FILE *stream, SolverContext *ctx)
{
    char c;
    MoveType *move;

    da_foreach_item(move, &ctx->solution_path) {
        switch (*move) {
        case M_UP:    c = 'D'; break;
        case M_DOWN:  c = 'U'; break;
        case M_LEFT:  c = 'R'; break;
        case M_RIGHT: c = 'L'; break;
        default: UNREACHABLE("output_solution"); break;
        }
        fprintf(stream, "%c\n", c);
    }
}

void extract_path(SolverContext *ctx, HashValue target_hash)
{
    int self_idx = hash_table_get(&ctx->ht, target_hash);
    while (self_idx != -1) {
        int parent_idx = ctx->es.items[self_idx].parent_idx;
        if (parent_idx != -1) {
            MoveType move = ctx->es.items[self_idx].move_made;
            da_append(&temp_stack, move);
        }
        self_idx = parent_idx;
    }

    for (int i = temp_stack.count - 1; i >= 0; i--) {
        apply_and_record_move(ctx, temp_stack.items[i]);
    }
    /* Reset stack */
    temp_stack.count = 0;
}

void apply_and_record_move(SolverContext *ctx, MoveType move)
{
    int src = ctx->cur_board.blank_idx;
    int dst = is_move_valid(ctx->cur_board, move);
    ASSERT(dst != -1);

    uint16_t tmp = ctx->cur_board.tiles[src];
    ctx->cur_board.tiles[src] = ctx->cur_board.tiles[dst];
    ctx->cur_board.tiles[dst] = tmp;
    ctx->cur_board.blank_idx = dst;

    da_append(&ctx->solution_path, move);
}

void execute_special_moves(SolverContext *ctx, const MoveType *moves, size_t count)
{
    for (size_t i = 0; i < count; i++) {
        apply_and_record_move(ctx, moves[i]);
    }
}

void special_move_for_row_clockwise(SolverContext *ctx)
{
    /* Moves
     *
     * 1. Check blank tile is under the target
     * 2.  Move UP
     * 3.  Move UP
     * 4.  Move RIGHT
     * 5.  Move DOWN
     * 6.  Move LEFT
     * 7.  Move DOWN
     * 8.  Move RIGHT
     * 9.  Move UP
     * 10. Move UP
     * 11. Move LEFT
     * 12. Move DOWN
    */

    /* Move blank tile to desire position */
    ctx->cur_dst_idx += board_size;
    ctx->cur_target_idx = ctx->cur_board.blank_idx;
    ctx->cur_target_tile = ctx->cur_board.tiles[ctx->cur_target_idx];

    solve_tile(ctx, false);

    ctx->cur_dst_idx -= board_size;
    unlock_tile(ctx->lock_map, ctx->cur_dst_idx);

    execute_special_moves(ctx, SPECIAL_MOVE_ROW_CW, sizeof(SPECIAL_MOVE_ROW_CW) / sizeof(MoveType));
}

void special_move_for_row_counterclockwise(SolverContext *ctx)
{
    /* Moves
     *
     * 1. Check blank tile is under the target
     * 2.  Move UP
     * 3.  Move UP
     * 4.  Move LEFT
     * 5.  Move DOWN
     * 6.  Move RIGHT
     * 7.  Move DOWN
     * 8.  Move LEFT
     * 9.  Move UP
     * 10. Move UP
     * 11. Move RIGHT
     * 12. Move DOWN
    */

    /* Move blank tile to desire position */
    ctx->cur_dst_idx += board_size;
    ctx->cur_target_idx = ctx->cur_board.blank_idx;
    ctx->cur_target_tile = ctx->cur_board.tiles[ctx->cur_target_idx];

    solve_tile(ctx, false);

    ctx->cur_dst_idx -= board_size;
    unlock_tile(ctx->lock_map, ctx->cur_dst_idx);

    execute_special_moves(ctx, SPECIAL_MOVE_ROW_CCW, sizeof(SPECIAL_MOVE_ROW_CCW) / sizeof(MoveType));
}

void special_move_for_col_clockwise(SolverContext *ctx)
{
    /* Moves
     *
     * 1. Check blank tile is on the right of the target
     * 2.  Move LEFT
     * 3.  Move LEFT
     * 4.  Move UP
     * 5.  Move RIGHT
     * 6.  Move DOWN
     * 7.  Move RIGHT
     * 8.  Move UP
     * 9.  Move LEFT
     * 10. Move LEFT
     * 11. Move DOWN
     * 12. Move RIGHT
    */

    /* Move blank tile to desire position */
    ctx->cur_dst_idx += 1;
    ctx->cur_target_idx = ctx->cur_board.blank_idx;
    ctx->cur_target_tile = ctx->cur_board.tiles[ctx->cur_target_idx];

    solve_tile(ctx, false);

    ctx->cur_dst_idx -= 1;
    unlock_tile(ctx->lock_map, ctx->cur_dst_idx);

    execute_special_moves(ctx, SPECIAL_MOVE_COL_CW, sizeof(SPECIAL_MOVE_COL_CW) / sizeof(MoveType));
}

void special_move_for_col_counterclockwise(SolverContext *ctx)
{
    /* Moves
     *
     * 1. Check blank tile is on the right of the target
     * 2.  Move LEFT
     * 3.  Move LEFT
     * 4.  Move DOWN
     * 5.  Move RIGHT
     * 6.  Move UP
     * 7.  Move RIGHT
     * 8.  Move DOWN
     * 9.  Move LEFT
     * 10. Move LEFT
     * 11. Move UP
     * 12. Move RIGHT
    */

    /* Move blank tile to desire position */
    ctx->cur_dst_idx += 1;
    ctx->cur_target_idx = ctx->cur_board.blank_idx;
    ctx->cur_target_tile = ctx->cur_board.tiles[ctx->cur_target_idx];

    solve_tile(ctx, false);

    ctx->cur_dst_idx -= 1;
    unlock_tile(ctx->lock_map, ctx->cur_dst_idx);

    execute_special_moves(ctx, SPECIAL_MOVE_COL_CCW, sizeof(SPECIAL_MOVE_COL_CCW) / sizeof(MoveType));
}

void test_manattan_distance(void)
{
    board_size = 4;
    board_size_square = board_size * board_size;

    uint16_t *goal_tiles = calloc(board_size_square, sizeof(uint16_t));
    uint16_t *temp_tiles = calloc(board_size_square, sizeof(uint16_t));
    for (size_t i = 0; i < board_size_square - 1; i++) {
        goal_tiles[i] = i + 1;
        temp_tiles[i] = (i + 8) % board_size_square;
    }

    for (size_t i = 0; i < board_size_square - 1; i++) {
        printf("%d ", temp_tiles[i]);
    }
    printf("\n");

    goal_board = (Board){
        .tiles     = goal_tiles,
        .blank_idx = board_size_square - 1,
    };
    Board temp_state = (Board){
        .tiles     = temp_tiles,
        .blank_idx = board_size_square - 1,
    };

    int row = 1;
    int col = 0;
    printf("[%d, %d] = %ld\n", row, col, heuristic_of_row(temp_state, row, col));

    free(goal_tiles);
}

int main(void)
{
    SolverContext ctx = {0};
    solver_context_init(&ctx);

    const char *solution_filename = "scramble/solution/sol.txt";
    FILE *sol_fptr = fopen(solution_filename, "w");

    // const char *init_state_filename = "scramble/3x3.txt";
    const char *init_state_filename = "scramble/4x4.txt";
    // const char *init_state_filename = "scramble/5x5.txt";
    // const char *init_state_filename = "scramble/7x7.txt";
    // const char *init_state_filename = "scramble/13x13.txt";
    // const char *init_state_filename = "scramble/15x15.txt";
    // const char *init_state_filename = "scramble/17x17.txt";
    // const char *init_state_filename = "scramble/28x28.txt";
    // const char *init_state_filename = "scramble/30x30.txt";
    // const char *init_state_filename = "scramble/50x50.txt";
    FILE *fptr = fopen(init_state_filename, "r");

    /* Get board size */
    get_board_size(fptr);

    /* Initialize Zobrist table */
    ctx.prng_state.a = INIT_PRNG_STATE;
    ctx.zobrist_table = zobrist_hash_table_init(&ctx.prng_state, board_size_square, board_size_square);
    ctx.zobrist_table_positions = board_size_square;
    ctx.zobrist_table_tiles = board_size_square;

    /* Initialize lock map */
    ctx.lock_map = calloc(board_size_square, sizeof(bool));

    /* Get root state */
    Board root_board = get_root_state(&ctx, fptr);

    /* Setup goal state */
    uint16_t *goal_tiles = calloc(board_size_square, sizeof(uint16_t));
    for (size_t i = 0; i < board_size_square - 1; i++) {
        goal_tiles[i] = i + 1;
    }

    goal_board = (Board){
        .metadata = {
            .hash_value = zobrist_hash((const HashValue **)ctx.zobrist_table, goal_tiles),
            .move_made  = __MOVE_TYPES_COUNT,
            .parent_idx = -1,
        },
        .tiles     = goal_tiles,
        .blank_idx = board_size_square - 1,
    };

    printf("Initial state:\n", init_state_filename);
    for (size_t i = 0; i < board_size; i++) {
        for (size_t j = 0; j < board_size; j++) {
            printf("%3d ", root_board.tiles[i*board_size + j]);
        }
        printf("\n");
    }
    printf("\n");

    /* Start to solve puzzle */
    ctx.cur_board = root_board;
    solve_puzzle(&ctx);

    /* Output solution */
    output_solution(sol_fptr, &ctx);

    printf("Solved:\n");
    for (size_t i = 0; i < board_size; i++) {
        for (size_t j = 0; j < board_size; j++) {
            printf("%3d ", ctx.cur_board.tiles[i*board_size + j]);
        }
        printf("\n");
    }
    printf("\n");

    fclose(fptr);
    fclose(sol_fptr);
    free(goal_tiles);
    solver_context_free(&ctx);
    da_free(temp_stack);

    return 0;
}
