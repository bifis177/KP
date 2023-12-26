#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>


#define MAX_OPENINGS 100 // Максимальное количество проемов (окна + двери)

struct OpeningData {
    int width;
    int height;
};

struct BuildingData {
    int blockWidth;
    int blockHeight;
    int wallWidth;
    int wallHeight;
    int numWindows;
    int numDoors;
    struct OpeningData openings[MAX_OPENINGS];
};

int calculateWallArea(const struct BuildingData* data) {
    return data->blockWidth * data->blockHeight * data->wallWidth * data->wallHeight;
}

int calculateOpeningArea(const struct BuildingData* data) {
    int windowArea = 0;
    for (int i = 0; i < data->numWindows; ++i) {
        windowArea += data->openings[i].width * data->openings[i].height;
    }

    int doorArea = 0;
    for (int i = 0; i < data->numDoors; ++i) {
        doorArea += data->openings[data->numWindows + i].width * data->openings[data->numWindows + i].height;
    }

    return windowArea + doorArea;
}

int calculateTotalWallArea(const struct BuildingData* data) {
    int wallArea = calculateWallArea(data);
    int openingArea = calculateOpeningArea(data);
    return wallArea - openingArea;
}

int calculateNumBlocks(const struct BuildingData* data) {
    int totalWallArea = calculateTotalWallArea(data);
    return totalWallArea / (data->blockWidth * data->blockHeight);
}

void writeDataToFile(const char* filename, const struct BuildingData* data, int numBlocks) {
    FILE* file;
    if (fopen_s(&file, filename, "w") == 0) {
        fprintf(file, "Ширина стенового блока: %d см\n", data->blockWidth);
        fprintf(file, "Высота стенового блока: %d см\n", data->blockHeight);
        fprintf(file, "Ширина стены: %d см\n", data->wallWidth);
        fprintf(file, "Высота стены: %d см\n", data->wallHeight);
        fprintf(file, "Количество оконных проемов: %d\n", data->numWindows);
        fprintf(file, "Количество дверных проемов: %d\n", data->numDoors);
        fprintf(file, "Необходимо %d стеновых блоков.\n", numBlocks);

        fclose(file);
    }
    else {
        printf("Ошибка при открытии файла для записи.\n");
    }
}

void displayResult(int numBlocks) {
    printf("Необходимо %d стеновых блоков.\n", numBlocks);
}

void getInput(struct BuildingData* data) {
    printf("Введите ширину стенового блока в см: ");
    scanf("%d", &(data->blockWidth));

    printf("Введите высоту стенового блока в см: ");
    scanf("%d", &(data->blockHeight));

    printf("Введите ширину стены в см: ");
    scanf("%d", &(data->wallWidth));

    printf("Введите высоту стены в см: ");
    scanf("%d", &(data->wallHeight));

    printf("Введите количество оконных проемов: ");
    scanf("%d", &(data->numWindows));

    for (int i = 0; i < data->numWindows; ++i) {
        printf("Введите ширину окна в см для окна %d: ", i + 1);
        scanf("%d", &(data->openings[i].width));

        printf("Введите высоту окна в см для окна %d: ", i + 1);
        scanf("%d", &(data->openings[i].height));
    }

    printf("Введите количество дверных проемов: ");
    scanf("%d", &(data->numDoors));

    for (int i = 0; i < data->numDoors; ++i) {
        printf("Введите ширину двери в см для двери %d: ", i + 1);
        scanf("%d", &(data->openings[data->numWindows + i].width));

        printf("Введите высоту двери в см для двери %d: ", i + 1);
        scanf("%d", &(data->openings[data->numWindows + i].height));
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    struct BuildingData buildingData;
    buildingData.blockWidth = 0;

    int choice;
    do {
        printf("\nГлавное меню:\n");
        printf("1. Ввести данные о здании\n");
        printf("2. Рассчитать и вывести необходимое количество стеновых блоков\n");
        printf("3. Вывести результаты в файл\n");
        printf("4. Выход\n");
        printf("Выберите опцию: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            getInput(&buildingData);
            break;
        case 2:
            if (buildingData.blockWidth == 0) {
                printf("Сначала введите данные о здании (опция 1).\n");
            }
            else {
                int numBlocks = calculateNumBlocks(&buildingData);
                displayResult(numBlocks);
            }
            break;
        case 3:
            if (buildingData.blockWidth == 0) {
                printf("Сначала введите данные о здании (опция 1).\n");
            }
            else {
                int numBlocks = calculateNumBlocks(&buildingData);
                writeDataToFile("building_data.txt", &buildingData, numBlocks);
            }
            break;
        case 4:
            printf("Выход из программы.\n");
            break;
        default:
            printf("Неверный ввод. Пожалуйста, выберите существующую опцию.\n");
        }

    } while (choice != 4);

    return 0;
}
