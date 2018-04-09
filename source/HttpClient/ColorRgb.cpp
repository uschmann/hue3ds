
#include <Hue/ColorRgb.h>
#include <math.h>

ColorRgb * ColorRgb::fromXy(float x, float y, float brightness) {
    ColorRgb * color = new ColorRgb();

    float z = 1.0f - x - y;
    float Y = brightness;
    float X = (Y / y) * x;
    float Z = (Y / y) * z;

    float r =  X * 1.656492f - Y * 0.354851f - Z * 0.255038f;
    float g = -X * 0.707196f + Y * 1.655397f + Z * 0.036152f;
    float b =  X * 0.051713f - Y * 0.121364f + Z * 1.011530f;

    r = r <= 0.0031308f ? 12.92f * r : (1.0f + 0.055f) * pow(r, (1.0f / 2.4f)) - 0.055f;
    g = g <= 0.0031308f ? 12.92f * g : (1.0f + 0.055f) * pow(g, (1.0f / 2.4f)) - 0.055f;
    b = b <= 0.0031308f ? 12.92f * b : (1.0f + 0.055f) * pow(b, (1.0f / 2.4f)) - 0.055f;

    color->r = r * 255;
    color->g = g * 255;
    color->b = b * 255;

    return color;
}

Uint32 ColorRgb::toInt() {
    return this->r | this->g >> 8 | this->b >>16 | 0xFF >> 24;
}