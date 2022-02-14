#include<raylib.h>
#include<iostream>

int main(){
    InitWindow(800, 600, "[GPU] Newton Solver rewrite");
    Shader NewtonShader = LoadShader(0, "shaders/newton.fs");
    int iTime_int = GetShaderLocation(NewtonShader, "iTime");

    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginShaderMode(NewtonShader);
                float iTime = GetTime();
                SetShaderValue(NewtonShader, iTime_int, &iTime , SHADER_UNIFORM_FLOAT);  
                DrawRectangle(0, 0, 800, 600, WHITE);
            EndShaderMode();
        EndDrawing();
    }
    std::cout << "Exitting" << std::endl;
}