#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dfa.h"

#define SIZE 251

void newDFA(int);

void** enterDFA();
void formatForPrint(const char, const char, char*, const int, int*);
int countChar(const char, const char[], const int);
void removeChar(const char, char*, const int);
void moveLeft(char*, const int, const int);
int checkValidity(char*, int*, const int);

void testDFA(void**);
int findLoc(char*, char*, int*, const int);

void saveDFA(void**);
void** readDFA(char*);

void newDFA(int options) {
    void** dfa = (void**)enterDFA();
    if(dfa == 0) return;
    testDFA(dfa);

    if(options == 1) saveDFA(dfa);

    // free memory
    for(int i = 0; i < 9; i++) {
        free(dfa[i]);
    }
}

void** enterDFA() {
    // States
    printf_s("Enter the set of states Q\nIndividual states sperated by a comma, spaces will be ignored, character limit: 250\n");
    char* states = (char*)calloc(SIZE, sizeof(char));
    if(states == NULL) {
        printf_s("Memory allocation error!\n");
        return 0;
    }
    fflush(stdin);
    fgets(states, SIZE, stdin);

    removeChar(' ', states, SIZE);
    removeChar('\n', states, SIZE);
    int* stateCount = (int*)calloc(1, sizeof(int));
    if(stateCount == NULL) {
        printf_s("Memory allocation error!\n");
        return 0;
    }
    *stateCount = countChar(',', states, SIZE) + 1;
    int* stateLocs = (int*)calloc(*stateCount, sizeof(int));
    if(stateLocs == NULL) {
        printf_s("Memory allocation error!\n");
        return 0;
    }
    formatForPrint(',', '\0', states, SIZE, stateLocs);
    if(checkValidity(states, stateLocs, *stateCount) == 0) {
        printf_s("Invalid state detected! Exiting process");
        return 0;
    }

    // Input alphabet
    printf_s("\n%d state%c registered\nNow enter the input alphabet\nSame rules as for entering the states\n", *stateCount, *stateCount == 1 ? '\0' : 's');
    char* symbols = (char*)calloc(SIZE, sizeof(char));
    if(symbols == NULL) {
        printf_s("Memory allocation error!\n");
        return 0;
    }
    fflush(stdin);
    fgets(symbols, SIZE, stdin);

    removeChar(' ', symbols, SIZE);
    removeChar('\n', symbols, SIZE);
    int* symbolCount = (int*)calloc(1, sizeof(int));
    if(symbolCount == NULL) {
        printf_s("Memory allocation error!\n");
        return 0;
    }
    *symbolCount = countChar(',', symbols, SIZE) + 1;
    int* symbolLocs = (int*)calloc(*symbolCount, sizeof(int));
    if(symbolLocs == NULL) {
        printf_s("Memory allocation error!\n");
        return 0;
    }
    formatForPrint(',', '\0', symbols, SIZE, symbolLocs);
    if(checkValidity(symbols, symbolLocs, *symbolCount) == 0) {
        printf_s("Invalid symbol detected! Exiting process");
        return 0;
    }

    // Transition function
    printf_s("\n%d symbol%c registered\nNow enter the transition function d\nChoose one of the following states for each transition and enter the corresponding number\nStates: ", *symbolCount, (*symbolCount == 1) ? '\0' : 's');
    for(int i = 0; i < *stateCount; i++) {
        printf_s("%d = %s%c ", i, states + stateLocs[i], i == *stateCount - 1 ? '\0' : ',');
    }
    puts("");

    int* transitionFunc = (int*)malloc(sizeof(int) * (*stateCount * (*symbolCount)));
    if(transitionFunc == NULL) {
        printf_s("Memory allocation error!");
        return 0;
    }
    for(int i = 0; i < *stateCount; i++) {
        for(int j = 0; j < *symbolCount; j++) {
            printf_s("d(%s, %s) = ", states + stateLocs[i], symbols + symbolLocs[j]);
            fflush(stdin);
            scanf("%d", transitionFunc + ((i * (*symbolCount)) + j));
            if(*(transitionFunc + ((i * (*symbolCount)) + j)) < 0 || *(transitionFunc + ((i * (*symbolCount)) + j)) > (*stateCount) - 1) {
                printf_s("State out of range! Try again\n");
                j--;
            }
        }
    }

    // Starting state
    printf_s("\nNow enter the starting state\nChoose one of the following states and enter the corresponding number\nStates: ");
    for(int i = 0; i < *stateCount; i++) {
        printf_s("%d = %s%c ", i, states + stateLocs[i], i == (*stateCount - 1) ? '\0' : ',');
    }
    puts("");
    int* startingState = (int*)malloc(sizeof(int));
    if(startingState == NULL) {
        printf_s("Memory allocation error!");
        return 0;
    }
    
    int safety = 0;
    while(1) {
        fflush(stdin);
        scanf("%d", startingState);

        if(safety >= 15) return 0;
        if(*startingState >= 0 && *startingState < *stateCount) break;
        printf_s("State out of range! Try again\n");
        safety++;
    }
    
    // Accepting states
    printf_s("\nNow enter the set of accepting states\n");
    int* acceptingStates = (int*)malloc(sizeof(int) * (*stateCount));
    if(acceptingStates == NULL) {
        printf_s("Memory allocation error!");
        return 0;
    }

    for(int i = 0, j = 0; i < *stateCount; i++) {
        printf_s("Is \'%s\' an accepting state? [y/n] ", states + stateLocs[i]);
        fflush(stdin);
        char answer;
        scanf("%c", &answer);
        if(answer == 'y' || answer == 'Y') {
            acceptingStates[i] = 1;
            j++;
        } else if(answer == 'n' || answer == 'N') {
            acceptingStates[i] = 0;
        } else {
            printf_s("Invalid input! Try again\n");
            i--;
        }

        if(j == 0 && i == *stateCount - 1) {
            printf_s("Zero accepting states? Sure? [y/n] ");
            fflush(stdin);
            scanf("%c", &answer);
            if(answer == 'y' || answer == 'Y') {
                
            } else if(answer == 'n' || answer == 'N') {
                i = -1;
            } else {
                printf_s("Invalid input! Exiting\n");
                return 0;
            }
        }
    }

    // Storing all of the pointers
    // char*, int*, int*, char*, int*, int*, int*, int*, int*
    void** dfaConfig = (void**)calloc(9, sizeof(void*));
    if(dfaConfig == NULL) {
        printf_s("Memory allocation error!");
        return 0;
    }

    dfaConfig[0] = states;
    dfaConfig[1] = stateCount;
    dfaConfig[2] = stateLocs;
    dfaConfig[3] = symbols;
    dfaConfig[4] = symbolCount;
    dfaConfig[5] = symbolLocs;
    dfaConfig[6] = transitionFunc;
    dfaConfig[7] = startingState;
    dfaConfig[8] = acceptingStates;

    return dfaConfig;
}



void testDFA(void** dfaConfig) {
    // Load DFA config
    char* states = dfaConfig[0];
    int* stateCount = dfaConfig[1];
    int* stateLocs = dfaConfig[2];
    char* symbols = dfaConfig[3];
    int* symbolCount = dfaConfig[4];
    int* symbolLocs = dfaConfig[5];
    int* transitionFunc = dfaConfig[6];
    int* startingState = dfaConfig[7];
    int* acceptingStates = dfaConfig[8];

    // Get the length of the longest symbol
    int maxLength = 0;
    for(int i = 0; i < *symbolCount; i++) {
        maxLength = strlen(&symbols[symbolLocs[i]]) > maxLength ? strlen(&symbols[symbolLocs[i]]) : maxLength;
    }

    char inputSymbol[maxLength + 1];
    int currentState = *startingState;
    int currentSymbol;

    printf_s("\nThe automaton starts in state \'%s\'\n", &states[stateLocs[currentState]]);
    printf_s("To end testing enter a symbol not part of the valid symbols.\nEnter one(!) symbol to be the first input of your DFA: ");

    while(1) {
        fflush(stdin);
        scanf("%s", inputSymbol);

        // Check if valid symbol was entered
        if(findLoc(inputSymbol, symbols, symbolLocs, *symbolCount) == -1) {
            printf_s("Symbol not part of the set of valid symbols. Exiting.\n");
            return;
        }

        // Figure out which symbol was entered
        currentSymbol = findLoc(inputSymbol, symbols, symbolLocs, *symbolCount);

        currentState = *(transitionFunc + (currentState * *symbolCount) + currentSymbol);
        printf_s("The DFA is now in state \'%s\'\nThis is %san accepting state.\n", &states[stateLocs[currentState]], acceptingStates[currentState] ? "" : "not ");
        printf_s("\nNext symbol: ");
    }
}



void saveDFA(void** dfaConfig) {
    // Load DFA config
    char* states = dfaConfig[0];
    int* stateCount = dfaConfig[1];
    int* stateLocs = dfaConfig[2];
    char* symbols = dfaConfig[3];
    int* symbolCount = dfaConfig[4];
    int* symbolLocs = dfaConfig[5];
    int* transitionFunc = dfaConfig[6];
    int* startingState = dfaConfig[7];
    int* acceptingStates = dfaConfig[8];

    // Filename with randomly generated number
    srand(time(0));
    int random = rand() % 10000;
    char filename[18];
    sprintf(filename, "savedDFA%d.txt", random);

    FILE *fp = fopen(filename, "w");
    if(fp == NULL) {
        printf_s("\nError while saving a DFA!");
        return;
    }

    // Writing values of the config in the created file
    fprintf(fp, "states:\n");
    for(int i = 0; i < *stateCount; i++) {
        fprintf(fp, "%s\n", &states[stateLocs[i]]);
    }

    fprintf(fp, "\nstateCount:\n%d\n", *stateCount);

    fprintf(fp, "\nstateLocs:\n");
    for(int i = 0; i < *stateCount; i++) {
        fprintf(fp, "%d\n", stateLocs[i]);
    }

    fprintf(fp, "\nsymbols:\n");
    for(int i = 0; i < *symbolCount; i++) {
        fprintf(fp, "%s\n", &symbols[symbolLocs[i]]);
    }

    fprintf(fp, "\nsymbolCount:\n%d\n", *symbolCount);

    fprintf(fp, "\nsymbolLocs:\n");
    for(int i = 0; i < *symbolCount; i++) {
        fprintf(fp, "%d\n", symbolLocs[i]);
    }

    fprintf(fp, "\ntransitionFunc:\n");
    for(int i = 0; i < (*stateCount) * (*symbolCount); i++) {
        fprintf(fp, "%d\n", transitionFunc[i]);
    }

    fprintf(fp, "\nstartingState:\n%d\n", *startingState);

    fprintf(fp, "\nacceptingStates:\n");
    for(int i = 0; i < *stateCount; i++) {
        fprintf(fp, "%d\n", acceptingStates[i]);
    }

    fclose(fp);
    printf_s("\nDFA sucessfully saved in \'%s\'\n!!! Make sure to rename that file to avoid it being overwritten in the future !!!\n(Chance 1 : 10000)", filename);
}



void** readDFA(char* filename) {
    FILE * fp = fopen(filename, "r");
    if(fp == NULL) {
        printf_s("\nFile \'%s\' seems to not exist. Exiting\n");
        return 0;
    }

    int readChar;
    while((readChar = fgetc(fp)) >= 0) {
        printf_s("%c", readChar);
    }

    fclose(fp);
    return 0;
}



void formatForPrint(const char a, const char b, char* str, const int size, int* locs) {
    locs[0] = 0;
    int locCount = 1;
    for(int i = 0; i < size; i++) {
        if(str[i] == a) {
            str[i] = b;
            locs[locCount] = i + 1;
            locCount++;
        }
    }
}

int countChar(const char ch, const char str[], const int size) {
    int count = 0;
    for(int i = 0; i < size; i++) {
        if(str[i] == ch)
            count++;
    }
    return count;
}

void removeChar(const char ch, char* str, const int size) {
    for(int i = 0; i < size; i++) {
        if(str[i] == ch) {
            moveLeft(str, size, i);
            i--;
        }
    }
}

void moveLeft(char* str, const int size, const int from) {
    for(int i = from; i < size - 1; i++)
        str[i] = str[i + 1];
}

int checkValidity(char* str, int* locs, const int count) {
    for(int i = 0; i < count; i++) {
        if(str[locs[i]] == '\0') {
            return 0;
        }
    }
    return 1;
}

int findLoc(char* symbol, char* symbols, int* locs, const int count) {
    for(int i = 0; i < count; i++) {
        if(strcmp(symbol, &symbols[locs[i]]) == 0) {
            return i;
        }
    }
    return -1;
}