#include <stdio.h>

#include "maflInfo.h"
#include "generalDefs.h"

#define VERSION "V0.1.4"

void listUsage();
void listShort();
void printLogo();
void printVersion();

void listUsage() {
    printf_s("mafl version \'%s\'\nUsage: \'mafl [Argument] [Options...]\'\n", VERSION);
    // General
    printf_s("\nGeneral arguments:\n");
    //  --help
    printf_s("\n\t--help, -h\n\t\tPrints this list of detailed information on the usage of mafl.exe\n");
    //  -?
    printf_s("\n\t-?\n\t\tPrints a short list of all availible arguments and options without explanation\n");
    //  --version
    printf_s("\n\t--version, -v\n\t\tPrints the currently installed version\n");

    // Maths
    printf_s("\nMathematics related arguments:\n");

    // AFL
    printf_s("\nComputer science related arguments:\n");
    //  --dfa
    printf_s("\n\t--dfa, -dfa\n\t\tReads a deterministic finite automaton\n\t\tThen let's you decide what to do with it\n");
    printf_s("\n\t\tOptions:\n");
    //      --save
    printf_s("\t\t\t--save, -s\n\t\t\t\tSaves the automaton configuration to a file afterwards\n");
    printf_s("\t\t\t\tFilename randomly generated if not specified otherwise (see below)\n");
    //          --name
    printf_s("\n\t\t\t\t--name <filename>, -n <filename>\n\t\t\t\t\tNames the saved config as specified\n");
    printf_s("\t\t\t\t\tDo not include any file extension here\n");
    //      --read
    printf_s("\n\t\t\t--read <file>, -r <file>\n\t\t\t\tReads a previously saved automaton config from <file>\n");
    //      --minimize
    printf_s("\n\t\t\t--minimize, -m\n\t\t\t\tMinimizes a read automaton (either manual or from file)\n\t\t\t\tIf combined with \'--save\' only the minimal DFA is saved\n");
}

void listShort() {
    printf_s("mafl version \'%s\'\nUsage: mafl.exe [Argument] [Options...]\n", VERSION);
    // General
    printf_s("\nGeneral arguments:\n");
    //  --help
    printf_s("\n\t--help, -h\n");
    //  -?
    printf_s("\t-?\n");
    //  --version
    printf_s("\t--version, -v\n");

    // Maths
    printf_s("\nMathematics related arguments:\n");

    // AFL
    printf_s("\nComputer science related arguments:\n");
    //  --dfa
    printf_s("\n\t--dfa, -dfa\n");
    printf_s("\t\tOptions:\n");
    //      --save
    printf_s("\t\t\t--save, -s\n");
    //          --name
    printf_s("\t\t\t\t--name <filename>, -n <filename>\n");
    //      --read
    printf_s("\t\t\t--read <file>, -r <file>\n");
    //      --minimize
    printf_s("\t\t\t--minimize, -m\n");
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

void printVersion() {
    printf_s("mafl version: \'%s\'\n", VERSION);
    printf_s("MIT License\tCopyright (c) 2024 KUHLwasStolen\n");
    printf_s("https://github.com/KUHLwasStolen/mafl-library \n");
}