#include <stdbool.h>
#include <stdio.h>

bool open_file_read(const char *file_name, FILE **file) {
    *file = fopen(file_name, "rb");
    return *file != NULL;
}

bool open_file_write(const char *file_name, FILE **file) {
    *file = fopen(file_name, "wb");
    return *file != NULL;
}

bool close_file(FILE *file) {
    return fclose(file) == 0;
}
