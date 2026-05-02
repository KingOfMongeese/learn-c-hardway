#include <database.h>
#include <die.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
    printf("\n------------ Database ----------------\n");

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

    printf("------------- END --------------------\n");
}

void Entry_print(struct Entry *en) {

    printf("%d | %s | %s |\n", en->id, en->name, en->email);
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

void Database_set(struct Connection *conn, int id, const char *name, const char *email) {

    struct Entry *entry = &conn->db->rows[id];
    if (entry->set) {
        die("Usage Error: already set, delete it first");
    }

    entry->set = true;
    char *res = strncpy(entry->name, name, MAX_DATA_SIZE);
    entry->name[MAX_DATA_SIZE - 1] = '\0';

    if (!res) {
        die("Database: name copy failed");
    }

    res = strncpy(entry->email, email, MAX_DATA_SIZE);
    entry->email[MAX_DATA_SIZE -1] = '\0';
    if (!res) {
        die("Database: email copy failed");
    }
}

void Database_get(struct Connection *conn, int id) {
    if (id < 0 || id >= MAX_ROWS) {
        die("Error: Invalid id");
    }

    struct Entry *entry = &conn->db->rows[id];

    if (entry->set) {
        Entry_print(entry);
    } else {
        die("Error: no entry for id");
    }
}

void Database_delete(struct Connection *conn, int id) {
    if (id < -1 || id >= MAX_ROWS) {
        die("Error: Invalid id");
    }

    if (id == -1) {
        for(int i = 0; i < MAX_ROWS; i++) {
            struct Entry new_entry = {.id = i, .set = false};
            conn->db->rows[i] = new_entry;
        }

        return;
    }

    struct Entry new_entry = {.id = id, .set = false};
    conn->db->rows[id] = new_entry;

}