#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int width = 140;
int height = 40;

void printAt(char character, int row,int column, char *buffer);
void printLine(int x1, int y1, int x2, int y2, char *buffer);
void printScreen(char *buffer, char *clean);
void projection(int x, int y, int z, int *px, int *py);

int main(){
    char *screenBuffer = malloc((height * width + 1) * sizeof(char));
    memset(screenBuffer,' ',height* width * sizeof(char));
    screenBuffer[height * width] = '\0';
    char *screenBufferClean = malloc((height * width + 1) * sizeof(char));
    strcpy(screenBufferClean,screenBuffer);
    // CMD commands
    system("cls");
    system("mode 140,40");
    // end CMD commands
    printf("%c]0;Print line%c%c",27,27,'\\');

    printLine(-4,5,10,10,screenBuffer);
    printLine(10,10,8,25,screenBuffer);
    printLine(8,25,-4,5,screenBuffer);
    printScreen(screenBuffer,screenBufferClean);
    usleep(1000000);

    //printLine(2,2,2,4,screenBuffer);
    //printScreen(screenBuffer,screenBufferClean);

    int *x1 = malloc(1*sizeof(int));
    int *y1 = malloc(1*sizeof(int));
    int *x2 = malloc(1*sizeof(int));
    int *y2 = malloc(1*sizeof(int));
    //Cubo 1
    projection(100,100,13,x1,y1);
    projection(100,500,13,x2,y2);
    printLine(*x1,*y1,*x2,*y2,screenBuffer);
    projection(500,500,13,x1,y1);
    printLine(*x1,*y1,*x2,*y2,screenBuffer);
    projection(500,100,13,x2,y2);
    printLine(*x1,*y1,*x2,*y2,screenBuffer);
    projection(100,100,13,x1,y1);
    printLine(*x1,*y1,*x2,*y2,screenBuffer);

    projection(100,100,23,x1,y1);
    projection(100,500,23,x2,y2);
    printLine(*x1,*y1,*x2,*y2,screenBuffer);
    projection(500,500,23,x1,y1);
    printLine(*x1,*y1,*x2,*y2,screenBuffer);
    projection(500,100,23,x2,y2);
    printLine(*x1,*y1,*x2,*y2,screenBuffer);
    projection(100,100,23,x1,y1);
    printLine(*x1,*y1,*x2,*y2,screenBuffer);

    projection(100,100,13,x1,y1);
    projection(100,100,23,x2,y2);
    printLine(*x1,*y1,*x2,*y2,screenBuffer);
    projection(100,500,13,x1,y1);
    projection(100,500,23,x2,y2);
    printLine(*x1,*y1,*x2,*y2,screenBuffer);
    projection(500,500,13,x1,y1);
    projection(500,500,23,x2,y2);
    printLine(*x1,*y1,*x2,*y2,screenBuffer);
    projection(500,100,13,x1,y1);
    projection(500,100,23,x2,y2);
    printLine(*x1,*y1,*x2,*y2,screenBuffer);
    //Fin cubo 1

    //Cubo 2
    projection(-50,-50,10,x1,y1);
    projection(-50,-250,10,x2,y2);
    printLine(*x1,*y1,*x2,*y2,screenBuffer);
    projection(-250,-250,10,x1,y1);
    printLine(*x1,*y1,*x2,*y2,screenBuffer);
    projection(-250,-50,10,x2,y2);
    printLine(*x1,*y1,*x2,*y2,screenBuffer);
    projection(-50,-50,10,x1,y1);
    printLine(*x1,*y1,*x2,*y2,screenBuffer);

    projection(-50,-50,20,x1,y1);
    projection(-50,-250,20,x2,y2);
    printLine(*x1,*y1,*x2,*y2,screenBuffer);
    projection(-250,-250,20,x1,y1);
    printLine(*x1,*y1,*x2,*y2,screenBuffer);
    projection(-250,-50,20,x2,y2);
    printLine(*x1,*y1,*x2,*y2,screenBuffer);
    projection(-50,-50,20,x1,y1);
    printLine(*x1,*y1,*x2,*y2,screenBuffer);

    projection(-50,-50,10,x1,y1);
    projection(-50,-50,20,x2,y2);
    printLine(*x1,*y1,*x2,*y2,screenBuffer);
    projection(-50,-250,10,x1,y1);
    projection(-50,-250,20,x2,y2);
    printLine(*x1,*y1,*x2,*y2,screenBuffer);
    projection(-250,-250,10,x1,y1);
    projection(-250,-250,20,x2,y2);
    printLine(*x1,*y1,*x2,*y2,screenBuffer);
    projection(-250,-50,10,x1,y1);
    projection(-250,-50,20,x2,y2);
    printLine(*x1,*y1,*x2,*y2,screenBuffer);
    //Fin cubo 2

    printScreen(screenBuffer,screenBufferClean);
    getchar();

    free(x1);
    free(y1);
    free(x2);
    free(y2);
    free(screenBuffer);
    free(screenBufferClean);
    return 0;
}

void printAt(char character, int row, int column, char *buffer){
    int uLimitRow = 0;
    int dLimitRow = height;
    int lLimitColumn = 0;
    int rLimitColumn = width;
    if(row < 0){
        return;
    }
    if(column < 0){
        return;
    }
    buffer[width * row + column] = character;
}

void printLine(int x1, int y1, int x2, int y2, char *buffer){
    float dx = x2 - x1;
    float dy = y2 - y1;
    if(x1 < x2){
        for(float x = x1, y = 0; x <= x2; x+=0.1){
            y = ((x - x1)/dx) * dy + y1;
            printAt('#',(int)x,(int)y,buffer);
        }
    }
    else if(x1 > x2){
        for(float x = x1, y = 0; x >= x2; x-=0.1){
            y = ((x - x1)/dx) * dy + y1;
            printAt('#',(int)x,(int)y,buffer);
        }
    }
    else if(y1 < y2){
        for(float y = y1, x = 0; y <= y2; y+=0.1){
            x = ((y - y1)/dy) * dx + x1;
            printAt('#',(int)x,(int)y,buffer);
        }
    }
    else{
        for(float y = y1, x = 0; y >= y2; y-=0.1){
            x = ((y - y1)/dy) * dx + x1;
            printAt('#',(int)x,(int)y,buffer);
        }
    }
    printAt('#',x1,y1,buffer);
    printAt('#',x2,y2,buffer);
}

void printScreen(char *buffer, char *clean){
    write(1,buffer,height*width);
    strcpy(buffer,clean);
}

void projection(int x, int y, int z, int *px, int *py){
    int dEyeToScreen = 1;
    float aux = 0;
    aux = x*dEyeToScreen/z;
    *px = (int)aux + (height/2);
    aux = y*dEyeToScreen/z;
    *py = (int)aux + (width/2);
}
