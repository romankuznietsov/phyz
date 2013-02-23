#ifndef GL_WINDOW_H
#define GL_WINDOW_H


#include <boost/thread.hpp>
#include "burden/Burden.h"
#include "DataObjects.h"


class GLWindow : public Burden
{
    public:
	void setAtomPositions(DataObjects::Vectors atomPositions);
	void setLinkPositions(DataObjects::VectorPairs linkPositions);
	void setAtomColors(DataObjects::Colors atomColors);
	void display();
	GLWindow();
	static void glThreadFunc(GLWindow* glWindow);
	void waitForDisplay();

    private:
	boost::mutex _mutex;
	boost::mutex _displayMutex;
	DataObjects::Vectors _atomPositions;
	DataObjects::VectorPairs _linkPositions;
	DataObjects::Colors _atomColors;
	int _height;
	int _width;
	void reshape(int width, int height);
	int _previousElapsedTime;
};


#endif // GL_WINDOW_H
