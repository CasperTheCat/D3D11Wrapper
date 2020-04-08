#pragma once

#include <string>

class Serialisable
{
public:
    virtual void Serialise(std::string strFilename) = 0;
};