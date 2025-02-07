#ifndef LIBRARY_H
#define LIBRARY_H

#include "library_global.h"
#include <QtCore/qglobal.h>

class __declspec(dllexport) Library
{

public:
    Library();
    int add(int a,int b);

};

#endif // LIBRARY_H
