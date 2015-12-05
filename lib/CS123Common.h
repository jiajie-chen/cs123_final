/**
 * @file CS123Common.h
 *
 * Contains data structures and macros commonly used in CS123.
 */
#pragma once
#ifndef __CS123COMMON_H__
#define __CS123COMMON_H__

#include "GL/glew.h"
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <iostream>
#include <QMessageBox>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>

// glu.h in different location on macs
#ifdef __APPLE__
#include <glu.h>
#else
#include <GL/glu.h>
#endif

// from http://en.wikipedia.org/wiki/Assertion_(computing)
#define COMPILE_TIME_ASSERT(pred) switch(0){case 0:case pred:;}

using std::cerr;
using std::cout;
using std::endl;
using std::max;
using std::min;

typedef double REAL;

// A structure for a color.  Each channel is 8 bits [0-255].
struct BGRA
{
    BGRA() : b(0), g(0), r(0), a(0) {}
    BGRA(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha = 255)
        : b(blue), g(green), r(red), a(alpha) {}

    // C++ TIP:
    // A union struct. Essentially, this makes b <==> channels[0],
    // g <==> channels[1], etc. In other words: b, g, r, and a are
    // stored at the same memory location as channels[4]. Note that
    // sizeof(b)+sizeof(g)+sizeof(r)+sizeof(a) = sizeof(channels)
    // so the memory overlaps **exactly**.
    //
    // You might want to take advantage of union structs in later
    // assignments, although we don't require or expect you to do so.
    //
    union {
        struct { unsigned char b, g, r, a; };
        unsigned char channels[4];
    };

    // @TODO: [OPTIONAL] You can implement some operators here for color arithmetic.

};

// A structure to store a rectangle on the screen.
struct CS123Rectangle {
   int minX;
   int maxX;
   int minY;
   int maxY;
};

// ---------------------
// Common math utilities
// ---------------------

#ifndef M_PI
    #define M_PI 3.14159265f
#endif

const float FLOAT_EPSILON = 1e-8;
const double DOUBLE_EPSILON = 1e-8;

inline bool floatEpsEqual(float a, float b) {
    // If the difference between a and b is less than epsilon, they are equal
    return fabs(a - b) < FLOAT_EPSILON;
}

inline bool doubleEpsEqual(double a, double b) {
    // If the difference between a and b is less than epsilon, they are equal
    return fabs(a - b) < DOUBLE_EPSILON;
}


#define NYI(f) { \
       char ss[999]; \
       (sprintf(ss, "Not yet implemented: %s, file %s, line %d\n", \
                              f, __FILE__, __LINE__)); \
       QMessageBox mb; \
       mb.setText(QString(ss)); \
       mb.setIcon(QMessageBox::Critical); \
       mb.exec(); \
       exit(0xf); \
   }


#endif
