#include "Drawing.h"
#include <GL/freeglut.h>


void Drawing::sphere(Vector position, float radius, Color color)
{
    glPushMatrix();
    position.translate();
    glBegin(GL_TRIANGLE_FAN);
    color.apply();
    glVertex2f(0.0f, 0.0f);
    glColor3f(0.0f, 0.0f, 0.0f);
    for (float a = 0.0f; a < 2.0f * M_PI + 0.7f; a += 0.7f)
    {
        glVertex2f(sin(a) * radius,
        	cos(a) * radius);
    }
    glEnd();
    glPopMatrix();
}


void Drawing::line(Vector from, Vector to, Color color)
{
    color.apply();
    glBegin(GL_LINES);
    from.vertex();
    to.vertex();
    glEnd();
}