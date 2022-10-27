#ifndef m2co_h
#define m2co_h

#include <stdio.h>
#include <string>
#include <string.h>

void hextorgb(const char* hex, int* r, int*g, int* b)
{
    sscanf(hex, "#%02x%02x%02x", r, g, b);
}

#ifdef __cplusplus
void setColor(const char* hex)
#else
void setColorHex(const char* hex)
#endif
{
    int r, g, b;
    hextorgb(hex, &r, &g, &b);
    printf("\x1b[38;2;%i;%i;%im", r, g, b);
}

void setColor(int r, int g, int b)
{
    printf("\x1b[38;2;%i;%i;%im", r, g, b);
}

inline void endColor()
{
    printf("\x1b[0m");
}

inline void ColorPrint(const char* text, int r, int g, int b)
{
    setColor(r, g, b);
    printf(text);
    endColor();
}

#ifdef __cplusplus
inline void ColorPrint(const char* text, const char* hex)
#else
inline void ColorPrintHex(const char* text, const char* hex)
#endif
{
    #ifdef __cplusplus
    setColor(hex);
    #else
    setColorHex(hex);
    #endif
    printf(text);
    endColor();
}

void GradientPrint(const char* str, int sr, int sg, int sb, int tr, int tg, int tb)
{
    float lenText = (float)strlen(str);
    float dr = static_cast<float>(tr - sr) / lenText;
    float dg = static_cast<float>(tg - sg) / lenText;
    float db = static_cast<float>(tb - sb) / lenText;

    for(int i = 0; i < (int)lenText; i++)
    {
        setColor(sr + (dr * i), sg + (dg * i), sb + (db * i));
        putchar(str[i]);
    }
    endColor();
}

#ifdef __cplusplus

template <typename T>
void setColor(T color)
{
    printf("\x1b[38;2;%i;%i;%im", color.r, color.g, color.b);
}

void GradientPrint(const std::string& str, int sr, int sg, int sb, int tr, int tg, int tb)
{
    float lenText = str.length();
    float dr = static_cast<float>(tr - sr) / lenText;
    float dg = static_cast<float>(tg - sg) / lenText;
    float db = static_cast<float>(tb - sb) / lenText;

    for(int i = 0; i < static_cast<int>(lenText); i++)
    {
        setColor(sr + (dr * i), sg + (dg * i), sb + (db * i));
        putchar(str[i]);
    }
    endColor();
}

void GradientPrint(const std::string& str, const char* start, const char* end)
{
    int sr, sg, sb, tr, tg, tb;
    hextorgb(start, &sr, &sg, &sb);
    hextorgb(end, &tr, &tg, &tb);

    float lenText = str.length();
    float dr = static_cast<float>(tr - sr) / lenText;
    float dg = static_cast<float>(tg - sg) / lenText;
    float db = static_cast<float>(tb - sb) / lenText;

    for(int i = 0; i < static_cast<int>(lenText); i++)
    {
        setColor(sr + (dr * i), sg + (dg * i), sb + (db * i));
        putchar(str[i]);
    }
    endColor();
}

template <typename T, typename T2>
void GradientPrint(const std::string& str, T s, T2 t)
{
    float lenText = str.length();

    float dr = static_cast<float>(t.r - s.r) / lenText;
    float dg = static_cast<float>(t.g - s.g) / lenText;
    float db = static_cast<float>(t.b - s.b) / lenText;

    for(int i = 0; i < static_cast<int>(lenText); i++)
    {
        setColor(s.r + (dr * i), s.g + (dg * i), s.b + (db * i));
        putchar(str[i]);
    }
    endColor();
}

#endif

#endif
