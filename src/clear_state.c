#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Record {
    int year, month, day, hour, minute, second, status, code;
};

void print_usage() {
    printf("Usage: Quest_3 <file_path> <start_date> <end_date>\n");
}

int is_in_time_range(struct Record *record, char *start_date, char *end_date) {
    // Парсинг дат из строк в структуры времени
    struct tm start_tm, end_tm, record_tm;
    memset(&start_tm, 0, sizeof(struct tm));
    memset(&end_tm, 0, sizeof(struct tm));
    memset(&record_tm, 0, sizeof(struct tm));

    if (sscanf(start_date, "%d.%d.%d", &start_tm.tm_mday, &start_tm.tm_mon, &start_tm.tm_year) != 3 ||
        sscanf(end_date, "%d.%d.%d", &end_tm.tm_mday, &end_tm.tm_mon, &end_tm.tm_year) != 3) {
        return 0;
    }

    start_tm.tm_year -= 1900;
    end_tm.tm_year -= 1900;

    start_tm.tm_hour = start_tm.tm_min = start_tm.tm_sec = 0;
    end_tm.tm_hour = end_tm.tm_min = end_tm.tm_sec = 0;

    record_tm.tm_year = record->year - 1900;
    record_tm.tm_mon = record->month - 1;
    record_tm.tm_mday = record->day;
    record_tm.tm_hour = record->hour;
    record_tm.tm_min = record->minute;
    record_tm.tm_sec = record->second;

    return (difftime(mktime(&record_tm), mktime(&start_tm)) >= 0 &&
            difftime(mktime(&record_tm), mktime(&end_tm)) <= 0);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        print_usage();
        return 1;
    }

    char *file_path = argv[1];
    char *start_date = argv[2];
    char *end_date = argv[3];

    FILE *file = fopen(file_path, "rb");
    if (!file) {
        printf("n/a\n");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    if (file_size == 0) {
        printf("n/a\n");
        fclose(file);
        return 1;
    }

    struct Record *records = (struct Record *)malloc(file_size);
    if (!records) {
        fclose(file);
        return 1;
    }

    fread(records, 1, file_size, file);
    fclose(file);

    int new_size = 0;

    for (long unsigned int i = 0; i < file_size / sizeof(struct Record); i++) {
        if (!is_in_time_range(&records[i], start_date, end_date)) {
            records[new_size++] = records[i];
        }
    }

    file = fopen(file_path, "wb");
    if (!file) {
        free(records);
        return 1;
    }

    fwrite(records, sizeof(struct Record), new_size, file);
    fclose(file);

    free(records);

    return 0;
}
