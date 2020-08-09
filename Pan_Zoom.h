#include <math.h>

double eyex = 4, eyey = 6, eyez = 4;

double cx = 0, cy = 1, cz = 0;

double yr = 0, rad_yaw = 0;

double pr = 0, rad_pitch = 0;

double rr = 0, rad_roll = 0;

double temp = 0;

double a[3], b[3], v[3], c[3], t[3];
double amod, bmod, vmod, cmod, tmod;

struct yaw_pitch_roll // struct for yaw pitch and roll
{
    int angle = 0;

    bool flag = true; // boolean value to know if the value has been changed before

}yaw, pitch, roll;

struct zoom  // struct for zoom
{
    double t = 1; // parameter in line equation
    bool flag = true; // boolean value to know if zoom has been changed before along zoom vector
    double ex, ey, ez; // fixed eye position zoom vector
    double cx, cy, cz; // fixed centre point for zoom vector
}zoom;

void changeRoll(int key, int x, int y)
{
    if (!roll.flag)
    {
        // roll angle calculated for a specific eye position and centre
        // thus the centre position won't be changed arbitrarily and will stay in a fixed circle
        rr = sqrt(pow(eyex - cx, 2) + pow(eyey - cy, 2));
        temp = acos((cy - eyey) / rr);

        roll.angle = int(temp / 0.0174533);
        roll.flag = true;
        printf("First adjustment roll = %d \n", roll.angle);
    }

    else if (key == GLUT_KEY_END)
    {
        ++roll.angle;
        printf("increase roll \n");
        if (roll.angle > 360)
        {
            roll.angle = 0;
        }
        rad_roll = 0.0174533 * roll.angle; // converting to radians
        //compute r
        rr = sqrt(pow(eyex - cx, 2) + pow(eyey - cy, 2));  // finding radius for the circle along which 
        cx = eyex + rr * cos(rad_roll); // x position changed
        cy = eyey + rr * sin(rad_roll); // y position changed
        printf("%d \n", roll.angle);
    }
    else if (key == GLUT_KEY_HOME)
    {
        --roll.angle;
        printf("decrease roll \n");
        if (roll.angle < 0)
            roll.angle = 360;

        rad_roll = 0.0174533 * roll.angle;
        //compute r
        rr = sqrt(pow(eyex - cx, 2) + pow(eyey - cy, 2));     // finding radius for the circle along which 
        cx = eyex + rr * cos(rad_roll);                // x position changed
        cy = eyey + rr * sin(rad_roll);               // y position changed
        printf("%d \n", roll.angle);
    }
    glutPostRedisplay();
}

void Pitch(int key, int x, int y)
{
    if (!pitch.flag)
    {
        // pitch angle calculated for a specific eye position and centre
        // thus the centre position won't be changed arbitrarily and will stay in a fixed circle
        pr = sqrt(pow(eyey - cy, 2) + pow(eyez - cz, 2));
        temp = acos((cy - eyey) / pr);
        /*if (temp < 0)
         {
             temp = 3.14 - temp;
         }*/
        pitch.angle = int(temp / 0.0174533);
        pitch.flag = true;
        printf("First adjustment pitch = %d \n", pitch.angle);

        a[0] = eyex - cx;
        a[1] = eyey - cy;
        a[2] = eyez - cz;
        amod = sqrt(pow(a[0], 2) + pow(a[1], 2) + pow(a[2], 2));
        a[0] = a[0] / amod;
        a[1] = a[1] / amod;
        a[2] = a[2] / amod;

        t[0] = eyex - cx;
        t[1] = eyey - cy;
        t[2] = 0;
        tmod = sqrt(pow(t[0], 2) + pow(t[1], 2) + pow(t[2], 2));
        t[0] = t[0] / amod;
        t[1] = t[1] / amod;
        t[2] = t[2] / amod;

        v[0] = a[1] * t[2] - a[2] * t[1];
        v[1] = a[0] * t[2] - a[2] * t[0];
        v[2] = a[0] * t[1] - a[1] * t[0];

        // b = a X v
        b[0] = a[1] * v[2] - a[2] * v[1];
        b[1] = a[0] * v[2] - a[2] * v[0];
        b[2] = a[0] * v[1] - a[1] * v[0];

        c[0] = eyex;
        c[1] = eyey;
        c[2] = eyez;
    }

    else if (key == GLUT_KEY_UP)
    {
        ++pitch.angle;
        printf("increase pitch \n");
        if (pitch.angle > 360)
        {
            pitch.angle = 0;
        }
        rad_pitch = 0.0174533 * pitch.angle;
        //compute r

        cx = c[0] + amod * cos(rad_pitch) * a[0] + amod * sin(rad_pitch) * b[0];
        cy = c[1] + amod * cos(rad_pitch) * a[1] + amod * sin(rad_pitch) * b[1];
        cz = c[2] + amod * cos(rad_pitch) * a[2] + amod * sin(rad_pitch) * b[2];
        
        printf("%d \n", pitch.angle);
    }
    else if (key == GLUT_KEY_DOWN)
    {
        --pitch.angle;
        printf("decrease yaw \n");
        if (pitch.angle < 0)
        {
            pitch.angle = 360;
        }
        rad_pitch = 0.0174533 * pitch.angle;
        //compute r
        cx = c[0] + amod * cos(rad_pitch) * a[0] + amod * sin(rad_pitch) * b[0];
        cy = c[1] + amod * cos(rad_pitch) * a[1] + amod * sin(rad_pitch) * b[1];
        cz = c[2] + amod * cos(rad_pitch) * a[2] + amod * sin(rad_pitch) * b[2];

        printf("%d \n", pitch.angle);
    }
    else
    {
        changeRoll(key, x, y);
        return;
    }
    glutPostRedisplay();
}

void changePitch(int key, int x, int y)
{
    if (!pitch.flag)
    {
        // pitch angle calculated for a specific eye position and centre
        // thus the centre position won't be changed arbitrarily and will stay in a fixed circle
        pr = sqrt(pow(eyey - cy, 2) + pow(eyez - cz, 2));
        temp = acos((cy - eyey) / pr);
        /*if (temp < 0)
         {
             temp = 3.14 - temp;
         }*/
        pitch.angle = int(temp / 0.0174533);
        pitch.flag = true;
        printf("First adjustment pitch = %d \n", pitch.angle);
    }
    else if (key == GLUT_KEY_UP)
    {
        ++pitch.angle;
        printf("increase pitch \n");
        if (pitch.angle > 360)
        {
            pitch.angle = 0;
        }
        rad_pitch = 0.0174533 * pitch.angle;
        //compute r
        pr = sqrt(pow(eyey - cy, 2) + pow(eyez - cz, 2)); // radius of cirlce along which centre will move is calculated
        cy = eyey + pr * cos(rad_pitch); // y coordinate of centre changed
        cz = eyez + pr * sin(rad_pitch); // x coordinate of centre changed
        printf("%d \n", pitch.angle);
    }
    else if (key == GLUT_KEY_DOWN)
    {
        --pitch.angle;
        printf("decrease yaw \n");
        if (pitch.angle < 0)
        {
            pitch.angle = 360;
        }
        rad_pitch = 0.0174533 * pitch.angle;
        //compute r
        pr = sqrt(pow(eyey - cy, 2) + pow(eyez - cz, 2));  // radius of cirlce along which centre will move is calculated
        cy = eyey + pr * cos(rad_pitch);  // y coordinate of centre changed
        cz = eyez + pr * sin(rad_pitch);  // x coordinate of centre changed
        printf("%d \n", pitch.angle);
    }
    else
    {
        changeRoll(key, x, y);
        return;
    }
    glutPostRedisplay();
}

void changeYaw(int key, int x, int y)
// yaw angle calculated for a specific eye position and centre
// thus the centre position won't be changed arbitrarily and will stay in a fixed circle
{
    if (!yaw.flag)
    {
        yr = sqrt(pow(eyex - cx, 2) + pow(eyey - cy, 2));  // radius of cirlce along which centre will move is calculated
        temp = acos((cx - eyex) / yr);
        /*if (temp < 0)
        {
            temp = 3.14 - temp;
        }*/
        yaw.angle = int(temp / 0.0174533);
        yaw.flag = true;
        printf("First adjustment yaw = %d \n", yaw.angle);
    }
    if (key == GLUT_KEY_RIGHT)
    {
        ++yaw.angle;
        printf("increase yaw \n");
        if (yaw.angle > 360)
        {
            yaw.angle = 0;
        }
        rad_yaw = 0.0174533 * yaw.angle;
        //compute r
        yr = sqrt(pow(eyex - cx, 2) + pow(eyez - cz, 2));  // radius of cirlce along which centre will move is calculated
        cx = eyex + yr * cos(rad_yaw); // x coordinate of centre changed
        cz = eyez + yr * sin(rad_yaw); // z coordinate of centre changed
        printf("%d \n", yaw.angle);
    }
    else if (key == GLUT_KEY_LEFT)
    {
        --yaw.angle;
        printf("decrease yaw \n");
        if (yaw.angle < 0)
        {
            yaw.angle = 360;
        }
        rad_yaw = 0.0174533 * yaw.angle;
        //compute r
        yr = sqrt(pow(eyex - cx, 2) + pow(eyez - cz, 2));  // radius of cirlce along which centre will move is calculated
        cx = eyex + yr * cos(rad_yaw);  // x coordinate of centre changed
        cz = eyez + yr * sin(rad_yaw);  // z coordinate of centre changed
        printf("%d \n", yaw.angle);
    }
    else
    {
        changePitch(key, x, y);
        return;
    }
    glutPostRedisplay();
}

void changeZoom(unsigned char key, int x, int y)
{
    if (!zoom.flag)
    {
        // parameter starts with one and decreases as the eye position closes centre
        zoom.ex = eyex;
        zoom.ey = eyey;
        zoom.ez = eyez;
        zoom.cx = cx;
        zoom.cy = cy;
        zoom.cz = cz;
        zoom.t = 1;
    }
    // parametric equation of line used
    // eye position moves along the initial vector

    if (key == 'k')
    {
        zoom.t += 0.1;
        eyex = zoom.cx + (zoom.t) * (zoom.ex - zoom.cx);
        eyey = zoom.cy + (zoom.t) * (zoom.ey - zoom.cy);
        eyez = zoom.cz + (zoom.t) * (zoom.ez - zoom.cz);
    }
    else
    {
        zoom.t -= 0.1;
        eyex = zoom.cx + (zoom.t) * (zoom.ex - zoom.cx);
        eyey = zoom.cy + (zoom.t) * (zoom.ey - zoom.cy);
        eyez = zoom.cz + (zoom.t) * (zoom.ez - zoom.cz);
    }
    glutPostRedisplay();
}

void Pan(unsigned char key, int x, int y) // Pan functin
{
    if (key == 't')     //forward
    {
        cz -= .1;
        eyez -= .1;
        yaw.flag = false;
        zoom.flag = false;
    }
    else if (key == 'g')     //back
    {
        cz += .1;
        eyez += .1;
        yaw.flag = false;
        zoom.flag = false;
    }
    else if (key == 'f')     //left
    {
        cx -= .1;
        eyex -= .1;
        yaw.flag = false;
        zoom.flag = false;
    }
    else if (key == 'h')     //right
    {
        cx += .1;
        eyex += .1;
        yaw.flag = false;
        zoom.flag = false;
    }
    else if (key == 'r')     //up
    {
        cy += .1;
        eyey += .1;
        yaw.flag = false;
        zoom.flag = false;
    }
    else if (key == 'v')     //down
    {
        cy -= .1;
        eyey -= .1;
        yaw.flag = false;
        zoom.flag = false;
    }
    else if (key == 'k' || key == 'm') //zoom in or out
    {
        changeZoom(key, x, y);
        return;
    }

    glutPostRedisplay();
}

bool eyePosition(unsigned char key, int x, int y)
{
    // changes eye position, similar to moving around
    if (key == 'w')     //forward
    {
        eyez -= .1;
        yaw.flag = false;
        zoom.flag = false;
    }
    else if (key == 's')     //back
    {
        eyez += .1;
        yaw.flag = false;
        zoom.flag = false;
    }
    else if (key == 'a')     //left
    {
        eyex -= .1;
        yaw.flag = false;
        zoom.flag = false;
    }
    else if (key == 'd')     //right
    {
        eyex += .1;
        yaw.flag = false;
        zoom.flag = false;
    }
    else if (key == 'q')     //up
    {
        eyey += .1;
        yaw.flag = false;
        zoom.flag = false;
    }
    else if (key == 'z')     //down
    {
        eyey -= .1;
        yaw.flag = false;
        zoom.flag = false;
    }
    else
    {
        return false;
    }
    glutPostRedisplay();
    return true;
}

void keyboard(unsigned char key, int x, int y)
{
    if (!eyePosition(key, x, y))
    {
        Pan(key, x, y);
    }
}