//
// CurvedBrush.h
//
// The header file for Curved Brush. 
//

#ifndef CURVEDBRUSH_H
#define CURVEDBRUSH_H

#include "ImpBrush.h"

class Convolution;
class Matrix;
class Paintly;

class CurvedBrush : public ImpBrush
{
public:
	CurvedBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );

	void BrushBegin( const Point source, const Point target );
	void BrushMove( const Point source, const Point target );
	void BrushEnd( const Point source, const Point target );
	char* BrushName( void );
private:
	Convolution* con;
	Matrix* kernel;
};

#endif