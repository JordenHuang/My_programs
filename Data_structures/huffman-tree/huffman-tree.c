#include <stdio.h>

#include "huffman-functions.c"

#define USER_INPUT_MAX_LEN 200

/* create a user menu, with:
create weight file
read weight file
show code table

encode:
1 from file
2 from keyboard input

decode:
1 from file
2 from keyboard input
*/

void menu(){
    // printf("Huffman coding\n");
    printf("Menu:\n");
    printf("IMPORTANT 1: read 'weight.txt' first, then encode or decode\n");
    printf("IMPORTANT 2: while encoding or decoding, if a character is not exist, it will show pipe character: '|'\n");
    printf("1: Create 'weight.txt' from another file (Only read the ascii printable characters, spaces becomes '|' in the weight.txt)\n");
    printf("2: Read the 'weight.txt'\n");
    printf("3: Show code table\n");

    printf("4: Encode, from file input\n");
    printf("5: Encode, from keyboard input\n");

    printf("6: Decode, from file input\n");
    printf("7: Decode, from keyboard input\n");

    printf("Q: Exit the program\n");
    printf("Enter your choice:\n> ");
}

int main(){
    // variables
    char user_choice;
    char user_input_string[USER_INPUT_MAX_LEN];

    FILE *user_file;
    char code[USER_INPUT_MAX_LEN];

    FILE *weight_file;
    char character;
    double weight;
    char **code_table = NULL;
    int code_table_row_count = 0;
    char path[CODE_MAX_SIZE];
    int table_col_index = 0;
    
    huffman_node_heap *min_heap = NULL;
    huffman_tree *root = NULL;
    
    int i, j;


    printf("Huffman coding\n");

    while(1){
        menu();
        scanf("%c", &user_choice);
        if(user_choice == 'Q' || user_choice == 'q'){
            // clear the spaces
            if(min_heap != NULL) heap_free(min_heap);
            if(code_table != NULL) path_table_free(&code_table, code_table_row_count);
            
            printf("Exiting the program\n");
            break;
        }

        fflush(stdin);
        
        switch(user_choice){
            case '1':  // create the weight file from another file
                printf("Enter the file name that contains the text for creating weight:\n> ");
                gets(user_input_string);  //string_to_decode.txt
                user_file = fopen(user_input_string, "r");
                if(user_file == NULL){
                    printf("Can not open '%s'\n", user_input_string);
                    break;
                }

                create_weight_file(user_file, NULL);

                printf("Done\n");
            break;

            case '2':  // read weight file, create heap and the tree
                // create min heap
                if(min_heap != NULL) heap_free(min_heap);
                min_heap = create_min_heap(HEAP_SIZE);

                // open the weight file
                printf("Reading characters and weights from the 'weight.txt'...\n");
                weight_file = fopen("weight.txt", "r");
                if(weight_file == NULL){
                    printf("Can not open ''weight.txt'\n");
                    break;
                }

                code_table_row_count = 0;
                // read characters and weights
                while(!feof(weight_file)){
                    fscanf(weight_file, "%c%lf ", &character, &weight);
                    if(character == NULL_CHARACTER) character = ' ';
                    min_heap_insertion(min_heap, character, weight, NULL);
                    code_table_row_count++;
                }
                printf("Done!\n");

                // create the huffman tree
                root = create_whole_huffman_tree(min_heap);

                // create code table
                if(code_table != NULL){
                    path_table_free(&code_table, code_table_row_count);
                }
                code_table = create_path_table(code_table_row_count, CODE_MAX_SIZE);

                printf("The codes are: \n");
                find_path_recursive(root, &code_table, path, 0, &table_col_index);
                table_col_index = 0;

                fclose(weight_file);
                weight_file = NULL;
            break;


            case '3':
                printf("Code table:\n");
                print_path_table(code_table, code_table_row_count);
            break;



            case '4':case '5':  // encode from file input and keyboard input
                if(user_choice == '4'){
                    printf("Enter the file name that contains the string to encode: \n> ");
                    gets(user_input_string);  //string_to_decode.txt
                    user_file = fopen(user_input_string, "r");
                    if(user_file == NULL){
                        printf("Can not open '%s'\n", user_input_string);
                        break;
                    }
                    fscanf(user_file, "%s", code);
                    fclose(user_file);
                }
                if(user_choice == '5'){
                    printf("Enter the string to encode:\n> ");
                    fgets(code, USER_INPUT_MAX_LEN - 1, stdin);
                }
                // printf("%s", code);

                // encoding
                // strlen(code)-1 because the new line character in the code string
                printf("\nThe encoding result:\n");
                huffman_encode(code_table, code_table_row_count, code, strlen(code)-1);
            break;

            

            case '6':case '7':  // decode from file input and keyboard input
                if(user_choice == '6'){
                    printf("Enter the file name that contains the binary string to decode: \n> ");
                    gets(user_input_string);  //string_to_decode.txt
                    user_file = fopen(user_input_string, "r");
                    if(user_file == NULL){
                        printf("Can not open '%s'\n", user_input_string);
                        break;
                    }
                    fscanf(user_file, "%s", code);
                    fclose(user_file);
                }
                if(user_choice == '7'){
                    // input the binary string
                    printf("Enter the binary string to decode: \n> ");
                    fgets(code, USER_INPUT_MAX_LEN - 1, stdin);
                }
                // printf("%s", code);

                // decoding
                // strlen(code)-1 because the new line character in the code string
                printf("\nThe plain text is: \n");
                huffman_decode(root, code, strlen(code)-1);
            break;

            default:
                printf("Invalid input, enter again\n");
            break;            
        }
        printf("\n\n");
    }


    return 0;
}

/* weight example

A    0.19
B    0.09
C    0.21
D    0.12
E    0.41

*/