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
	void fade_in();

	void draw_fade(int old_width, int old_height, unsigned char* old_painting);

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

	LinkedList* m_SavedPhoto;
};

#endif