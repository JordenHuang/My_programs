#include <stdio.h>
#include <math.h>
#include <windows.h>
//#include <string.h>
//#include <conio.h>

char symbols[4400];  // 100*44
float check_front_symbols[4400]; // check which symbol is in the front
char background_ascii_code=' ';

int cube_width=40;  // ��������
int width=100, height=44;  // �e��

float rotate_speed_for_x=0.05;  // ¶X�b���઺�t��
float rotate_speed_for_y=0.05;  // ¶Y�b���઺�t��
float rotate_speed_for_z=0.01;  // ¶Z�b���઺�t��

// int distance_from_edge=100;  // ����t���Z��


float a=0, b=0, c=0;  // ����(����)
float x, y, z;  // coordinate
int position;  // position in the matrice


//  THE ROTATION MATRIX FROM WIKIPEDIA
// float cal_x(int x, int y, int z){
//     return x*cos(c)*cos(b) + y*sin(c)*cos(b) - z*sin(b);
// }
//
// float cal_y(int x, int y, int z){
//     return x*(-sin(c)*cos(a) + cos(c)*sin(b)*sin(a)) + y*(cos(c)*cos(a) + sin(c)*sin(b)*sin(a)) + z*cos(b)*sin(a);
// }
//
// float cal_z(int x, int y, int z){
//     return x*(sin(c)*sin(a) + cos(c)*sin(b)*cos(a)) + y*(-cos(c)*sin(a) + sin(c)*sin(b)*cos(a)) + z*cos(b)*cos(a);
// }


// from �u�N�ҥ�  �� X�b, Y�b, Z�b �@���઺����x�}
float calculate_X(int x, int y, int z){
    return x*cos(b)*cos(c) - y*cos(b)*sin(c) + z*sin(b);
}
float calculate_Y(int x, int y, int z){
    return x*(sin(a)*sin(b)*cos(c) + cos(a)*sin(c)) + y*(cos(a)*cos(c)- sin(a)*sin(b)*sin(c)) - z*sin(a)*cos(b);
}
float calculate_Z(int x, int y, int z){
    return (sin(a)*sin(c) - cos(a)*sin(b)*cos(c))*x + (cos(a)*sin(b)*sin(c) + sin(a)*cos(c))*y + cos(a)*cos(b)*z;
}

void calculate_cube_surface(float cube_x, float cube_y, float cube_z, char symbol){  // �p�⧹���I�����x,y,z���y��, �ഫ���b �}�C[position] ���禡
    x = (int)round(calculate_X(cube_x, cube_y, cube_z));
    y = round(calculate_Y(cube_x, cube_y, cube_z));
    z = calculate_Z(cube_x, cube_y, cube_z);

    //  printf("X: %f, Y: %f, Z: %f \n", x, y, z);

    y = (int)(y/2);
    position = (22-y)*100 + 50-(-x);


    if(check_front_symbols[position]==0){
        check_front_symbols[position] = z;
        symbols[position] = symbol;
    }
    else if(check_front_symbols[position] > z){
        check_front_symbols[position] = z;
        symbols[position] = symbol;
    }
    
}

int main(){
    float cube_x, cube_y;
    int k = 0;
    printf("\x1b[2J");
    
    while(1){
        memset(symbols, background_ascii_code, width*height);
        memset(check_front_symbols, 0, width*height*4);
        for(cube_y = -cube_width/2; cube_y <= cube_width/2; cube_y += 0.5){
            for(cube_x = -cube_width/2; cube_x <= cube_width/2; cube_x += 0.5){
                calculate_cube_surface(cube_x, cube_y, -cube_width/2, '+');//
                calculate_cube_surface(cube_x, cube_y, cube_width/2, ';');
                calculate_cube_surface(-cube_width/2, cube_y, cube_x, '$');//
                calculate_cube_surface(cube_width/2, cube_y, cube_x, '@');
                calculate_cube_surface(cube_x, -cube_width/2, cube_y, '^');//
                calculate_cube_surface(cube_x, cube_width/2, cube_y, '~');
            }
        }
        
        
        printf("\x1b[H");
        
        for(int i=0; i <= width*height; i++){  // �t�d��X�򴫦檺�{��
            if(i%width > 0){
                putchar(symbols[i]);
            }
            else{
                putchar(10);
            }
        }
        
        
        a += rotate_speed_for_x;  // rotation speed
        b += rotate_speed_for_y;
        c += rotate_speed_for_z;
        Sleep(5);
        // k++;

        if(c==3.14){
            break;
        }

    }

}