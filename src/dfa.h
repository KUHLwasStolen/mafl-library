#ifndef DFA_H
#define DFA_H

// arguments: save, read
void newDFA(char*, char*);
// returned pointers: char* states, int* stateCount, int* stateLocs, char* symbols, int* symbolCount, int* symbolLocs, int* transitionFunc, int* startingState, int* acceptingStates
void** enterDFA();
void testDFA(void**);

#endif