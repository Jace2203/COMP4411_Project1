//
// paintview.h
//
// The header file for painting view of the input images
//

#ifndef PAINTVIEW_H
#define PAINTVIEW_H

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>

class ImpressionistDoc;

class LinkedList
{
public:
	LinkedList(int w, int h);
	~LinkedList();
	char* photo;
	LinkedList* next;
};

class Pointll
{
public:
	Pointll(int x, int y);
	~Pointll();
	Point xy;
	Pointll* next;
};

class PaintView : public Fl_Gl_Window
{
public:
	PaintView(int x, int y, int w, int h, const char* l);
	void draw();
	int handle(int event);

	void refresh();
	
	void resizeWindow(int width, int height);

	void SaveCurrentContent();

	void RestoreContent();

	void CreateSavedPhoto();
	void SaveForUndo();
	void LoadForUndo();
	void AutoPaint(int spacing);

	void DrawPaintly();
	void paintLayer(unsigned char* canvas, unsigned char* referenceImage, int R);
	double AreaError(int x, int y, double grid, Point& max, double* D);
	double ColorDiff(GLubyte* color1, GLubyte* color2);
	GLubyte* GetColor(unsigned char* source, int x, int y);
	void makeSplineStroke(int x_0, int y_0, int R, unsigned char* referenceImage);

	ImpressionistDoc *m_pDoc;

private:
	GLvoid* m_pPaintBitstart;
	int		m_nDrawWidth,
			m_nDrawHeight,
			m_nStartRow, 
			m_nEndRow,
			m_nStartCol, 
			m_nEndCol,
			m_nWindowWidth, 
			m_nWindowHeight;
	Point	m_pAutoPaintPoint;
	Pointll* m_pllMax;
	int		 m_nNumMax;

	LinkedList* m_SavedPhoto;
};

#endif