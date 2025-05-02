#ifndef VALIDATOR_SINGLE_H
#define VALIDATOR_SINGLE_H

#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>

bool validate_sudoku(int sudoku[9][9]);

#endif
