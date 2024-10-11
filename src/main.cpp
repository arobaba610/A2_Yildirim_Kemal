#include "raylib.h"
#include "Math.h"

// Effectively GL_LINE_LOOP, draws a square given its vertices
void DrawLineLoop(Vector2* points, int pointCount, Color color)
{
    float thickness = 2.0f;
    for (int i = 0; i < pointCount; i++)
    {
        int curr = i;
        int next = (i + 1) % pointCount;  
        Vector2 A = points[curr];
        Vector2 B = points[next];
        DrawLineEx(A, B, thickness, color);
    }
}

// Function to calculate the midpoints between each pair of vertices to generate the next smaller square
void GenerateNextSquare(Vector2* currentSquare, Vector2* nextSquare)
{
    for (int i = 0; i < 4; i++)
    {
        int next = (i + 1) % 4;
        nextSquare[i] = (currentSquare[i] + currentSquare[next]) * 0.5f;  // Calculating  midpoint
    }
}

int main()
{
    InitWindow(800, 800, "Shrinking Squares");
    SetTargetFPS(60);

    //the window dimensions
    float w = GetScreenWidth();
    float h = GetScreenHeight();

    // Define the initial large square
    Vector2 squares[9][4];  // 8 squares + the initial square
    squares[0][0] = { 0.0f, 0.0f };  // Top-left
    squares[0][1] = { w, 0.0f };     // Top-right
    squares[0][2] = { w, h };        // Bottom-right
    squares[0][3] = { 0.0f, h };     // Bottom-left

    // Generate the next squares based on midpoints
    for (int i = 1; i < 9; i++)
    {
        GenerateNextSquare(squares[i - 1], squares[i]);
    }

    // colors for each square
    Color colors[8] = { RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE, VIOLET, LIME };

    while (!WindowShouldClose())  
    {
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw each square in a different color
        for (int i = 0; i < 8; i++)
        {
            DrawLineLoop(squares[i], 4, colors[i]);  // Draw square with 4 vertices
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
