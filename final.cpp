#include <GL/glut.h> 
#include <GL/gl.h>
#include<math.h>


//<extra>
#include "ObjModelLoader.h" 
string filename = "monkey.obj";
ObjModelLoader *monkeyModel = NULL;
//</extra>


void draw_circle(float x1,float y1,float radius,float level, float r,float g,float b)
{
  //wrt table, adjusting x and z coordinates
  x1=x1-1;
  y1=y1-1;
	glColor4f(r,g,b,1);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(x1,level,y1);
	float x2,y2,angle;
	for (angle=1.0f;angle<361.0f;angle+=0.2)
	{
	    x2 = x1+sin(angle)*radius;
	    y2 = y1+cos(angle)*radius;
	    glVertex3f(x2,level,y2);
	}
	glEnd();
}
void draw_doughnuts()
{
    glColor4f(1,1,0,1);
    glutSolidTorus(0.02,0.07,20,20);
}
void draw_cake()
{
    GLUquadricObj *p = gluNewQuadric(); 
    glPushMatrix(); 
    glColor3f(1,1,0);  
    gluCylinder(p,0.26,0.26, 0.2, 30, 30); 
    glPopMatrix(); 
}
void draw_laddoo()
{
    glColor4f(1,1,0,1);
    glutSolidSphere(0.05,20,20);
}
void draw_teapot()
{
    glColor4f(1,0,1,1); 
    glutSolidTeapot(0.5);
}
void draw_leg(float xt, float yt, float zt)
{
  glPushMatrix();
  	glTranslatef(xt, yt, zt); 
  	glScalef(0.1, 1, 0.1); 
  	glutSolidCube(1.0); 
  glPopMatrix(); 
}
void draw_table() 
{
  glColor4f(.5,.5, .5,1); 
  glPushMatrix(); 
  	glScalef(2, 0.1, 2); 
  	glutSolidCube(1.0); 
  glPopMatrix(); 
  draw_leg(0.95,-0.5,-0.95); 
  draw_leg(0.95,-0.5,0.95); 
  draw_leg(-0.95,-0.5,-0.95); 
  draw_leg(-0.95,-0.5,0.95); 
}
void draw_axes()
{
  glLineWidth(2.0); 
  glBegin(GL_LINES); 
    glColor3f(1,0,0);  
    glVertex3f(0,0,0); 
    glVertex3f(.15,0,0); 
    glColor3f(0,1,0);  
    glVertex3f(0,0,0); 
    glVertex3f(0,.15,0); 
    glColor3f(0,0,1); 
    glVertex3f(0,0,0); 
    glVertex3f(0,0,.15); 
  glEnd(); 
  glLineWidth(1.0); 
}
void draw_wall()
{
  glColor4f(0,0,1,1); 
  glPushMatrix(); 
  glScalef(3, 0.01, 4); 
  glutSolidCube(1.0);
  glPopMatrix(); 
}
void display()
{
	glClearColor(0,0,0,1);  // specify the background color 
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //clear framebuffer
  glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	// set up the projection matrix 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	gluPerspective(60, 1, .1, 100); 
	//glOrtho(-3,3,-3,3,-3,3);
	// set up the modelview matrix 
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	//position the camera 
	gluLookAt(0.5,4,3, 0,1,0, 0,1,0);
 

	//plates
  draw_circle(0,0.5,0.3,1.05, 0,0,0);//omlets
  draw_circle(0,-0.5,0.3,1.05 ,0,0,0);//doughnuts
  draw_circle(0.7,0,0.3,1.05, 0,0,0);//cake
  draw_circle(-0.5,0,0.3,1.05, 0,0,0);//laddoos
  //omlets
  draw_circle(0,0.35,0.12,1.05, 1,1,1);
  draw_circle(0,0.35,0.05,1.05, 1,1,0);

  draw_circle(0,0.6,0.12,1.05, 1,1,1);
  draw_circle(0,0.6,0.05,1.05, 1,1,0);
  //table 
	glPushMatrix(); 
  		glTranslatef(-1, 1, -1); 
  		draw_table();            
  		//teapot on table
  		glPushMatrix();
  			glTranslatef(0,.15, 0);        // position a teapot at (0,0.2,0) relative to the table 
  			glScalef(.4, .4, .4);         // the size of the teapot is 0.4x0.4x0.4
  		  draw_teapot();
  		glPopMatrix(); 
      //laddoos on plate
      glPushMatrix();
        glTranslatef(-0.6,0.1,-0.1);
        draw_laddoo();
      glPopMatrix();
      glPushMatrix();
        glTranslatef(-0.3,0.1,-0.1); 
        draw_laddoo();
      glPopMatrix();  
      glPushMatrix();
        glTranslatef(-0.3,0.1,0.1); 
        draw_laddoo();
      glPopMatrix(); 
      glPushMatrix();
        glTranslatef(-0.6,0.1,0.1); 
        draw_laddoo();
      glPopMatrix();

      //doughnuts
      glPushMatrix();
        glTranslatef(-0.1,0.1,-0.6);
        glRotatef(-90, 1, 0, 0); 
        draw_doughnuts();
      glPopMatrix();
      glPushMatrix();
        glTranslatef(-0.1,0.1,-0.3); 
        glRotatef(-90, 1, 0, 0); 
        draw_doughnuts();
      glPopMatrix();  
      glPushMatrix();
        glTranslatef(0.1,0.1,-0.3);
        glRotatef(-90, 1, 0, 0);  
        draw_doughnuts();
      glPopMatrix(); 
      glPushMatrix();
        glTranslatef(0.1,0.1,-0.6);
        glRotatef(-90, 1, 0, 0);  
        draw_doughnuts();
      glPopMatrix();  

      //cake
      glPushMatrix();
         glRotatef(-90, 1, 0, 0);
         glTranslatef(0.7,0.05,0);
         draw_cake();
      glPopMatrix();




  //<extra>
      monkeyModel->Draw();
  //</extra>  



	glPopMatrix(); 
  //cake top
  draw_circle(0.7,0,0.26,1.24, 1,1,0);
	draw_axes();
	
  //walls
  glPushMatrix(); 
  glTranslatef(-2,1.5,0); 
  glRotatef(90, 0, 0, 1); 
  draw_wall(); 
  glPopMatrix();

  glPushMatrix(); 
  glTranslatef(0,1.5,-2); 
  glRotatef(90, 1, 0, 0);
  glRotatef(90, 0, 1, 0); 
  draw_wall(); 
  glPopMatrix();

  glPushMatrix(); 
  glTranslatef(2,1.5,0); 
  glRotatef(90, 0, 0, 1); 
  draw_wall(); 
  glPopMatrix();
  


	glutSwapBuffers(); 
}
int main(int argc, char** argv) 
{



  //<extra>
  monkeyModel = new ObjModelLoader(filename);
  //</extra>



  glutInit(&argc, argv); 
  glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH); 
  glutInitWindowSize(600,600); 
  glutCreateWindow("scene"); 
  glutDisplayFunc(display);
  glutMainLoop(); 
}