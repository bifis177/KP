#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <locale.h>


#define MAX_OPENINGS 100 // ������������ ���������� ������� (���� + �����)

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
        fprintf(file, "������ ��������� �����: %d ��\n", data->blockWidth);
        fprintf(file, "������ ��������� �����: %d ��\n", data->blockHeight);
        fprintf(file, "������ �����: %d ��\n", data->wallWidth);
        fprintf(file, "������ �����: %d ��\n", data->wallHeight);
        fprintf(file, "���������� ������� �������: %d\n", data->numWindows);
        fprintf(file, "���������� ������� �������: %d\n", data->numDoors);
        fprintf(file, "���������� %d �������� ������.\n", numBlocks);

        fclose(file);
    }
    else {
        printf("������ ��� �������� ����� ��� ������.\n");
    }
}

void displayResult(int numBlocks) {
    printf("���������� %d �������� ������.\n", numBlocks);
}

void getInput(struct BuildingData* data) {
    printf("������� ������ ��������� ����� � ��: ");
    scanf("%d", &(data->blockWidth));

    printf("������� ������ ��������� ����� � ��: ");
    scanf("%d", &(data->blockHeight));

    printf("������� ������ ����� � ��: ");
    scanf("%d", &(data->wallWidth));

    printf("������� ������ ����� � ��: ");
    scanf("%d", &(data->wallHeight));

    printf("������� ���������� ������� �������: ");
    scanf("%d", &(data->numWindows));

    for (int i = 0; i < data->numWindows; ++i) {
        printf("������� ������ ���� � �� ��� ���� %d: ", i + 1);
        scanf("%d", &(data->openings[i].width));

        printf("������� ������ ���� � �� ��� ���� %d: ", i + 1);
        scanf("%d", &(data->openings[i].height));
    }

    printf("������� ���������� ������� �������: ");
    scanf("%d", &(data->numDoors));

    for (int i = 0; i < data->numDoors; ++i) {
        printf("������� ������ ����� � �� ��� ����� %d: ", i + 1);
        scanf("%d", &(data->openings[data->numWindows + i].width));

        printf("������� ������ ����� � �� ��� ����� %d: ", i + 1);
        scanf("%d", &(data->openings[data->numWindows + i].height));
    }
}

int main() {
    setlocale(LC_ALL, "ru");
    struct BuildingData buildingData;
    buildingData.blockWidth = 0;

    int choice;
    do {
        printf("\n������� ����:\n");
        printf("1. ������ ������ � ������\n");
        printf("2. ���������� � ������� ����������� ���������� �������� ������\n");
        printf("3. ������� ���������� � ����\n");
        printf("4. �����\n");
        printf("�������� �����: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            getInput(&buildingData);
            break;
        case 2:
            if (buildingData.blockWidth == 0) {
                printf("������� ������� ������ � ������ (����� 1).\n");
            }
            else {
                int numBlocks = calculateNumBlocks(&buildingData);
                displayResult(numBlocks);
            }
            break;
        case 3:
            if (buildingData.blockWidth == 0) {
                printf("������� ������� ������ � ������ (����� 1).\n");
            }
            else {
                int numBlocks = calculateNumBlocks(&buildingData);
                writeDataToFile("building_data.txt", &buildingData, numBlocks);
            }
            break;
        case 4:
            printf("����� �� ���������.\n");
            break;
        default:
            printf("�������� ����. ����������, �������� ������������ �����.\n");
        }

    } while (choice != 4);

    return 0;
}
