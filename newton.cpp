#include<raylib.h>
#include<iostream>

int main(){
    InitWindow(800, 600, "[GPU] Newton Solver rewrite");
    Shader NewtonShader = LoadShader(0, "shaders/newton.fs");

    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginShaderMode(NewtonShader);
                DrawRectangle(0, 0, 800, 600, WHITE);
            EndShaderMode();
        EndDrawing();
    }
    std::cout << "Exitting" << std::endl;
}