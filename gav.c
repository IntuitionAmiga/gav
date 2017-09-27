// Degolfed and optimized version of 2004 IOCCC winner by Gavare
// (c) 2017 Zayn Otley, Karl Churchill

#include <stdio.h>

const int h_size = 1024;   //Horizontal resolution
const int v_size = 768;    //Vertical resolution
const int aa_factor = 1;

const int camX = 0;
const int camY = -10;
const int camZ = -7;

const int scale = 1296;
//const int root = 36;  //Not used for currently unknown reason
const int max_colour = 255;
const int max_depth = 9;

const int max_root_mask=32768;

int sphereX, S, sphereY;

const int sphere_diameter=2;

// For a given input value, set the global sphereX, sphereY and S values.
// TODO figure out what S represents
void locateSphere(const int b) {
    // Changing these to an actual const byte array results in the lookup being loaded into a different location and with different alignment, all of whuch kills performance.
    // Each byte in the string is encoded so that the result is signed. Original subtracted 64 from the character value. This saves a pair of integer subtractions.
    sphereX = (signed char)"\xF1\xF1\xF1\xF1\xF8\xF8\xF6\xFA\xF6\xFA\xFF\xFF\x01\x01\x06\x06\x08\x08\x0D\x0D\x0F\x0F\xF5\xF5\xF5\xF5\xF7\xF7\xF9\xF9\x00\x00\xFE\xFE\xFE\x02\x02\x02\x07\x07\x09\x09\x0B\x0B"[b];
    sphereY = (signed char)"\x03\x00\xFD\xFA\xFA\x03\x00\x00\xFD\xFD\x00\xFD\xFA\x03\x00\xFD\xFA\x03\x00\xFD\xFA\x03\xF5\xF3\xF1\xEF\xF5\xF1\xF3\xEF\xF5\xF1\xF3\xF1\xEF\xF3\xF1\xEF\xF5\xF3\xF1\xEF\xF5\xF3"[b];
    //    sphereX="1""111886:6:??AAFFHHMMOO55557799@@>>>BBBGGIIKK"[b]-64;
    //    sphereY="C@=::C@@==@=:C@=:C@=:C5""31/513/5131/31/531/53"[b ]-64;

    //S can't go above 1268 or below -11 without the spheres not rendering.
    //It's possibly the transparency level as -11 makes them see-through

    if (b < 22) {
        S = 9;
    } else {
        S = 0;
    }

}

int squareroot_sub(int x, int mask, int guess) {
    mask ?  (guess ^= mask, guess * guess > x
            ? (guess ^= mask) : 0, squareroot_sub(x, mask / 2, guess))
            : (sphereX = guess);

    return 0;
}

int square_root(const int x) {
    squareroot_sub(x, max_root_mask, 0);
    return 0;
}

int hit_sphere_q;

int hit_sphere(const int object_number, int x, int y, int z, const int dx, const int dy, const int dz, int a, int b) {
    locateSphere(object_number);
    x -= sphereX * scale;
    y -= S * scale;
    z -= sphereY * scale;
    b = x * x / scale + y * y / scale + z * z / scale - sphere_diameter * sphere_diameter * scale;
    a = -x * dx / scale - y * dy / scale - z * dz / scale;
    hit_sphere_q =  ((b = a * a / scale - b) >= 0
                  ? (squareroot_sub(b * scale, max_root_mask, 0),
                     b = sphereX,
                     a + (a > b ? -b : b))
                  : -1.0);
    return 0;
}

int find_closest_index,
    find_closest_distance;

int find_closest(const int object_number, const int x, const int y, const int z, const int dX, const int dY, const int dZ, const int notindex) {
    //Z = !c ? -1 : Z;
    if (!object_number) {
        find_closest_index=-1;
    } //else {
      //  Z=Z;
    //}

    object_number < 44 ? (hit_sphere(object_number, x, y, z, dX, dY, dZ, 0, 0), (hit_sphere_q > 0 && object_number != notindex && (hit_sphere_q < find_closest_distance || find_closest_index < 0)) ? (find_closest_distance = hit_sphere_q, find_closest_index = object_number) : 0, find_closest(object_number + 1, x, y, z, dX, dY, dZ, notindex)): 0;

    return 0;
}

int trace_ray_Red,
    trace_ray_Green,
    trace_ray_Blue,
    nX,
    nY,
    nZ;

int trace_ray(int orig_x, int orig_y, int orig_z, int dir_x, int dir_y, int dir_z, const int depth, const int notindex, int tmpcol, int closest_i_saved) {
    find_closest(0, orig_x, orig_y, orig_z, dir_x, dir_y, dir_z, notindex);
    depth > 0 && find_closest_index >= 0? (orig_x += dir_x * find_closest_distance / scale, orig_y += dir_y * find_closest_distance / scale, orig_z += dir_z * find_closest_distance / scale, locateSphere(find_closest_index), nX = orig_x - sphereX * scale,nY = orig_y - S * scale, nZ = orig_z - sphereY * scale, tmpcol = (-2 * nX - 2 * nY + nZ) / 3,square_root(nX * nX + nY * nY + nZ * nZ), tmpcol /= sphere_diameter, tmpcol *= tmpcol, tmpcol *= 200, tmpcol /= (scale * scale),closest_i_saved = find_closest_index, sphereX != 0 ? (nX = -nX * scale / sphereX, nY = -nY * scale / sphereX, nZ = -nZ * scale / sphereX) : 0,sphereX = (dir_x * nX + dir_y * nY + dir_z * nZ) / scale, dir_x -= nX * sphereX / (scale / 2),dir_y -= nY * sphereX / (scale / 2), dir_z -= nZ * sphereX / (scale / 2),trace_ray(orig_x, orig_y, orig_z, dir_x, dir_y, dir_z, depth - 1, find_closest_index, 0, 0), trace_ray_Red /= 2, trace_ray_Green /= 2, trace_ray_Blue /= 2,closest_i_saved = closest_i_saved < 22? 7: (closest_i_saved < 30 ? 1: (closest_i_saved < 38 ? 2 : (closest_i_saved < 44 ? 4 : (closest_i_saved == 44 ? 6 : 3)))),trace_ray_Red += closest_i_saved & 1 ? tmpcol : 0, trace_ray_Green += closest_i_saved & 2 ? tmpcol : 0, trace_ray_Blue += closest_i_saved & 4 ? tmpcol : 0): (depth == max_depth ? (orig_z += 2, dir_z = orig_z > 0 ? orig_z / 8 : orig_z / 20) : 0,dir_z > 0 ? (trace_ray_Blue = dir_z * dir_z / scale, trace_ray_Red = 255 - 250 * trace_ray_Blue / scale, trace_ray_Green = 255 - 150 * trace_ray_Blue / scale,trace_ray_Blue = 255 - 100 * trace_ray_Blue / scale): (trace_ray_Blue = dir_z * dir_z / scale,trace_ray_Blue < scale / 5 ? (trace_ray_Red = 255 - 210 * trace_ray_Blue / scale, trace_ray_Green = 255 - 435 * trace_ray_Blue / scale, trace_ray_Blue = 255 - 720 * trace_ray_Blue / scale) : (trace_ray_Blue -= scale / 5, trace_ray_Red = 213 - 110 * trace_ray_Blue / scale,trace_ray_Green = 168 - 113 * trace_ray_Blue / scale, trace_ray_Blue = 111 - 85 * trace_ray_Blue / scale)),depth!=max_depth ? (trace_ray_Red /= 2, trace_ray_Green /= 2, trace_ray_Blue /= 2) : 0);

    if (trace_ray_Red<0) {
        trace_ray_Red=0;
    } else {
        if (trace_ray_Red>max_colour) {
            trace_ray_Red=max_colour;
        } //else
            //trace_ray_Red=trace_ray_Red;
    }

    if (trace_ray_Green<0) {
        trace_ray_Green=0;
    } else {
        if (trace_ray_Green>max_colour) {
            trace_ray_Green=max_colour;
        } //else
            //trace_ray_Green=trace_ray_Green;
    }

    if (trace_ray_Blue<0) {
        trace_ray_Blue=0;
    } else {
        if (trace_ray_Blue>max_colour) {
            trace_ray_Blue=max_colour;
        } //else
            //trace_ray_Blue=trace_ray_Blue;
    }

    return 0;
}

int Red,Green,Blue;

int dpil_helper(int const x, int const y, int a, int b) {
    trace_ray(scale * camX + scale * 40 * (aa_factor * x + a)
                  / h_size / aa_factor
                  - scale * 20, scale * camY,scale * camZ
                  - scale * 30 * (aa_factor * y + b)
                  / v_size / aa_factor + scale * 15,
                  0,
                  scale,
                  0,
                  max_depth,
                  -1,
                  0,
                  0);

    Red += trace_ray_Red;
    Green += trace_ray_Green;
    Blue += trace_ray_Blue;

    if (++a<aa_factor) {
        dpil_helper(x, y, a, b);
    } else {
        if (++b < aa_factor) {
            dpil_helper(x, y, 0, b);
        } else {
            return 0;
        }
    }

    return 0;

}

int do_pixels_in_line(int x, int y) {
    Red = Green = Blue = 0; //Initialise pixel values to 0/Black
    dpil_helper(x, y, 0, 0);

    if (x<h_size) {
        (printf("%c%c%c",
                Red/aa_factor/aa_factor,
                Green/aa_factor/aa_factor,
                Blue/aa_factor),
                do_pixels_in_line(x + 1, y));
    } else {
        x=0;
    }

    return 0;
}

int render_scanline(int ypos) {
    do_pixels_in_line(0, --ypos ? render_scanline(ypos), ypos : ypos);
    return 0;
}

int main() {
    printf("P6\n%i %i\n255\n", h_size, v_size);
    render_scanline(v_size);
    return 0;
}
