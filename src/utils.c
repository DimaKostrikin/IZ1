#include "HWRK/utils.h"

char *read_string(FILE *stream) {
    if (!stream)
        return NULL;

    printf("Введите строку:\n");

    int size_of_buffer = 1;

    char *string = (char*)calloc(size_of_buffer, sizeof(char));
    if (!string) {
        fprintf(stderr, "Allocation error.");
        return NULL;
    }

    char c = getc(stream);
    int lenght_of_string = 0;

    while (c != '\n') {
        string[lenght_of_string++] = c;
        if (lenght_of_string >= size_of_buffer) {
            size_of_buffer *= 2;
            char *temp = (char*)realloc(string, size_of_buffer * sizeof(char));
            if (!temp) {
                free(string);
                fprintf(stderr, "Allocation error.");
                return NULL;
            }
            string = temp;
        }
        c = getc(stream);
    }
    string[lenght_of_string] = '\0';
    return string;
}


int filter(const char **vect_of_strings, const int *num_of_lines, char ***res_vect) {
    if (!vect_of_strings)
        return -1;
    if (!num_of_lines)
        return -1;
    if (!res_vect)
        return -1;

    int number_res = 0;
    char **res = NULL;
    res = (char**)calloc(1, sizeof(char*));
    char **temp = NULL;
    int j = 0;


    for (int i = 0; i < *num_of_lines; ++i) {
        if (is_url(vect_of_strings[i])) {
            ++number_res;
            temp = (char**)realloc(res, number_res * sizeof(char*));
            if (!temp) {
                for (int k = 0; k < j; ++k) {
                    free(res[k]);
                }
                free(res);
                fprintf(stderr, "Allocation error.");
                return -1;
            }

            res[j] = (char*)calloc(strlen(vect_of_strings[i]) + 1, sizeof(char));
            if (!res[j]) {
                for (int k = 0; k < j; ++k) {
                    free(res[k]);
                }
                free(res);
                fprintf(stderr, "Allocation error.");
                return -1;
            }
            strcpy(res[j], vect_of_strings[i]);
            ++j;
        }
    }
    *res_vect = res;
    return number_res;
}

int init(FILE *stream) {
    if (!stream)
        return -1;

    printf("Введите количество строк:\n");
    int num_of_lines = 0;

    int err = fscanf(stream, "%d", &num_of_lines);
    getc(stream);  // Scanf выдает в stdin \n. Считываем его.
    if (!err || num_of_lines < 0) {
        return -1;
    }

    char **vect_of_strings = (char**)calloc(num_of_lines, sizeof(char*));
    if (!vect_of_strings) {
        fprintf(stderr, "Allocation error.");
        return -1;
    }

    for (int i = 0; i < num_of_lines; ++i) {
        vect_of_strings[i] = read_string(stream);
        if (!vect_of_strings[i]) {
            --i;
            for (; i >= 0; --i) {
                free(vect_of_strings[i]);
            }
        }
    }

    char **res_vect = NULL;
    int num_of_urls = filter((const char**)vect_of_strings, &num_of_lines, &res_vect);
    printf("%d\n", num_of_urls);
    for (int i = 0; i < num_of_urls; ++i) {
        printf("%s\n", res_vect[i]);
    }

    for (int i = 0; i < num_of_lines; ++i) {
        free(vect_of_strings[i]);
    }
    free(vect_of_strings);

    for (int i = 0; i < num_of_urls; ++i) {
        free(res_vect[i]);
    }
    free(res_vect);

    return num_of_urls;
}
