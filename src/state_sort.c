#include <stdio.h>
#include <stdlib.h>

// Структура для представления записи
struct Record {
    int year, month, day, hour, minute, second, status, code;
};

int readRecord(FILE *file, struct Record *record);
void writeRecord(FILE *file, const struct Record *record);
void printRecord(const struct Record *record);
void printFile(const char *filename);
int compareRecords(const void *a, const void *b);
void sortRecords(const char *filename);
void addRecord(const char *filename, const struct Record *newRecord);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    int choice;

    do {
        printf("Menu:\n");
        printf("0 - Print file content\n");
        printf("1 - Sort and print file content\n");
        printf("2 - Add record, sort, and print file content\n");
        printf("3 - Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 0:
                printFile(filename);
                break;

            case 1:
                sortRecords(filename);
                printFile(filename);
                break;

            case 2: {
                struct Record newRecord;
                printf("Enter new record details (year month day hour minute second status code):\n");
                scanf("%d %d %d %d %d %d %d %d", &newRecord.year, &newRecord.month, &newRecord.day,
                      &newRecord.hour, &newRecord.minute, &newRecord.second, &newRecord.status,
                      &newRecord.code);

                addRecord(filename, &newRecord);
                sortRecords(filename);
                printFile(filename);
                break;
            }

            case 3:
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 3);

    return 0;
}

// Функция для чтения записи из файла
int readRecord(FILE *file, struct Record *record) { return fread(record, sizeof(struct Record), 1, file); }

// Функция для записи записи в файл
void writeRecord(FILE *file, const struct Record *record) { fwrite(record, sizeof(struct Record), 1, file); }

// Функция для вывода записи в консоль
void printRecord(const struct Record *record) {
    printf("%04d-%02d-%02d %02d:%02d:%02d Status: %d Code: %d\n", record->year, record->month, record->day,
           record->hour, record->minute, record->second, record->status, record->code);
}

// Функция для сравнения двух записей по дате и времени
int compareRecords(const void *a, const void *b) {
    const struct Record *recordA = (const struct Record *)a;
    const struct Record *recordB = (const struct Record *)b;

    // Сравниваем по году, месяцу, дню, часу, минуте, секунде
    if (recordA->year != recordB->year) return recordA->year - recordB->year;
    if (recordA->month != recordB->month) return recordA->month - recordB->month;
    if (recordA->day != recordB->day) return recordA->day - recordB->day;
    if (recordA->hour != recordB->hour) return recordA->hour - recordB->hour;
    if (recordA->minute != recordB->minute) return recordA->minute - recordB->minute;
    if (recordA->second != recordB->second) return recordA->second - recordB->second;

    return 0;  // Записи одинаковые по дате и времени
}

// Функция для сортировки записей в файле
void sortRecords(const char *filename) {
    FILE *file = fopen(filename, "rb+");
    if (!file) {
        printf("n/a\n");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    if (fileSize == 0) {
        printf("n/a\n");
        fclose(file);
        return;
    }

    fseek(file, 0, SEEK_SET);

    size_t recordCount = fileSize / sizeof(struct Record);
    struct Record *records = malloc(fileSize);

    if (!records) {
        printf("n/a\n");
        fclose(file);
        return;
    }

    fread(records, sizeof(struct Record), recordCount, file);
    qsort(records, recordCount, sizeof(struct Record), compareRecords);

    fseek(file, 0, SEEK_SET);
    fwrite(records, sizeof(struct Record), recordCount, file);

    free(records);
    fclose(file);
}

// Функция для добавления записи в файл
void addRecord(const char *filename, const struct Record *newRecord) {
    FILE *file = fopen(filename, "ab");
    if (!file) {
        printf("n/a\n");
        return;
    }

    writeRecord(file, newRecord);
    fclose(file);
}

// Функция для вывода содержимого файла в консоль
void printFile(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("n/a\n");
        return;
    }

    struct Record record;

    while (readRecord(file, &record)) {
        printRecord(&record);
    }

    fclose(file);
}