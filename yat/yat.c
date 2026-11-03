#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#define VERT    "\u2551"
#define HORIZ   "\u2550"
#define END     "\u255A"
#define CROSS   "\u2560"

/*
 * we have 4 types of configurations:
 *
 * 1. VERT END HORIZ
 * 2. VERT CROSS HORIZ
 *
 * 3. SPACE CROSS HORIZ
 * 4. SPACE END HORIZ
 *
 * the 1 implies that we are not at the end of the father but
 * at the end of the children
 *
 * the 2 implies that we are not at the end of the father and
 * not at the end of the children
 *
 * the 3 implies that we are at the end of the father but not
 * of the children
 *
 * the 4 imppies that we are at the end of the father and at
 * the end of the children
 */

void ntt_rdiropen(const char *dn, const char *prefix, int is_last);

void ntt_rdraw(const char *dn, const char *prefix,
        const struct dirent *curr, int is_last) {

    char next_dir_name[strlen(dn) + strlen(curr->d_name) + 2];
    snprintf (
        next_dir_name, sizeof(next_dir_name),
        "%s/%s",dn, curr->d_name
    );

    char new_prefix[strlen(prefix) + strlen(is_last ? END HORIZ " " : CROSS HORIZ" ") + 1];
    snprintf (
        new_prefix, sizeof(new_prefix),
        "%s%s", prefix, is_last ? END HORIZ " " : CROSS HORIZ"  "
    );
    ntt_rdiropen(next_dir_name, new_prefix, 0);
}

void ntt_rdiropen(const char *dn, const char *prefix, int is_last) {
    DIR *dir = opendir(dn);
    if (!dir) { return; }

    struct dirent *next = NULL;
    struct dirent curr;
    int started = 0;

    for (;;) {
        errno = 0;
        next = readdir(dir);

        /* conditions for kipping the iteration */
        if (next == NULL) { break; }
        if (strcmp(next->d_name, ".") == 0 ||
            strcmp(next->d_name, "..") == 0) { continue; }
        if (started == 0) { started = 1; curr = *next; continue; }

        if (curr.d_type == DT_DIR) {
            printf("%s %s\n", prefix, curr.d_name);
            ntt_rdraw
        }
        curr = *next;
    }

    if (started) {
        if (curr.d_type == DT_DIR) {
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) { printf("Must give the name of folder\n"); return 1; }
    ntt_rdiropen(argv[1],  "", 0);
}
