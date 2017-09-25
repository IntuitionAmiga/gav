// Degolfed and optimized version of 2004 IOCCC winner by Gavare
// (c) 2017 Zayn Otley

#include <stdio.h>

const int horizontal = 1024;   //Horizontal resolution
const int vertical = 768;    //Vertical resolution
const int antialias_factor = 1;

const int J = 0;
const int K = -10;
const int L = -7;
const int multiplier = 1296;
const int N = 36;
const int O = 255;
const int P = 9;

//int _ = 1 << 15;
const int max_colours=32768;

int sphereX, S, sphereY;

const int D=2;

// For a given input value, set the global sphereX, sphereY and S values.
// TODO figure out what S represents
void locateSphere(int b) {
    // Changing these to an actual const byte array results in the lookup being loaded into a different location and with different alignment, all of whuch kills performance.
    // Each byte in the string is encoded so that the result is signed. Original subtracted 64 from the character value. This saves a pair of integer subtractions.
    sphereX = (int)"\xF1\xF1\xF1\xF1\xF8\xF8\xF6\xFA\xF6\xFA\xFF\xFF\x01\x01\x06\x06\x08\x08\x0D\x0D\x0F\x0F\xF5\xF5\xF5\xF5\xF7\xF7\xF9\xF9\x00\x00\xFE\xFE\xFE\x02\x02\x02\x07\x07\x09\x09\x0B\x0B"[b];
    sphereY = (int)"\x03\x00\xFD\xFA\xFA\x03\x00\x00\xFD\xFD\x00\xFD\xFA\x03\x00\xFD\xFA\x03\x00\xFD\xFA\x03\xF5\xF3\xF1\xEF\xF5\xF1\xF3\xEF\xF5\xF1\xF3\xF1\xEF\xF3\xF1\xEF\xF5\xF3\xF1\xEF\xF5\xF3"[b];

    //S = b < 22 ? 9 : 0;
    if (b < 22) {
        S = 9;
    } else {
        S = 0;
    }

//    D = 2;
}

int I(int x, int vertical, int horizontal) {
    vertical ? (horizontal ^= vertical, horizontal * horizontal > x ? (horizontal ^= vertical) : 0, I(x, vertical / 2, horizontal)) : (sphereX = horizontal);
    return 0;
}

int H(int x) {
    I(x, max_colours, 0);
    return 0;
}

int p;

int q(int c, int x, int y, int z, int k, int l, int m, int a, int b) {
    locateSphere(c);
    x -= sphereX * multiplier;
    y -= S * multiplier;
    z -= sphereY * multiplier;
    b = x * x / multiplier + y * y / multiplier + z * z / multiplier - D * D * multiplier;
    a = -x * k / multiplier - y * l / multiplier - z * m / multiplier;
    p = ((b = a * a / multiplier - b) >= 0 ? (I(b * multiplier, max_colours, 0), b = sphereX, a + (a > b ? -b : b)): -1.0);

    return 0;
}

int Z,W;

int o(int c, int x, int y, int z, int k, int l, int m, int a) {
    //Z = !c ? -1 : Z;
    if (!c) {
        Z=-1;
    } else {
        Z=Z;
    }

    c < 44 ? (q(c, x, y, z, k, l, m, 0, 0), (p > 0 && c != a && (p < W || Z < 0)) ? (W = p, Z = c) : 0, o(c + 1, x, y, z, k, l, m, a)): 0;

    return 0;
}

int RedGradient,GreenGradient,BlueGradient,u,v,w;

int gradient_fill(int e, int f, int g, int h, int i, int j, int d, int a, int b, int V) {
    //Think this whole function creates the gradient backdrop

    o(0, e, f, g, h, i, j, a);
    d > 0 && Z >= 0? (e += h * W / multiplier, f += i * W / multiplier, g += j * W / multiplier, locateSphere(Z), u = e - sphereX * multiplier,v = f - S * multiplier, w = g - sphereY * multiplier, b = (-2 * u - 2 * v + w) / 3,H(u * u + v * v + w * w), b /= D, b *= b, b *= 200, b /= (multiplier * multiplier),V = Z, sphereX != 0 ? (u = -u * multiplier / sphereX, v = -v * multiplier / sphereX, w = -w * multiplier / sphereX) : 0,sphereX = (h * u + i * v + j * w) / multiplier, h -= u * sphereX / (multiplier / 2),i -= v * sphereX / (multiplier / 2), j -= w * sphereX / (multiplier / 2),gradient_fill(e, f, g, h, i, j, d - 1, Z, 0, 0), RedGradient /= 2, GreenGradient /= 2, BlueGradient /= 2,V = V < 22? 7: (V < 30 ? 1: (V < 38 ? 2 : (V < 44 ? 4 : (V == 44 ? 6 : 3)))),RedGradient += V & 1 ? b : 0, GreenGradient += V & 2 ? b : 0, BlueGradient += V & 4 ? b : 0): (d == P ? (g += 2, j = g > 0 ? g / 8 : g / 20) : 0,j > 0 ? (BlueGradient = j * j / multiplier, RedGradient = 255 - 250 * BlueGradient / multiplier, GreenGradient = 255 - 150 * BlueGradient / multiplier,BlueGradient = 255 - 100 * BlueGradient / multiplier): (BlueGradient = j * j / multiplier,BlueGradient < multiplier / 5 ? (RedGradient = 255 - 210 * BlueGradient / multiplier, GreenGradient = 255 - 435 * BlueGradient / multiplier, BlueGradient = 255 - 720 * BlueGradient / multiplier) : (BlueGradient -= multiplier / 5, RedGradient = 213 - 110 * BlueGradient / multiplier,GreenGradient = 168 - 113 * BlueGradient / multiplier, BlueGradient = 111 - 85 * BlueGradient / multiplier)),d != P ? (RedGradient /= 2, GreenGradient /= 2, BlueGradient /= 2) : 0);
//  d > 0 && Z >= 0 ? (e += h * W / M, f += i * W / M, g += j * W / M, locateSphere(Z), u = e - sphereX * M,v = f - S * M, w = g - sphereY * M, b = (-2 * u - 2 * v + w) / 3,H(u * u + v * v + w * w), b /= D, b *= b, b *= 200, b /= (M * M),V = Z, sphereX != 0 ? (u = -u * M / sphereX, v = -v * M / sphereX, w = -w * M / sphereX): 0,sphereX = (h * u + i * v + j * w) / M, h -= u * sphereX / (M / 2),i -= v * sphereX / (M / 2), j -= w * sphereX / (M / 2),n            (e, f, g, h, i, j, d - 1, Z, 0, 0), Q           /= 2, T             /= 2, U            /= 2,V = V < 22? 7: (V < 30 ? 1: (V < 38 ? 2 : (V < 44 ? 4 : (V == 44 ? 6 : 3)))),Q           += V & 1 ? b : 0, T             += V & 2 ? b : 0, U            += V & 4 ? b : 0): (d == P ? (g += 2, j = g > 0 ? g / 8 : g / 20) : 0,j > 0 ? (U            = j * j / M, Q           = 255 - 250 * U            / M, T             = 255 - 150 * U            / M,U            = 255 - 100 * U            / M): (U            = j * j / M,U            < M / 5 ? (Q           = 255 - 210 * U            / M, T             = 255 - 435 * U            / M, U            = 255 - 720 * U            / M) : (U            -= M / 5, Q           = 213 - 110 * U            / M,T             = 168 - 113 * U            / M, U            = 111 - 85 * U            / M)),d != P ? (Q           /= 2, T             /= 2, U            /= 2) : 0);

    //Q = Q < 0 ? 0 : Q > O ? O : Q;
    if (RedGradient<0) {
        RedGradient=0;
    } else {
        if (RedGradient>O) {
            RedGradient=O;
        } else
            RedGradient=RedGradient;
    }

    //T = T < 0 ? 0 : T > O ? O : T;
    if (GreenGradient<0) {
        GreenGradient=0;
    } else {
        if (GreenGradient>O) {
            GreenGradient=O;
        } else
            GreenGradient=GreenGradient;
    }

    //U = U < 0 ? 0 : U > O ? O : U;
    if (BlueGradient<0) {
        BlueGradient=0;
    } else {
        if (BlueGradient>O) {
            BlueGradient=O;
        } else
            BlueGradient=BlueGradient;
    }

    return 0;
}

int Red,Green,Blue;

int t(int x, int y, int a, int b) {
    gradient_fill(multiplier * J + multiplier * 40 * (antialias_factor * x + a) / horizontal / antialias_factor - multiplier * 20, multiplier * K,multiplier * L - multiplier * 30 * (antialias_factor * y + b) / vertical / antialias_factor + multiplier * 15, 0, multiplier, 0, P, -1, 0, 0);
    Red += RedGradient;
    Green += GreenGradient;
    Blue += BlueGradient;
    ++a < antialias_factor ? t(x, y, a, b) : (++b < antialias_factor ? t(x, y, 0, b) : 0);
    return 0;
}

int r(int x, int y) {
    Red = Green = Blue = 0; //Initialise pixel values to 0/Black
    t(x, y, 0, 0);

    //x < horizontal ? (printf("%c%c%c", Red / antialias_factor / antialias_factor, Green / antialias_factor / antialias_factor, Blue / antialias_factor / antialias_factor), r(x + 1, y)) : 0;
    if (x<horizontal) {
        (printf("%c%c%c", Red/antialias_factor/antialias_factor,Green/antialias_factor/antialias_factor,Blue/antialias_factor),r(x + 1, y));
    }
    return 0;
}

int render_scanline(int ypos) {
    r(0, --ypos ? render_scanline(ypos), ypos : ypos);
    return 0;
}

int main() {
    printf("P6\n%i %i\n255\n", horizontal, vertical);
    render_scanline(vertical);
    return 0;
}
