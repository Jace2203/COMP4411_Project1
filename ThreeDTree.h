#ifndef THREEDTREE_H
#define THREEDTREE_H

class ThreeDTree
{
public:    
    class Color
    {
    public:
        Color();
        Color(int r, int g, int b);
        // Color(char* name);
        Color(unsigned char* color);
        
        ~Color();

        int r() const;
        int g() const;
        int b() const;

    private:
        unsigned char* rgb;
    };

    enum RGB
    {
        R = 0,
        G,
        B
    };

    ThreeDTree(Color** colors, int size, RGB rgb = R);

private:
    ThreeDTree *left, *right;
    Color* color;

    static void sortColor(Color** colors, Color** sorted_colors, int size, RGB rgb);
};

#endif