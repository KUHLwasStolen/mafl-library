#ifndef DFA_H
#define DFA_H

void newDFA(int);
// returned pointers: char* states, int* stateCount, int* stateLocs, char* symbols, int* symbolCount, int* symbolLocs, int* transitionFunc, int* startingState, int* acceptingStates
void** enterDFA();
void testDFA(void**);

#endif