#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>

// Declare the Address struct type
// name and email are strings at a fixed width of MAX_DATA (512)
struct Address {
    int id;
    int set;
    char *name;
    char *email;
};

// Declare the Database struct type
// rows is an array of length MAX_ROWS (100), containing Address structs
struct Database {
    // Array is pointing to a range of memory, maybe this ensures
    // the Address structs in the array are sequentially stored in mem?
    int max_rows;
    int max_data;
    struct Address *rows;
};

// Declare the Connection struct type
// file is a pointer to a FILE struct
// db is a pointer to a Database struct
struct Connection {
    FILE *file;
    struct Database *db;
};

void Database_close(struct Connection *conn);

// Declare the die method
// errno is an external variable, if it's set, just perror the message
// if it's not set, perror "ERROR: {message}"
// Finally, exit with failure
void die(const char *message, struct Connection *conn)
{
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    if (conn) Database_close(conn);

    exit(1);
}

// Declare the Address_print function
// Takes a pointer to an Address as a param
// Use struct pointer access to print the fields
void Address_print(struct Address *addr)
{
    printf("%d %s %s\n",
            addr->id, addr->name, addr->email);
}

void Database_print(struct Database *db)
{
    printf("max_rows: %d\nmax_data: %d\n",
            db->max_rows, db->max_data);
}

// Declare the Database_load function
void Database_list(struct Connection *conn);

void Database_load(struct Connection *conn)
{
    rewind(conn->file);

    // Read conn->file into conn->db
    // Each block is the sizeof(struct Database)
    // Read 1 block
    int rc = fread(&conn->db->max_rows, sizeof(int), 1, conn->file);
    if (rc != 1) die("Failed to load database.", conn);

    rc = fread(&conn->db->max_data, sizeof(int), 1, conn->file);
    if (rc != 1) die("Failed to load database.", conn);

    int i = 0;
    for (i = 0; i < conn->db->max_rows; i++) {
        struct Address row = {.id = i, .set = 0};
        int id = 0;
        fread(&id, sizeof(int), 1, conn->file);
        row.id = id;

        int set = 0;
        fread(&set, sizeof(int), 1, conn->file);
        row.set = set;

        char *name = malloc(sizeof(char) * conn->db->max_data);
        char *email = malloc(sizeof(char) * conn->db->max_data);
        fread(name, sizeof(char) * conn->db->max_data, 1, conn->file);
        fread(email, sizeof(char) * conn->db->max_data, 1, conn->file);
        row.name = name;
        row.email = email;
    }
}

// Declare the Database_open function
struct Connection *Database_open(const char *filename, char mode, int max_rows)
{
    // Alloc memory for a struct Connection, store the pointer in conn
    struct Connection *conn = malloc(sizeof(struct Connection));
    // If memory didn't allocate, bail
    if (!conn) die("Memory error", conn);

    conn->db = malloc(sizeof(struct Database));
    if (!conn->db) die("Memory error", conn);

    if (mode == 'c') {
        // Create new 0 length file, open for writing, positioned at BOF
        conn->file = fopen(filename, "w");
        conn->db->rows = malloc(sizeof(struct Address) * max_rows);
        conn->db->max_rows = max_rows;
    } else {
        // Open file for reading and writing, positioned at BOF
        conn->file = fopen(filename, "r+");

        fread(&max_rows, sizeof(int), 1, conn->file);
        conn->db->rows = malloc(sizeof(struct Address) * max_rows);
        conn->db->max_rows = max_rows;

        if (conn->file) {
            // Read out the file if the pointer opened successfully
            Database_load(conn);
        }
    }

    // If the file pointer didn't open, bail
    if (!conn->file) die("Failed to open the file", conn);

    return conn;
}

// Declare the Database_close function
void Database_close(struct Connection *conn)
{
    // If conn is not NULL
    if (conn) {
        // Close the file handler if it's open
        if (conn->file) fclose(conn->file);

        int i = 0;
        for (i = 0; i < conn->db->max_rows; i++) {
            struct Address *row = &conn->db->rows[i];
            free(row->name);
            free(row->email);
        }

        // Free the memory at conn->db
        if (conn->db) free(conn->db);
        // Free the memory at conn
        free(conn);
    }
}

// Declare the Database_write function
void Database_write(struct Connection *conn)
{
    // Seek the file pointer to the beginning of the file
    rewind(conn->file);

    // Write the 1 block of sizeof(struct Database)
    // into the file stream pointed to by conn->file
    // populated by the data pointed to by conn->db
    int rc = fwrite(&conn->db->max_rows, sizeof(int), 1, conn->file);
    // If file write failed, bail
    if (rc != 1) die("Failed to write database.", conn);

    fwrite(&conn->db->max_data, sizeof(int), 1, conn->file);

    int i = 0;
    for (i = 0; i < conn->db->max_rows; i++) {
        struct Address *row = &conn->db->rows[i];

        fwrite(&row->id, sizeof(int), 1, conn->file);
        fwrite(&row->set, sizeof(int), 1, conn->file);
        fwrite(row->name, sizeof(char) * conn->db->max_data, 1, conn->file);
        fwrite(row->email, sizeof(char) * conn->db->max_data, 1, conn->file);
    }

    // Write buffered data to disk
    rc = fflush(conn->file);
    // If flush failed, bail
    if (rc == -1) die("Cannot flush database.", conn);
}

// Declare the Database_create function
void Database_create(struct Connection *conn, int max_rows, int max_data)
{
    conn->db->max_rows = max_rows;
    conn->db->max_data = max_data;

    int i = 0;
    for (i = 0; i < conn->db->max_rows; i++) {
        // make a prototype to initialize it
        // Can do a literal here because it's on the stack
        struct Address addr = {.id = i, .set = 0};
        addr.name = malloc(sizeof(char) * max_data);
        addr.email = malloc(sizeof(char) * max_data);

        strncpy(addr.name, "", max_data);
        strncpy(addr.email, "", max_data);
        // then just assign it
        conn->db->rows[i] = addr;
    }
}

// Declare the Database_set function
void Database_set(struct Connection *conn, int id, const char *name, const char *email)
{
    // Getting the pointer from the Address in ->rows[id]
    struct Address *addr = &conn->db->rows[id];
    if (addr->set) die("Already set, delete it first", conn);

    addr->set = 1;

    // Copy name into addr->name
    if (!name || !email) die("No name or email", conn);

    addr->name = malloc(conn->db->max_data);
    char *res = strncpy(addr->name, name, conn->db->max_data);
    addr->name[conn->db->max_data - 1] = '\0';
    if (!res) die("Name copy failed", conn);

    addr->email = malloc(conn->db->max_data);
    res = strncpy(addr->email, email, conn->db->max_data);
    addr->email[conn->db->max_data - 1] = '\0';
    if (!res) die("Email copy failed.", conn);
}

// Declare the Database_get function
void Database_get(struct Connection *conn, int id)
{
    // Getting the pointer from the Address in ->rows[id]
    struct Address *addr = &conn->db->rows[id];

    if (addr->set) {
        // Print the address if set
        Address_print(addr);
    } else {
        die("ID is not set", conn);
    }
}

// Declare the Database_delete function
void Database_delete(struct Connection *conn, int id)
{
    // This is not actually deleting name and email, hm
    // Maybe since they're on the stack, the pointers get freed?
    struct Address addr = {.id = id, .set = 0};
    conn->db->rows[id] = addr;
}

// Declare the Database_list function
void Database_list(struct Connection *conn)
{
    int i = 0;
    struct Database *db = conn->db;

    // Loop through all the rows in conn->db
    for (i = 0; i < conn->db->max_rows; i++) {
        struct Address *cur = &db->rows[i];
        printf("%p %d\n", cur, cur->set);

        if (cur->set) {
            // If it's set, print it
            Address_print(cur);
        }
    }
}

int main(int argc, char *argv[])
{
    // Needs at least 3 args
    // ex17 <dbfile> <action>
    if (argc < 3) die("USAGE: ex17 <dbfile> <action> [action params]", NULL);

    char *filename = argv[1];
    char action = argv[2][0];
    int id = 0;

    // Convert argv[3] to an int
    if (argc > 3) id = atoi(argv[3]);
    struct Connection *conn = Database_open(filename, action, id);

    switch(action) {
        case 'c':
            {
            int max_data = 512;
            // Create all the addresses
            if (argc < 4) {
                die("USAGE: ex17 <dbfile> c <max_rows> [max_data]", conn);
            }

            if (argc > 4) max_data = atoi(argv[4]);
            Database_create(conn, id, max_data);

            // Commit the fresh DB to disk
            Database_write(conn);
            }
            break;

        case 'g':
            if (argc != 4) die("Need an id to get", conn);

            if (id >= conn->db->max_rows) {
                die("There's not that many records.", conn);
            }

            // Get the address at ID and print it out
            Database_get(conn, id);
            break;

        case 's':
            if (argc != 6) die("Need id, name, email to set", conn);

            if (id >= conn->db->max_rows) {
                die("There's not that many records.", conn);
            }

            // Set the value at id, commit
            Database_set(conn, id, argv[4], argv[5]);
            Database_write(conn);
            break;

        case 'd':
            if (argc != 4) die("Need id to delete", conn);

            if (id >= conn->db->max_rows) {
                die("There's not that many records.", conn);
            }

            // Delete the value at id, commit
            Database_delete(conn, id);
            Database_write(conn);
            break;

        case 'l':
            // List all addresses in db
            Database_list(conn);
            break;

        default:
            die("Invalid action, only: c=create, g=get, s=set, d=del, l=list", conn);
    }

    // Close the handler, free the mem
    Database_close(conn);

    return 0;
}
