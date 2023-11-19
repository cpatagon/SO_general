#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#define FIFO_PATH "/tmp/myfifo"

// Manejador de señales
void signal_handler(int signum) {
    int fd;
    char *sign_msg;

    if (signum == SIGUSR1) {
        sign_msg = "SIGN:1\n";
    } else if (signum == SIGUSR2) {
        sign_msg = "SIGN:2\n";
    }

    fd = open(FIFO_PATH, O_WRONLY);
    write(fd, sign_msg, strlen(sign_msg));
    close(fd);
}

int main() {
    int fd;
    char input[100];

    // Crear el FIFO
    mkfifo(FIFO_PATH, 0666);

    // Configurar los manejadores de señales
    signal(SIGUSR1, signal_handler);
    signal(SIGUSR2, signal_handler);

    while (1) {
        // Leer entrada del usuario
        fgets(input, 100, stdin);

        // Escribir en el FIFO
        fd = open(FIFO_PATH, O_WRONLY);
        write(fd, "DATA:", 5);
        write(fd, input, strlen(input));
        close(fd);
    }

    return 0;
}
