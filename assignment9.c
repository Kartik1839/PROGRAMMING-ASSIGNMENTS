#include <stdio.h>
#include <stdlib.h>

int main() {
    char source_path[256], dest_path[256];
    FILE *src_file, *dest_file;
    int ch;

    printf("Enter source file name: ");
    if (scanf("%255s", source_path) != 1) {
        return 1;
    }

    printf("Enter destination file name: ");
    if (scanf("%255s", dest_path) != 1) {
        return 1;
    }

    // Open source file in read mode
    src_file = fopen(source_path, "r");
    if (src_file == NULL) {
        perror("Error opening source file");
        return 1;
    }

    // Open (or create) destination file in write mode
    dest_file = fopen(dest_path, "w");
    if (dest_file == NULL) {
        perror("Error opening destination file");
        fclose(src_file);
        return 1;
    }

    // Read character by character until EOF and write to destination file
    while ((ch = fgetc(src_file)) != EOF) {
        if (fputc(ch, dest_file) == EOF) {
            perror("Error writing to destination file");
            fclose(src_file);
            fclose(dest_file);
            return 1;
        }
    }

    printf("File copied successfully from '%s' to '%s'.\n", source_path, dest_path);

    fclose(src_file);
    fclose(dest_file);

    return 0;
}
