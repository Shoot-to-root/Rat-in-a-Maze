#include <stdio.h>

#define MAX_SIZE 100

int maze[MAX_SIZE][MAX_SIZE];
int visited[MAX_SIZE][MAX_SIZE];

// Function to perform Depth-First Search
int dfs(int row, int col, int rows, int cols) {
    // Check if the current position is outside the maze or a wall
    if (row < 0 || col < 0 || row >= rows || col >= cols || maze[row][col] == 1 || visited[row][col] == 1) {
        return 0;
    }

    // Mark the current position as visited
    visited[row][col] = 1;

    // Check if we have reached the exit
    if (row == rows - 1 && col == cols - 1) {
        return 1;
    }

    // Try moving in all possible directions: up, down, left, right
    if (dfs(row - 1, col, rows, cols) || dfs(row + 1, col, rows, cols) || dfs(row, col - 1, rows, cols) || dfs(row, col + 1, rows, cols)) {
        // Path found
        return 1;
    }

    // If no path is found, mark the current position as not part of the path
    visited[row][col] = 0;
    return 0;
}

int main() {
    int index;
    printf("輸入檔案編號: ");
    scanf("%d", &index);

    char filename[20];
    sprintf(filename, "data%d.txt", index);

    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int rows, cols;
    fscanf(file, "%d,%d", &rows, &cols);
    
    if (rows <= 0 || cols <= 0 || rows > MAX_SIZE || cols > MAX_SIZE) {
        printf("Invalid maze dimensions\n");
        fclose(file);
        return 1;
    }

    printf("Maze size: %dx%d\n", rows, cols);

    // Reading the maze from the file
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            fscanf(file, "%d", &maze[i][j]);
        }
    }

    fclose(file);

    // Printing the maze with borders
    for (int i = 0; i < rows + 2; ++i) {
        for (int j = 0; j < cols + 2; ++j) {
            if (i == 0 || j == 0 || i == rows + 1 || j == cols + 1 || maze[i - 1][j - 1] == 1) {
                printf("# ");  // Wall for border and '1' values
            } else {
                printf("  ");  // Walkable path
            }
        }
        printf("\n");
    }

    // Initialize the visited array
    for (int i = 1; i < MAX_SIZE; ++i) {
        for (int j = 1; j < MAX_SIZE; ++j) {
            visited[i][j] = 0;
        }
    }

    // Perform DFS to find a path
    if (dfs(0, 0, rows, cols)) {
        printf("\nPath is found!\n");

        // Print the maze with the path
        printf("\nMaze size: %dx%d\n", rows, cols);
        for (int i = 0; i < rows + 2; ++i) {
            for (int j = 0; j < cols + 2; ++j) {
                if (i > 0 && j > 0 && visited[i - 1][j - 1]) {
                    printf(". ");  // Print '.' if the cell above and to the left is part of the path
                } else if (i == 0 || j == 0 || i == rows + 1 || j == cols + 1 || maze[i - 1][j - 1] == 1) {
                    printf("# ");  // Print '#' for border and '1' values
                } else {
                    printf("  ");  // Print ' ' for walkable path
                }
            }
            printf("\n");
        }
    } else {
        printf("No path is found.\n");
    }

    return 0;
}
