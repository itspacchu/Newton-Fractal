#include<iostream>
#include<raylib.h>
#include<vector>
#include<complex>
#include<thread>

#define ComplexNo std::complex<double> 
#define SCREENW 800
#define SCREENH 600
#define DENSITY 0.23
#define STEPSIZE 1

bool is_processing = false;
int IndexCount = 0;

typedef struct RootObj
{
    ComplexNo num;
    ComplexNo original;
    ComplexNo prevPos;
    Color color = WHITE;
    bool toCheck = true;
    bool nearRoot = false;
    int index = -1;
};

ComplexNo cmp(double a, double b)
{
    return ComplexNo(a, b);
}

std::vector<RootObj> points;

Color colors[5] = {(Color){110,60,188,255}, (Color){114,103,203,255}, (Color){152,186,231,255}, (Color){152,186,231,255}, (Color){184,228,240,255}};

ComplexNo OffsetOrigin(ComplexNo num)
{
    ComplexNo origin = {SCREENW/2,SCREENH/2};
    return num - origin;
}

ComplexNo fxnZ(ComplexNo z)
{
    //return 122.45*pow(z,5) + 432.12*pow(z,4) + cmp(123.0,453.2)*pow(z,3) - 120.12*pow(z,2) - 152.12*z - 452.12;
    return pow(z,5) + pow(z,2) - z + cmp(1,0);
}

ComplexNo dfxnZ(ComplexNo z)
{
    //return  122.45*5.0*pow(z,4) + 432.12*4.0*pow(z,3) + cmp(123.0,453.2)*3.0*pow(z,2) - 120.12*2.0*z - 152.12;
    return 5.0*pow(z,4) + 2.0*z - cmp(1,0);
}

ComplexNo newton(ComplexNo z,double stepSize = STEPSIZE)
{
    return z - stepSize * (fxnZ(z)/dfxnZ(z));
}

float GetDistance(ComplexNo a, ComplexNo b)
{
    return sqrt(pow(a.real()-b.real(),2) + pow(a.imag()-b.imag(),2));
}

void GiveColorsToRoots(int chunk=0,int max=0,int chunksize=0){
    is_processing = true;

    int lower = chunk*chunksize;
    int upper = (chunk+1)*chunksize;

    for(int i = lower; i < upper; i++){
        for(int j=0;j<points.size(); j++){
            if(GetDistance(points[i].num, points[j].num) < 1.0){
                if(points[i].index == -1 && points[j].index != -1){
                    points[i].index = points[j].index;
                }
                else if(points[j].index == -1 && points[i].index != -1){
                    points[j].index = points[i].index;
                }
                else if(points[i].index == -1 & points[j].index == -1){
                    points[i].index = IndexCount;
                    points[j].index = IndexCount;
                    IndexCount++;
                }
            }
        }
    }
    for(int i = lower; i < upper; i++){
        points[i].color = colors[points[i].index];
        points[i].num = points[i].original;
    }
    is_processing = false;
}

float Remap(float val, float oldMin, float oldMax, float newMin, float newMax)
{
    return newMin + (newMax - newMin) * ((val - oldMin) / (oldMax - oldMin));
}



int main(){
    float drawScale = 1.0;
    ComplexNo offsetfrom;
    int ITER = 0;
    for(int j=-SCREENH/(2.0); j <SCREENH/(2.0); j+=1/DENSITY)
    {
        for(int i=-SCREENW/2; i<SCREENW/2; i+=1/DENSITY)
        {
            points.push_back(RootObj{ComplexNo(i,j), ComplexNo(i,j)});
        }
    }

    InitWindow(800, 600, "Newton Raphson Method");
    SetTargetFPS(75);
    ClearBackground({25,25,25,255});
    while (!WindowShouldClose()){
        BeginDrawing();
        ClearBackground({25,25,25,255});
        for(int i=0; i<points.size(); i++){
            Color col = points[i].color;
            DrawRectangle(drawScale * points[i].num.real() + SCREENW/2, drawScale * points[i].num.imag() + SCREENH/2, 1/DENSITY, 1/DENSITY,col);
        }
        
        if(IsKeyPressed(KEY_BACKSPACE) && !is_processing){
            for(int i=1; i<50; i++){
                std::thread colorize0(GiveColorsToRoots,i,points.size(),points.size()/50);
                colorize0.detach();
                std::cout << "Thread " << i << " started" << std::endl;
            }

        }
        if(IsKeyDown(KEY_SPACE)){
            for(int i=0; i<points.size(); i++)
            {
                if(GetDistance(points[i].num,points[i].prevPos) < STEPSIZE/5.0)
                {
                    continue;
                }
                points[i].prevPos = points[i].num;
                points[i].num = newton(points[i].num);
            }
            ITER ++;
        }
        int boost = 1.0f;
        if(IsKeyDown(KEY_LEFT_SHIFT)){
            boost = 20.0f;
        }else{
            boost = 1.0f;
        }
        if(IsKeyDown(KEY_UP)){
            drawScale += 0.1*boost;
        }else if(IsKeyDown(KEY_DOWN)){
            drawScale -= 0.1*boost;
        }
        DrawText(TextFormat("Iteration : %d :: Draw Scale : %f :: isProcessing : %d ",ITER,drawScale,is_processing), 20, 20, 20, WHITE);
        EndDrawing();
    }
}