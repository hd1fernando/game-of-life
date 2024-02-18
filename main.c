#include <stdio.h>
#include <stdlib.h>

int** matrix_2d_create_empty(int row_size, int col_size){
    int** matrix = (int**)calloc(row_size, sizeof(int*));
    if(matrix == NULL){
        printf("can't allocate rows of the matrix\n");
        exit(0);
    }

    for(int i = 0; i < row_size; ++i){
        matrix[i] = (int*)calloc(col_size,sizeof(int));
        if(matrix[i] == NULL){
            printf("can't allocate cols for the matrix\n");
            exit(0);
        }
    }
    
    return matrix;
}

void matrix_2d_free(int** matrix, int row_size){
    for(int i = 0; i < row_size; ++i){
        free(matrix[i]);
    }
    free(matrix);
}

void matrix_2d_print(int** matrix, int row_size, int col_size){
    for(int i = 0; i < row_size; ++i){
        for(int j = 0; j < col_size; ++j){
            printf("%d",matrix[i][j]);
        }
        printf("\n");
    }
}

int main(void){
    int** matrix = matrix_2d_create_empty(10, 10);
    matrix_2d_print(matrix, 10, 10);
    
    matrix_2d_free(matrix, 10);
    return 0;
}
