enum move_type{up=-2, down, left, right};
enum Bool_type{False, True};

typedef enum Bool_type boool;
typedef enum move_type moves;



struct list_node{
    moves move;
    struct list_node *next_node;
};

typedef struct list_node list;


struct stack_node{
    moves move;
    struct stack_node *next_node;
};

typedef struct stack_node stack;