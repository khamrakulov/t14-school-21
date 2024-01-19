#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define n_a "n/a\n"

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

void printMenu();
int compareRecords(const void *a, const void *b);
void printRecords(struct Record *records, size_t count);
struct Record *loadRecords(const char *filename, size_t *count);
void saveRecords(const char *filename, struct Record *records, size_t count);
void addAndSortRecord(struct Record *records, size_t *count);

int main(int argc, char *argv[]) {
  // Если количество аргументов не равно 2 выводит ошибку
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    return EXIT_FAILURE;
  }

  const char *filename = argv[1];
  size_t count = 0;
  struct Record *records = loadRecords(filename, &count); // Получение записи

  // Если файл пустой, то возвращаем NULL
  if (!records) {
    printf("%s", n_a);
    return EXIT_SUCCESS;
  }

  // Меню
  int choice;

  do {
    // Вывод меню
    printMenu();
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {
    // Вывод записей
    case 0:
      if (count > 0) {
        printRecords(records, count);
      } else {
        printf("%s", n_a);
      }
      break;
    // Сортировка и вывод
    case 1:
      if (count > 0) {
        qsort(records, count, sizeof(struct Record), compareRecords);
        printRecords(records, count);
      } else {
        printf("%s", n_a);
      }
      break;
    // Добавление и сортировка
    case 2:
      addAndSortRecord(records, &count);
      printRecords(records, count);
      break;
    // Выход
    case 3:
      break;
    default:
      printf("Invalid choice. Try again.\n");
    }

  } while (choice != 3);

  // Сохранение записей
  saveRecords(filename, records, count);

  free(records);

  return EXIT_SUCCESS;
}

// Вывод меню
void printMenu() {
  printf("\nMenu:\n");
  printf("0. Print records\n");
  printf("1. Sort records and print\n");
  printf("2. Add and sort record\n");
  printf("3. Exit\n");
}

int compareRecords(const void *a, const void *b) {
  const struct Record *recordA = (const struct Record *)a;
  const struct Record *recordB = (const struct Record *)b;

  if (recordA->year != recordB->year) {
    return recordA->year - recordB->year;
  }
  if (recordA->month != recordB->month) {
    return recordA->month - recordB->month;
  }
  if (recordA->day != recordB->day) {
    return recordA->day - recordB->day;
  }
  if (recordA->hour != recordB->hour) {
    return recordA->hour - recordB->hour;
  }
  if (recordA->minute != recordB->minute) {
    return recordA->minute - recordB->minute;
  }
  if (recordA->second != recordB->second) {
    return recordA->second - recordB->second;
  }

  return recordA->status - recordB->status;
}

void printRecords(struct Record *records, size_t count) {
  for (size_t i = 0; i < count; ++i) {
    printf("%d-%02d-%02d %02d:%02d:%02d  Status: %d  Code: %d\n",
           records[i].year, records[i].month, records[i].day, records[i].hour,
           records[i].minute, records[i].second, records[i].status,
           records[i].code);
  }
}

// Функция для получения записи из файла
struct Record *loadRecords(const char *filename, size_t *count) {
  FILE *file = fopen(filename, "rb");
  if (!file) {
    perror("Unable to open file");
    exit(EXIT_FAILURE);
  }

  // Получение размера файла
  fseek(file, 0, SEEK_END);
  long fileSize = ftell(file);
  fseek(file, 0, SEEK_SET);

  // Если файл пустой, то возвращаем NULL
  if (fileSize <= 0) {
    fclose(file);
    return NULL;
  }

  // Количество записей в файле
  *count = fileSize / sizeof(struct Record);

  struct Record *records = (struct Record *)malloc(fileSize);
  if (!records) {
    perror("Memory allocation error");
    exit(EXIT_FAILURE);
  }

  // Чтение записей из файла
  fread(records, sizeof(struct Record), *count, file);

  fclose(file);
  return records;
}

void saveRecords(const char *filename, struct Record *records, size_t count) {
  FILE *file = fopen(filename, "wb");
  if (!file) {
    perror("Unable to open file");
    exit(EXIT_FAILURE);
  }

  fwrite(records, sizeof(struct Record), count, file);

  fclose(file);
}

void addAndSortRecord(struct Record *records, size_t *count) {
  (*count)++;
  // Переделение памяти
  records = (struct Record *)realloc(records, (*count) * sizeof(struct Record));
  if (!records) {
    perror("Memory allocation error");
    exit(EXIT_FAILURE);
  }

  // Добавление записи
  printf("Enter year, month, day, hour, minute, second, status, code "
         "(space-separated): ");
  scanf("%d %d %d %d %d %d %d %d", &records[*count - 1].year,
        &records[*count - 1].month, &records[*count - 1].day,
        &records[*count - 1].hour, &records[*count - 1].minute,
        &records[*count - 1].second, &records[*count - 1].status,
        &records[*count - 1].code);

  qsort(records, *count, sizeof(struct Record), compareRecords);
}