#include <database.h>
#include <die.h>

int main(int argc, char *argv[]) {

    if (argc < 3) {
        die("Usage Error: app </path/to/dbfile> <action, such as 'l'> [action params]\n\nactions:\nc: make a new database\nl: list database\ns: set a row\ng: get a row\nd: delete a row (-1 for all data)");
    }

    char *filename = argv[1];

    // ensure is only 1 char
    char action = argv[2][0];
    struct Connection *conn = Connection_open(filename, action);
    int id = 0;

    if (argc > 3) id = atoi(argv[3]);
    if (id > MAX_ROWS) die("Usage Error: ID is past max rows");

    switch (action)
    {
    case 'c':
        Database_create(conn);
        Database_write(conn);
        printf("Database created: %s\n", filename);
        break;

    case 'l':
        Database_list(conn);
        break;

    case 's':
        if (argc < 5) {
            die("Usage Error: set needs id, name, email");
        }
        Database_set(conn, id, argv[4], argv[5]);
        Database_write(conn);
        break;

    case 'g':
        if (argc != 4) {
            die("Usage Error: need an id to get");
        }

        Database_get(conn, id);
        break;

    case 'd':
        if (argc != 4) {
            die("Usage Error: need an id to delete");
        }

        Database_delete(conn, id);
        Database_write(conn);
        break;


    default:
        die("Usage Error: Unkown action\n");
        break;
    }

    Connection_close(conn);

    return 0;
}