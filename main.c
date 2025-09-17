#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

static volatile sig_atomic_t running = 1;

void handle_sigint(int sig) { (void)sig; running = 0; }

void hide_cursor(void) { printf("[?25l"); fflush(stdout); }
void show_cursor(void) { printf("[?25h"); fflush(stdout); }

int main(int argc, char **argv) {
    bool use_12h = false;
    bool show_date = false;

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-12") == 0) use_12h = true;
        else if (strcmp(argv[i], "-d") == 0) show_date = true;
        else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            printf("Uso: %s [-12] [-d]\n", argv[0]);
            printf("  -12 : formato 12 horas (com AM/PM)\n");
            printf("  -d  : mostrar data\n");
            return 0;
        } else {
            fprintf(stderr, "Opcao desconhecida: %s\n", argv[i]);
            return 1;
        }
    }

    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handle_sigint;
    sigaction(SIGINT, &sa, NULL);

    hide_cursor();
    printf("[2J[H");

    while (running) {
        struct timespec now_ts;
        clock_gettime(CLOCK_REALTIME, &now_ts);

        time_t t = now_ts.tv_sec;
        struct tm local;
        localtime_r(&t, &local);

        char timebuf[64];
        const char *fmt = use_12h ? "%I:%M:%S %p" : "%H:%M:%S";
        if (strftime(timebuf, sizeof(timebuf), fmt, &local) == 0) strcpy(timebuf, "--:--:--");

        if (show_date) {
            char datebuf[64];
            if (strftime(datebuf, sizeof(datebuf), "%Y-%m-%d", &local) == 0) strcpy(datebuf, "----:--:--");
            printf("\r[2K%s  %s", timebuf, datebuf);
        } else {
            printf("\r[2K%s", timebuf);
        }
        fflush(stdout);

        struct timespec sleep_ts;
        sleep_ts.tv_sec = 0;
        sleep_ts.tv_nsec = 1000000000L - now_ts.tv_nsec;
        if (sleep_ts.tv_nsec >= 1000000000L) sleep_ts.tv_nsec = 0;

        while (running && nanosleep(&sleep_ts, &sleep_ts) == -1) {
            continue;
        }
    }

    show_cursor();
    printf("\n");

    return 0;
}
