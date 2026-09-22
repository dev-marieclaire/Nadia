// common/geometry.h
#pragma once
#ifndef GEOMETRY_H
#define GEOMETRY_H

typedef struct
{
    int x, y;
} point2d;

typedef struct
{
    int x, y, z;
} point3d;

typedef struct
{
    point2d position;
    int b, h;
} rect;

typedef struct
{
    point2d position;
    int radius;
} circle;

#endif // End of GEOMETRY_H
