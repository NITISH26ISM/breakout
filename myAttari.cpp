#include <iostream>
#include <cmath>
#include <GL/gl.h>
#include <GL/glut.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define maxn 100
using namespace std;


struct brick{
    int state;
    int e;
    brick(){
        state = 1;
        e = 1;
    }
};
brick arr[maxn][5];
static int ball_x = 500;
static int ball_y = 40;
static int ball_vec_x = 1;
static int ball_vec_y = -1;
static int animationPeriod = 4;
static int isAnimate = 0;
static int tray_x = 500;
static int tray_y = 0;

const double DEG2RAD = 3.1415926535897932384/180;

void drawCircle(float radius)
{
   glBegin(GL_POINTS);
    glColor3f(1.0f,0.0f,0.0f);
    double i;
   for ( i=0; i < 360 ; i= i+1)
   {
      double degInRad = i*DEG2RAD;
      glVertex2f(cos(degInRad)*radius+ball_x  ,sin(degInRad)*radius+ball_y  );
   }

   glEnd();
}




void render( void ){
    glClear(GL_COLOR_BUFFER_BIT);


    for( int i = 0; i < 20 ; i++){
        for( int j =0 ; j<5 ; j++)
            if( arr[i][j].state == 1){
                glBegin(GL_POLYGON);
                    glColor3f(0.7,0.7,0.6);
                    glVertex2i(i*50,900-j*52);
                    glVertex2i(i*50,950-j*52);
                    glVertex2i(i*50+45,950-j*52);
                    glVertex2i(i*50+45,900-j*52);
                glEnd();
        }
    }

    glPointSize(10);
            glBegin(GL_POLYGON);
                glColor3f((rand()%255)/255.0,(rand()%255)/255.0,(rand()%255)/255.0);
                glVertex2i(tray_x-60,2);
                glVertex2i(tray_x-60,20);
                glVertex2i(tray_x+60,20);
                glVertex2i(tray_x+60,2);
            glEnd();

            glColor3f((rand()%255)/255.0,(rand()%255)/255.0,(rand()%255)/255.0);
            drawCircle(10);


    glFlush();

}

void moveahead(void){
    if( ball_x >= 1000){
        ball_vec_x *= -1;
    }
    else if( ball_y >= 1000 ){
        ball_vec_y *=-1;
    }
    else if( ball_x <= 0){
        ball_vec_x *= -1;
    }
    else if(ball_x >= tray_x -60 && ball_x <= tray_x + 60 && ball_y == 40){
        ball_vec_y *= -1;
    }

    ball_x += ball_vec_x;
    ball_y += ball_vec_y;

    if( ball_y >= 645){
            int x = ball_x/50;
            int y = (900-ball_y)/50;
            y--;
            if( arr[x][y].state == 1 ){
                arr[x][y].state = 0;
                ball_vec_y *= -1;

            }

    }



    if(ball_y<0){
        cout<<"well played try again!!";
        exit(0);
    }

}

void animate(int value){
    if(isAnimate){
        moveahead();
        glutPostRedisplay();
        glutTimerFunc(animationPeriod, animate, 1);
    }

}

void keyInput(unsigned char key , int x, int y){
    switch(key){
    case 27:
        exit(0);
    case ' ':
        if(isAnimate) isAnimate = 0;
        else{
            isAnimate = 1;
            animate(1);
        }
        break;
    }
}


void specialKeyInput(int key , int x , int y ){
    if( key == GLUT_KEY_LEFT  && tray_x >=60 ){
        tray_x -= 20;
    }
    else if( key == GLUT_KEY_RIGHT  && tray_x <= 940 ){
        tray_x += 20;
    }
    glutPostRedisplay();
}


void setup(void){
	glClearColor(0.0,0.0,0.0,0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,1000,0.0,1000);
}

void printInteraction(void){
	cout<<"Interaciton:"<<endl;
	cout<<"hey welcome here!!"<<endl;
	cout<<"use space bar or pause the game {-_-} ___ "<<endl;
	cout<<"use arrow keys to control your skate (_;p) "<<endl;
}

int main( int argc , char** argv ){
    srand(time(NULL));
    printInteraction();
    glutInit( &argc, argv );
    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGBA );
    glutInitWindowSize( 800, 500 );
    glutInitWindowPosition( 100 , 100 );
    glutCreateWindow("break out intruder!!");
    setup();
    glutDisplayFunc(render);
    //glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);

    glutMainLoop();
}
