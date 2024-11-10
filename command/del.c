#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

void delete_file(const char *file_path, int verbose) {
    if (verbose) {
        printf("Deleting file: %s\n", file_path);
    }

    if (remove(file_path) != 0) {
        perror("Error deleting file");
    }
}

void delete_directory(const char *directory_path, int verbose) {
    DIR *dir = opendir(directory_path);
    if (!dir) {
        perror("Error opening directory for deletion");
        return;
    }

    struct dirent *entry;
    char path[1024];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        snprintf(path, sizeof(path), "%s/%s", directory_path, entry->d_name);

        if (entry->d_type == DT_DIR) {
            delete_directory(path, verbose);
        } else {
            delete_file(path, verbose);
        }
    }

    closedir(dir);

    if (verbose) {
        printf("Deleting directory: %s\n", directory_path);
    }

    if (rmdir(directory_path) != 0) {
        perror("Error deleting directory");
    }
}

void print_usage(const char *program_name) {
    printf("Usage: %s [options] <path>\n", program_name);
    printf("Options:\n");
    printf("  -v, --verbose      Enable verbose output\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    int verbose = 0;

    for (int i = 1; i < argc - 1; ++i) {
        if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
            verbose = 1;
        } else {
            print_usage(argv[0]);
            return 1;
        }
    }

    const char *path = argv[argc - 1];

    struct stat statbuf;

    if (stat(path, &statbuf) == -1) {
        perror("Error checking path");
        return 1;
    }

    if (S_ISDIR(statbuf.st_mode)) {
        delete_directory(path, verbose);
    }
    else if (S_ISREG(statbuf.st_mode)) {
        delete_file(path, verbose);
    }
    else {
        printf("Specified path is neither a regular file nor a directory\n");
        return 1;
    }

    printf("Successfully deleted %s\n", path);
    return 0;
}
