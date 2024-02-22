#include <stdio.h>
#include <string.h>

#include "dfa.h"
#include "maflInfo.h"
#include "generalDefs.h"

#define FLAG_COUNT 8

int checkFlags(int[], char*[], int argc);

int main(int argc, char* args[]) {
    // variables for arguments and options
    // the value specifies where they are in args (-1 = not set)
    // 0 = -h, 1 = -?, 2 = -v, 3 = -dfa, 4 = --save, 5 = --name, 6 = --read, 7 = --minimize
    int flags[] = {-1, -1, -1, -1, -1, -1, -1, -1};

    // check which flags the user wants to use
    for(int i = 1; i < argc; i++) {
        if(strcmp(args[i], "--help") == 0 || strcmp(args[i], "-h") == 0) {
            flags[0] = i;
            continue;
        } else if(strcmp(args[i], "-?") == 0) {
            flags[1] = i;
            continue;
        } else if(strcmp(args[i], "--version") == 0 || strcmp(args[i], "-v") == 0) {
            flags[2] = i;
            continue;
        } else if(strcmp(args[i], "--dfa") == 0 || strcmp(args[i], "-dfa") == 0) {
            flags[3] = i;
            continue;
        } else if(strcmp(args[i], "--save") == 0 || strcmp(args[i], "-s") == 0) {
            flags[4] = i;
            continue;
        } else if(strcmp(args[i], "--name") == 0 || strcmp(args[i], "-n") == 0) {
            flags[5] = i;
            continue;
        } else if(strcmp(args[i], "--read") == 0 || strcmp(args[i], "-r") == 0) {
            flags[6] = i;
            continue;
        } else if(strcmp(args[i], "--minimize") == 0 || strcmp(args[i], "-m") == 0) {
            flags[7] = i;
            continue;
        }

        if(strcmp(args[i - 1], "--name") != 0 && strcmp(args[i - 1], "-n") != 0 && strcmp(args[i - 1], "--read") != 0 && strcmp(args[i - 1], "-r") != 0) {
            printf_s("\'%s\' unknown! Exiting.\n", args[i]);
            return 0;
        }
    }

    // check if the user set the flags without conflicts
    int setFlags = checkFlags(flags, args, argc);
    if(setFlags < 0) {
        return 0;
    }

    // execute program according to users specification
    // 0 = -h, 1 = -?, 2 = -v, 3 = -dfa, 4 = --save, 5 = --name, 6 = --read, 7 = --minimize
    if(setFlags == 0) {
        printLogo();
        printf_s("For information on how to use mafl type \'mafl --help\'\n\n");
        printVersion();
        return 0;
    }
    if(flags[0] != -1) {
        listUsage();
        return 0;
    }
    if(flags[1] != -1) {
        listShort();
        return 0;
    }
    if(flags[2] != -1) {
        printVersion();
        return 0;
    }
    if(flags[3] != -1) {
        int minimize = 0;
        char *save = 0, *read = 0;

        if(flags[4] != -1) {
            save = "";
            if(flags[5] != -1) save = args[flags[5] + 1];
        }
        if(flags[6] != -1) read = args[flags[6] + 1];
        if(flags[7] != -1) minimize = 1;

        newDFA(save, read, minimize);
        return 0;
    }
    
    return 0;
}

// 0 = -h, 1 = -?, 2 = -v, 3 = -dfa, 4 = --save, 5 = --name, 6 = --read, 7 = --minimize
int checkFlags(int flags[], char* args[], int argc) {
    int setFlags = 0;
    for(int i = 0; i < FLAG_COUNT; i++) {
        if(flags[i] != -1) setFlags++;
    }

    if(setFlags == 0) return 0;

    if(setFlags > 1 && (flags [0] != -1 || flags[1] != -1 || flags[2] != -1)) {
        printf_s("\nERR: \'--help\', \'-?\', \'--version\' can only be used on their own!\n");
        return -1;
    } 
    if(flags[3] == -1 && (flags[4] != -1 || flags[5] != -1 || flags[6] != -1 || flags[7] != -1))  {
        printf_s("\nERR: Options are missing an argument! (e.g. \'--dfa\')\n");
        return -1;
    }
    if(flags[4] == -1 && flags[5] != -1) {
        printf_s("\nERR: \'--name\' specified but \'--save\' is not!\n");
        return -1;
    }
    if(flags[5] != -1 && (flags[5] + 1 > argc || args[flags[5] + 1][0] == '-')) {
        printf_s("\nERR: Please specify a name for your file!\n");
        return -1;
    }
    if(flags[6] != -1 && (flags[6] + 1 > argc || args[flags[6] + 1][0] == '-')) {
        printf_s("\nERR: Please specify a name for the read file!\n");
        return -1;
    }
    if(flags[4] != -1 && flags[6] != -1 && flags[7] == -1) {
        printf_s("WARN: DFA will be saved unchanged form current save.\n\n");
    }

    return setFlags;
}