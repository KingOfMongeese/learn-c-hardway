#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct Person {
    char *name;
    uint8_t age;
    uint8_t height_inches;
    uint16_t weight_lbs;
};

struct Person *alloc_Person(char *name, uint8_t age, uint8_t height_inches, uint16_t weight_lbs) {

    struct Person *someone = malloc(sizeof *someone);
    assert(someone != NULL);

    someone->name = malloc(strlen(name) + 1);
    assert(someone->name != NULL);

    // safe as we malloced the full size of the buffer already
    // NOLINTNEXTLINE
    strcpy(someone->name, name);
    someone->age = age;
    someone->height_inches = height_inches;
    someone->weight_lbs = weight_lbs;

    return someone;
}

struct Person create_Person(char *name, uint8_t age, uint8_t height_inches, uint16_t weight_lbs ) {

    struct Person someone = {
        .name = name,
        .age = age,
        .height_inches = height_inches,
        .weight_lbs = weight_lbs,
    };

    return someone;
}

void Person_destroy(struct Person *p) {

    assert(p != NULL);

    free(p->name);
    free(p);
}

void Person_print(struct Person *p) {
    printf("Name: %s\n", p->name);
    printf("    Age: %d\n", p->age);
    printf("    Height: %d inches\n", p->height_inches);
    printf("    Weight: %d lbs\n", p->weight_lbs);
    printf("\n\n");
}

int main(int argc, char *argv[]) {
    struct Person *heap_person = alloc_Person("Joe", 4, 24, 45);
    struct Person stack_person = create_Person("frank", 20, 56, 156);

    Person_print(heap_person);
    Person_print(&stack_person);

    Person_destroy(heap_person);

    return 0;
}