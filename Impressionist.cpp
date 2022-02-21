//
// impressionist.cpp
//
// The main driver program for the other parts. We have two major components,
// UI and Doc.
// They do have a link to each other as their member such that they can 
// communicate.
//

#include <stdio.h>

#include <FL/Fl.h>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

#include "impressionistUI.h"
#include "impressionistDoc.h"

#include "ThreeDTree.h"

ImpressionistUI *impUI;
ImpressionistDoc *impDoc;

int main(int	argc, 
		 char**	argv) 
{
	impDoc = new ImpressionistDoc();

	// Create the UI
	impUI = new ImpressionistUI();

	// Set the impDoc which is used as the bridge between UI and brushes
	impUI->setDocument(impDoc);
	impDoc->setUI(impUI);

	Fl::visual(FL_DOUBLE|FL_INDEX);

	impUI->show();
	
    int num = 7;
    ThreeDTree::Color** colors = new ThreeDTree::Color*[num];

    colors[0] = new ThreeDTree::Color(100,0,0);
    colors[1] = new ThreeDTree::Color(20,0,0);
    colors[2] = new ThreeDTree::Color(50,0,0);
    colors[3] = new ThreeDTree::Color(70,0,0);
    colors[4] = new ThreeDTree::Color(0,0,0);
    colors[5] = new ThreeDTree::Color(90,0,0);
    colors[6] = new ThreeDTree::Color(80,0,0);

    ThreeDTree* root = new ThreeDTree(colors, num, ThreeDTree::R);

    for (int i = 0; i < num; i++)
    {
		printf("%p\n", colors[i]);
        delete colors[i];
    }
    delete[] colors;

	return Fl::run();
}

// global functions
float frand()
{
	return (float)rand()/RAND_MAX;
}

int irand(int max)
{
	return rand()%max;
}
