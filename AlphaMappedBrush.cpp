//
// AlphaMappedBrush.cpp
//
// The implementation of Alpha Mapped Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"
#include "AlphaMappedBrush.h"

extern float frand();

AlphaMappedBrush::AlphaMappedBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void AlphaMappedBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	BrushMove( source, target );
}

void AlphaMappedBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "AlphaMappedBrush::BrushMove  document is NULL\n" );
		return;
	}

	glPointSize( (float)1 );
	SetColor( source );
	GLfloat color[4];
	glGetFloatv(GL_CURRENT_COLOR, color);

	unsigned char* alpha_bmp = pDoc->m_ucAlphaMap;
	int alpha_width = pDoc->m_nAlphaMapWidth;
	int alpha_height = pDoc->m_nAlphaMapHeight;

	glBegin( GL_POINTS );
		for (int i = 0; i < alpha_height; i++)
		{
			for (int j = 0; j < alpha_width; j++)
			{
				color[3] = (alpha_bmp[(i * alpha_width + j) * 3] * 29.9 + 
							alpha_bmp[(i * alpha_width + j) * 3 + 1] * 58.7 + 
							alpha_bmp[(i * alpha_width + j) * 3 + 2] * 11.4) / 100 / 255;
				glColor4d(color[0], color[1], color[2], color[3]);

				if (j + target.x > pDoc->m_nPaintWidth)
				{
					break;
				}
				else
				{
					glVertex2d( target.x + j, target.y + i );
				}
			}

			if (i + target.y > pDoc->m_nPaintHeight)
				break;
		}
	glEnd();
}

void AlphaMappedBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

