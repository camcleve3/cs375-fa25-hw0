#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    FILE *fp = NULL;
    if (argc == 1) {
        fp = stdin;
    } else if (argc == 2) {
        fp = fopen(argv[1], "r");
        if (!fp) {
            perror(argv[1]);
            return 1;
        }
    } else {
        fprintf(stderr, "Usage: %s [file]\n", argv[0]);
        return 1;
    }

    int lines = 0, words = 0, bytes = 0;
    int in_word = 0;
    int c;

    while ((c = fgetc(fp)) != EOF) {
        bytes++;
        if (c == '\n') lines++;
        if (isspace(c)) {
            in_word = 0;
        } else if (!in_word) {
            words++;
            in_word = 1;
        }
    }

    printf("%7d %7d %7d", lines, words, bytes);
    if (argc == 2) printf(" %s", argv[1]);
    printf("\n");

    if (fp != stdin) fclose(fp);
    return 0;
}
