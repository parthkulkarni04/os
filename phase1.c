#include <stdio.h>

// Declare the main_memory array
char main_memory[100][4];

int main() {
    // Open the input file
    FILE *file = fopen("/input1.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read lines from the file
    char line[256];
    int current_row = 0;
    int current_col = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (line[0] == '$' && line[1] == 'A' && line[2] == 'M' && line[3] == 'J') {
            continue;
        } else if (line[0] == '$' && line[1] == 'D' && line[2] == 'T' && line[3] == 'A') {
            current_row = 10;
            current_col = 0;
            continue;
        } else if (line[0] == '$' && line[1] == 'E' && line[2] == 'N' && line[3] == 'D') {
            break;
        }

        // Read characters from the line and store them in main_memory
        for (int i = 0; line[i] != '\0' && line[i] != '\n'; ++i) {
            main_memory[current_row][current_col] = line[i];
            current_col += 1;
            if (current_col == 4) {
                current_col = 0;
                current_row += 1;
            }
        }
    }

    // Close the file
    fclose(file);

    // Print the contents of main_memory
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 4; ++j) {
            printf("%c ", main_memory[i][j]);
        }
        printf("\n");
    }

    // Initialize variables
    int SI = 0;
    int current_column = 0;
    current_row = 0;

    // Loop through each row of main_memory
    while (current_row < 100) {
        if (current_column == 0) {
            char content[3];
            content[0] = main_memory[current_row][0];
            content[1] = main_memory[current_row][1];
            content[2] = '\0';

            if (strcmp(content, "GD") == 0) {
                SI = 1;
            } else if (strcmp(content, "PD") == 0) {
                SI = 2;
            } else if (strcmp(content, "H") == 0) {
                SI = 3;
            }

            current_column += 1;
        } else if (SI == 1) {
            // Get data from row located at current_row + 9
            char *data_row = main_memory[current_row + 9];
            // printf("%s", data_row);
            SI = 0;
            current_column = 0;
            current_row += 1;
        } else if (SI == 2) {
            // Print data from row located at current_row + 9
            char *data_row = main_memory[current_row + 9];
            printf("%s\n", data_row);
            SI = 0;
            current_column = 0;
            current_row += 1;
        } else if (SI == 3) {
            // Print two blank lines
            printf("\n\n");
            SI = 0;
            current_column = 0;
            current_row += 1;
        } else {
            current_column = 0;
            current_row += 1;
        }
    }

    return 0;
}