#include <stdio.h>
#include "src/stack_gen.h"

STACK_CREATION(int, int);
STACK_CREATION(float, float);
STACK_CREATION(unsigned int, unsigned_int);
STACK_CREATION(unsigned long long, unsigned_long_long);

int main(void)
{
    Stack_int *topi = NULL;
    Stack_int *curi;
    stack_push_int(&topi, 1);
    stack_push_int(&topi, 2);
    printf("empty: %d\n", stack_empty_int(topi));
    stack_push_int(&topi, 3);
    stack_foreach(curi, topi) {
        printf("%d ", curi->item);
    } printf("\n");
    stack_pop_int(&topi);
    stack_foreach(curi, topi) {
        printf("%d ", curi->item);
    } printf("\n");
    stack_pop_int(&topi);
    stack_foreach(curi, topi) {
        printf("%d ", curi->item);
    } printf("\n");
    printf("empty: %d\n", stack_empty_int(topi));
    stack_pop_int(&topi);
    stack_foreach(curi, topi) {
        printf("%d ", curi->item);
    } printf("\n");
    printf("empty: %d\n", stack_empty_int(topi));


    Stack_float *topf = NULL;
    Stack_float *curf;
    stack_push_float(&topf, 1.f);
    stack_push_float(&topf, 2.f);
    printf("empty: %d\n", stack_empty_float(topf));
    stack_push_float(&topf, 3.f);
    stack_foreach(curf, topf) {
        printf("%f ", curf->item);
    } printf("\n");
    stack_pop_float(&topf);
    stack_foreach(curf, topf) {
        printf("%f ", curf->item);
    } printf("\n");
    stack_pop_float(&topf);
    stack_foreach(curf, topf) {
        printf("%f ", curf->item);
    } printf("\n");
    printf("empty: %d\n", stack_empty_float(topf));
    stack_pop_float(&topf);
    stack_foreach(curf, topf) {
        printf("%f ", curf->item);
    } printf("\n");
    printf("empty: %d\n", stack_empty_float(topf));


    return 0;
}
