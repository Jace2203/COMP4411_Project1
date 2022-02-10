//
// StrokeDirection.cpp
//
// The implementation of obtaining stroke direction
//

#include "impressionistDoc.h"
#include "impressionistUI.h"

#include "StrokeDirection.h"

#include <math.h>

StrokeDirection::StrokeDirection()
: m_pStartMousePos(0, 0), m_pEndMousePos(0, 0)
{
}

// Start measuring stroke direction
void StrokeDirection::StrokeBegin(Point source)
{
    setStartMousePos(source);
}

// Update stroke direction
void StrokeDirection::StrokeMove(Point source)
{
    setEndMousePos(source);
}

// Stop measuring stroke direction, then calculate the angle
void StrokeDirection::StrokeEnd(Point source)
{
    setEndMousePos(source);

    m_nAngle = (int)(atan2f(m_pEndMousePos.y - m_pStartMousePos.y, m_pEndMousePos.x - m_pStartMousePos.x) * 180 / M_PI);

    if (m_nAngle < 0)
    {
        m_nAngle += 360;
    }
}

// ====================================================
//                      Accessors
// ====================================================

void StrokeDirection::setStartMousePos(Point source)
{
    m_pStartMousePos = source;
}

Point StrokeDirection::getStartMousePos()
{
    return m_pStartMousePos;
}

void StrokeDirection::setEndMousePos(Point source)
{
    m_pEndMousePos = source;
}

Point StrokeDirection::getEndMousePos()
{
    return m_pEndMousePos;
}

int StrokeDirection::getAngle(Point source, Point target, int type)
{
    return m_nAngle;
}