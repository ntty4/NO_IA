#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

#define VERT    "\u2551"
#define HORIZ   "\u2550"
#define END     "\u255A"
#define CROSS   "\u2560"

#define DIR_COLOR(my_dir) \
    "\x1b[91m" my_dir "\x1b[0m"

#define FILE_COLOR(my_dir) \
    "\x1b[92m" my_dir "\x1b[0m"

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

/* there the key for winning is:
 * that we print the END and CORSS for the current element if is the last or not,
 * but in reality we will give to the next directory SPACE or LINE, because:
 *
 * - we are inside a folder that is the last one:
 *   then before the next element we will must print an SPACE
 *   because the father forlder has no more childs to continue
 *
 * - we are inside the a folder that is not the last one:
 *   then before the next element we will must print A VERT 
 *   because the father folder has other childs to continue */

void ntt_rdiropen(const char *dn, const char *prefix);


void ntt_rdiropen(const char *dn, const char *prefix) {
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

        /* actual logic of iteration */
        if (curr.d_type == DT_DIR) { 
            printf("%s%s "DIR_COLOR("%s\n"), prefix, CROSS HORIZ, curr.d_name);
            /* creating the next directory entry */
            char next_dir_name[strlen(dn) + strlen(curr.d_name) + 2];
            snprintf (
                next_dir_name, sizeof(next_dir_name), "%s/%s",dn, curr.d_name
            );

            /* creating the next prefix for the next branch */
            char *this_prefix = VERT "  ";
            char new_prefix[strlen(prefix) + strlen(this_prefix) + 1];
            snprintf (
                new_prefix, sizeof(new_prefix),
                "%s%s", prefix, this_prefix
            );
            /* iterating on the next directory */
            ntt_rdiropen(next_dir_name, new_prefix);
        }
        else { printf("%s%s "FILE_COLOR("%s\n"), prefix, CROSS HORIZ, curr.d_name); }
        curr = *next;
    }
    if (errno != 0) {
        perror("Error with readdir");
        closedir(dir);
        return;
    }
    closedir(dir);

    if (started) {
        switch(curr.d_type) {
            case DT_DIR:
                printf("%s%s "DIR_COLOR("%s\n"), prefix, END HORIZ, curr.d_name); break;
            default:
                printf("%s%s "FILE_COLOR("%s\n"), prefix, END HORIZ, curr.d_name); break;
        }

        if (curr.d_type == DT_DIR) {
            char next_dir_name[strlen(dn) + strlen(curr.d_name) + 2];
            snprintf (
                next_dir_name, sizeof(next_dir_name), "%s/%s",dn, curr.d_name
            );

            char *this_prefix = "   ";
            char new_prefix[strlen(prefix) + strlen(this_prefix) + 1];
            snprintf (
                new_prefix, sizeof(new_prefix),
                "%s%s", prefix, this_prefix
            );

            ntt_rdiropen(next_dir_name, new_prefix);
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) { printf("Must give the name of folder\n"); return 1; }
    printf("%s\n", argv[1]);
    ntt_rdiropen(argv[1],  "");
}
