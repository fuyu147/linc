#include <stddef.h>

#include "raylib.h"

int main()
{
        InitWindow(300, 300, "linc");
        SetExitKey(KEY_Q);

        SetConfigFlags(FLAG_WINDOW_RESIZABLE);

        while (!WindowShouldClose())
        {
                BeginDrawing();

                ClearBackground(BEIGE);
                DrawText("Hey", 30, 30, 30, PURPLE);

                EndDrawing();
        }

        return 0;
}
