#include <GL/glut.h> /// Glut header file for implementing OpenGL Functions

/// Header file will be used in main.cpp(Main code to draw lines between any two endpoints and circle at any centre

int temp;
int xc, yc;

float m;
float r, g, b;

/** Function to lightup Pixels of a Circle
    Follows 8 way symmetry and
    uses Bresenham's Midpoint algorithm for a Circle*/
void plot_point(int x, int y)
{
    glBegin(GL_POINTS);
    glColor3f(r, g, b);
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc - y, yc - x);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc - y, yc + x);
    glEnd();
}

/** Function to lightup Pixels of a line*/
void setPixel(int x, int y)
{
    glBegin(GL_POINTS);
    glColor3f(1, 1, 1); /// Setting the Color of Line to White
    glVertex2i(x, y);
    glEnd();
}

class line
{
public:
    int x1, y1, x2, y2;

    void lineFunc(int x1, int y1, int x2, int y2); ///Function that implements Bresenham's Midpoint Algorithm

    line(int xa, int ya, int xb, int yb) /// Class Constructor
    {
        x1 = xa;
        x2 = xb;
        y1 = ya;
        y2 = yb;

        lineFunc(x1, y1, x2, y2);
    }
};

/// Definition of Function that will implement Bresenham's Algorithm
void line::lineFunc(int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    if (dx != 0)
    {
        m = (float(dy) / float(dx)); /// Slope of the line
        if (m >= 0) /// if the Slope is Positive
        {
            if (m <= 1) ///One pixel per column will be illuminated
            {
                if (dx < 0) /// Interchange coordinates to draw the same line in opposite direction.
                {
                    temp = x1;
                    x1 = x2;
                    x2 = temp;

                    temp = y1;
                    y1 = y2;
                    y2 = temp;

                    dx = -1 * dx;
                    dy = -1 * dy;
                }
                int d = 2 * dy - dx;
                int dE = 2 * dy; /// Declaration of Decision variable for choosing E Pixel
                int dNE = 2 * (dy - dx); /// Declaration of Decision variable for choosing NE Pixel
                int x = x1, y = y1;
                setPixel(x, y); /// x , y Pixel will lightup

                while (x < x2) // while loop will finish line
                {
                    if (d <= 0)
                    {
                        d = d + dE; // E Pixel is chosen & E is chosen even if d = 0
                    }
                    else
                    {
                        d = d + dNE; // NE Pixel is chosen
                        y++; /// y Co-ordinate will be incremented
                    }
                    x++;/// x Co-ordinate will be incremented
                    setPixel(x, y); /// x , y Pixel will lightup
                }
                glFlush();
            }
            else /// When slope is greater than 1
            {
                if (dy < 0) /// Interchange coordinates to draw the same line in opposite direction.
                {
                    temp = x1;
                    x1 = x2;
                    x2 = temp;

                    temp = y1;
                    y1 = y2;
                    y2 = temp;

                    dx = -1 * dx;
                    dy = -1 * dy;
                }
                int d = 2 * dx - dy;
                int dN = 2 * dx; /// Declaration of Decision variable for choosing E Pixel
                int dNE = 2 * (dx - dy); /// Declaration of Decision variable for choosing NE Pixel
                int x = x1, y = y1;
                setPixel(x, y);

                while (y < y2) /// while loop will finish line
                {
                    if (d <= 0)
                    {
                        d = d + dN; /// N Pixel is chosen & E is chosen even if d = 0
                    }
                    else
                    {
                        d = d + dNE; /// NE Pixel is chosen
                        x++;/// x Co-ordinate will be incremented
                    }
                    y++;/// y Co-ordinate will be incremented
                    setPixel(x, y); /// x , y Pixel will lightup
                }
                glFlush();
            }

        }
        else /// negetive slope
        {
            if (m >= -1) /// One pixel per column
            {
                if (dx < 0) /// Interchange coordinates to draw the same line in opposite direction.
                {
                    temp = x1;
                    x1 = x2;
                    x2 = temp;

                    temp = y1;
                    y1 = y2;
                    y2 = temp;

                    dx = -1 * dx;
                    dy = -1 * dy;
                }
                int d = 2 * dy + dx;
                int dE = 2 * dy; /// Declaration of Decision variable for choosing E Pixel
                int dSE = 2 * (dy + dx); /// Declaration of Decision variable for choosing SE Pixel
                int x = x1, y = y1;
                setPixel(x, y);

                while (x < x2) /// while loop will finish line
                {
                    if (d >= 0)
                    {
                        d = d + dE; /// E Pixel is chosen & E is chosen even if d = 0
                    }
                    else
                    {
                        d = d + dSE; /// SE Pixel is chosen
                        y--;/// y Co-ordinate is incremented
                    }
                    x++;
                    setPixel(x, y); /// x , y Pixel will lightup
                }
                glFlush();
            }
            else /// When slope is lesser than -1
            {
                if (dy > 0) /// Interchange coordinates to draw the same line in opposite direction.
                {
                    temp = x1;
                    x1 = x2;
                    x2 = temp;

                    temp = y1;
                    y1 = y2;
                    y2 = temp;

                    dx = -1 * dx;
                    dy = -1 * dy;
                }
                int d = 2 * dx + dy;
                int dS = 2 * dx; /// Declaration of Decision variable for choosing E Pixel
                int dSE = 2 * (dx + dy); /// Declaration of Decision variable for choosing NE Pixel
                int x = x1, y = y1;
                setPixel(x, y);

                while (y > y2) /// while loop will finish line
                {
                    if (d <= 0)
                    {
                        d = d + dS; /// S Pixel is chosen & E is chosen even if d = 0
                    }
                    else
                    {
                        d = d + dSE; /// SE Pixel is chosen
                        x++;/// x is incremented
                    }
                    y--;/// y is incremented
                    setPixel(x, y);
                }
                glFlush();
            }
        }
    }
    else /// for infinite slope - Special Case - Bresenham's algorithm is not implemented
    {
        int x = x1, y = y1;
        while (y <= y2)
        {
            setPixel(x, y);
            y++;
        }
        glFlush();
    }
}

class circle
{
public:
    int r, level;
    void circleFunc(int rad); /// Function that will implement Bresenham's midpoint Algorithm for Circle
    void circleColor();

    circle(int xcen, int ycen, int radius) /// Class Circle Constructor.
    {
        xc = xcen;
        yc = ycen;
        r = radius;

        circleColor(); /// Function call of circleColor
        circleFunc(r); /// Function call of circleFunc
    }
};

void circle::circleColor()
{
    /// Circle Color as a function of level
    level = ((480 - yc) / 15) % 15; /// level is an integer
    /// Different colors
    if (level == 0)
    {
        r = 0;
        g = 0;
        b = 1;
    }
    else if (level == 1)
    {
        r = 1;
        g = 0;
        b = 0;
    }
    else if (level == 2)
    {
        r = 0;
        g = 1;
        b = 0;
    }
    else if (level == 3)
    {
        r = 1;
        g = 1;
        b = 0;
    }
    else if (level == 4)
    {
        r = 1;
        g = 0;
        b = 1;
    }
    else if (level == 5)
    {
        r = 0;
        g = 1;
        b = 1;
    }
    else if (level == 6)
    {
        r = 0.5;
        g = 0.5;
        b = 0;
    }
    else if (level == 7)
    {
        r = 0;
        g = 0.5;
        b = 0.5;
    }
    else if (level == 8)
    {
        r = 0.5;
        g = 1;
        b = 0.5;
    }
    else if (level == 9)
    {
        r = 1;
        g = 1;
        b = 0.5;
    }
    else if (level == 10)
    {
        r = 1;
        g = 0.5;
        b = 0;
    }
    else if (level == 11)
    {
        r = 0;
        g = 1;
        b = 0.5;
    }
    else if (level == 12)
    {
        r = 0.75;
        g = 0.5;
        b = 0.25;
    }
    else if (level == 13)
    {
        r = 0.25;
        g = 0.75;
        b = 0;
    }
    else
    {
        r = 0.75;
        g = 0.75;
        b = 0.25;
    }
}

/// Function to draw a circle using bresenham's midpoint algorithm
void circle::circleFunc(int radius)
{
    int x = 0, y = radius;
    int d = 1 - radius;
    int deltaE = 3;
    int deltaSE = 5 - 2 * radius;
    /** Plot the points */
   /** Plot the first point */
    plot_point(x, y);

    /** Find all vertices till x=y */
    while (x < y)
    {
        if (d < 0) {						///choose E pixel
            d += deltaE; 				///increment d by deltaE
            deltaE += 2;				///increment deltaE by 2
            deltaSE += 2;				///increment deltaSE by 2
        }
        else {							///chose SE pixel
            d += deltaSE;				///increment d by deltaSE
            deltaE += 2;				///increment deltaE by 2
            deltaSE += 4;				///increment deltaSE by 4
            y--;    /// Decrement of y Co-ordinate
        }
        x++;  /// Increment of x Co-ordinate
        plot_point(x, y);				//plot the updated point
    }
    glFlush();
}

