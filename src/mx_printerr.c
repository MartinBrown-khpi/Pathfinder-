#include "pathfinder.h"

void mx_printerr(const char *err) {
    write(STDERR_FILENO, err, mx_strlen(err));
}
