//
// CurvedBrush.cpp
//
// The implementation of Curved Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"
#include "CurvedBrush.h"

#include "Convolution.h"
#include "Paintly.h"

#include <math.h>

extern float frand();

CurvedBrush::CurvedBrush(ImpressionistDoc *pDoc, char *name)
: ImpBrush(pDoc, name), con(NULL), kernel(NULL)
{
}

void CurvedBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc *pDoc = GetDocument();
	ImpressionistUI *dlg = pDoc->m_pUI;

	BrushMove(source, target);
}

void CurvedBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc *pDoc = GetDocument();
	ImpressionistUI *dlg = pDoc->m_pUI;

	if (pDoc == NULL)
	{
		printf("CurvedBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	int r = size / 2;
	int triangle_amount = 60;
	double step = M_PI * 2 / triangle_amount;
	
	// if (paintly == NULL)
	// {
	// 	paintly = new Paintly(pDoc);
	// 	paintly->genRefImage(pDoc->m_ucOriginal, pDoc->m_nPaintWidth, pDoc->m_nPaintHeight, size);
	// }
	Paintly* paintly = pDoc->m_pPaintly;
	
	if (con == NULL)
		con = new Convolution(paintly->m_ucRefImage, pDoc->m_nWidth, pDoc->m_nHeight);

	glBegin(GL_TRIANGLE_FAN);
		SetColor(source);
		glVertex2d(target.x, target.y);
		for (int i = 0; i <= triangle_amount; i++)
		{
			glVertex2d(target.x + r * cos(i * step), target.y + r * sin(i * step));
		}
	glEnd();

	Point pt = Point(target);
	double lastDx = 0.0, lastDy = 0.0;

	GLubyte* strokeColor = pDoc->GetOriginalPixel(target);

	double f = 1.0;

	for (int j = 0; j < 10; j++)
	{
		GLubyte* refImageColor = paintly->GetColor(paintly->m_ucRefImage, pt.x, pt.y);
		GLubyte* canvasColor = paintly->GetColor(pDoc->m_ucPainting, pt.x, pt.y);

		if (j > 4 && Paintly::ColorDiff(refImageColor, canvasColor) < Paintly::ColorDiff(refImageColor, strokeColor))
			break;

		double gx = con->XGradient(pt.x, pt.y);
		double gy = con->YGradient(pt.x, pt.y);
		double rr = sqrt(gx * gx + gy * gy);
		gx = gx / rr;
		gy = gy / rr;
		
		if (gx == 0 && gy == 0)
			break;

		double dx = -gy, dy = gx;
		if (lastDx * dx + lastDy * dy < 0)
		{
			dx = -dx;
			dy = -dy;
		}
		
		dx = f * dx + (1 - f) * lastDx;
		dy = f * dy + (1 - f) * lastDy;
		rr = sqrt(dx * dx + dy * dy);
		dx = dx / rr;
		dy = dy / rr;
		pt.x = pt.x + size * dx / 2;
		pt.y = pt.y + size * dy / 2;
		lastDx = dx;
		lastDy = dy;
		
		glBegin(GL_TRIANGLE_FAN);
			glVertex2d(pt.x, pt.y);
			for (int i = 0; i <= triangle_amount; i++)
			{
				glVertex2d(pt.x + r * cos(i * step), pt.y + r * sin(i * step));
			}
		glEnd();
	}
}

void CurvedBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
	delete con;
	con = NULL;
	delete kernel;
	kernel = NULL;
}
