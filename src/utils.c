#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void error_handle(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

