#include<raylib.h>
#include<iostream>
#include<math.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

int main(){
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "[GPU] Newton Solver rewrite");
    Shader NewtonShader = LoadShader(0, "shaders/newton.fs");

    int iResolution_int = GetShaderLocation(NewtonShader, "iResolution");
    Vector2 iResolution = (Vector2){SCREEN_WIDTH, SCREEN_HEIGHT};
    SetShaderValue(NewtonShader, iResolution_int, &iResolution , SHADER_UNIFORM_VEC2);  

    int iTime_int = GetShaderLocation(NewtonShader, "iTime");
    int roots_int = GetShaderLocation(NewtonShader, "roots");

    while(!WindowShouldClose()){
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginShaderMode(NewtonShader);
                float iTime = GetTime();
                Vector3 roots = {1.69f-sin(iTime*2*PI/20.0), 1.32f-iTime*0.1, -1.0f+iTime*0.1};
                SetShaderValue(NewtonShader, iTime_int, &iTime , SHADER_UNIFORM_FLOAT);  
                SetShaderValue(NewtonShader, roots_int, &roots , SHADER_UNIFORM_VEC3);  
                DrawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITE);
            EndShaderMode();
            DrawFPS(10, 10);
        EndDrawing();
    }
    std::cout << "Exitting" << std::endl;
}