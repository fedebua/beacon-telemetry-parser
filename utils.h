#ifndef UTILS_H
#define UTILS_H
#include <stdlib.h>

long open_file(int argc, char* argv[], FILE** fp);
void add_to_csv(const char* filename, const char* variable_name,  double* values, size_t number);

#endif /* UTILS_H */