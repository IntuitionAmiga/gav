// Degolfed and optimized version of 2004 IOCCC winner by Gavare
// (c) 2017 Zayn Otley

#include <stdio.h>

int horizontal = 1024;   //Horizontal resolution
int vertical = 768;    //Vertical resolution
int antialias_factor = 1;

int J = 0;
int K = -10;
int L = -7;
int M = 1296;
int N = 36;
int O = 255;
int P = 9;

//int _ = 1 << 15;
int max_colours=32768;

int E, S, C, D;

int F(int b) {
    E = "1111886:6:??AAFFHHMMOO55557799@@>>>BBBGGIIKK"[b]-64;
    C = "C@=::C@@==@=:C@=:C@=:C531/513/5131/31/531/53"[b]-64;

    //S = b < 22 ? 9 : 0;
    if (b<22) {
        S=9;
    } else {
        S=0;
    }

    D = 2;
    return 0;
}

int I(int x, int vertical, int horizontal) {
    vertical ? (horizontal ^= vertical, horizontal * horizontal > x ? (horizontal ^= vertical) : 0, I(x, vertical / 2, horizontal)) : (E = horizontal);
    return 0;
}

int H(int x) {
    I(x, max_colours, 0);
    return 0;
}

int p;

int q(int c, int x, int y, int z, int k, int l, int m, int a, int b) {
    F(c);
    x -= E * M;
    y -= S * M;
    z -= C * M;
    b = x * x / M + y * y / M + z * z / M - D * D * M;
    a = -x * k / M - y * l / M - z * m / M;
    p = ((b = a * a / M - b) >= 0 ? (I(b * M, max_colours, 0), b = E, a + (a > b ? -b : b)): -1.0);
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
    d > 0 && Z >= 0? (e += h * W / M, f += i * W / M, g += j * W / M, F(Z), u = e - E * M,v = f - S * M, w = g - C * M, b = (-2 * u - 2 * v + w) / 3,H(u * u + v * v + w * w), b /= D, b *= b, b *= 200, b /= (M * M),V = Z, E != 0 ? (u = -u * M / E, v = -v * M / E, w = -w * M / E) : 0,E = (h * u + i * v + j * w) / M, h -= u * E / (M / 2),i -= v * E / (M / 2), j -= w * E / (M / 2),gradient_fill(e, f, g, h, i, j, d - 1, Z, 0, 0), RedGradient /= 2, GreenGradient /= 2, BlueGradient /= 2,V = V < 22? 7: (V < 30 ? 1: (V < 38 ? 2 : (V < 44 ? 4 : (V == 44 ? 6 : 3)))),RedGradient += V & 1 ? b : 0, GreenGradient += V & 2 ? b : 0, BlueGradient += V & 4 ? b : 0): (d == P ? (g += 2, j = g > 0 ? g / 8 : g / 20) : 0,j > 0 ? (BlueGradient = j * j / M, RedGradient = 255 - 250 * BlueGradient / M, GreenGradient = 255 - 150 * BlueGradient / M,BlueGradient = 255 - 100 * BlueGradient / M): (BlueGradient = j * j / M,BlueGradient < M / 5 ? (RedGradient = 255 - 210 * BlueGradient / M, GreenGradient = 255 - 435 * BlueGradient / M, BlueGradient = 255 - 720 * BlueGradient / M) : (BlueGradient -= M / 5, RedGradient = 213 - 110 * BlueGradient / M,GreenGradient = 168 - 113 * BlueGradient / M, BlueGradient = 111 - 85 * BlueGradient / M)),d != P ? (RedGradient /= 2, GreenGradient /= 2, BlueGradient /= 2) : 0);
//  d > 0 && Z >= 0 ? (e += h * W / M, f += i * W / M, g += j * W / M, F(Z), u = e - E * M,v = f - S * M, w = g - C * M, b = (-2 * u - 2 * v + w) / 3,H(u * u + v * v + w * w), b /= D, b *= b, b *= 200, b /= (M * M),V = Z, E != 0 ? (u = -u * M / E, v = -v * M / E, w = -w * M / E): 0,E = (h * u + i * v + j * w) / M, h -= u * E / (M / 2),i -= v * E / (M / 2), j -= w * E / (M / 2),n            (e, f, g, h, i, j, d - 1, Z, 0, 0), Q           /= 2, T             /= 2, U            /= 2,V = V < 22? 7: (V < 30 ? 1: (V < 38 ? 2 : (V < 44 ? 4 : (V == 44 ? 6 : 3)))),Q           += V & 1 ? b : 0, T             += V & 2 ? b : 0, U            += V & 4 ? b : 0): (d == P ? (g += 2, j = g > 0 ? g / 8 : g / 20) : 0,j > 0 ? (U            = j * j / M, Q           = 255 - 250 * U            / M, T             = 255 - 150 * U            / M,U            = 255 - 100 * U            / M): (U            = j * j / M,U            < M / 5 ? (Q           = 255 - 210 * U            / M, T             = 255 - 435 * U            / M, U            = 255 - 720 * U            / M) : (U            -= M / 5, Q           = 213 - 110 * U            / M,T             = 168 - 113 * U            / M, U            = 111 - 85 * U            / M)),d != P ? (Q           /= 2, T             /= 2, U            /= 2) : 0);

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
    gradient_fill(M * J + M * 40 * (antialias_factor * x + a) / horizontal / antialias_factor - M * 20, M * K,M * L - M * 30 * (antialias_factor * y + b) / vertical / antialias_factor + M * 15, 0, M, 0, P, -1, 0, 0);
    Red += RedGradient;
    Green += GreenGradient;
    Blue += BlueGradient;
    ++a < antialias_factor ? t(x, y, a, b) : (++b < antialias_factor ? t(x, y, 0, b) : 0);
    return 0;
}

int r(int x, int y) {
    Red = Green = Blue = 0; //Initialise pixel values to 0/Black
    t(x, y, 0, 0);
    x < horizontal ? (printf("%c%c%c", Red / antialias_factor / antialias_factor, Green / antialias_factor / antialias_factor, Blue / antialias_factor / antialias_factor), r(x + 1, y)) : 0;
    return 0;
}

int s(int y) {
    r(0, --y ? s(y), y : y);
    return 0;
}

int main() {
    printf("P6\n%i %i\n255\n", horizontal, vertical);
    s(vertical);
    return 0;
}