#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h> 
#include <GL/gl.h>
#include <stdc++.h>
#include <Pan_Zoom.h>
#include "Components.h"
//#include "ObjLoader.h" 



using namespace std;


int press_x, press_y;
int release_x, release_y;
float x_angle = 0.0;
float y_angle = 0.0;
float scale_size = 1.0;
float camera_distance = 5.0;

int xform_mode = 0;

#define XFORM_NONE    0 
#define XFORM_ROTATE  1
#define XFORM_SCALE   2

void display()
{
    glClearColor(0, 0, 0, 1);  // specify the background color 
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear framebuffer
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    // set up the projection matrix 
    glEnable(GL_NORMALIZE);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, .1, 100);

    // set up the modelview matrix 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    //position the camera 
    gluLookAt(eyex, eyey, eyez, cx, cy, cz, 0, 1, 0);

    glRotatef(x_angle, 0, 1, 0);
    glRotatef(y_angle, 1, 0, 0);
    glScalef(scale_size, scale_size, scale_size);

    // Start to draw the scene

    draw_axes();   // the axes are the local frame for the floor 
    draw_floor();
    draw_wallframes();
    draw_allchairs();

    /*glPushMatrix();
    glTranslatef(2, -0.35, -2.2);
    draw_surface(0.8, 1.2, 0.5, 0.2, 0.2, 0.2, 0.2);
    glTranslatef(0, 0.65, 0);
    draw_surface(0.8, 0.1, 0.5, 0.8, 0.5, 0.3, 0.4);
    glPushMatrix();
    glTranslatef(0, 0.05, 0);
    glScalef(.2, .2, .2);
    drawbottle();
    glPopMatrix();
    glPopMatrix();
    draw_eatables();
    glPushMatrix();
    glTranslatef(0.55, 0.6, -2.5);
    glRotatef(48, 0, 0, 1);
    glScalef(0.7, 0.7, 0.7);
    drawCarrot();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.4, 0.9, 0);
    glScalef(15, 15, 15);
    drawChilly();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1.25, 1.88, -2.4);
    glScalef(.13, .13, .13);
    drawTree();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.2, -0.5, -2.4);
    glScalef(.12, .12, .12);
    drawPoptree();
    glPopMatrix();*/


    // drawObject();
    glutSwapBuffers();
}

/*void mymouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN) {
        press_x = x; press_y = y;
        if (button == GLUT_LEFT_BUTTON)
            xform_mode = XFORM_ROTATE;
        else if (button == GLUT_RIGHT_BUTTON)
            xform_mode = XFORM_SCALE;
    }
    else if (state == GLUT_UP) {
        release_x = x; release_y = y;
        if (button == GLUT_LEFT_BUTTON) {
            xform_mode = XFORM_ROTATE;
            x_angle += (release_x - press_x);
            y_angle += (release_y - press_y);
            if (x_angle > 180) x_angle -= 360;
            else if (x_angle < -180) x_angle += 360;
            if (y_angle > 180) y_angle -= 360;
            else if (y_angle < -180) y_angle += 360;

        }
        else if (button == GLUT_RIGHT_BUTTON) {
            xform_mode = XFORM_SCALE;
            float old_size = scale_size;
            scale_size -= (release_y - press_y) / 60.0;
            if (scale_size < 0) scale_size = old_size;
        }
    }
    display();
}

// /////////////////////////////////////////////////////////

void mymotion(int x, int y)
{
    static int count = 0;
    if (xform_mode == XFORM_ROTATE) {
        x_angle += (x - press_x) / 10.0;
        if (x_angle > 180) x_angle -= 360;
        else if (x_angle < -180) x_angle += 360;
        press_x = x;

        y_angle += (y - press_y) / 10.0;
        if (y_angle > 180) y_angle -= 360;
        else if (y_angle < -180) y_angle += 360;
        press_y = y;
    }
    else if (xform_mode == XFORM_SCALE) {
        float old_size = scale_size;
        scale_size -= (y - press_y) / 60.0;
        if (scale_size < 0) scale_size = old_size;
        press_y = y;
    }
    count++;
    if (count >= 5) { display(); count = 0; }
}*/


void Init()
{
    glClearColor(0, 0, 0, 1);  // specify the background color 
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    // set up the projection matrix 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, 1, .1, 100);

    // set up the modelview matrix 
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("scene");
    //glutReshapeFunc(reshape);
    Init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    //glutMouseFunc(mymouse);
    //glutMotionFunc(mymotion);
    glutSpecialFunc(changeYaw);

    /*loadCarrot("Objects/Carrot.obj");
    loadChilly("Objects/chilly.obj");
    loadTree("Objects/Oak_Tree.obj");
    loadPopTree("Objects/Poplar_Tree.obj");
    loadBottle("Objects/bottel.obj");*/
    glutMainLoop();
}