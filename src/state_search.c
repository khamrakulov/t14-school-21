#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Record {
    int year, month, day, hour, minute, second, status, code;
};

#define DATE_LENGTH 11

void searchDateInFile(const char *filename, const char *searchDate);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <searchDate>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    const char *searchDate = argv[2];

    searchDateInFile(filename, searchDate);

    return EXIT_SUCCESS;
}

void searchDateInFile(const char *filename, const char *searchDate) {
    FILE *file = fopen(filename, "rb");

    if (file == NULL) {
        fprintf(stderr, "Error: Unable to open the file '%s'\n", filename);
        exit(EXIT_FAILURE);
    }

    struct Record record;
    size_t recordsRead;

    while ((recordsRead = fread(&record, sizeof(struct Record), 1, file)) == 1) {
        char buffer[DATE_LENGTH];
        // Форматирование даты в формат "дд.мм.гггг"
        snprintf(buffer, sizeof(buffer), "%02d.%02d.%04d", record.day, record.month, record.year);

        if (strcmp(buffer, searchDate) == 0) {
            printf("%s\n", buffer);
            fclose(file);
            return;
        }
    }

    if (feof(file)) {
        printf("n/a\n");
    } else if (ferror(file)) {
        perror("Error reading file");
    }

    fclose(file);
}