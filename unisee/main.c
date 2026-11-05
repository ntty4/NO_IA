#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

#define TABLE_HEIGHT    6
#define TABLE_WIDTH     6
#define CELLEN          6

#define TABLE_HEAD(name) \
    "\x1b[38;5;96m"name"\x1b[0m"

const char *table[TABLE_HEIGHT][TABLE_WIDTH] = {
    { "TIME", "MON", "TUE", "WED", "THU", "FRI" },
    { "1PM", "BDD", "OS", "ALG1", "ALG1", "OS" },
    { "2PM", "BDD", "OS", "ALG1", "ALG1", "OS" },
    { "3PM", "AR1", "BDD", "ALG1", "OS", "ALG1" },
    { "4PM", "AR1", "BDD", "BDD", "OS", "ALG1" },
    { "5PM", "AR1", "BDD", "BDD", "OS", "NONE" },
};

void print_line(void) {
    for(int i = 0; i < TABLE_WIDTH; i++) {
        printf("*");
        for (int j = 0; j < CELLEN; j++) {
            printf("-");
        }
    }
    printf("*\n");
}

static void helper_print_row(size_t row, size_t i) {
    size_t len = strlen(table[row][i]);
    size_t left_padding = (CELLEN - len) / 2;
    putchar('|');
    for(size_t j = 0; j < left_padding; j++) { putchar(' '); }
    row == 0 ? printf(TABLE_HEAD("%s"), table[row][i]) : printf("%s", table[row][i]);
    for(size_t j = 0; j < CELLEN-(len+left_padding); j++) { putchar(' '); }
}

static void print_row(size_t row) {
    for(size_t i = 0; i < TABLE_WIDTH; i++)
        { helper_print_row(row, i);}
    printf("|\n");
    if (row == 0) { print_line(); }
}

void print_table(void) {
    print_line();
    for(int i = 0; i < TABLE_HEIGHT; i++) {
        print_row(i);
    }
}

int main(void) {
    print_table();
}
