#include <stdlib.h>  // exit
#include <stdio.h>
#include <sys/uio.h> // readv writev
#include <fcntl.h>   // open O_RDONLY
#include <string.h>  // strncpy


/**
 * Transfer multiple buffers of data in a single system call.
 *
 * The array iov defines the set of buffers to be transferred. Each element is
 * an iovec struct:
 *
 *     struct iovec {
 *       void *iov_base;    // Start address of buffer
 *       size_t iov_len;    // Number of bytes to transfer to/from buffer
 *     }
 */

/**
 * readv reads a contiguous sequence of bytes from a file and places these bytes
 * into the specified buffers ("scatter input"). Each buffer (starting with
 * iov[0]) is completely filled before moving to the next one.
 *
 * One can be sure that the range of bytes read is contiguous even if another
 * process attempts to manipulate the offset at the same time, because the
 * kernel peforms a single data transfer between the file and user memory.
 */
void sgio_read() {
    puts("START -sgio read\n");

    #define NUMBER_OF_BUFFERS 2

    puts("    Allocating buffers...\n");
    #define BUF1_SIZE 5
    #define BUF2_SIZE 3
    struct iovec iov[2]; // An array of 2 buffers.
    ssize_t requestedBytes = 0;

    char str1[BUF1_SIZE];
    char str2[BUF2_SIZE];

    iov[0].iov_base = str1;
    iov[0].iov_len = BUF1_SIZE;
    requestedBytes += iov[0].iov_len;

    iov[1].iov_base = str2;
    iov[1].iov_len = BUF2_SIZE;
    requestedBytes += iov[1].iov_len;

    int fd = open("sample_text.txt", O_RDONLY);
        if (fd == -1) exit(1);

    /**
     * Returns number of bytes read, 0 on EOF, or -1 on error.
     */
    ssize_t bytesRead = readv(fd, iov, NUMBER_OF_BUFFERS);
    if (bytesRead == -1) {
        puts("ERROR: readv failed.");
        exit(1);
    }

    if (bytesRead < requestedBytes) puts("Read fewer bytes than requested.");

    char buf1Str[iov[0].iov_len + 1];
    strncpy(buf1Str, iov[0].iov_base, iov[0].iov_len);
    buf1Str[iov[0].iov_len] = '\0';

    char buf2Str[iov[1].iov_len + 1];
    strncpy(buf2Str, iov[1].iov_base, iov[1].iov_len);
    buf2Str[iov[1].iov_len] = '\0';

    puts("    ---");
    printf("    BUF1 contents: %s|\n", buf1Str);
    printf("    BUF2 contents: %s|\n", buf2Str);
    puts("    ---\n");

    printf("    Bytes requested: %ld\n    Bytes read: %ld\nEND -sgio read\n\n",
           (long) requestedBytes, (long) bytesRead);
}
