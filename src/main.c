#include <stdio.h>
#include <stdbool.h>
#include <getopt.h>
#include <stdlib.h>

#include "common.h"
#include "file.h"
#include "parse.h"



void print_usage(char *argv[]) {
    printf("Usage: %s [-n] [-f filename]\n", argv[0]);
    printf("  -n            Create a new database file\n");
    printf("  -f filename   Specify the database file name\n");
    printf("  -a addstring  Add an employee with the given details\n");
    printf("  -h            Display this help message\n");
}



int main(int argc, char *argv[]) {
	int c = 0;
	bool newfile = false;
	char *filename = NULL;
    char *addstring = NULL;
    int db_fd = -1;
    struct dbheader_t *header = NULL;

	while ((c = getopt(argc, argv, "anf:")) != -1) {
		switch(c) {
			case 'f':
				filename = optarg;
				break;
			case 'n':
				newfile = true;
				break;
            case 'a':
                addstring = optarg;
                break;
            case '?':
                printf("Unknown option: %c\n", optopt);
                break;          
            default:
                print_usage(argv);
                return -1;
                break;
		}
	}
	
    if (filename == NULL) {
        print_usage(argv);
        return -1;
    }

	if (newfile) {		
        db_fd = create_db_file(filename);
        if (db_fd < 0) {
            fprintf(stderr, "Error creating database file: %s\n", filename);
            return -1; 
        }
        if(create_db_header(&header) == -1) {
            fprintf(stderr, "Error creating database header\n");
            close(db_fd);
            return -1;
        }     
        output_file(db_fd, header, NULL);   
	} else {
        db_fd = open_db_file(filename);
        if (db_fd < 0) {
            fprintf(stderr, "Error opening database file: %s\n", filename);
            return -1; 
        }
    }

    printf("Database file opened successfully: %s\n", filename);
    printf("new file: %s\n", newfile ? "true" : "false");
    
}
