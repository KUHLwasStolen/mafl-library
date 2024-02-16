#include <stdio.h>
#include <string.h>

#include "dfa.h"
#include "maflInfo.h"
#include "generalDefs.h"

int main(int argc, char* args[]) {
    if(argc == 2) {
        if(strcmp(args[1], "-h") == 0 || strcmp(args[1], "--help") == 0) {
            listUsage();
        } else if(strcmp(args[1], "-?") == 0) {
            listShort();
        } else if(strcmp(args[1], "--dfa") == 0 || strcmp(args[1], "-dfa") == 0) {
            newDFA(0, 0);
        } else if(strcmp(args[1], "--version") == 0 || strcmp(args[1], "-v") == 0) {
            printVersion();
        }

    } else if(argc == 3) {
        if(strcmp(args[1], "--dfa") == 0 || strcmp(args[1], "-dfa") == 0) {
            if(strcmp(args[2], "--save") == 0 || strcmp(args[2], "-s") == 0) {
                newDFA("", 0);
            }
        }

    } else if(argc == 4) {
        if(strcmp(args[1], "--dfa") == 0 || strcmp(args[1], "-dfa") == 0) {
            if(strcmp(args[2], "--read") == 0 || strcmp(args[2], "-r") == 0) {
                newDFA(0, args[3]);
            }
        }

    } else if(argc == 5) {
        if(strcmp(args[1], "--dfa") == 0 || strcmp(args[1], "-dfa") == 0) {
            if(strcmp(args[2], "--save") == 0 || strcmp(args[2], "-s") == 0) {
                if(strcmp(args[3], "--name") == 0 || strcmp(args[3], "-n") == 0) {
                    newDFA(args[4], 0);
                }
            }
        }

    } else {
        printLogo();
        printf_s("For information on how to use mafl type \'mafl --help\'\n\n");
        printVersion();
        return 0;
    }
    
    return 0;
}