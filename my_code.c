#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct my_operation {
    int op1;
    int op2;
    char operation[16];
    int result;
}my_op;

void get_result(char* fileline);
my_op* extract_struct_from_string(char *string_to_be_extracted);

int main(int argc, char const *argv[]) {

    int result;
    char line[200] = {0u};
    char filename[100];
    if (argc != 2) {
        printf("Wrong argument!\n");
        return 0;
    }

    strcpy(filename, argv[1]);

    printf ("Compiling file = %s\n", filename);

    char string[200] = {0u};
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Can not open the file!\n");
        return 0;
    }

    while(fgets(line, 200,  fp) != NULL) {
        get_result(line);
    }
    return 0;
}

int perform_operation(my_op* this_line_struct) {
    int result = 0;
    char operator = 0;
    if (strcmp(this_line_struct->operation, "ADD") == 0) {
        operator = '+';
    } else if ( strcmp(this_line_struct->operation, "SUB") == 0) {
        operator = '-';
    } else if (strcmp(this_line_struct->operation, "MUL") == 0) {
        operator = '*';
    } else if (strcmp(this_line_struct->operation, "DIV") == 0) {
        operator = '/';
    }

    switch (operator)
    {
    case '+':
        result = this_line_struct->op1 + this_line_struct->op2;
        break;
    
    case '-':
        result = this_line_struct->op1 - this_line_struct->op2;
        break;

    case '*':
        result = this_line_struct->op1 * this_line_struct->op2;
        break;
    
    case '/':
        result = this_line_struct->op1 / this_line_struct->op2;
        break;
    default:
        //error
        break;
    }
    return result;
}

my_op* extract_struct_from_string(char *string_to_be_extracted) {
    int extracted_op1 = 0, extracted_op2 = 0;
    char operation[16], op1[16], op2[16];
    unsigned char operation_found = 0, op1_found = 0, op2_found = 0;
    int index_operation =0, index_op1=0, index_op2=0;
    char ch;
    if (*string_to_be_extracted == '#') {
        //printf("Comment line \n");
        return NULL;
    }
    while(ch = *string_to_be_extracted) {
        if (operation_found == 0) {
            if (ch != '(') {
                operation[index_operation++] = ch;
            } else {
                operation_found = 1;
                operation[index_operation] = 0;
                //printf("operation found = %s\n",operation);
            }
        } else if (op1_found == 0) {
            if (ch != ',') {
                op1[index_op1++] = ch;
            } else {
                op1_found = 1;
                op1[index_op1] = 0;
                //printf("op1 found = %s\n",op1);
                extracted_op1 = atoi(op1);
                //printf("op1 found int = %d\n", extracted_op1);
            } 
        } else if (op2_found == 0) {
            if (ch != ')') {
                op2[index_op2++] = ch;
            } else {
                op2_found = 1;
                op2[index_op2] = 0;
                //printf("op2 found = %s\n",op2);
                extracted_op2 = atoi(op2);
                //printf("op2 found int = %d\n", extracted_op2);
            } 
        }
        string_to_be_extracted++;
    }
    my_op* new_struct = (my_op*) malloc(sizeof(my_op));
    new_struct->op1 = extracted_op1;
    new_struct->op2 = extracted_op2;
    strcpy(new_struct->operation, operation);
    return new_struct;
}

void get_result(char* fileline) {
    my_op* this_line_param = extract_struct_from_string(fileline);
    if (this_line_param != NULL) {
        printf("%d\n", perform_operation(this_line_param));
    }
}