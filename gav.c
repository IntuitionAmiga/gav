// Degolfed and optimized version of 2004 IOCCC winner by Gavare
// (c) 2017 Zayn Otley, Karl Churchill

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

const int max_colours=32768;

int sphereX, S, sphereY;

const int sphere_size=2;


// For a given input value, set the global sphereX, sphereY and S values.
// TODO figure out what S represents
void locateSphere(const int b) {
    // Changing these to an actual const byte array results in the lookup being loaded into a different location and with different alignment, all of whuch kills performance.
    // Each byte in the string is encoded so that the result is signed. Original subtracted 64 from the character value. This saves a pair of integer subtractions.
    sphereX = (signed char)"\xF1\xF1\xF1\xF1\xF8\xF8\xF6\xFA\xF6\xFA\xFF\xFF\x01\x01\x06\x06\x08\x08\x0D\x0D\x0F\x0F\xF5\xF5\xF5\xF5\xF7\xF7\xF9\xF9\x00\x00\xFE\xFE\xFE\x02\x02\x02\x07\x07\x09\x09\x0B\x0B"[b];
    sphereY = (signed char)"\x03\x00\xFD\xFA\xFA\x03\x00\x00\xFD\xFD\x00\xFD\xFA\x03\x00\xFD\xFA\x03\x00\xFD\xFA\x03\xF5\xF3\xF1\xEF\xF5\xF1\xF3\xEF\xF5\xF1\xF3\xF1\xEF\xF3\xF1\xEF\xF5\xF3\xF1\xEF\xF5\xF3"[b];
    //    sphereX="1""111886:6:??AAFFHHMMOO55557799@@>>>BBBGGIIKK"[b]-64;
    //    sphereY="C@=::C@@==@=:C@=:C@=:C5""31/513/5131/31/531/53"[b ]-64;

    if (b < 22) {
        S = 9;
    } else {
        S = 0;
    }
}

int I(int x, int vertical, int horizontal) {
    vertical ?
                (horizontal ^= vertical, horizontal * horizontal > x ?
                     (horizontal ^= vertical) : 0, I(x, vertical / 2, horizontal))
              :
                (sphereX = horizontal);

    //if (vertical) {

    return 0;
}

int H(const int x) {
    I(x, max_colours, 0);
    return 0;
}

int p;

int q(const int c, int x, int y, int z, const int k, const int l, const int m, int a, int b) {
    locateSphere(c);
    x -= sphereX * multiplier;
    y -= S * multiplier;
    z -= sphereY * multiplier;
    b = x * x / multiplier + y * y / multiplier + z * z / multiplier - sphere_size * sphere_size * multiplier;
    a = -x * k / multiplier - y * l / multiplier - z * m / multiplier;
    p = ((b = a * a / multiplier - b) >= 0 ? (I(b * multiplier, max_colours, 0), b = sphereX, a + (a > b ? -b : b)): -1.0);

    return 0;
}

int Z,W;

int o(const int c, const int x, const int y, const int z, const int k, const int l, const int m, const int a) {
    //Z = !c ? -1 : Z;
    if (!c) {
        Z=-1;
    } //else {
      //  Z=Z;
    //}

    c < 44 ? (q(c, x, y, z, k, l, m, 0, 0), (p > 0 && c != a && (p < W || Z < 0)) ? (W = p, Z = c) : 0, o(c + 1, x, y, z, k, l, m, a)): 0;

    return 0;
}

int RedGradient,GreenGradient,BlueGradient,u,v,w;

int gradient_fill(int e, int f, int g, int h, int i, int j, const int d, const int a, int b, int V) {
    //Think this whole function creates the gradient backdrop

    o(0, e, f, g, h, i, j, a);
    d > 0 && Z >= 0? (e += h * W / multiplier, f += i * W / multiplier, g += j * W / multiplier, locateSphere(Z), u = e - sphereX * multiplier,v = f - S * multiplier, w = g - sphereY * multiplier, b = (-2 * u - 2 * v + w) / 3,H(u * u + v * v + w * w), b /= sphere_size, b *= b, b *= 200, b /= (multiplier * multiplier),V = Z, sphereX != 0 ? (u = -u * multiplier / sphereX, v = -v * multiplier / sphereX, w = -w * multiplier / sphereX) : 0,sphereX = (h * u + i * v + j * w) / multiplier, h -= u * sphereX / (multiplier / 2),i -= v * sphereX / (multiplier / 2), j -= w * sphereX / (multiplier / 2),gradient_fill(e, f, g, h, i, j, d - 1, Z, 0, 0), RedGradient /= 2, GreenGradient /= 2, BlueGradient /= 2,V = V < 22? 7: (V < 30 ? 1: (V < 38 ? 2 : (V < 44 ? 4 : (V == 44 ? 6 : 3)))),RedGradient += V & 1 ? b : 0, GreenGradient += V & 2 ? b : 0, BlueGradient += V & 4 ? b : 0): (d == P ? (g += 2, j = g > 0 ? g / 8 : g / 20) : 0,j > 0 ? (BlueGradient = j * j / multiplier, RedGradient = 255 - 250 * BlueGradient / multiplier, GreenGradient = 255 - 150 * BlueGradient / multiplier,BlueGradient = 255 - 100 * BlueGradient / multiplier): (BlueGradient = j * j / multiplier,BlueGradient < multiplier / 5 ? (RedGradient = 255 - 210 * BlueGradient / multiplier, GreenGradient = 255 - 435 * BlueGradient / multiplier, BlueGradient = 255 - 720 * BlueGradient / multiplier) : (BlueGradient -= multiplier / 5, RedGradient = 213 - 110 * BlueGradient / multiplier,GreenGradient = 168 - 113 * BlueGradient / multiplier, BlueGradient = 111 - 85 * BlueGradient / multiplier)),d != P ? (RedGradient /= 2, GreenGradient /= 2, BlueGradient /= 2) : 0);

    if (RedGradient<0) {
        RedGradient=0;
    } else {
        if (RedGradient>O) {
            RedGradient=O;
        } //else
            //RedGradient=RedGradient;

    }

    if (GreenGradient<0) {
        GreenGradient=0;
    } else {
        if (GreenGradient>O) {
            GreenGradient=O;
        } //else
            //GreenGradient=GreenGradient;
    }

    if (BlueGradient<0) {
        BlueGradient=0;
    } else {
        if (BlueGradient>O) {
            BlueGradient=O;
        } //else
            //BlueGradient=BlueGradient;
    }

    return 0;
}

int Red,Green,Blue;

int t(int const x, int const y, int a, int b) {
    gradient_fill(multiplier * J + multiplier * 40 * (antialias_factor * x + a)
                  / horizontal / antialias_factor
                  - multiplier * 20, multiplier * K,multiplier * L
                  - multiplier * 30 * (antialias_factor * y + b)
                  / vertical / antialias_factor + multiplier * 15,
                  0,
                  multiplier,
                  0,
                  P,
                  -1,
                  0,
                  0);

    Red += RedGradient;
    Green += GreenGradient;
    Blue += BlueGradient;

    if (++a<antialias_factor) {
        t(x, y, a, b);
    } else {
        if (++b < antialias_factor) {
            t(x, y, 0, b);
        } else {
            return 0;
        }
    }

    return 0;

}

int r(int x, int y) {
    Red = Green = Blue = 0; //Initialise pixel values to 0/Black
    t(x, y, 0, 0);

    if (x<horizontal) {
        (printf("%c%c%c",
                Red/antialias_factor/antialias_factor,
                Green/antialias_factor/antialias_factor,
                Blue/antialias_factor),
                r(x + 1, y));
    } else {
        x=0;
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
