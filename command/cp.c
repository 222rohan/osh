#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

// Function to copy a file
void copy_file(const char *source, const char *destination, int force, int verbose) {
    if (verbose) {
        printf("Copying file: %s to %s\n", source, destination);
    }

    if (!force && access(destination, F_OK) != -1) {
        printf("File %s already exists. Use -f to force overwrite.\n", destination);
        return;
    }

    FILE *src = fopen(source, "rb");
    FILE *dest = fopen(destination, "wb");

    if (!src || !dest) {
        perror("Error opening files");
        if (src) fclose(src);
        if (dest) fclose(dest);
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    size_t bytesRead;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), src)) > 0) {
        fwrite(buffer, 1, bytesRead, dest);
    }

    fclose(src);
    fclose(dest);
}

void copy_directory(const char *source_dir, const char *dest_dir, int force, int verbose) {
    if (verbose) {
        printf("Copying directory: %s to %s\n", source_dir, dest_dir);
    }

    DIR *dir = opendir(source_dir);
    if (!dir) {
        perror("Error opening source directory");
        exit(EXIT_FAILURE);
    }

    if (mkdir(dest_dir, 0755) == -1) {
        if (access(dest_dir, F_OK) == -1) {
            perror("Error creating destination directory");
            closedir(dir);
            exit(EXIT_FAILURE);
        }
    }

    struct dirent *entry;
    char source_path[1024], dest_path[1024];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        snprintf(source_path, sizeof(source_path), "%s/%s", source_dir, entry->d_name);
        snprintf(dest_path, sizeof(dest_path), "%s/%s", dest_dir, entry->d_name);

        if (entry->d_type == DT_DIR) {
            copy_directory(source_path, dest_path, force, verbose);
        }
        else if (entry->d_type == DT_REG) {
            copy_file(source_path, dest_path, force, verbose);
        }
    }

    closedir(dir);
}

void print_usage(const char *program_name) {
    printf("Usage: %s [options] <source> <destination>\n", program_name);
    printf("Options:\n");
    printf("  -r, --recursive    Copy directories recursively\n");
    printf("  -f, --force        Force overwrite of existing files\n");
    printf("  -v, --verbose      Enable verbose output\n");
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        print_usage(argv[0]);
        return 1;
    }

    int force = 0;
    int verbose = 0;
    int recursive = 1; 


    for (int i = 1; i < argc - 2; ++i) {
        if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "--recursive") == 0) {
            recursive = 1;
        }
        else if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--force") == 0) {
            force = 1;
        }
        else if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0) {
            verbose = 1;
        }
        else {
            print_usage(argv[0]);
            return 1;
        }
    }

    const char *source = argv[argc - 2];
    const char *destination = argv[argc - 1];

    struct stat statbuf;

    if (stat(source, &statbuf) == -1) {
        perror("Error checking source");
        return 1;
    }

    if (S_ISDIR(statbuf.st_mode)) {
        if (!recursive) {
            printf("Source is a directory, but -r flag is not set. Aborting...\n");
            return 1;
        }
        copy_directory(source, destination, force, verbose);
    }
    else if (S_ISREG(statbuf.st_mode)) {
        copy_file(source, destination, force, verbose);
    }
    else {
        printf("Source is neither a regular file nor a directory\n");
        return 1;
    }

    printf("Successfully copied from %s to %s\n", source, destination);
    return 0;
}
