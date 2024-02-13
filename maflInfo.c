#include <stdio.h>

#include "maflInfo.h"
#include "generalDefs.h"

#define VERSION "V0.1"

void listUsage();
void listShort();
void printLogo();

void listUsage() {
    printf_s("mafl version \'%s\'\nUsage: mafl.exe [Argument] [Options...]\n", VERSION);
    // General
    printf_s("\nGeneral arguments:\n");
    //  --help
    printf_s("\n\t--help, -h\n\t\tPrints this list of detailed information on the usage of mafl.exe\n");
    //  -?
    printf_s("\n\t-?\n\t\tPrints a short list of all availible arguments and options without explanation\n");

    // Maths
    printf_s("\nMathematics related arguments:\n");

    // AFL
    printf_s("\nComputer science related arguments:\n");
    //  --dfa
    printf_s("\n\t--dfa, -dfa\n\t\tReads a deterministic finite automaton\n\t\tThen let's you decide what to do with it\n");
    printf_s("\n\t\tOptions:\n");
    //      --save
    printf_s("\t\t\t--save, -s\n\t\t\t\tSaves the automaton configuration to a file afterwards\n");
    //      --read
    printf_s("\n\t\t\t--read <file>, -r <file>\n\t\t\t\tReads a previously saved automaton config from <file>\n");
}

void listShort() {
    printf_s("mafl version \'%s\'\nUsage: mafl.exe [Argument] [Options...]\n", VERSION);
    // General
    printf_s("\nGeneral arguments:\n");
    //  --help
    printf_s("\n\t--help, -h\n");
    //  -?
    printf_s("\t-?\n");

    // Maths
    printf_s("\nMathematics related arguments:\n");

    // AFL
    printf_s("\nComputer science related arguments:\n");
    //  --dfa
    printf_s("\n\t--dfa, -dfa\n");
    printf_s("\t\tOptions:\n");
    //      --save
    printf_s("\t\t\t--save, -s\n");
    //      --read
    printf_s("\t\t\t--read <file>, -r <file>\n");
}

void printLogo() {
    // Most difficult part of the project:
    printf_s("           /////////////////////////////////////////////////////////////////////////////////\n");
    printf_s("          ///      /////      ////////////     ////////////             ///   /////////////\n");
    printf_s("         ///   /   ///   /   ///////////   /   ///////////   /////////////   /////////////\n");
    printf_s("        ///   //   /   //   //////////   ///   //////////   /////////////   /////////////\n");
    printf_s("       ///   ///     ///   /////////   /////   /////////   /////////////   /////////////\n");
    printf_s("      ///   ////   ////   ////////   ///////   ////////             ///   /////////////\n");
    printf_s("     ///   ///////////   ///////   /////////   ///////   /////////////   /////////////\n");
    printf_s("    ///   ///////////   //////                 //////   /////////////   /////////////\n");
    printf_s("   ///   ///////////   /////   /////////////   /////   /////////////   /////////////\n");
    printf_s("  ///   ///////////   ////   ///////////////   ////   /////////////   /////////////\n");
    printf_s(" ///   ///////////   ///   /////////////////   ///   /////////////             ///\n");
    printf_s("/////////////////////////////////////////////////////////////////////////////////\n");
    puts("");
}