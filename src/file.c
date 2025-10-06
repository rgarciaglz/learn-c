#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "file.h"
#include "common.h"
#include "parse.h"


int create_db_file(char *filename) {
    int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        return -1; // File open/create error
    }
    //create db header
    struct dbheader_t *header = NULL;
    if (create_db_header(&header) != 0) {
        close(fd);
        return -1; // Header creation error
    }

    // Write the header to the file
    ssize_t bytesWritten = write(fd, header, sizeof(struct dbheader_t));
    if (bytesWritten != sizeof(struct dbheader_t)) {
        free(header);
        close(fd);
        return -1; // Write error
    }


    return fd; // Success
}

int open_db_file(char *filename) {
    int fd = open(filename, O_RDWR);
    if (fd < 0) {   
        return -1; // File open error
    }
    //should validate header from file
    struct dbheader_t *header = NULL;
    if (validate_db_header(fd, &header) != 0) {
        close(fd);
        return -1; // Header validation error
    }

    return fd; // Success, return file descriptor
}


