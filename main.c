#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

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
            if(matrix[i][j] == 1)
                printf("* ");
            else
               printf(". ");
           // printf("(%d,%d) ", i, j);
        }
        printf("\n");
    }
    printf("\n");
}

int count_neighbors(int** matrix, int row_size, int col_size,int row, int col, int value){
    int result = 0;
    
    for(int i = -1; i < 2; ++i){
        for(int j =  -1; j < 2; ++j){
            int local_row = (row + i + row_size) % row_size;
            int local_col = (col + j + col_size) % col_size;
            result += matrix[local_row][local_col];            
        }
    }

    result -= matrix[row][col];

    return result;
}

void copy_matrix(int** from, int** dest, int row, int col){
    for(int i  = 0; i < row; ++i){
        for(int j = 0; j < col; ++j){
            dest[i][j] = from[i][j];
        }
    }
}

void matrix_2d_populate(int** matrix, int row_size, int col_size){
    for(int i = 0; i < row_size;++i){
        for(int j = 0; j < col_size; ++j){
            matrix[i][j] = rand() % 2;
        }
    }
}

void clear(){
   printf("\033[H\033[J");
}

int main(void){
    clear();
    const int size = 50;
    int** matrix = matrix_2d_create_empty(size, size);
    int** temp_matrix = matrix_2d_create_empty(size, size);

    // blinker seed
 //   matrix[20][21] = 1;
  //  matrix[20][22] = 1;
   // matrix[20][23] = 1;

    // pentominoi
//   matrix[2][3] = 1;
 //   matrix[2][4] = 1;
 //   matrix[3][2] = 1;
 //   matrix[3][3] = 1;
  //  matrix[4][3] = 1;

    // glider
    matrix[2][2] = 1;
    matrix[3][3] = 1;
    matrix[3][4] = 1;
    matrix[4][2] = 1;
    matrix[4][3] = 1;

    matrix_2d_populate(matrix, size, size);

    copy_matrix(matrix, temp_matrix, size, size);
    
    int live_cell = 1;
    int dead_cell = 0;
    while(true){
        // execute rules
        for(int i = 0; i < size; ++i){
            for(int j = 0; j < size; ++j){
                int nums_of_live_neighbors = count_neighbors(matrix, size, size, i, j, live_cell);
                bool lived_cell_should_die = matrix[i][j] == live_cell && (nums_of_live_neighbors < 2 || nums_of_live_neighbors > 3);
                if(lived_cell_should_die){
                    temp_matrix[i][j] = 0;
                    continue;
                }
                
                bool died_cell_can_born = matrix[i][j] == dead_cell && nums_of_live_neighbors == 3;
                if(died_cell_can_born){
                    temp_matrix[i][j] = 1;
                    continue;
                }
            }
        }

        copy_matrix(temp_matrix, matrix, size, size);
        matrix_2d_print(matrix, size, size);
        clear();
        sleep(1);
    }
    
    matrix_2d_free(matrix, size);
    matrix_2d_free(temp_matrix, size);
    return 0;
}
