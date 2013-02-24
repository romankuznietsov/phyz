#ifndef GL_WINDOW_H
#define GL_WINDOW_H


#include <boost/thread.hpp>
#include "burden/Burden.h"
#include "CommonTypes.h"


class GLWindow : public Burden
{
    public:
	GLWindow();
	void setAtomPositions(CommonTypes::Vectors atomPositions);
	void setLinkPositions(CommonTypes::VectorPairs linkPositions);
	void setAtomColors(CommonTypes::Colors atomColors);
	void display();
	static void glThreadFunc(GLWindow* glWindow);
	void waitForDisplay();

    private:
	boost::mutex _mutex;
	boost::mutex _displayMutex;
	CommonTypes::Vectors _atomPositions;
	CommonTypes::VectorPairs _linkPositions;
	CommonTypes::Colors _atomColors;
	int _height;
	int _width;
	void reshape(int width, int height);
	int _previousElapsedTime;
};


#endif // GL_WINDOW_H
