//
// paintview.cpp
//
// The code maintaining the painting view of the input images
//

#include "impressionist.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "paintview.h"
#include "ImpBrush.h"
#include "StrokeDirection.h"
#include <math.h>
#include <iostream>


#define LEFT_MOUSE_DOWN		1
#define LEFT_MOUSE_DRAG		2
#define LEFT_MOUSE_UP		3
#define RIGHT_MOUSE_DOWN	4
#define RIGHT_MOUSE_DRAG	5
#define RIGHT_MOUSE_UP		6


#ifndef WIN32
#define min(a, b)	( ( (a)<(b) ) ? (a) : (b) )
#define max(a, b)	( ( (a)>(b) ) ? (a) : (b) )
#endif

static int		eventToDo;
static int		isAnEvent=0;
static Point	coord;

LinkedList::LinkedList(int w, int h)
{
	photo = new char[w*h*3];
	next = nullptr;
}

LinkedList::~LinkedList()
{
}

Pointll::Pointll(int x, int y)
{
	xy = Point(x, y);
	next = nullptr;
}

Pointll::~Pointll()
{
}

static int		autopaint = 0;
static int		autopaintspacing = 0;

PaintView::PaintView(int			x, 
					 int			y, 
					 int			w, 
					 int			h, 
					 const char*	l)
						: Fl_Gl_Window(x,y,w,h,l)
{
	m_nWindowWidth	= w;
	m_nWindowHeight	= h;
	m_SavedPhoto = nullptr;
	m_pllMax = nullptr;
}


void PaintView::draw()
{
	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_FRONT_AND_BACK);
	#endif // !MESA

	glEnable( GL_BLEND );
	glBlendFunc(GL_SRC_ALPHA,
		GL_ONE_MINUS_SRC_ALPHA);

	if(!valid())
	{

		glClearColor(0.7f, 0.7f, 0.7f, 1.0);

		// We're only using 2-D, so turn off depth 
		glDisable( GL_DEPTH_TEST );

		ortho();

		glClear( GL_COLOR_BUFFER_BIT );
	}

	Point scrollpos;// = GetScrollPosition();
	scrollpos.x = 0;
	scrollpos.y	= 0;

	m_nWindowWidth	= w();
	m_nWindowHeight	= h();

	int drawWidth, drawHeight;
	drawWidth = min( m_nWindowWidth, m_pDoc->m_nPaintWidth );
	drawHeight = min( m_nWindowHeight, m_pDoc->m_nPaintHeight );

	int startrow = m_pDoc->m_nPaintHeight - (scrollpos.y + drawHeight);
	if ( startrow < 0 ) startrow = 0;

	m_pPaintBitstart = m_pDoc->m_ucPainting + 
		3 * ((m_pDoc->m_nPaintWidth * startrow) + scrollpos.x);

	m_nDrawWidth	= drawWidth;
	m_nDrawHeight	= drawHeight;

	m_nStartRow		= startrow;
	m_nEndRow		= startrow + drawHeight;
	m_nStartCol		= scrollpos.x;
	m_nEndCol		= m_nStartCol + drawWidth;

	if ( m_pDoc->m_ucPainting && !isAnEvent) 
	{
		RestoreContent();

	}

	if (autopaint == 1)
	{
		int x = 0, y = 0;

		glReadBuffer(GL_BACK);

		glPixelStorei( GL_PACK_ALIGNMENT, 1 );
		glPixelStorei( GL_PACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );

		while (x < m_nDrawWidth)
		{
			m_pAutoPaintPoint.x = x;
			m_pAutoPaintPoint.y = y;
			glTranslated(0, m_nWindowHeight - m_nDrawHeight, 0);
			m_pDoc->m_pCurrentBrush->BrushBegin( m_pAutoPaintPoint, m_pAutoPaintPoint );
			if (y > m_nDrawHeight)
			{
				x = x + autopaintspacing;
				y = 0;
			}
			y = y + autopaintspacing;
			glTranslated(0, -(m_nWindowHeight - m_nDrawHeight), 0);
		}
		autopaint = 0;
		m_pDoc->m_pCurrentBrush->BrushEnd(m_pAutoPaintPoint, m_pAutoPaintPoint);

		glReadPixels( 0, 
				m_nWindowHeight - m_nDrawHeight, 
				m_nDrawWidth, 
				m_nDrawHeight, 
				GL_RGB, 
				GL_UNSIGNED_BYTE, 
				m_pPaintBitstart );

		RestoreContent();
	}

	if ( m_pDoc->m_ucPainting && isAnEvent) 
	{

		// Clear it after processing.
		isAnEvent	= 0;	

		Point source( coord.x + m_nStartCol, m_nEndRow - coord.y );
		Point target( coord.x, m_nWindowHeight - coord.y );
		
		// This is the event handler
		switch (eventToDo) 
		{
		case LEFT_MOUSE_DOWN:
			m_pDoc->m_pCurrentBrush->BrushBegin( source, target );
			break;
		case LEFT_MOUSE_DRAG:
			m_pDoc->m_pCurrentBrush->BrushMove( source, target );
			break;
		case LEFT_MOUSE_UP:
			m_pDoc->m_pCurrentBrush->BrushEnd( source, target );
			m_pDoc->m_pStrokeDirection->resetLastMousePos();

			SaveCurrentContent();
			RestoreContent();
			break;
		case RIGHT_MOUSE_DOWN:
			if (m_pDoc->m_nStrokeType == STROKE_SLIDER)
			{
				SaveCurrentContent();
				int offset = m_pDoc->m_pUI->m_mainWindow->h() - m_pDoc->m_nPaintHeight - 25;
				m_pDoc->m_pStrokeDirection->StrokeBegin(source, offset);
			}

			break;
		case RIGHT_MOUSE_DRAG:
			if (m_pDoc->m_nStrokeType == STROKE_SLIDER)
			{
				RestoreContent();
				int offset = m_pDoc->m_pUI->m_mainWindow->h() - m_pDoc->m_nPaintHeight - 25;
				m_pDoc->m_pStrokeDirection->StrokeMove(source, offset);
			}

			break;
		case RIGHT_MOUSE_UP:
			if (m_pDoc->m_nStrokeType == STROKE_SLIDER)
			{
				RestoreContent();
				m_pDoc->m_pStrokeDirection->StrokeEnd(source);

				m_pDoc->setAngle(m_pDoc->m_pStrokeDirection->getAngle(m_pDoc, source, target, m_pDoc->m_nStrokeType));
			}

			break;

		default:
			printf("Unknown event!!\n");		
			break;
		}
	}

	glFlush();

	#ifndef MESA
	// To avoid flicker on some machines.
	glDrawBuffer(GL_BACK);
	#endif // !MESA

}


int PaintView::handle(int event)
{
	switch(event)
	{
	case FL_ENTER:
	    redraw();
		break;
	case FL_PUSH:
		SaveForUndo();
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DOWN;
		else
			eventToDo=LEFT_MOUSE_DOWN;
		isAnEvent=1;
		redraw();
		break;
	case FL_DRAG:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_DRAG;
		else
			eventToDo=LEFT_MOUSE_DRAG;
		isAnEvent=1;
		redraw();
		break;
	case FL_RELEASE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		if (Fl::event_button()>1)
			eventToDo=RIGHT_MOUSE_UP;
		else
			eventToDo=LEFT_MOUSE_UP;
		isAnEvent=1;
		redraw();
		break;
	case FL_MOVE:
		coord.x = Fl::event_x();
		coord.y = Fl::event_y();
		break;
	default:
		return 0;
		break;

	}


	m_pDoc->setMousePos(Point(coord.x, coord.y));

	return 1;
}

void PaintView::refresh()
{
	redraw();
}

void PaintView::resizeWindow(int width, int height)
{
	resize(x(), y(), width, height);
}

void PaintView::SaveCurrentContent()
{
	// Tell openGL to read from the front buffer when capturing
	// out paint strokes
	glReadBuffer(GL_FRONT);

	glPixelStorei( GL_PACK_ALIGNMENT, 1 );
	glPixelStorei( GL_PACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	
	glReadPixels( 0, 
				  m_nWindowHeight - m_nDrawHeight, 
				  m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart );
}


void PaintView::RestoreContent()
{
	glDrawBuffer(GL_BACK);

	glClear( GL_COLOR_BUFFER_BIT );

	glRasterPos2i( 0, m_nWindowHeight - m_nDrawHeight );
	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );
	glPixelStorei( GL_UNPACK_ROW_LENGTH, m_pDoc->m_nPaintWidth );
	glDrawPixels( m_nDrawWidth, 
				  m_nDrawHeight, 
				  GL_RGB, 
				  GL_UNSIGNED_BYTE, 
				  m_pPaintBitstart);

//	glDrawBuffer(GL_FRONT);
}

void PaintView::CreateSavedPhoto()
{
	m_SavedPhoto = new LinkedList(m_pDoc->m_nPaintWidth, m_pDoc->m_nPaintHeight);
	memset(m_SavedPhoto->photo, 0, m_pDoc->m_nPaintWidth*m_pDoc->m_nPaintHeight*3);
}

void PaintView::SaveForUndo()
{
	if (m_SavedPhoto != NULL)
	{
		LinkedList* temp = m_SavedPhoto;
		while (temp->next != nullptr)
			temp = temp->next;
		temp->next = new LinkedList(m_nDrawWidth, m_nDrawHeight);
		memcpy(temp->next->photo, m_pPaintBitstart, m_nDrawWidth*m_nDrawHeight*3);
	}
}

void PaintView::LoadForUndo()
{
	if (m_SavedPhoto !=nullptr)
	{
		if (m_SavedPhoto->next != nullptr)
		{
			LinkedList* temp = m_SavedPhoto;
			while (temp->next->next != nullptr)
				temp = temp->next;
			memcpy(m_pPaintBitstart, temp->next->photo, m_nDrawWidth*m_nDrawHeight*3);
			delete temp->next;
			temp->next = nullptr;
			redraw();
		}
	}
}

void PaintView::AutoPaint(int spacing)
{
	autopaintspacing = spacing;
	autopaint = 1;
	redraw();
}

void PaintView::DrawPaintly()
{
	m_pDoc->setBrushType(2);
	srand(time(NULL));

	unsigned char* canvas = new unsigned char[m_nDrawWidth * m_nDrawHeight * 3];
	memset (canvas, 0, m_nDrawWidth * m_nDrawHeight * 3);
	unsigned char* sourceImage = m_pDoc->m_ucBitmap;
	unsigned char* referenceImage;

	int size = pow(2, m_pDoc->m_nPaintlyR0Level + 1);
	for (int layer = 0; layer < m_pDoc->m_nPaintlyLayer; ++layer)
	{
		m_nNumMax = 0;
		//m_pDoc->setSize(size);

		/*apply blur - need to be added*/
		referenceImage = sourceImage;

		/*paintLayer*/
		paintLayer(canvas, referenceImage, size);

		Point* PointList = new Point[m_nNumMax];
		Point temp_pt;
		Pointll* head = m_pllMax;
		int index;
		for(int t = 0; t < m_nNumMax; ++t)
		{
			PointList[t] = head->xy;
			head = head->next;
		}

		for(int t = 0; t < m_nNumMax; ++t)
		{
			index = rand() % m_nNumMax;
			temp_pt = PointList[index];
			PointList[index] = PointList[t];
			PointList[t] = temp_pt;
		}

		glDrawBuffer(GL_FRONT_AND_BACK);
		m_pDoc->setSize(size);
		for(int t = 0; t < m_nNumMax; ++t)
			m_pDoc->m_pCurrentBrush->BrushMove( PointList[t], PointList[t] );
		glFlush();
		SaveCurrentContent();
		size /= 2;
	}
	

	printf("finish");
}

void PaintView::paintLayer(unsigned char* canvas, unsigned char* referenceImage, int R)
{
	double* D = new double[m_nDrawWidth*m_nDrawHeight];
	Point max;
	GLubyte color1[3], color2[3];
	double grid = m_pDoc->m_nPaintlyGridSize * R;


	for (int y = 0; y < m_nDrawHeight; ++y)
		for (int x = 0; x < m_nDrawWidth; ++x)
		{
			memcpy(color1, canvas + 3 * (x + y * m_nDrawWidth), 3);
			memcpy(color2, referenceImage + 3 * (x + y * m_nDrawWidth), 3);
			D[x+y*m_nDrawWidth] = ColorDiff(color1, color2);
		}

	for (int y = 0; y < m_nDrawHeight; y += grid)
		for (int x = 0; x < m_nDrawWidth; x += grid)
		{
			if (AreaError(x, y, grid / 2, max, D) > m_pDoc->m_nPaintlyTheshold)
			{
				if (!m_pllMax)
					m_pllMax = new Pointll(max.x, max.y);
				else
				{
					Pointll* temp = m_pllMax;
					while(temp->next)
						temp = temp->next;
					temp->next = new Pointll(max.x, max.y);
				}
				++m_nNumMax;
				//printf("%d %d max: %d %d\n", x, y, max.x, max.y);
			}
		}
}

void PaintView::makeSplineStroke(int x_0, int y_0, int R, unsigned char* referenceImage)
{
}

double PaintView::AreaError(int x, int y, double grid, Point& max, double* D)
{
	int upper_x = (x + grid > m_nDrawWidth) ? m_nDrawWidth : x + grid,
		lower_x = (x - grid < 0) ? 0 : x - grid,
		upper_y = (y + grid > m_nDrawHeight) ? m_nDrawHeight : y + grid,
		lower_y = (y - grid < 0) ? 0 : y - grid;
	double error = 0;
	double nMax = 0;
	max = Point(lower_x, lower_y);

	for(int j = lower_y; j < upper_y; ++j)
		for(int i = lower_x; i < upper_x; ++i)
		{
			error += D[i+j*m_nDrawWidth];
			if (D[i+j*m_nDrawWidth] > nMax)
			{
				D[i + j * m_nDrawWidth];
				max = Point(i, j);
			}
		}
	return error / (4 * grid * grid);
}

double PaintView::ColorDiff(GLubyte* color1, GLubyte* color2)
{
	return sqrt(pow(*(color1) - *(color2), 2) + pow(*(color1+1) - *(color2+1), 2) + pow(*(color1+2) - *(color2+2), 2));
}

GLubyte* PaintView::GetColor(unsigned char* source, int x, int y )
{
	if ( x < 0 ) 
		x = 0;
	else if ( x >= m_nDrawWidth ) 
		x = m_nDrawWidth-1;

	if ( y < 0 ) 
		y = 0;
	else if ( y >= m_nDrawHeight ) 
		y = m_nDrawHeight-1;

	return (GLubyte*)(source + 3 * (y*m_nDrawHeight + x));
}