#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "file.h"
#include "common.h"
#include "parse.h"


int create_db_file(char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd >= 0) {
        close(fd);
        return -1; // File already exists
    }

    fd = open(filename, O_RDWR | O_CREAT, 0644);
    if (fd < 0) {
        return -1; // File open/create error
    }  

    return fd; // Success
}

int open_db_file(char *filename) {
    int fd = open(filename, O_RDWR);
    if (fd < 0) {   
        return -1; // File open error
    }
    return fd; // Success, return file descriptor
}


