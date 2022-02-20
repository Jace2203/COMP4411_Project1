//
// WarpBrush.cpp
//
// The implementation of Warp Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "ImpressionistDoc.h"
#include "ImpressionistUI.h"
#include "WarpBrush.h"

extern float frand();

WarpBrush::WarpBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void WarpBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	BrushMove( source, target );
}

void WarpBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "WarpBrush::BrushMove  document is NULL\n" );
		return;
	}


}

void WarpBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

