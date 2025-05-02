#include "validator_pthread.h"
struct args{
    int sudoku[9][9];
    int i;
};

void* check_row(void *arg) {
    struct args t = *(struct args*)arg;
    bool seen[10] = { false };
    for (int i = 0; i < 9; i++) {
        int num = t.sudoku[t.i][i];
        if (num < 1 || num > 9 || seen[num]) {validate_thread[t.i] = false;}
        seen[num] = true;
    }
}

void* check_col(void *arg) {
    struct args t = *(struct args*)arg;
    bool seen[10] = { false };
    for (int i = 0; i < 9; i++) {
        int num = t.sudoku[i][t.i];
        if (num < 1 || num > 9 || seen[num]) {validate_thread[t.i + 9] = false;}
        seen[num] = true;
    }
}

bool check_grid(int sudoku[9][9], int startRow, int startCol) {
    bool seen[10] = { false };
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int num = sudoku[startRow + i][startCol + j];
            if (num < 1 || num > 9 || seen[num]) return false;
            seen[num] = true;
        }
    }
    return true;
}
void* grid_thread(void* arg) {
    struct args t = *(struct args*)arg;
    for (int i = 0; i < 9; i += 3) {
        for (int j = 0; j < 9; j += 3) {
            if (!check_grid(t.sudoku, i, j)) {
                validate_thread[18] = false; 
            }
        }
    }
}
bool validate_sudoku(int sudoku[9][9]) {
    struct args t;
    pthread_t threads [19];
    for(int i = 0;i < 9;i++){
        for(int j = 0;j < 9;j++)
            t.sudoku[i][j] = sudoku[i][j];
    }
    for (int i = 0; i < 9; i++) {
        t.i = i;
        pthread_create(&threads[i],NULL,check_row,&t);
        pthread_create(&threads[9+i],NULL,check_col,&t);
    }
    pthread_create(&threads[18],NULL,grid_thread,&t);
    for (int i = 0; i < 19; i++) {
        pthread_join(threads[i], NULL);
    }
    for(int i = 0;i < 19;i++) {
        if(validate_thread[i] == false)
            return false;
    }
    return true;
}
