#pragma once
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

// TODO make variable
// TODO dynamic?
#define MAX_DATA_SIZE 512
#define MAX_ROWS 100

struct Entry {
    uint32_t id;
    bool set;
    char name[MAX_DATA_SIZE];
    char email[MAX_DATA_SIZE];
};

struct Database {
    struct Entry rows[MAX_ROWS];
};

struct Connection {
    FILE *file;
    struct Database *db;
};

// open and load the database to a `Connection`
// Call `Connection_close` when finished
struct Connection *Connection_open(const char *filename, char mode);

// Close a database and free its memory
void Connection_close(struct Connection *conn);

// Print out the all the contents of the database in this connection
void Database_list(struct Connection *conn);

// Create a new zeroed database
void Database_create(struct Connection *conn);

// Write out a database to the `conn`
void Database_write(struct Connection *conn);