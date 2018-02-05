#include "color.hpp"
// // Hue
// static auto hsv(T)(T h)
// {
//     this(h, 255, 255, 255);
// }
//
// // HSV
// static auto hsv(T, U, V)(T h, U s, V v)
// {
//     this(h, s, v, 255);
// }
//
// // HSVA
// // TODO: h 0-360
// static auto hsv(T, U, V, W)(T h, U s, V v, W a)
// {
//     if (s == 0)
//     {
//         return Color(v, a);
//     }
//
//     int h_ = h / 60;
//     float f = cast(float)h/60 - h_;
//     ubyte m = cast(ubyte)(v * (1 - cast(float)s/255));
//     ubyte n = cast(ubyte)(v * (1 - cast(float)s/255 * f));
//     ubyte k = cast(ubyte)(v * (1 - cast(float)s/255 * (1-f)));
//
//     ubyte r, g, b;
//     switch (h_)
//     {
//     case 0:
//         r = v; g = k; b = m;
//         break;
//     case 1:
//         r = n; g = v; b = m;
//         break;
//     case 2:
//         r = m; g = v; b = k;
//         break;
//     case 3:
//         r = m; g = n; b = v;
//         break;
//     case 4:
//         r = k; g = m; b = v;
//         break;
//     case 5:
//         r = v; g = m; b = n;
//         break;
//     default:
//         assert(0);
//     }
//
//     return Color(r, g, b, a);
// }
