/*
    KIARA YOST

    COP 3502C

    Programming Assignment #3: Strands (Linked Lists)

    10/8/2025

    PURPOSE: 
    In the original NY Times Strands game, users are given a 2D grid of letters, and are asked to
    partition the grid into "strands", where each strand is a path formed by starting at one letter and
    moving in one of the eight directions to get to the next letter, continuing the process until each
    letter in the grid is part of precisely one word.

    The program builds the structure in the manner designated, then handles the following query types in sequence:

    1. Given a position in the grid, prints out the word that grid position is part of in the current Strands configuration.

    2. Given a position in the grid, reverse the word that grid position is part of.

    3. Given a position in the grid that is an ending position, as well as an adjacent position that is a
        starting position for a different word, concatenate those two words together
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct dllnode {
char ch;
struct dllnode* prev;
struct dllnode* next;
} dllnode;

#define NUMDIR 8 //CHANGED TO DEFINE. SETUP STATED IN INSTRUCTIONS CAUSED ERRORS

dllnode*** readGrid(int numRows, int numCols);
void readDirections(dllnode*** grid, int numRows, int numCols);
void printWord(dllnode*** grid);
void reverseWord(dllnode*** grid, int numRows, int numCols);
void concatenateWords(dllnode*** grid);
void readQueries(dllnode*** grid, int numRows, int numCols);
void freeGrid(dllnode*** grid, int numRows, int numCols);

int main(void) {
    int numRows;
    int numCols;
    dllnode*** strandsGrid;

    scanf("%d %d", &numRows, &numCols);

    strandsGrid = readGrid(numRows, numCols);

    readDirections(strandsGrid, numRows, numCols);

    readQueries(strandsGrid, numRows, numCols);

    freeGrid(strandsGrid, numRows, numCols);

    return 0;
}

dllnode*** readGrid(int numRows, int numCols) {
    char* temp = (char*)malloc((numCols + 1) * sizeof(char));
    dllnode*** grid = (dllnode***)malloc((sizeof(dllnode**)) * numRows);

    for(int i = 0; i < numRows; i++) {
        grid[i] = (dllnode**)malloc((sizeof(dllnode*)) * numCols);
        
        scanf("%s", temp);

        for(int j = 0; j < numCols; j++) {
            grid[i][j] = (dllnode*)malloc(sizeof(dllnode));
            grid[i][j]->ch = temp[j];
        }
    }
    
    free(temp);

    return grid;
    //returns dynamically allocated pointer to 2d array of pointers to nodes
    //that contains each read char into its respective node
}

void readDirections(dllnode*** grid, int numRows, int numCols) {
    //const int NUMDIR = 8; CHANGED TO DEFINE. SETUP STATED IN INSTRUCTIONS CAUSED ERRORS
    const int NULLPTR = -1;
    const int DR[NUMDIR] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int DC[NUMDIR] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int direction;

    //Reads direction of next node
    for(int i = 0; i < numRows; i++) {
        for(int j = 0; j < numCols; j++) {
            scanf("%d", &direction);

            if(direction == NULLPTR) {
                grid[i][j]->next = NULL;
            }
            else {
                grid[i][j]->next = grid[i + DR[direction]][j + DC[direction]];
            }
        }
    }

    //Reads direction of prev node
    for(int i = 0; i < numRows; i++) {
        for(int j = 0; j < numCols; j++) {
            scanf("%d", &direction);

            if(direction == NULLPTR) {
                grid[i][j]->prev = NULL;
            }
            else {
                grid[i][j]->prev = grid[i + DR[direction]][j + DC[direction]];
            }
        }
    }
}

void printWord(dllnode*** grid) {
    int row;
    int col;
    dllnode* letter;

    scanf(" %d ", &row);
    scanf(" %d ", &col);

    letter = grid[row][col];

    //checks if queried grid square contains starting letter; 
    //if not, moves to starting letter
    while(letter->prev != NULL) {
        letter = letter->prev;
    }

    //prints each letter in the word, beginning from the starting letter
    while(letter != NULL) {
        printf("%c", letter->ch);
        letter = letter->next;
    }

    printf("\n");

}

void reverseWord(dllnode*** grid, int numRows, int numCols) {
    int row;
    int col;
    dllnode** word = (dllnode**)malloc((sizeof(dllnode*)) * (numRows * numCols));
    dllnode* temp;
    int wordLen = 0;

    scanf("%d %d", &row, &col);

    temp = grid[row][col];

    //checks if queried grid square contains starting letter; 
    //if not, moves to starting letter
    while(temp->prev != NULL) {
        temp = temp->prev;
    }

    //sets up array of pointers (word) pointing to each node in a word, in order
    for(int i = 0; temp != NULL; i++) {
        word[i] = temp;
        temp = temp->next;
        ++wordLen;
    }

    //passes through each node pointer in word array and swaps prev and next
    for(int i = 0; i < wordLen; i++) {
        if(i == 0) {
            word[i]->next = NULL;
            word[i]->prev = word[i+1];
        }
        else if(i == wordLen - 1) {
            word[i]->next = word[i-1];
            word[i]->prev = NULL;
        }
        else {
            word[i]->next = word[i-1];
            word[i]->prev = word[i+1];
        }
    }

    free(word);
}

void concatenateWords(dllnode*** grid) {
    int row1;
    int col1;
    int row2;
    int col2;

    scanf("%d %d %d %d", &row1 ,&col1, &row2, &col2);

    grid[row1][col1]->next = grid[row2][col2];

    grid[row2][col2]->prev = grid[row1][col1];

    //connects two words by changing the next of the last grid square in the first word
    //to the first grid square in the second word and connecting the prev of the first
    //grid square in the second word to the last grid square in the first word
}

void readQueries(dllnode*** grid, int numRows, int numCols) {
    int numQueries;
    int queryType;

    scanf("%d", &numQueries);

    for(int i = 0; i < numQueries; i++) {
        scanf(" %d ", &queryType);

        if(queryType == 1) {
            printWord(grid);
        }
        else if (queryType == 2) {
            reverseWord(grid, numRows, numCols);
        }
        else {
            concatenateWords(grid);
        }
    }

    //reads number of queries and each query's type 
}

void freeGrid(dllnode*** grid, int numRows, int numCols) {
    for(int i = 0; i < numRows; i++) {
        for(int j = 0; j < numCols; j++) {
            free(grid[i][j]);
        }

        free(grid[i]);
    }
    free(grid);

    //frees each grid square, grid row, and the grid itself 
}