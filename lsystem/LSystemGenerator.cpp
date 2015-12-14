#include "LSystemGenerator.h"

#include "LSystemData.h"

LSystemGenerator::LSystemGenerator(const LSystemData &data) :
    m_initial(data.initial),
    m_rules(data.rules),
    m_mats()
{
    memset(&m_defaultMat, 0, sizeof(CS123SceneMaterial));
    m_defaultMat.textureMap = new CS123SceneFileMap;
    m_defaultMat.bumpMap = new CS123SceneFileMap;
    m_defaultMat.textureMap->isUsed = false;
    m_defaultMat.bumpMap->isUsed = false;
    m_defaultMat.cDiffuse.r = m_defaultMat.cDiffuse.g = m_defaultMat.cDiffuse.b = 1;

    // must copy mat pointers because the TA support code doesn't follow standard C++ practices
    for (const CS123SceneMaterial &m : data.mats) {
        CS123SceneMaterial mat = m;

        CS123SceneFileMap *texMap = new CS123SceneFileMap();
        texMap->isUsed = m.textureMap->isUsed;
        texMap->filename = m.textureMap->filename;
        texMap->repeatU = m.textureMap->repeatU;
        texMap->repeatV = m.textureMap->repeatV;
        mat.textureMap = texMap;

        CS123SceneFileMap *bumpMap = new CS123SceneFileMap();
        bumpMap->isUsed = m.bumpMap->isUsed;
        bumpMap->filename = m.bumpMap->filename;
        bumpMap->repeatU = m.bumpMap->repeatU;
        bumpMap->repeatV = m.bumpMap->repeatV;
        mat.bumpMap = bumpMap;

        if (mat.textureMap->isUsed) {
            QString path(mat.textureMap->filename.c_str());
            QImage image(path);
            if (image.isNull()) {
                mat.textureMap->isUsed = 0;
            } else {
                glGenTextures(1, &mat.textureMap->texid);
                glBindTexture(GL_TEXTURE_2D, mat.textureMap->texid);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glBindTexture(GL_TEXTURE_2D, 0);
            }
        }

        if (mat.bumpMap->isUsed) {
            QString path(mat.bumpMap->filename.c_str());
            QImage image(path);
            if (image.isNull()) {
                mat.bumpMap->isUsed = 0;
            } else {
                glGenTextures(1, &mat.bumpMap->texid);
                glBindTexture(GL_TEXTURE_2D, mat.bumpMap->texid);
                glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.width(), image.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.bits());
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glBindTexture(GL_TEXTURE_2D, 0);
            }
        }

        m_mats.push_back(mat);
    }
}

LSystemGenerator::~LSystemGenerator()
{
    // must delete mat pointers
    delete m_defaultMat.textureMap;
    delete m_defaultMat.bumpMap;

    for (CS123SceneMaterial &m : m_mats) {
        glDeleteTextures(1, &m.textureMap->texid);
        glDeleteTextures(1, &m.bumpMap->texid);

        delete m.textureMap;
        delete m.bumpMap;
    }
}

std::string LSystemGenerator::makeLSystem(int depth)
{
    std::string currSystem = m_initial;

    // iterate through lsystem for depth
    for (int i = 0; i < depth; i++) {
        // go through the current system by symbol and generate next iteration
        std::string nextSystem;
        for (char &replace : currSystem) {
            // if that symbol is in the replacement rules, replace, else put back
            if (m_rules.find(replace) != m_rules.end()) {
                nextSystem += m_rules[replace];
            } else {
                nextSystem += replace;
            }
        }
        currSystem = nextSystem;
    }

    std::cout << currSystem << std::endl;
    return currSystem;
}

CS123SceneMaterial LSystemGenerator::getMaterial(int index)
{
    if (m_mats.size() > 0) {
        return m_mats[index % m_mats.size()];
    }

    return m_defaultMat;
}

std::vector<CS123SceneMaterial> LSystemGenerator::getMaterials()
{
    return m_mats;
}
