#include <database.h>
#include <die.h>

int main(int argc, char *argv[]) {

    if (argc < 3) {
        die("Usage Error: app </path/to/dbfile> <action, such as 'l'> [action params]\n\nactions:\nc: make a new database\nl: list database");
    }

    char *filename = argv[1];

    // ensure is only 1 char
    char action = argv[2][0];
    struct Connection *conn = Connection_open(filename, action);

    switch (action)
    {
    case 'c':
        Database_create(conn);
        Database_write(conn);
        break;

    case 'l':
        Database_list(conn);
        break;

    default:
        die("Usage Error: Unkown action\n");
        break;
    }

    Connection_close(conn);


    return 0;
}