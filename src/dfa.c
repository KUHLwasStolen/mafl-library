#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "dfa.h"
#include "generalDefs.h"

#define SIZE 251

void newDFA(char*, char*, int, int);

void** enterDFA();
void formatForPrint(const char, const char, char*, const int, int*);
int countChar(const char, const char[], const int);
void removeChar(const char, char*, const int);
void moveLeft(char*, const int, const int);
int checkValidity(char*, int*, const int);

void testDFA(void**);
int findLoc(char*, char*, int*, const int);

void saveDFA(void**, char*);

void** readDFA(char*);
int getSection(char*);

void** minimizeDFA(void**);
void** editDFA(void**);

void newDFA(char* save, char* read, int minimize, int edit) {
    void** dfa = NULL;
    if(read == 0) {
        dfa = (void**)enterDFA();
    } else {
        dfa = (void**)readDFA(read);
    }
    if(dfa == 0) return;

    if(minimize != 0) dfa = minimizeDFA(dfa);
    if(edit != 0) dfa = editDFA(dfa);

    testDFA(dfa);

    if(save != 0) saveDFA(dfa, save);

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
        printf_s("Invalid state detected! Exiting.");
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
        printf_s("Invalid symbol detected! Exiting.");
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
        char answer;
        fflush(stdin);
        scanf(" %c", &answer);
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
            scanf(" %c", &answer);
            if(answer == 'y' || answer == 'Y') {
                
            } else if(answer == 'n' || answer == 'N') {
                i = -1;
            } else {
                printf_s("Invalid input! Exiting.\n");
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

    printf_s("\nThe available symbol%s: ", *symbolCount == 1 ? " is" : "s are");
    for(int i = 0; i < *symbolCount; i++) {
        printf_s("\'%s\'%c ", &symbols[symbolLocs[i]], i == (*symbolCount) - 1 ? '\0' : ',');
    }
    printf_s("\n\nThe automaton starts in state \'%s\'\n", &states[stateLocs[currentState]]);
    printf_s("This is %san accepting state.\n", acceptingStates[currentState] ? "" : "not ");
    printf_s("\nTo end testing enter a symbol not part of the valid symbols.\nEnter one(!) symbol to be the first input of your DFA: ");

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

        currentState = *(transitionFunc + (currentState * (*symbolCount)) + currentSymbol);
        printf_s("\nThe DFA is now in state \'%s\'\nThis is %san accepting state.\n", &states[stateLocs[currentState]], acceptingStates[currentState] ? "" : "not ");
        printf_s("\nNext symbol: ");
    }
}



void saveDFA(void** dfaConfig, char* name) {
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

    char* filename = NULL;
    if(strcmp(name, "") == 0) {
        // Filename with randomly generated number
        srand(time(0));
        int random = rand() % 10000;
        filename = calloc(17, sizeof(char));
        if(filename == NULL) {
            printf_s("Memory allocation error!\n");
            return;
        }
        sprintf(filename, "savedDFA%d.txt", random);
    } else {
        // User-specified filename
        filename = calloc(strlen(name) + 5, sizeof(char));
        if(filename == NULL) {
            printf_s("Memory allocation error!\n");
            return;
        }
        sprintf(filename, "%s.txt", name);
    }

    FILE *fp = fopen(filename, "w");
    if(fp == NULL) {
        printf_s("\nError while saving a DFA!");
        return;
    }

    // Writing values of the config in the created file, different sections seperated by '#'
    fprintf(fp, "#\nstates:\n");
    for(int i = 0; i < *stateCount; i++) {
        fprintf(fp, "%s\n", &states[stateLocs[i]]);
    }

    fprintf(fp, "#\nstateCount:\n%d\n", *stateCount);

    fprintf(fp, "#\nstateLocs:\n");
    for(int i = 0; i < *stateCount; i++) {
        fprintf(fp, "%d\n", stateLocs[i]);
    }

    fprintf(fp, "#\nsymbols:\n");
    for(int i = 0; i < *symbolCount; i++) {
        fprintf(fp, "%s\n", &symbols[symbolLocs[i]]);
    }

    fprintf(fp, "#\nsymbolCount:\n%d\n", *symbolCount);

    fprintf(fp, "#\nsymbolLocs:\n");
    for(int i = 0; i < *symbolCount; i++) {
        fprintf(fp, "%d\n", symbolLocs[i]);
    }

    fprintf(fp, "#\ntransitionFunc:\n");
    for(int i = 0; i < (*stateCount) * (*symbolCount); i++) {
        fprintf(fp, "%d\n", transitionFunc[i]);
    }

    fprintf(fp, "#\nstartingState:\n%d\n", *startingState);

    fprintf(fp, "#\nacceptingStates:\n");
    for(int i = 0; i < *stateCount; i++) {
        fprintf(fp, "%d\n", acceptingStates[i]);
    }

    // End of config marked by ##
    // !!The '\n' is very important here or else errors will occur during reading!!
    fprintf(fp, "##\n");

    fclose(fp);
    printf_s("\nDFA sucessfully saved in \'%s\'\n", filename);
    if(strcmp(name, "") == 0) {
        printf_s("!!! Make sure to rename that file to avoid it being overwritten in the future !!!\n(Chance 1 : 10000)\n");
    }
}



void** readDFA(char* filename) {
    // Try to read file
    FILE * fp = fopen(filename, "r");
    if(fp == NULL) {
        printf_s("\nFile \'%s\' seems to not exist. Exiting.\n", filename);
        return 0;
    }

    char *states, *symbols;
    int *stateCount, *stateLocs, *symbolCount, *symbolLocs, *transitionFunc, *startingState, *acceptingStates;
    void **dfaConfig = NULL;
    states = symbols = NULL;
    stateCount = stateLocs = symbolCount = symbolCount = transitionFunc = startingState = acceptingStates = NULL;

    // Allocate memory for pointers where we know the size already 
    // (states, stateCount, symbols, symbolCount, startingState, dfaConfig)
    states = calloc(SIZE, sizeof(char));
    stateCount = calloc(1, sizeof(int));
    symbols = calloc(SIZE, sizeof(char));
    symbolCount = calloc(1, sizeof(int));
    startingState = calloc(1, sizeof(int));
    dfaConfig = calloc(9, sizeof(void*));

    // Check correct allocation for all at once
    if(states == 0 || stateCount == 0 || symbols == 0 || symbolCount == 0 || startingState == 0 || dfaConfig == 0) {
        printf_s("\nMemory allocation error! Exiting!\n");
        fclose(fp);
        return 0;
    }

    char readLine[100];
    int readChar;
    char charBlock[2];
    // Sections: -3 = ivalid section read, -2 = starting value, -1 = none (ready for next), 
    //           0 = states, 1 = stateCount, 2 = stateLocs, 3 = symbols, 4 = symbolCount,
    //           5 = symbolLocs, 6 = transitionFunc, 7 = startingState, 8 = acceptingStates
    int currentSection = -2;
    // Variable for writing data to pointers without losing position between loops
    int pointerPos = 0;

    // There are 9 sections to read from the file, i will keep track of the count
    // i is a different variable than currentState to better detect faulty files
    for(int i = 0; i < 10; ) {
        readLine[0] = '\0';
        readChar = fgetc(fp);

        // this while loop reads one whole line (ommits the \n)
        while(readChar >= 0 && readChar != '\n') {
            sprintf(charBlock, "%c", readChar);
            strcat(readLine, charBlock);
            readChar = fgetc(fp);
        }
        if(readChar < 0) {
            printf_s("\nEnd of file reached before all arguments were read! Exiting!\n");
            fclose(fp);
            return 0;
        }
        
        // section dependent code
        switch(currentSection) {
            case -2:
                break;
            case -1: 
                currentSection = getSection(readLine);
                break;
            case 0:
                if(strcmp(readLine, "#") == 0) break;
                for(int j = 0; j < strlen(readLine); j++) {
                    states[pointerPos++] = readLine[j];
                }
                states[pointerPos++] = '\0';
                break;
            case 1:
                if(strcmp(readLine, "#") == 0) break;
                *stateCount = (int)strtol(readLine, NULL, 10);
                stateLocs = calloc(*stateCount, sizeof(int));
                acceptingStates = calloc(*stateCount, sizeof(int));
                if(stateLocs == NULL || acceptingStates == NULL) {
                    printf_s("\nMemory allocation error! Exiting!\n");
                    fclose(fp);
                    return 0;
                }
                break;
            case 2:
                if(strcmp(readLine, "#") == 0) break;
                stateLocs[pointerPos++] = (int)strtol(readLine, NULL, 10);
                break;
            case 3:
                if(strcmp(readLine, "#") == 0) break;
                for(int j = 0; j < strlen(readLine); j++) {
                    symbols[pointerPos++] = readLine[j];
                }
                symbols[pointerPos++] = '\0';
                break;
            case 4:
                if(strcmp(readLine, "#") == 0) break;
                *symbolCount = (int)strtol(readLine, NULL, 10);
                symbolLocs = calloc(*symbolCount, sizeof(int));
                transitionFunc = calloc((*symbolCount) * (*stateCount), sizeof(int));
                if(symbolLocs == NULL || transitionFunc == NULL) {
                    printf_s("\nMemory allocation error! Exiting!\n");
                    fclose(fp);
                    return 0;
                }
                break;
            case 5:
                if(strcmp(readLine, "#") == 0) break;
                symbolLocs[pointerPos++] = (int)strtol(readLine, NULL, 10);
                break;
            case 6:
                if(strcmp(readLine, "#") == 0) break;
                transitionFunc[pointerPos++] = (int)strtol(readLine, NULL, 10);
                break;
            case 7:
                if(strcmp(readLine, "#") == 0) break;
                *startingState = (int)strtol(readLine, NULL, 10);
                break;
            case 8:
                if(strcmp(readLine, "#") == 0) break;
                acceptingStates[pointerPos++] = (int)strtol(readLine, NULL, 10);
                break;
            default:
                printf_s("\nSomething went wrong while reading a config!\n");
                fclose(fp);
                return 0;
        }

        // '#' is used as a speration symbol for different sections
        if(strcmp(readLine, "#") == 0) {
            // increase section count (!not the same as current section!)
            i++;
            // ready to read next section
            currentSection = -1;
            // reset pointer position
            pointerPos = 0;
        } else if(i == 9 && strcmp(readLine, "##") == 0) {
            // If the program reaches exactly this state we can be pretty certain that everything went right :)
            printf_s("DFA configuration read succesfully!\nYou can now interact with the automaton.\n\n");
            i++;
        }
    }
    

    fclose(fp);
    
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



// This method will utilize the so called table construction method
void** minimizeDFA(void** dfaConfig) {
    char* states = dfaConfig[0];
    int* stateCount = dfaConfig[1];
    int* stateLocs = dfaConfig[2];
    char* symbols = dfaConfig[3];
    int* symbolCount = dfaConfig[4];
    int* symbolLocs = dfaConfig[5];
    int* transitionFunc = dfaConfig[6];
    int* startingState = dfaConfig[7];
    int* acceptingStates = dfaConfig[8];

    
    if((*stateCount) <= 1) {
        // If there is only one state (or less???) there is nothing to minimize
        return dfaConfig;
    }

    // set up a 'matrix' with all combinations of states
    // we will mark (set to 1) states here that we know are different from each other
    int differenceMatrix[*stateCount][*stateCount ];
    for(int i = 0; i < (*stateCount); i++) {
        for(int j = 0; j < (*stateCount); j++) {
            differenceMatrix[i][j] = 0;
        }
    }

    /* Visualization of the matrix if stateCount is 4 and states: q0, q1, q2, q3
    ----|----|----|----|----|
     q0 |    |    |    |    |
    ----|----|----|----|----|
     q1 |    |    |    |    |
    ----|----|----|----|----|
     q2 |    |    |    |    |
    ----|----|----|----|----|
     q3 |    |    |    |    |
    ----|----|----|----|----|
        | q0 | q1 | q2 | q3 |

    We can ignore all state combinations of a state with itself, e.g. (q1, q1)
    Also combinations such as (q1, q3) and (q3, q1) are the same
    --> So in real-life we would construct a matrix more like this:
    ----|----|
     q1 |    |
    ----|----|----|
     q2 |    |    |
    ----|----|----|----|
     q3 |    |    |    |
    ----|----|----|----|
        | q0 | q1 | q2 |

    But to keep the implementation of the algorithm simple, we create a matrix as shown above
    */

    // now we mark all combinations where one state is accepting and the other is not
    // we definitely know that they are not the same
    for(int i = 0; i < (*stateCount); i++) {
        for(int j = 0; j < (*stateCount); j++) {
            if(acceptingStates[i] == 1 && acceptingStates[j] != 1) {
                differenceMatrix[i][j] = 1;
            }
        }
    }

    /* now we need helper tables for the remaining checks
    Basic method:
    We find out where each state goes with one of the symbols (we repeat this for all symbols)
    Let's say q1 goes to q2 and q2 goes to q3
    Then we check if (q2, q3) is marked in our main matrix/table
    If yes: we mark (q1, q2) in the main table
    If no: do nothing

    As said we repeat this for all symbols
    And we also repeat this whole procedure until the main table doesn't change anymore
    */    

    int markChanges, iGoesTo, jGoesTo;
    do {
        markChanges = 0;

        for(int c = 0; c < (*symbolCount); c++) {
            for(int i = 0; i < (*stateCount); i++) {
                iGoesTo = transitionFunc[(i * (*symbolCount)) + c];

                for(int j = 0; j < (*stateCount); j++) {
                    jGoesTo = transitionFunc[(j * (*symbolCount)) + c];

                    if(differenceMatrix[iGoesTo][jGoesTo] == 1 && differenceMatrix[i][j] == 0) {
                        markChanges++;
                        differenceMatrix[i][j] = 1;
                    }
                }
            }
        }
        
    } while(markChanges != 0);

    // Now we have identified all states that are different
    // That also means that we have identified all the states that are NOT different
    // We can merge such pairs (that are not marked in the matrix)

    int usedStateCount = 0;
    int newStateCount = 0;

    int usedStates[*stateCount];
    for(int i = 0; i < (*stateCount); i++) {
        usedStates[i] = 0;
    }

    int filteredDiffMatr[*stateCount][*stateCount];
    for(int i = 0; i < (*stateCount); i++) {
        for(int j = 0; j < (*stateCount); j++) {
            filteredDiffMatr[i][j] = 0;
        }
    }

    // this creates a simple way to merge the states
    // simplified: flips all entries in the diffMatr and removes repeated pairs
    for(int i = 0; i < (*stateCount); i++) {
        for(int j = 0; j < (*stateCount); j++) {
            if(usedStateCount == (*stateCount) || usedStates[i] == 1) break;

            if(differenceMatrix[i][j] == 0) {
                usedStateCount++;
                filteredDiffMatr[i][j] = 1;

                if(i == j) {
                    newStateCount++;
                } else {
                    usedStates[j] = 1;
                }
            }
        }
        if(usedStateCount == (*stateCount)) break;
    }

    // let's allocate memory for the new, minimal DFA
    char *minStates = NULL;
    int *minStateCount, *minTransitionFunc, *minStartingState, *minAcceptingStates, *minStateLocs;
    minStateCount = minTransitionFunc = minStateLocs = minStartingState = minAcceptingStates = NULL;
    void **minDFA = NULL;
    // symbols, symbolCount, symbolLocs stay the same
    
    minStates = (char*)calloc(SIZE, sizeof(char));
    minStateCount = (int*)calloc(1, sizeof(int));
    minStateLocs = (int*)calloc(newStateCount, sizeof(int));
    minStartingState = (int*)calloc(1, sizeof(int));
    minAcceptingStates = (int*)calloc(newStateCount, sizeof(int));
    minTransitionFunc = (int*)calloc(newStateCount * (*symbolCount), sizeof(int));
    minDFA = (void**)calloc(9, sizeof(void*));

    if(minStates == 0 || minStateCount == 0 || minStateLocs == 0 || minStartingState == 0 || minAcceptingStates == 0 || minTransitionFunc == 0 || minDFA == 0) {
        printf_s("\nMemory allocation error!\n");
        return 0;
    }

    *minStateCount = newStateCount;

    // now we create the new state strings, the starting states, accepting states
    // and a lookup table to determine the new tranistion function 
    // (basically a mapping where we enter an old state number get the new equivaltent)
    usedStateCount = 0; // reusing this variable for counting string pos
    int currentState = 0;
    int modified = 0;
    int lookupTable[*stateCount];
    for(int i = 0; i < (*stateCount); i++) {
        // initializing to something that will not be there after the assignment (if everything worked)
        lookupTable[i] = -1;
    }

    for(int i = 0; i < (*stateCount); i++) {
        for(int j = 0; j < (*stateCount); j++) {
            if(filteredDiffMatr[i][j] == 1) {
                // strings
                usedStateCount += strlen(&states[stateLocs[j]]);
                strcat(minStates, &states[stateLocs[j]]);
                modified = 1;

                // starting state
                if(j == *startingState) {
                    *minStartingState = currentState;
                }

                // accepting states
                if(acceptingStates[j] == 1) {
                    minAcceptingStates[currentState] = 1;
                }

                // lookup table
                lookupTable[j] = currentState;
            }
        }

        if(modified == 1) {
            minStates[usedStateCount] = ',';
            currentState++;
            usedStateCount++;
        }
        modified = 0;
    }

    formatForPrint(',', '\0', minStates, SIZE, minStateLocs);

    // now we create the new transition function using the lookup table
    for(int i = 0; i < (*stateCount); i++) {
        for(int j = 0; j < (*symbolCount); j++) {
            minTransitionFunc[(lookupTable[i] * (*symbolCount)) + j] = lookupTable[transitionFunc[(i * (*symbolCount)) + j]];
        }
    }

    // show the user the results
    printf_s("\nGot rid of %d states (%d --> %d)\n", (*stateCount) - (*minStateCount), *stateCount, *minStateCount);
    printf_s("The new states are:\n");
    for(int i = 0; i < (*minStateCount); i++) {
        printf_s("\'%s\' %s\n", &minStates[minStateLocs[i]], minAcceptingStates[i] == 1 ? ((*minStartingState) == i ? "(accepting, starting)" : "(accepting)") : ((*minStartingState) == i ? "(starting)" : ""));
    }
    printf_s("\nThe new transition function:\n");
    for(int i = 0; i < (*minStateCount); i++) {
        for(int j = 0; j < (*symbolCount); j++) {
            printf_s("d(%s, %s) = %s\n", &minStates[minStateLocs[i]], &symbols[symbolLocs[j]], &minStates[minStateLocs[minTransitionFunc[(i * (*symbolCount)) + j]]]);
        }
    }

    printf_s("\nThe automaton you will be testing is the minimal one.\n");

    // free the memory from the old automaton that's not needed anymore
    free(states);
    free(stateCount);
    free(stateLocs);
    free(acceptingStates);
    free(startingState);
    free(transitionFunc);

    // assign new, minimized DFA
    minDFA[0] = minStates;
    minDFA[1] = minStateCount;
    minDFA[2] = minStateLocs;
    minDFA[3] = symbols;
    minDFA[4] = symbolCount;
    minDFA[5] = symbolLocs;
    minDFA[6] = minTransitionFunc;
    minDFA[7] = minStartingState;
    minDFA[8] = minAcceptingStates;    

    return minDFA;
}



void** editDFA(void** dfaConfig) {
    char* states = dfaConfig[0];
    int* stateCount = dfaConfig[1];
    int* stateLocs = dfaConfig[2];
    char* symbols = dfaConfig[3];
    int* symbolCount = dfaConfig[4];
    int* symbolLocs = dfaConfig[5];
    int* transitionFunc = dfaConfig[6];
    int* startingState = dfaConfig[7];
    int* acceptingStates = dfaConfig[8];

    char firstLayer = 0, secondLayer = 0;

    char loop = 1;
    while(loop) {
        switch(firstLayer) {
            // first layer options
            case 0:
                printf_s("\nEdit DFA:\n");
                printf_s("[0] States\n\tedit names, add/remove state,\n\tedit starting state, edit accepting states\n");
                printf_s("[1] Symbols\n\tchange names, add/remove symbols\n");
                printf_s("[2] Transition function\n\tchange one/all transition(s)\n");
                printf_s("[q] Quit\n");
                printf_s("Type the symbol in brackets to choose the corresponding action\n");
                
                fflush(stdin);
                scanf(" %c", &firstLayer);
                puts("");
                break;

            // edit states
            case '0':
                switch(secondLayer) {
                    // edit state options
                    case 0:
                        printf_s("Edit states:\n[0] edit names\n[1] add state\n[2] remove state\n");
                        printf_s("[3] edit starting state\n[4] edit accepting states\n[q] back\n");
                        printf_s("Type the symbol in brackets to choose the corresponding action\n");

                        fflush(stdin);
                        scanf(" %c", &secondLayer);
                        puts("");
                        break;

                    // edit state names
                    case '0':
                        printf_s("These are all available states:\n");
                        for(int i = 0; i < *stateCount; i++) {
                            printf_s("[%d] \'%s\'%s", i, &states[stateLocs[i]], i + 1 == *stateCount ? "\n" : ", ");
                        }
                        printf_s("Enter the number of the state of which you want to edit the name.\n");

                        int editedState = 0;
                        fflush(stdin);
                        scanf(" %d", &editedState);
                        if(editedState < 0 || editedState + 1 > *stateCount) {
                            printf_s("\nInvalid input!\n");
                            secondLayer = 0;
                            break;
                        }

                        int maxLength = SIZE - strlen(&states[stateLocs[*stateCount]]) - 1 + strlen(&states[stateLocs[editedState]]);
                        printf_s("Enter a new name for \'%s\'\n(max. length: %d)\n", &states[stateLocs[editedState]], maxLength - 1);
                        char newName[maxLength];
                        // TRY: move newName to heap, this might be allowed instead of a variable length array
                        newName[0] = 0;
                        fflush(stdin);
                        fgets(newName, maxLength, stdin);
                        removeChar('\n', newName, 21);
                        removeChar(' ', newName, 21);
                        int oldLength = strlen(&states[stateLocs[editedState]]);
                        int sizeDiff = strlen(newName) - oldLength;
                        printf_s("%d\n", sizeDiff);

                        secondLayer = 0;
                        break;

                    // add state
                    case '1':
                        printf_s("Currently under construction\n");
                        secondLayer = 0;
                        break;

                    // remove state
                    case '2':
                        printf_s("Currently under construction\n");
                        secondLayer = 0;
                        break;

                    // edit starting state
                    case '3':
                        printf_s("Enter the corresponding number of the state that should be the new starting state\n");
                        for(int i = 0; i < *stateCount; i++) {
                            printf_s("%d = \'%s\'%s%s", i, &states[stateLocs[i]], i == *startingState ? " (current)" : "", i + 1 == *stateCount ? "\n" : ", ");
                        }

                        int newStartingState;
                        fflush(stdin);
                        scanf("%d", &newStartingState);

                        if(newStartingState < 0 || newStartingState > *stateCount - 1) {
                            printf_s("\nInvalid input!\n");
                            break;
                        }
                        *startingState = newStartingState;
                        printf_s("\nThe starting state now is \'%s\'\n", &states[stateLocs[*startingState]]);

                        secondLayer = 0;
                        break;

                    // edit accepting states
                    case '4':
                        printf_s("Currently: ");
                        for(int i = 0; i < *stateCount; i++) {
                            printf_s("\'%s\'%s%s", &states[stateLocs[i]], acceptingStates[i] == 1 ? " (acc)" : "", i + 1 == *stateCount ? "\n" : ", ");
                        }
                        printf_s("The following configuration will overwrite the current one.\n\n");

                        for(int i = 0, j = 0; i < *stateCount; i++) {
                            printf_s("Is \'%s\' an accepting state? [y/n] ", states + stateLocs[i]);
                            char answer;
                            fflush(stdin);
                            scanf(" %c", &answer);
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
                                scanf(" %c", &answer);
                                if(answer == 'y' || answer == 'Y') {
                                    
                                } else if(answer == 'n' || answer == 'N') {
                                    i = -1;
                                } else {
                                    printf_s("Invalid input! Defaulted to \'y\'\n");
                                }
                            }
                        }

                        secondLayer = 0;
                        break;

                    // back
                    case 'q':
                    case 'Q':
                        secondLayer = 0;
                        firstLayer = 0;
                        break;

                    default:
                        printf_s("Invalid input!\n");
                        secondLayer = 0;
                        break;
                }
                break;

            // edit symbols
            case '1':
                printf_s("Currently under construction\n");
                firstLayer = 0;
                break;

            // edit transition function
            case '2':
                switch(secondLayer) {
                    // edit transition function options
                    case 0:
                        printf_s("Edit transition function:\n");
                        printf_s("[0] edit a single transition\n[1] edit the whole function\n");
                        printf_s("[q] back\n");
                        printf_s("Type the symbol in brackets to choose the corresponding action\n");

                        fflush(stdin);
                        scanf(" %c", &secondLayer);
                        puts("");
                        break;
                    
                    // edit one transition
                    case '0':
                        printf_s("Enter the number of the of the corresponding transition which you want to edit\n");
                        for(int i = 0; i < *stateCount; i++) {
                            for(int j = 0; j < *symbolCount; j++) {
                                printf_s("[%d] d(%s, %s) = %s\t", (i * (*symbolCount)) + j, &states[stateLocs[i]], &symbols[symbolLocs[j]], &states[stateLocs[transitionFunc[(i * (*symbolCount)) + j]]]);
                                if(((i * (*symbolCount)) + j) % 2 == 1) puts("");
                            }
                        }
                        puts("");

                        int editedTransition;
                        fflush(stdin);
                        scanf("%d", &editedTransition);
                        if(editedTransition < 0 || editedTransition + 1 > (*stateCount) * (*symbolCount)) {
                            printf_s("Invalid input!\n");
                            secondLayer = 0;
                            break;
                        }

                        printf_s("Choose one of the following states as the new transition destination and enter the corresponding number\nStates: ");
                        for(int i = 0; i < *stateCount; i++) {
                            printf_s("%d = %s%c ", i, states + stateLocs[i], i == *stateCount - 1 ? '\0' : ',');
                        }
                        puts("");

                        int newDestination;
                        printf_s("d(%s, %s) = ", states + stateLocs[editedTransition / (*symbolCount)], symbols + symbolLocs[editedTransition % (*symbolCount)]);
                        fflush(stdin);
                        scanf("%d", &newDestination);
                        if(newDestination < 0 || newDestination + 1 > (*stateCount)) {
                            printf_s("Invalid input!\n");
                            secondLayer = 0;
                            break;
                        }

                        transitionFunc[editedTransition] = newDestination;
                        secondLayer = 0;
                        break;
                    
                    // edit the whole function
                    case '1':
                        printf_s("Choose one of the following states for each transition and enter the corresponding number\nStates: ");
                        for(int i = 0; i < *stateCount; i++) {
                            printf_s("%d = %s%c ", i, states + stateLocs[i], i == *stateCount - 1 ? '\0' : ',');
                        }
                        puts("");

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
                        puts("");

                        secondLayer = 0;
                        break;

                    // back
                    case 'q':
                    case 'Q':
                        secondLayer = 0;
                        firstLayer = 0;
                        break;

                    default:
                        printf_s("Invalid Input!\n");
                        secondLayer = 0;
                        break;
                }
                break;

            case 'q':
            case 'Q':
                loop = 0;
                break;

            default:
                printf_s("Invalid input!\n");
                firstLayer = 0;
                break;
        }
    }

    return dfaConfig;
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

// moves the characters in a string one character to the left
// deletes to the left side
void moveLeft(char* str, const int size, const int from) {
    if(from + 1 > size || from < 0) return;
    for(int i = from; i < size - 1; i++)
        str[i] = str[i + 1];
}

// moves the characters in a string one character to the right
// deletes to the right side
void moveRight(char* str, const int size, const int from) {
    if(from + 1 > size || from < 0) return;
    for(int i = size - 1; i > from; i--)
        str[i] = str[i - 1];
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

int getSection(char* readLine) {
    if(strcmp(readLine, "states:") == 0) {
        return 0;
    } else if(strcmp(readLine, "stateCount:") == 0) {
        return 1;
    } else if(strcmp(readLine, "stateLocs:") == 0) {
        return 2;
    } else if(strcmp(readLine, "symbols:") == 0) {
        return 3;
    } else if(strcmp(readLine, "symbolCount:") == 0) {
        return 4;
    } else if(strcmp(readLine, "symbolLocs:") == 0) {
        return 5;
    } else if(strcmp(readLine, "transitionFunc:") == 0) {
        return 6;
    } else if(strcmp(readLine, "startingState:") == 0) {
        return 7;
    } else if(strcmp(readLine, "acceptingStates:") == 0) {
        return 8;
    }

    return -3;
}