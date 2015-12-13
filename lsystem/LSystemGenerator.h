#ifndef LSYSTEMGENERATOR_H
#define LSYSTEMGENERATOR_H

#include "CS123SceneData.h"
#include <string>
#include <map>
#include <vector>

struct LSystemData;

class LSystemGenerator
{
public:
    LSystemGenerator(const LSystemData &data);
    ~LSystemGenerator();

    std::string makeLSystem(int depth);
    CS123SceneMaterial getMaterial(int index);

private:
    std::string m_initial;
    std::map<char, std::string> m_rules;
    std::vector<CS123SceneMaterial> m_mats;

    CS123SceneMaterial m_defaultMat;
};

#endif // LSYSTEMGENERATOR_H
