#ifndef __AL_BLEND__
#define __AL_BLEND__
/*         ______   ___    ___
 *        /\  _  \ /\_ \  /\_ \
 *        \ \ \L\ \\//\ \ \//\ \      __     __   _ __   ___
 *         \ \  __ \ \ \ \  \ \ \   /'__`\ /'_ `\/\`'__\/ __`\
 *          \ \ \/\ \ \_\ \_ \_\ \_/\  __//\ \L\ \ \ \//\ \L\ \
 *           \ \_\ \_\/\____\/\____\ \____\ \____ \ \_\\ \____/
 *            \/_/\/_/\/____/\/____/\/____/\/___L\ \/_/ \/___/
 *                                           /\____/
 *                                           \_/__/
 *
 *      Main header file for the entire Allegro blend library.
 *
 *      By Ray Burgemeestre
 *
 *      All the macro's and research was done by Nathan Moinvaziri.
 *      I just made an allegro interface for the macro's on his 
 *      blog post [1].
 *
 *      Some adjustments were made to make it compatible with my
 *      compiler (Visual studio 2010 c++ compiler).
 *
 *      This implementation is header only, so you only need to
 *      include this file after allegro.h, and nothing else.
 *
 *      [1]: http://www.nathanm.com/photoshop-blending-math/
 *      See readme.txt for copyright information.
 */

typedef double float64;
typedef int int32;
typedef unsigned char uint8;

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#define ChannelBlend_Normal(B,L)     ((uint8)(B)) 
#define ChannelBlend_Lighten(B,L)    ((uint8)((L > B) ? L:B)) 
#define ChannelBlend_Darken(B,L)     ((uint8)((L > B) ? B:L)) 
#define ChannelBlend_Multiply(B,L)   ((uint8)((B * L) / 255)) 
#define ChannelBlend_Average(B,L)    ((uint8)((B + L) / 2)) 
#define ChannelBlend_Add(B,L)        ((uint8)(min(255, (B + L)))) 
#define ChannelBlend_Subtract(B,L)   ((uint8)((B + L < 255) ? 0:(B + L - 255))) 
#define ChannelBlend_Difference(B,L) ((uint8)(abs(B - L))) 
#define ChannelBlend_Negation(B,L)   ((uint8)(255 - abs(255 - B - L))) 
#define ChannelBlend_Screen(B,L)     ((uint8)(255 - (((255 - B) * (255 - L)) >> 8))) 
#define ChannelBlend_Exclusion(B,L)  ((uint8)(B + L - 2 * B * L / 255)) 
#define ChannelBlend_Overlay(B,L)    ((uint8)((L < 128) ? (2 * B * L / 255):(255 - 2 * (255 - B) * (255 - L) / 255))) 
#define ChannelBlend_SoftLight(B,L)  ((uint8)((L < 128)?(2*((B>>1)+64))*((float)L/255):(255-(2*(255-((B>>1)+64))*(float)(255-L)/255)))) 
#define ChannelBlend_HardLight(B,L)  (ChannelBlend_Overlay(L,B)) 
#define ChannelBlend_ColorDodge(B,L) ((uint8)((L == 255) ? L:min(255, ((B << 8 ) / (255 - L))))) 
#define ChannelBlend_ColorBurn(B,L)  ((uint8)((L == 0) ? L:max(0, (255 - ((255 - B) << 8 ) / L)))) 
#define ChannelBlend_LinearDodge(B,L)(ChannelBlend_Add(B,L)) 
#define ChannelBlend_LinearBurn(B,L) (ChannelBlend_Subtract(B,L)) 
#define ChannelBlend_LinearLight(B,L)((uint8)(L < 128)?ChannelBlend_LinearBurn(B,(2 * L)):ChannelBlend_LinearDodge(B,(2 * (L - 128)))) 
#define ChannelBlend_VividLight(B,L) ((uint8)(L < 128)?ChannelBlend_ColorBurn(B,(2 * L)):ChannelBlend_ColorDodge(B,(2 * (L - 128)))) 
#define ChannelBlend_PinLight(B,L)   ((uint8)(L < 128)?ChannelBlend_Darken(B,(2 * L)):ChannelBlend_Lighten(B,(2 * (L - 128)))) 
#define ChannelBlend_HardMix(B,L)    ((uint8)((ChannelBlend_VividLight(B,L) < 128) ? 0:255)) 
#define ChannelBlend_Reflect(B,L)    ((uint8)((L == 255) ? L:min(255, (B * B / (255 - L))))) 
#define ChannelBlend_Glow(B,L)       (ChannelBlend_Reflect(L,B)) 
#define ChannelBlend_Phoenix(B,L)    ((uint8)(min(B,L) - max(B,L) + 255)) 
#define ChannelBlend_Alpha(B,L,O)    ((uint8)(O * B + (1 - O) * L)) 
#define ChannelBlend_AlphaF(B,L,F,O) (ChannelBlend_Alpha(F(B,L),B,O)) 

#define ColorBlend_Buffer(T,B,L,M)      (T)[0] = ChannelBlend_##M((B)[0], (L)[0]), \
                                        (T)[1] = ChannelBlend_##M((B)[1], (L)[1]), \
                                        (T)[2] = ChannelBlend_##M((B)[2], (L)[2])

#define ColorBlend_Normal(T,B,L)        (ColorBlend_Buffer(T,B,L,Normal)) 
#define ColorBlend_Lighten(T,B,L)       (ColorBlend_Buffer(T,B,L,Lighten)) 
#define ColorBlend_Darken(T,B,L)        (ColorBlend_Buffer(T,B,L,Darken)) 
#define ColorBlend_Multiply(T,B,L)      (ColorBlend_Buffer(T,B,L,Multiply)) 
#define ColorBlend_Average(T,B,L)       (ColorBlend_Buffer(T,B,L,Average)) 
#define ColorBlend_Add(T,B,L)           (ColorBlend_Buffer(T,B,L,Add)) 
#define ColorBlend_Subtract(T,B,L)      (ColorBlend_Buffer(T,B,L,Subtract)) 
#define ColorBlend_Difference(T,B,L)    (ColorBlend_Buffer(T,B,L,Difference)) 
#define ColorBlend_Negation(T,B,L)      (ColorBlend_Buffer(T,B,L,Negation)) 
#define ColorBlend_Screen(T,B,L)        (ColorBlend_Buffer(T,B,L,Screen)) 
#define ColorBlend_Exclusion(T,B,L)     (ColorBlend_Buffer(T,B,L,Exclusion)) 
#define ColorBlend_Overlay(T,B,L)       (ColorBlend_Buffer(T,B,L,Overlay)) 
#define ColorBlend_SoftLight(T,B,L)     (ColorBlend_Buffer(T,B,L,SoftLight)) 
#define ColorBlend_HardLight(T,B,L)     (ColorBlend_Buffer(T,B,L,HardLight)) 
#define ColorBlend_ColorDodge(T,B,L)    (ColorBlend_Buffer(T,B,L,ColorDodge)) 
#define ColorBlend_ColorBurn(T,B,L)     (ColorBlend_Buffer(T,B,L,ColorBurn)) 
#define ColorBlend_LinearDodge(T,B,L)   (ColorBlend_Buffer(T,B,L,LinearDodge)) 
#define ColorBlend_LinearBurn(T,B,L)    (ColorBlend_Buffer(T,B,L,LinearBurn)) 
#define ColorBlend_LinearLight(T,B,L)   (ColorBlend_Buffer(T,B,L,LinearLight)) 
#define ColorBlend_VividLight(T,B,L)    (ColorBlend_Buffer(T,B,L,VividLight)) 
#define ColorBlend_PinLight(T,B,L)      (ColorBlend_Buffer(T,B,L,PinLight)) 
#define ColorBlend_HardMix(T,B,L)       (ColorBlend_Buffer(T,B,L,HardMix)) 
#define ColorBlend_Reflect(T,B,L)       (ColorBlend_Buffer(T,B,L,Reflect)) 
#define ColorBlend_Glow(T,B,L)          (ColorBlend_Buffer(T,B,L,Glow)) 
#define ColorBlend_Phoenix(T,B,L)       (ColorBlend_Buffer(T,B,L,Phoenix)) 
#define ColorBlend_Hue(T,B,L)            ColorBlend_Hls(T,B,L,HueL,LuminationB,SaturationB) 
#define ColorBlend_Saturation(T,B,L)     ColorBlend_Hls(T,B,L,HueB,LuminationB,SaturationL) 
#define ColorBlend_Color(T,B,L)          ColorBlend_Hls(T,B,L,HueL,LuminationB,SaturationL) 
#define ColorBlend_Luminosity(T,B,L)     ColorBlend_Hls(T,B,L,HueB,LuminationL,SaturationB) 

#define ColorBlend_Hls(T,B,L,O1,O2,O3) {                                        \
    float64 HueB, LuminationB, SaturationB;                                     \
    float64 HueL, LuminationL, SaturationL;                                     \
    Color_RgbToHls((B)[2],(B)[1],(B)[0], &HueB, &LuminationB, &SaturationB);    \
    Color_RgbToHls((L)[2],(L)[1],(L)[0], &HueL, &LuminationL, &SaturationL);    \
    Color_HlsToRgb(O1,O2,O3,&(T)[2],&(T)[1],&(T)[0]);                           \
    } 

int32 Color_HueToRgb(float64 M1, float64 M2, float64 Hue, float64 *Channel) 
{ 
    if (Hue < 0.0) 
        Hue += 1.0; 
    else if (Hue > 1.0) 
        Hue -= 1.0; 

    if ((6.0 * Hue) < 1.0) 
        *Channel = (M1 + (M2 - M1) * Hue * 6.0); 
    else if ((2.0 * Hue) < 1.0) 
        *Channel = (M2); 
    else if ((3.0 * Hue) < 2.0) 
        *Channel = (M1 + (M2 - M1) * ((2.0F / 3.0F) - Hue) * 6.0); 
    else 
        *Channel = (M1); 

    return true; 
} 

int32 Color_RgbToHls(uint8 Red, uint8 Green, uint8 Blue, float64 *Hue, float64 *Lumination, float64 *Saturation) 
{ 
    float64 Delta; 
    float64 Max, Min; 
    float64 Redf, Greenf, Bluef; 

    Redf    = ((float64)Red   / 255.0F); 
    Greenf  = ((float64)Green / 255.0F); 
    Bluef   = ((float64)Blue  / 255.0F);  

    Max     = max(max(Redf, Greenf), Bluef); 
    Min     = min(min(Redf, Greenf), Bluef); 

    *Hue        = 0; 
    *Lumination = (Max + Min) / 2.0F; 
    *Saturation = 0; 

    if (Max == Min) 
        return true; 

    Delta = (Max - Min); 

    if (*Lumination < 0.5) 
        *Saturation = Delta / (Max + Min); 
    else 
        *Saturation = Delta / (2.0 - Max - Min); 

    if (Redf == Max) 
        *Hue = (Greenf - Bluef) / Delta; 
    else if (Greenf == Max) 
        *Hue = 2.0 + (Bluef - Redf) / Delta; 
    else 
        *Hue = 4.0 + (Redf - Greenf) / Delta; 

    *Hue /= 6.0;  

    if (*Hue < 0.0) 
        *Hue += 1.0;        

    return true; 
} 

int32 Color_HlsToRgb(float64 Hue, float64 Lumination, float64 Saturation, uint8 *Red, uint8 *Green, uint8 *Blue) 
{ 
    float64 M1, M2; 
    float64 Redf, Greenf, Bluef; 

    if (Saturation == 0) 
        { 
        Redf    = Lumination; 
        Greenf  = Lumination; 
        Bluef   = Lumination; 
        } 
    else 
        { 
        if (Lumination <= 0.5) 
            M2 = Lumination * (1.0 + Saturation); 
        else 
            M2 = Lumination + Saturation - Lumination * Saturation; 

        M1 = (2.0 * Lumination - M2); 

        Color_HueToRgb(M1, M2, Hue + (1.0F / 3.0F), &Redf); 
        Color_HueToRgb(M1, M2, Hue, &Greenf); 
        Color_HueToRgb(M1, M2, Hue - (1.0F / 3.0F), &Bluef); 
        } 

    *Red    = (uint8)(Redf * 255); 
    *Blue   = (uint8)(Bluef * 255); 
    *Green  = (uint8)(Greenf * 255); 

    return true; 
} 

#define COLOR_OPAQUE                (0) 
#define COLOR_TRANSPARENT           (127) 

#define RGB_SIZE                    (3) 
#define RGB_BPP                     (24) 
#define RGB_MAXRED                  (255) 
#define RGB_MAXGREEN                (255) 
#define RGB_MAXBLUE                 (255) 

#define ARGB_SIZE                   (4) 
#define ARGB_BPP                    (32) 
#define ARGB_MAXALPHA               (127) 
#define ARGB_MAXRED                 (RGB_MAXRED) 
#define ARGB_MAXGREEN               (RGB_MAXGREEN) 
#define ARGB_MAXBLUE                (RGB_MAXBLUE) 

/*********************************************************************/ 

#define Color_GetChannel(c,shift)   ((uint8)((c) >> (shift))) 
#define Color_Reverse(c,bpp)        ((((uint8)(c) << 24) | ((uint8)((c) >> 8 ) << 16) | ((uint8)((c) >> 16) << 8 ) | \
                                    ((uint8)((c) >> 24))) >> (32 - (bpp)))

#define Rgb_ByteWidth(width)        ((width) * RGB_SIZE) 
#define Rgb_PixelWidth(width)       ((width) / RGB_SIZE) 

#define Rgb_GetRed(rgb)             (Color_GetChannel(rgb, 0)) 
#define Rgb_GetGreen(rgb)           (Color_GetChannel(rgb, 8)) 
#define Rgb_GetBlue(rgb)            (Color_GetChannel(rgb, 16)) 

#define Rgba_GetRed(rgba)           (Color_GetChannel(rgba, 24)) 
#define Rgba_GetGreen(rgba)         (Color_GetChannel(rgba, 16)) 
#define Rgba_GetBlue(rgba)          (Color_GetChannel(rgba, 8)) 
#define Rgba_GetAlpha(rgba)         (Color_GetChannel(rgba, 0)) 

#define Argb_GetAlpha(argb)         (Color_GetChannel(argb, 24)) 
#define Argb_GetRed(argb)           (Color_GetChannel(argb, 16)) 
#define Argb_GetGreen(argb)         (Color_GetChannel(argb, 8)) 
#define Argb_GetBlue(argb)          (Color_GetChannel(argb, 0)) 

#define MakeRgb(r,g,b)              (((uint32)(uint8)(b) << 16) | ((uint16)(uint8)(g) << 8 ) | (uint8)(r)) 
#define MakeRgba(r,g,b,a)           (((uint32)(uint8)(r) << 24) | ((uint16)(uint8)(g) << 16) | ((uint16)(uint8)(b) << 8 ) | (uint8)(a)) 
#define MakeArgb(a,r,g,b)           (((uint32)(uint8)(a) << 24) | ((uint32)(uint8)(r) << 16) | ((uint16)(uint8)(g) << 8 ) | (uint8)(b)) 

#define HexToRgb(hex)               (MakeRgb(((hex & 0xFF0000) >> 16), ((hex & 0x00FF00) >> 8 ), (hex & 0xFF))) 

int blender_lighten(int &basecolor, int &blendcolor)
{
	return makecol(
		ChannelBlend_Lighten(getr(basecolor), getr(blendcolor)),
		ChannelBlend_Lighten(getg(basecolor), getg(blendcolor)),
		ChannelBlend_Lighten(getb(basecolor), getb(blendcolor))
	);
}

int blender_darken(int &basecolor, int &blendcolor)
{
	return makecol(
		ChannelBlend_Darken(getr(basecolor), getr(blendcolor)),
		ChannelBlend_Darken(getg(basecolor), getg(blendcolor)),
		ChannelBlend_Darken(getb(basecolor), getb(blendcolor))
	);
}

int blender_multiply(int &basecolor, int &blendcolor)
{
	return makecol(
		ChannelBlend_Multiply(getr(basecolor), getr(blendcolor)),
		ChannelBlend_Multiply(getg(basecolor), getg(blendcolor)),
		ChannelBlend_Multiply(getb(basecolor), getb(blendcolor))
	);
}

int blender_average(int &basecolor, int &blendcolor)
{
	return makecol(
		ChannelBlend_Average(getr(basecolor), getr(blendcolor)),
		ChannelBlend_Average(getg(basecolor), getg(blendcolor)),
		ChannelBlend_Average(getb(basecolor), getb(blendcolor))
	);
}

int blender_add(int &basecolor, int &blendcolor)
{
	return makecol(
		ChannelBlend_Add(getr(basecolor), getr(blendcolor)),
		ChannelBlend_Add(getg(basecolor), getg(blendcolor)),
		ChannelBlend_Add(getb(basecolor), getb(blendcolor))
	);
}

int blender_subtract(int &basecolor, int &blendcolor)
{
	return makecol(
		ChannelBlend_Subtract(getr(basecolor), getr(blendcolor)),
		ChannelBlend_Subtract(getg(basecolor), getg(blendcolor)),
		ChannelBlend_Subtract(getb(basecolor), getb(blendcolor))
	);
}

int blender_difference(int &basecolor, int &blendcolor)
{
	return makecol(
		ChannelBlend_Difference(getr(basecolor), getr(blendcolor)),
		ChannelBlend_Difference(getg(basecolor), getg(blendcolor)),
		ChannelBlend_Difference(getb(basecolor), getb(blendcolor))
	);
}

int blender_negation(int &basecolor, int &blendcolor)
{
	return makecol(
		ChannelBlend_Negation(getr(basecolor), getr(blendcolor)),
		ChannelBlend_Negation(getg(basecolor), getg(blendcolor)),
		ChannelBlend_Negation(getb(basecolor), getb(blendcolor))
	);
}

int blender_screen(int &basecolor, int &blendcolor)
{
	return makecol(
		ChannelBlend_Screen(getr(basecolor), getr(blendcolor)),
		ChannelBlend_Screen(getg(basecolor), getg(blendcolor)),
		ChannelBlend_Screen(getb(basecolor), getb(blendcolor))
	);
}

int blender_exclusion(int &basecolor, int &blendcolor)
{
	return makecol(
		ChannelBlend_Exclusion(getr(basecolor), getr(blendcolor)),
		ChannelBlend_Exclusion(getg(basecolor), getg(blendcolor)),
		ChannelBlend_Exclusion(getb(basecolor), getb(blendcolor))
	);
}

int blender_overlay(int &basecolor, int &blendcolor)
{
	return makecol(
		ChannelBlend_Overlay(getr(basecolor), getr(blendcolor)),
		ChannelBlend_Overlay(getg(basecolor), getg(blendcolor)),
		ChannelBlend_Overlay(getb(basecolor), getb(blendcolor))
	);
}

int blender_softlight(int &basecolor, int &blendcolor)
{
	return makecol(
		ChannelBlend_SoftLight(getr(basecolor), getr(blendcolor)),
		ChannelBlend_SoftLight(getg(basecolor), getg(blendcolor)),
		ChannelBlend_SoftLight(getb(basecolor), getb(blendcolor))
	);
}

int blender_hardlight(int &basecolor, int &blendcolor)
{
	return makecol(
		ChannelBlend_HardLight(getr(basecolor), getr(blendcolor)),
		ChannelBlend_HardLight(getg(basecolor), getg(blendcolor)),
		ChannelBlend_HardLight(getb(basecolor), getb(blendcolor))
	);
}

int blender_colordodge(int &basecolor, int &blendcolor)
{
	return makecol(
		ChannelBlend_ColorDodge(getr(basecolor), getr(blendcolor)),
		ChannelBlend_ColorDodge(getg(basecolor), getg(blendcolor)),
		ChannelBlend_ColorDodge(getb(basecolor), getb(blendcolor))
	);
}

int blender_colorburn(int &basecolor, int &blendcolor)
{
	return makecol(
		ChannelBlend_ColorBurn(getr(basecolor), getr(blendcolor)),
		ChannelBlend_ColorBurn(getg(basecolor), getg(blendcolor)),
		ChannelBlend_ColorBurn(getb(basecolor), getb(blendcolor))
	);
}

int blender_lineardodge(int &basecolor, int &blendcolor)
{
	return makecol(
		ChannelBlend_LinearDodge(getr(basecolor), getr(blendcolor)),
		ChannelBlend_LinearDodge(getg(basecolor), getg(blendcolor)),
		ChannelBlend_LinearDodge(getb(basecolor), getb(blendcolor))
	);
}
int blender_linearburn(int &basecolor, int &blendcolor)
{
	return makecol(
		ChannelBlend_LinearBurn(getr(basecolor), getr(blendcolor)),
		ChannelBlend_LinearBurn(getg(basecolor), getg(blendcolor)),
		ChannelBlend_LinearBurn(getb(basecolor), getb(blendcolor))
	);
}
int blender_linearlight(int &basecolor, int &blendcolor)
{
	return makecol(
		ChannelBlend_LinearLight(getr(basecolor), getr(blendcolor)),
		ChannelBlend_LinearLight(getg(basecolor), getg(blendcolor)),
		ChannelBlend_LinearLight(getb(basecolor), getb(blendcolor))
	);
}

int blender_vividlight(int &basecolor, int &blendcolor)
{
	return makecol(
		ChannelBlend_VividLight(getr(basecolor), getr(blendcolor)),
		ChannelBlend_VividLight(getg(basecolor), getg(blendcolor)),
		ChannelBlend_VividLight(getb(basecolor), getb(blendcolor))
	);
}
int blender_pinlight(int &basecolor, int &blendcolor)
{
	return makecol(
		ChannelBlend_PinLight(getr(basecolor), getr(blendcolor)),
		ChannelBlend_PinLight(getg(basecolor), getg(blendcolor)),
		ChannelBlend_PinLight(getb(basecolor), getb(blendcolor))
	);
}

int blender_hardmix(int &basecolor, int &blendcolor)
{
	return makecol(
		ChannelBlend_HardMix(getr(basecolor), getr(blendcolor)),
		ChannelBlend_HardMix(getg(basecolor), getg(blendcolor)),
		ChannelBlend_HardMix(getb(basecolor), getb(blendcolor))
	);
}

int blender_reflect(int &basecolor, int &blendcolor)
{
	return makecol(
		ChannelBlend_Reflect(getr(basecolor), getr(blendcolor)),
		ChannelBlend_Reflect(getg(basecolor), getg(blendcolor)),
		ChannelBlend_Reflect(getb(basecolor), getb(blendcolor))
	);
}
int blender_glow(int &basecolor, int &blendcolor)
{
	return makecol(
		ChannelBlend_Glow(getr(basecolor), getr(blendcolor)),
		ChannelBlend_Glow(getg(basecolor), getg(blendcolor)),
		ChannelBlend_Glow(getb(basecolor), getb(blendcolor))
	);
}
int blender_phoenix(int &basecolor, int &blendcolor)
{
	return makecol(
		ChannelBlend_Phoenix(getr(basecolor), getr(blendcolor)),
		ChannelBlend_Phoenix(getg(basecolor), getg(blendcolor)),
		ChannelBlend_Phoenix(getb(basecolor), getb(blendcolor))
	);
}

int blender_hue(int &basecolor, int &blendcolor)
{
    float64 HueB, LuminationB, SaturationB;                                     
    float64 HueL, LuminationL, SaturationL;                                     

	Color_RgbToHls(getr(basecolor),getg(basecolor),getb(basecolor), &HueB, &LuminationB, &SaturationB);
    Color_RgbToHls(getr(blendcolor),getg(blendcolor), getb(blendcolor), &HueL, &LuminationL, &SaturationL);    
	
	uint8 r, g, b;
	Color_HlsToRgb(HueL,LuminationB,SaturationB, &r, &g, &b);
	return makecol(r, g, b);
}

int blender_saturation(int &basecolor, int &blendcolor)
{
    float64 HueB, LuminationB, SaturationB;                                     
    float64 HueL, LuminationL, SaturationL;                                     

	Color_RgbToHls(getr(basecolor),getg(basecolor),getb(basecolor), &HueB, &LuminationB, &SaturationB);
    Color_RgbToHls(getr(blendcolor),getg(blendcolor), getb(blendcolor), &HueL, &LuminationL, &SaturationL);    
	
	uint8 r, g, b;
	Color_HlsToRgb(HueB,LuminationB,SaturationL, &r, &g, &b);
	return makecol(r, g, b);
}

int blender_color(int &basecolor, int &blendcolor)
{
    float64 HueB, LuminationB, SaturationB;                                     
    float64 HueL, LuminationL, SaturationL;                                     

	Color_RgbToHls(getr(basecolor),getg(basecolor),getb(basecolor), &HueB, &LuminationB, &SaturationB);
    Color_RgbToHls(getr(blendcolor),getg(blendcolor), getb(blendcolor), &HueL, &LuminationL, &SaturationL);    
	
	uint8 r, g, b;
	Color_HlsToRgb(HueL,LuminationB,SaturationL, &r, &g, &b);
	return makecol(r, g, b);
}

int blender_luminosity(int &basecolor, int &blendcolor)
{
    float64 HueB, LuminationB, SaturationB;                                     
    float64 HueL, LuminationL, SaturationL;                                     

	Color_RgbToHls(getr(basecolor),getg(basecolor),getb(basecolor), &HueB, &LuminationB, &SaturationB);
    Color_RgbToHls(getr(blendcolor),getg(blendcolor), getb(blendcolor), &HueL, &LuminationL, &SaturationL);    
	
	uint8 r, g, b;
	Color_HlsToRgb(HueB,LuminationL,SaturationB, &r, &g, &b);
	return makecol(r, g, b);
}


typedef int (*blender_func_ptr)(int &basecolor, int &blendcolor);

void put_blended_pixel(BITMAP *dest, int x, int y, int color, blender_func_ptr blender_function)
{
	int basecolor = getpixel(dest, x, y);
	putpixel(dest, x, y, blender_function(basecolor, color));
}

#endif // __AL_BLEND__
/* vim: set tabstop=4 sts=4 noexpandtab: */
