#ifndef MOLLERTRUMBORE_H
#define MOLLERTRUMBORE_H
#include <stdbool.h>
#include "Vector3.h"
#include "Triangle.h"

bool MollerTrumbore(struct Vector3 rayOrigin,
                    struct Vector3 rayVector,
                    struct Triangle inputTriangle,
                    struct Vector3 outIntersectionPosition);

#endif

