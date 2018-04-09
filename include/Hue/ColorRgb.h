

#ifndef ColorRgb__h
#define ColorRgb__h

#include <SDL/SDL.h>

class ColorRgb {
    public:
        Uint8 r;
        Uint8 g;
        Uint8 b;
        static ColorRgb * fromXy(float x, float y, float brightness);
        Uint32 toInt();
};

#endif