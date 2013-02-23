#ifndef YAML_LOADER_H
#define YAML_LOADER_H


#include <string>
#include "Model.h"


class YamlLoader
{
    public:
	YamlLoader();
	bool load(std::string fileName, Model& model);
};


#endif // YAML_LOADER_H
