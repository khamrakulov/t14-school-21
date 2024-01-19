#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Record {
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;
    int status;
    int code;
};

int searchRecordByDate(const char *filename, const char *searchDate, struct Record *foundRecord);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <filename> <searchDate>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    char *date = argv[2];

    struct Record foundRecord;

    if (!searchRecordByDate(filename, date, &foundRecord)) {
        printf("n/a");
        return EXIT_SUCCESS;
    }

    printf("%d", foundRecord.code);

    return EXIT_SUCCESS;
}

int searchRecordByDate(const char *filename, const char *searchDate, struct Record *foundRecord) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Unable to open file");
        return 0;
    }

    while (fread(foundRecord, sizeof(struct Record), 1, file) == 1) {
        char dateStr[20];
        // Форматирование даты
        sprintf(dateStr, "%02d.%02d.%04d", foundRecord->day, foundRecord->month, foundRecord->year);

        if (strcmp(dateStr, searchDate) == 0) {
            fclose(file);
            return 1;  // Если запись найдена, то возвращаем 1
        }
    }

    fclose(file);
    return 0;  // Если запись не найдена, то возвращаем 0
}