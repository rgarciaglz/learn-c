#include "parse.h"
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define HEADER_MAGIC 0x4c4c4144
#define NAME_LEN 256
#define ADDRESS_LEN 256


int create_db_header(int fd, struct dbheader_t **headerOut) {
    if (headerOut == NULL) {
        return -1; // Invalid argument
    }

    struct dbheader_t *header = (struct dbheader_t *)malloc(sizeof(struct dbheader_t));
    if (header == NULL) {
        return -1; // Memory allocation failure
    }

    header->magic = HEADER_MAGIC;
    header->version = 1;
    header->count = 0;
    header->filesize = sizeof(struct dbheader_t);

    *headerOut = header;
    return 0; // Success
}

int validate_db_header(int fd, struct dbheader_t **headerOut) {
    if (fd < 0 || headerOut == NULL) {
        return -1; // Invalid argument
    }

    struct dbheader_t *header = (struct dbheader_t *)malloc(sizeof(struct dbheader_t));
    if (header == NULL) {
        return -1; // Memory allocation failure
    }

    ssize_t bytesRead = read(fd, header, sizeof(struct dbheader_t));
    if (bytesRead != sizeof(struct dbheader_t)) {
        free(header);
        return -1; // Read error or incomplete read
    }

    if (header->magic != HEADER_MAGIC) {
        free(header);
        return -1; // Invalid magic number
    }

    *headerOut = header;
    return 0; // Success
}

int read_employees(int fd, struct dbheader_t * header, struct employee_t **employeesOut) {
    validate_db_header(fd, &header); // Placeholder call to avoid unused parameter warning
    *employeesOut = (struct employee_t *)malloc(sizeof(struct employee_t) * header->count);
    if (*employeesOut == NULL) {
        return -1; // Memory allocation failure
    }

    ssize_t bytesRead = read(fd, *employeesOut, sizeof(struct employee_t) * header->count);
    if (bytesRead != sizeof(struct employee_t) * header->count) {
        free(*employeesOut);
        return -1; // Read error or incomplete read
    }

    return 0; // Success
}

int output_file(int fd, struct dbheader_t *header, struct employee_t *employees) {
    if (fd < 0 || header == NULL || employees == NULL) {
        return -1; // Invalid argument
    }

    // Write the header
    ssize_t bytesWritten = write(fd, header, sizeof(struct dbheader_t));
    if (bytesWritten != sizeof(struct dbheader_t)) {
        return -1; // Write error
    }

    // Write the employees
    for (unsigned int i = 0; i < header->count; i++) {
        bytesWritten = write(fd, &employees[i], sizeof(struct employee_t));
        if (bytesWritten != sizeof(struct employee_t)) {
            return -1; // Write error
        }
    }

    return 0;
}