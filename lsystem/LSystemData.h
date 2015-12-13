#ifndef LSYSTEMDATA_H
#define LSYSTEMDATA_H

#include "CS123SceneData.h"

#include <string>
#include <map>
#include <vector>

struct LSystemData
{
   std::string initial;
   std::map<std::string, std::string> rules;
   std::vector<CS123SceneMaterial> mats;
};

#endif // LSYSTEMDATA_H
