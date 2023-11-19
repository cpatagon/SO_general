#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FIFO_PATH "/tmp/myfifo"

int main() {
    int fd;
    char buffer[100];

    // Abrir el FIFO
    fd = open(FIFO_PATH, O_RDONLY);

    while (1) {
        // Leer del FIFO
        if (read(fd, buffer, 100) > 0) {
            if (strncmp(buffer, "DATA:", 5) == 0) {
                // Escribir en log.txt
                FILE *flog = fopen("log.txt", "a");
                fputs(buffer + 5, flog);
                fclose(flog);
            } else if (strncmp(buffer, "SIGN:", 5) == 0) {
                // Escribir en signals.txt
                FILE *fsignal = fopen("signals.txt", "a");
                fputs(buffer + 5, fsignal);
                fclose(fsignal);
            }
        }
    }

    close(fd);

    return 0;
}
