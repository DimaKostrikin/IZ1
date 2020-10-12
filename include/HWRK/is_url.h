#ifndef IZ1_IS_URL_H
#define IZ1_IS_URL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    LEXEM_PROTOCOL = 0,
    LEXEM_DOT,
    LEXEM_END_OF_STRING,
    LEXEM_NOTHING,
    LEXEM_SPACE,
    LEXEM_COUNT
} lexem_t;

typedef enum {
    STAGE_BEGIN = 0,
    STAGE_DOMAIN,
    STAGE_DOT,
    STAGE_END,
    STAGE_ERROR,
    STAGE_COUNT
} state_t;

typedef struct {
    unsigned int count_of_dots;
    unsigned int count_of_symbols;
} counts;


void incr_dots(counts *count);
void decr_dots(counts *count);
void incr_get_symbols(counts *count);

void clean_buffer(char *buffer);
lexem_t get_lexem(char *buffer);
int is_url(const char *string);


#endif //IZ1_IS_URL_H

