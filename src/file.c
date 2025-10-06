#include <stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "file.h"
#include "common.h"


int create_db_file(char *filename) {
    int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        return -1; // File open/create error
    }
    return fd;
}

int open_db_file(char *filename) {
    int fd = open(filename, O_RDWR);
    if (fd < 0) {   
        return -1; // File open error
    }
    return fd; // Success, return file descriptor
}


