#ifndef IO_H
#define IO_H
#include <stdbool.h>
#include <stdio.h>

#endif //IO_H

bool open_file_read(const char *file_name, FILE **file);

bool open_file_write(const char *file_name, FILE **file);

bool close_file(FILE *file);
