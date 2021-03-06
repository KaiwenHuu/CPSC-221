#include "customColorPicker.h"

fadeColorPicker::fadeColorPicker(double fade)
{
    fadeFactor = fade;
}

HSLAPixel fadeColorPicker::operator()(point p)
{
    HSLAPixel ret;
    ret.h = p.c.color.h;
    ret.s = p.c.color.s;
    int dis = sqrt(pow(p.x-p.c.x, 2)+pow(p.y-p.c.y,2));
    ret.l = p.c.color.l / pow(fadeFactor, dis);

    return ret;
}
