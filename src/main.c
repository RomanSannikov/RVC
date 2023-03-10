#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "init.h"
#include "add.h"
#include "error_handling.h"

void run(int argc, char* argv[])
{
    if (strcmp(argv[1], "init") == 0 && argc == 2) {
        createFileStructure();
    } else if (strcmp(argv[1], "add") == 0) {
        addFilesToStagingArea(argv + 2, argc - 2);
    } else {
        errno = EINVAL;
        addError("unknown command");
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2) {
        errno = EINVAL;
        addError("no command is specified");
    } else {
        run(argc, argv);
    }

    if (errno != 0) {
        fprintf(stderr, "%s\n", strerror(errno));
        for (unsigned i = 0; i < getNumberOfErrors(); ++i) {
            fprintf(stderr, "%s\n", getError(i));
        }
        
    }


    return 0;
}