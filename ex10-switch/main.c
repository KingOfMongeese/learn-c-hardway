#include <stdio.h>
#include <ctype.h>
#include <stdint.h>

void handle_string(char str[]);

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Error: need cmd line args\n");
        return 1;
    }

    for (int i = 1; i < argc; i++) {
        printf("counting vowels for %s\n", argv[i]);
        handle_string(argv[i]);
        printf("---------\n\n");
    }

    return 0;
}

void handle_string(char str[]) {
    int cnt = 1;
    uint16_t vowel_cnt = 0;
    for (char *i = &str[0]; *i != '\0'; i++) {
        char letter = tolower(*i);
        switch (letter) {
            case 'a':
                printf("%d. a\n", cnt);
                vowel_cnt++;
                break;

            case 'i':
                printf("%d. i\n", cnt);
                vowel_cnt++;
                break;

            case 'o':
                printf("%d. o\n", cnt);
                vowel_cnt++;
                break;

            case 'u':
                printf("%d. u\n", cnt);
                vowel_cnt++;
                break;

            case 'e':
                printf("%d. e\n", cnt);
                vowel_cnt++;
                break;

            default:
                printf("%d. %c Is not a vowel\n", cnt, letter);
                break;
        }
        cnt++;
    }

    printf("Total vowels: %d\n", vowel_cnt);
}