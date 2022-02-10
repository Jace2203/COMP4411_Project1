//
// PointBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"
#include "ScatteredLineBrush.h"

#include <math.h>

extern float frand();

ScatteredLineBrush::ScatteredLineBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void ScatteredLineBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	BrushMove( source, target );
}

void ScatteredLineBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "ScatteredLineBrush::BrushMove document is NULL\n" );
		return;
	}

    int size = pDoc->getSize();
    int width = pDoc->getWidth();
    int angle = pDoc->getAngle();

	int num = (int)(frand() * 2 + 3);

	for (int i = 0; i < num; i++)
	{
		double new_size = size - (size * frand() / 2);
		double new_width = width - (width * frand() / 2);
		double x_offset = frand() * size - ceil(size / 2);
		double y_offset = frand() * size - ceil(size / 2);

		glPushMatrix();
		glTranslated(target.x + x_offset, target.y + y_offset, 0.0);
		glRotated(angle + frand() * 5 - 2, 0.0, 0.0, 1.0);
		glBegin(GL_POLYGON);
			SetColor(Point((int)(source.x + x_offset), (int)(source.y + y_offset)));

    	    glVertex2d(ceil(new_size / 2) - new_size, 	ceil(new_width / 2) - new_width);
    	    glVertex2d(ceil(new_size / 2) - new_size, 	ceil(new_width / 2));
    	    glVertex2d(ceil(new_size / 2), 				ceil(new_width / 2));
    	    glVertex2d(ceil(new_size / 2),				ceil(new_width / 2) - new_width);

		glEnd();
		glPopMatrix();
	}
}

void ScatteredLineBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

