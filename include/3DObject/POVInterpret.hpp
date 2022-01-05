#pragma once

#include <iostream>

class POVInterpret
{
public:
    POVInterpret(std::istream& input);
    ~POVInterpret();

    void Interpret();
};