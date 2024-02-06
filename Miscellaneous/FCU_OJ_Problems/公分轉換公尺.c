#include <stdio.h>

int main(void){
    /*printf("#2 ??¬å??è½??????¬å°º\n");
    printf("Enter a number: ");*/

    int cm_x;
    float m_x;

    scanf("%d", &cm_x);
    m_x=cm_x/100.0;
                        
    printf("%.2f m", m_x);

    return 0;
}