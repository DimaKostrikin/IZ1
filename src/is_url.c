#include "HWRK/is_url.h"

typedef void (*action_t)(counts *count);

typedef struct {
    state_t state;
    action_t action;
} table_t;

void incr_dots(counts *count) {  // Если в урле 0 точек, он невалидный.
    if (!count) {
        return;
    }
    ++count->count_of_dots;
}

void decr_dots(counts *count) {  // Если в урле 1 точка в конце, то он невалидный.
    if (!count) {
        return;
    }
    --count->count_of_dots;
}

void incr_get_symbols(counts *count) {  // Функция нужна для отслеживания кол-ва считываемых символов в самом начале.
    if (!count) {
        return;
    }
    ++count->count_of_symbols;
}

table_t syntax[STAGE_COUNT][LEXEM_COUNT] = {  // Таблица переходов состояний.
                  /* PROTOCOL */              /* DOT */                      /*LEXEM_END_OF_STRING         /*LEXEM NOTHING*/
    /* BEGIN */  {{STAGE_DOMAIN, NULL}, {STAGE_ERROR, NULL},    {STAGE_ERROR, NULL},    {STAGE_BEGIN, incr_get_symbols}, {STAGE_ERROR, NULL}},
    /* DOMAIN */ {{STAGE_ERROR, NULL},  {STAGE_DOT, incr_dots}, {STAGE_END, NULL},      {STAGE_DOMAIN, NULL},            {STAGE_ERROR, NULL}},
    /* DOT */    {{STAGE_ERROR, NULL},  {STAGE_ERROR, NULL},    {STAGE_END, decr_dots}, {STAGE_DOMAIN, NULL},            {STAGE_ERROR, NULL}},
};

void clean_buffer(char *buffer) {  // После каждой полученной лексемы нужно затереть буфер, чтобы не получать их снова.
    if (!buffer) {
        return;
    }
    for (int i = 0; i < 9; ++i) {
        buffer[i] = '1';
    }
}

lexem_t get_lexem(char *buffer) {  // Функция получения из буфера нужных лексем для перехода в новое состояние.
    if (!buffer) {
        return LEXEM_END_OF_STRING;
    }
    if (strstr(buffer, "://")) {
        clean_buffer(buffer);
        return LEXEM_PROTOCOL;
    }
    if (buffer[8] == '.') {
        clean_buffer(buffer);
        return LEXEM_DOT;
    }
    if (buffer[8] == '\0') {
        clean_buffer(buffer);
        return LEXEM_END_OF_STRING;
    }
    if (buffer[8] == ' ') {
        clean_buffer(buffer);
        return LEXEM_SPACE;
    }
    return LEXEM_NOTHING;

}

void left_offset(char *buffer) {  // Функция смещения элементов буфера на один влево.
    for (int i = 0; i < 8; ++i) {
        buffer[i] = buffer[i+1];
    }
}

int is_url(const char *string) {
    char buffer[10] = "123456789";  // Инициализация проходного буфера. Этот буфер будет проходить посимвольно по анализируемой строке.
    int i = 0;
    counts count;

    count.count_of_symbols = 0;
    count.count_of_dots = 0;

    state_t state = STAGE_BEGIN;  // Начальное состояние.
    while (state != STAGE_ERROR && state != STAGE_END) {
        buffer[8] = string[i];
        lexem_t lexem = get_lexem(buffer);
        left_offset(buffer);

        table_t table = syntax[state][lexem];

        if (table.action)
            table.action(&count);

        state = table.state;
        ++i;

        if (state == STAGE_DOMAIN && count.count_of_symbols == 2) {
            state = STAGE_ERROR;
        }
    }
    return !(state == STAGE_ERROR || !count.count_of_dots);
}

