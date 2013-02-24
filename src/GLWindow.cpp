#include "GLWindow.h"
#include "foreach.h"
#include "Drawing.h"
#include "Atom.h"


const Color linkColor(0.5f, 0.5f, 0.5f);
const Color atomColor(1.0f, 1.0f, 1.0f);


GLWindow::GLWindow() : _previousElapsedTime(0)
{

}


void GLWindow::display()
{
    boost::this_thread::interruption_point();

    while(!_mutex.try_lock());
    CommonTypes::Vectors atomPositions = _atomPositions;
    CommonTypes::VectorPairs linkPositions = _linkPositions;
    CommonTypes::Colors atomColors = _atomColors;
    _mutex.unlock();

    glPushMatrix();
    glTranslatef(_width / 2.0f, _height / 2.0f, 0.0f);
    glScalef(1.0f, -1.0f, 1.0f);

    foreach (CommonTypes::VectorPair vp, linkPositions)
	Drawing::line(vp.first, vp.second, linkColor);

    if (atomPositions.size() == atomColors.size())
    {
	for (unsigned int i = 0; i < atomPositions.size(); ++i)
	{
	    Drawing::sphere(atomPositions[i], Atom::radius(), atomColors[i]);
	}
    }
    else
    {
	foreach (Vector v, atomPositions)
	{
	    Drawing::sphere(v, Atom::radius(), atomColor);
	}
    }

    glPopMatrix();

    int elapsedTime = glutGet(GLUT_ELAPSED_TIME);
    int dt = elapsedTime - _previousElapsedTime;
    _previousElapsedTime = elapsedTime;

    char c[32];
    sprintf(c, "%i", dt);

    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(_width - 60.0f, _height -  10.0f, 0.0f);
    glScalef(0.2f, -0.2f, 1.0f);
    glutStrokeString(GLUT_STROKE_ROMAN, (unsigned char *)c);
    glPopMatrix();
    _displayMutex.unlock();
}


void GLWindow::setAtomPositions(CommonTypes::Vectors atomPositions)
{
    boost::this_thread::interruption_point();

    while(!_mutex.try_lock());
    _atomPositions = atomPositions;
    _mutex.unlock();
}


void GLWindow::reshape(int width, int height)
{
    _width = width;
    _height = height;
}


void GLWindow::setLinkPositions(CommonTypes::VectorPairs linkPositions)
{
    while(!_mutex.try_lock());
    _linkPositions = linkPositions;
    _mutex.unlock();
}


void GLWindow::setAtomColors(CommonTypes::Colors atomColors)
{
    while(!_mutex.try_lock());
    _atomColors = atomColors;
    _mutex.unlock();
}


void GLWindow::glThreadFunc(GLWindow* glWindow)
{
    glWindow->run();
}


void GLWindow::waitForDisplay()
{
    static auto _sleepTime = boost::posix_time::milliseconds(2);
    while(not _displayMutex.try_lock())
	boost::this_thread::sleep(_sleepTime);
    _displayMutex.lock();
}
