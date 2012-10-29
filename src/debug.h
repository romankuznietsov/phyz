#ifndef DEBUG_H
#define DEBUG_H


#include <iostream>
#include <string>


void debug(std::string text)
{
	std::cout << text << std::endl;
}


void debug(std::string text, float value)
{
	std::cout << text << " : " << value << std::endl;
}


#endif // DEBUG_H
