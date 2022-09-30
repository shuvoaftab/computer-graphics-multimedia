//
//  main.cpp
//  OpenGL
//
//  Created by Ibrahim Sharif on 28/9/22.
//

#define GL_SILENCE_DEPRECATION //MacOS Warning Suppression
#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>

int width = 500;
int height = width;

int graph_length, x, y, angle;
double xc, yc;

void initDefaultColor(void);
void draw(void);

void inputs(){
    
    do{
        printf("Enter the Graph Quadrant Length (Minimum 10) : ");
        scanf("%d", &graph_length);
    }while (graph_length < 10);
    
    printf("Enter the Initial Line Point from Origin (X,Y) : ");
    scanf("%d %d", &x, &y);
    
    printf("Enter the Rotation Angle About Origin : ");
    scanf("%d", &angle);
}


void initDefaultColor(){
    glClearColor(1, 1, 1, 1);
}

void reshape(int x, int y){
    
    //viewport
    glViewport(0, 0, (GLsizei)x, (GLsizei)y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    gluOrtho2D(-graph_length, +graph_length, -graph_length, +graph_length);
    //gluPerspective(0, aspect_ratio, 0.01f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    
    //projection
}

void graph(){
    
    glLineWidth(1.0);
    glBegin(GL_LINES);
    
    glColor3ub(253, 237, 236);
    // Positive X
    for (int i=1; i<=graph_length; i++) {
        glVertex2i(-graph_length, i);
        glVertex2i(graph_length, i);
    }
    // Negative X
    for (int i=graph_length; i>=1; i--) {
        glVertex2i(-graph_length, -i);
        glVertex2i(graph_length, -i);
    }
    
    
    glColor3ub(234, 250, 241);
    // Positive Y
    for (int i=1; i<=graph_length; i++) {
        glVertex2i(i, -graph_length);
        glVertex2i(i, graph_length);
    }
    // Negative Y
    for (int i=graph_length; i>=1; i--) {
        glVertex2i(-i, -graph_length);
        glVertex2i(-i, graph_length);
    }

    glEnd();

}

void axis(){
    
    glLineWidth(2.0);
    glBegin(GL_LINES);
    
    // X Axis
    glColor3ub(236, 112, 99 );
    glVertex2i(-graph_length, 0);
    glVertex2i(graph_length, 0);
    
    // Y Axis
    glColor3ub(82, 190, 128);
    glVertex2i(0, -graph_length);
    glVertex2i(0, graph_length);

    glEnd();
}

void original(){
    glColor3ub(46, 134, 193);
    //glPointSize(width/graph_length/2);
    glLineWidth(3.0);
    glBegin(GL_LINES);
   
    glVertex2i(0, 0);
    glVertex2i(x, y);
    
    glEnd();
}


void rotated(){
    
    xc = (x*(cos(angle))) - (y*(sin(angle)));
    yc = (x*(sin(angle))) + (y*(cos(angle)));
    
    glColor3ub(125, 60, 152);
    
    glLineWidth(3.0);
    glBegin(GL_LINES);

    glVertex2i(0, 0);
    glVertex2f(xc, yc);
    
    glEnd();
    
}

void draw(){

    //clear
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    //******            D R A W    F U N C T I O N S       *******
    graph();
    axis();
    original();
    rotated();
    
    glFlush();
}



int main(int argc, char * argv[]) {
    
    inputs();
    
    glutInit(&argc, argv);
    glutInitWindowPosition(300, 200);
    glutInitWindowSize(width, height);
    glutCreateWindow("OpenGL GLUT from MacOS");
    
    initDefaultColor();
    glutDisplayFunc(draw);
    glutReshapeFunc(reshape);
    
    glutMainLoop();
    
    return 0;
}
