//
// PointBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"
#include "LineBrush.h"

#include <math.h>

extern float frand();

LineBrush::LineBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void LineBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	BrushMove( source, target );
}

void LineBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "LineBrush::BrushMove  document is NULL\n" );
		return;
	}

    int size = pDoc->getSize();
    int width = pDoc->getWidth();
    int angle = pDoc->getAngle();

	glPushMatrix();
	glTranslated(target.x, target.y, 0.0);
	glRotated(angle, 0.0, 0.0, 1.0);
	glLineWidth(width);
	glBegin(GL_LINES);
		SetColor( source );

		glVertex2d(-size / 2, 0);
		glVertex2d(size / 2, 0);
		
	glEnd();
	glPopMatrix(); 
}

void LineBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

