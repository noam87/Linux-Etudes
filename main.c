#include <stdio.h> // puts
#include <string.h> // strcmp
#include "scatter_gather_io.h"

#define HELP_STRING "\n\n\nAvailable Commands\n"\
                    "==================\n\n"\
                    "-sgio [read | write]\n"\
                    "        (scatter-gather IO)\n"\
                    "        Read/write to file using multiple buffers in a "\
                            "single system call.\n\n"

void chooseEtude(int argc, char* argv[]) {
    if (strcmp(argv[0], "help") == 0) { puts(HELP_STRING); }
    else if (strcmp(argv[0], "-sgio") == 0) {
        if (argc == 2 && strcmp(argv[1], "read") == 0) { sgio_read(); }
        else { puts("-sgio expects an argument.\n"); }
    }
    else { puts("Unknown command!"); }
}

int main(int argc, char* argv[]) {
    if (argc >= 2) {
        chooseEtude(argc - 1, &argv[1]);
    } else {
        puts("You must pass a second argument.\n");
    }

    return 0;
}
