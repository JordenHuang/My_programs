#include <stdio.h>
#include <stdlib.h>

struct Stack{
    int *array;
    int top;
    int capacity;
    char name;
};

struct Stack* createStack(int capacity, char name);

void push(struct Stack* Stack, int item);
int pop(struct Stack* Stack);
void movenums(int numitems, struct Stack* source, struct Stack* dest, struct Stack* aux);


int main() {
    int numitems;
    int i;

    // ��J�L�l�`��
    printf("Enter the number of items:");
    scanf("%d", &numitems);

    // �إߤT�ӬW�l A B C
    struct Stack* source = createStack(numitems, 'A');
    struct Stack* dest = createStack(numitems, 'C');
    struct Stack* aux = createStack(numitems, 'B');

    // ��L�l��iA�W,�Ѥj���p
    for (i=numitems; i >= 1; i--){
        push(source, i);
    }

    // �}�l�e����C��
    movenums(numitems, source, dest, aux);

    return 0;
}

struct Stack* createStack(int capacity, char name) {
    /* stack�̭��s�F:
        capacity: �N�O�L�l���ƶq
        top: ����top����m
        array: �ΰ}�C�ӷ�@stack�Ӧs��L�l����m���
        name: stack���W�r(�s��������)
    */
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (int*)malloc(capacity * sizeof(int));
    stack->name = name;
    return stack;
}
void push(struct Stack* Stack, int item) {
    // �����ò���top����m
    if (Stack->top < Stack->capacity - 1) {
        Stack->array[++Stack->top] = item;
    }
}
int pop(struct Stack* Stack) {
    // �����ò���top����m, ��^�ǸӦ�m�s��item (�N�Odisk���s��)
    if (Stack->top >= 0) {
        return Stack->array[Stack->top--];
    }
    return -1;
}


void movenums(int numitems, struct Stack* source, struct Stack* dest, struct Stack* aux){
    // ���j���e����Ѫk
    // recursion �� movenums function
    // �p�G�L�l�ƶq�O1, recursion �� base case
    // p.s aux�O���~��
    if (numitems == 1) {
        int item = pop(source);
        push(dest, item);
        printf("Move disk 1 from stack %c to stack %c\n", source->name, dest->name);
        return;
    }

    // ��W�����L�l����
    movenums(numitems - 1, source, aux, dest);  // keep swaping the dest and aux, good
    
    // ���ʦۤv
    int item = pop(source);
    push(dest, item);
    printf("Move disk %d from stack %c to stack %c\n", item /*numitems�]�i�H*/, source->name, dest->name);
    
    // ��W�����L�l���^��
    movenums(numitems - 1, aux, dest, source);
}