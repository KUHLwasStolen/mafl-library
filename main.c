#include <stdio.h>
#include <string.h>

#include "dfa.h"
#include "maflInfo.h"

int main(int argc, char* args[]) {
    if(argc == 2) {
        if(strcmp(args[1], "-h") == 0 || strcmp(args[1], "--help") == 0) {
            listUsage();
        } else if(strcmp(args[1], "-?") == 0) {
            listShort();
        } else if(strcmp(args[1], "--dfa") == 0 || strcmp(args[1], "-dfa") == 0) {
            newDFA(0);
        }

    } else if(argc == 3) {
        if(strcmp(args[1], "--dfa") == 0 || strcmp(args[1], "-dfa") == 0) {
            if(strcmp(args[2], "--save") == 0 || strcmp(args[2], "-s") == 0) {
                newDFA(1);
            }
        }

    } else {
        printLogo();
        printf_s("For information on how to use mafl type \'mafl.exe --help\'");
        return 0;
    }
    
    return 0;
}