#include <database.h>
#include <die.h>
#include <stdlib.h>
#include <stdio.h>

void Database_load(struct Connection *conn);
void Entry_print(struct Entry *en);

struct Connection *Connection_open(const char *filename, char action) {
    struct Connection *conn = malloc(sizeof *conn);
    if(!conn) {
        die("Connection: Memory error on open");
    }

    conn->db = malloc(sizeof *conn->db);
    if (!conn->db) {
        die("Connection: Memory error on database alloc");
    }

    if (action == 'c') {
        // create database
        conn->file = fopen(filename, "w");
        printf("made file\n");
    } else {
        // reopen existing file
        conn->file = fopen(filename, "r+");

        if(conn->file) {
            Database_load(conn);
        }

    }

    if(!conn->file) {
        die("Connection: failed to open file");
    }

    return conn;
}

void Database_load(struct Connection *conn) {
    int rc = fread(conn->db, sizeof *conn->db, 1, conn->file);
    if (rc != 1) {
        die("Connection: failed to load database");
    }
}

void Connection_close(struct Connection *conn) {
    if (conn) {
        if (conn->file) {
            fclose(conn->file);
        }

        if (conn->db){
            free(conn->db);
        }

        free(conn);
    }
}

void Database_list(struct Connection *conn) {
    int i = 0;
    bool did_print = false;
    struct Database *db = conn->db;

    for (i = 0; i < MAX_ROWS; i++) {
        struct Entry *entry = &db->rows[i];

        if (entry->set) {
            Entry_print(entry);
            did_print = true;
        }
    }

    if (!did_print) {
        printf("No data\n");
    }
}

void Entry_print(struct Entry *en) {

    printf("%d %s %s\n", en->id, en->name, en->email);
}

void Database_create(struct Connection *conn) {
    int i = 0;

    for (i = 0; i < MAX_ROWS; i++) {
        struct Entry entry = {
            .id = i,
            .set = false,
        };

        conn->db->rows[i] = entry;
    }
}

void Database_write(struct Connection *conn) {
    if(!conn->file) {
        die("Connection: file pointer is null");
    }

    rewind(conn->file);

    int rc = fwrite(conn->db, sizeof *conn->db, 1, conn->file);
    if (rc != 1) {
        die("Database: failed to write to database file");
    }

    rc = fflush(conn->file);
    if (rc == -1) {
        die("Database: failed to flush file buffer");
    }

}