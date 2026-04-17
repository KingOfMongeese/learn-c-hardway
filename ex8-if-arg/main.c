#include <stdio.h>

int main(int argc, char *argv[]) {

    if (argc == 1) {
        printf("1 argument: %s\n", argv[0]);
    } else if (argc > 1 && argc < 4) {
        printf("Received %d args\n", argc);

        // increments the pointer, at the end points to null
        for(int i = 0; i < argc; i++) {
            printf("%s ", *argv++);
        }

        printf("\nNow in reverse\n");
        // deincrements the pointer first as it was 1 past valid data before
        for (int i = argc; i > 0; i--) {
            printf("%s ", *--argv);
        }

        printf("\n");
    } else {
        printf("So many args!\n");
    }

    return 0;
}