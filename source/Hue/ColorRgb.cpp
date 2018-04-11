
#include <Hue/ColorRgb.h>
#include <math.h>

ColorRgb * ColorRgb::fromXy(float x, float y, float brightness) {
    ColorRgb * color = new ColorRgb();

    printf("brighntess: %.6f\n", brightness);

    float z = 1.0f - x - y;
    float Y = brightness;
    float X = (Y / y) * x;
    float Z = (Y / y) * z;

    float _r =  X * 1.656492f - Y * 0.354851f - Z * 0.255038f;
    float _g = -X * 0.707196f + Y * 1.655397f + Z * 0.036152f;
    float _b =  X * 0.051713f - Y * 0.121364f + Z * 1.011530f;

    printf("r: %.6f, g: %.6f, b: %.6f\n", _r, _g, _b);

    _r = _r <= 0.0031308f ? 12.92f * _r : (1.0f + 0.055f) * pow(_r, (1.0f / 2.4f)) - 0.055f;
    _g = _g <= 0.0031308f ? 12.92f * _g : (1.0f + 0.055f) * pow(_g, (1.0f / 2.4f)) - 0.055f;
    _b = _b <= 0.0031308f ? 12.92f * _b : (1.0f + 0.055f) * pow(_b, (1.0f / 2.4f)) - 0.055f;

    printf("r: %.6f, g: %.6f, b: %.6f\n", _r, _g, _b);
    printf("#######\n");

    color->r = (int)(_r * (float)255);
    color->g = (int)(_g * (float)255);
    color->b = (int)(_b * (float)255);

    return color;
}

Uint32 ColorRgb::toInt() {
    return this->r | this->g >> 8 | this->b >>16 | 0xFF >> 24;
}