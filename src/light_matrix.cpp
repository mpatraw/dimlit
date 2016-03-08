#include <cassert>
#include <cmath>
#include <cstdio>
#include <algorithm>

#include "light_matrix.hpp"

// Uses inverse square law (I1/I2 = D2^2/D1^2) to find D2:
// D2 = sqrt(D1^2 * I1 / I2), where D1^2 = 1
static int find_distance_of_intensity(int intensity)
{
    return std::floor(std::sqrt(intensity / 0.999999999f));
}

// Finds out how much intensity it takes to reach a distance.
// I1 = I2 * D2^2 / D1^2, where I2 = 1, and D1 = 1.
static int find_intensity_for_distance(int distance)
{
    return distance * distance;
}

// I2 = I1/(D2^2/D1^2)
static int find_intensity_at_distance(int intensity, int distance)
{
    if (distance == 0) {
        return intensity;
    }
    return intensity / (distance * distance);
}

static int distance_squared(int x0, int y0, int x1, int y1)
{
    return (x0 - x1) * (x0 - x1) + (y0 - y1) * (y0 - y1);
}

static bool within_bounds(int x, int y, int width, int height)
{
    return x >= 0 && x < width && y >= 0 && y < height;
}

LightMatrix::LightMatrix(int width, int height) : mWidth{width}, mHeight{height}
{
    mBrightness.resize(width * height);
    mLightEmitted.resize(width * height);
}

int LightMatrix::width() const
{
    return mWidth;
}

int LightMatrix::height() const
{
    return mHeight;
}

bool LightMatrix::inBounds(int x, int y) const
{
    return x >= 0 && x < width() && y >= 0 && y < height();
}

int LightMatrix::brightness(int x, int y) const
{
    assert(within_bounds(x, y, mWidth, mHeight));
    return mBrightness[y * mWidth + x];
}

int LightMatrix::lightEmitted(int x, int y) const
{
    assert(within_bounds(x, y, mWidth, mHeight));
    return mLightEmitted[y * mWidth + x];
}

void LightMatrix::emitLight(int x, int y, int amount)
{
    assert(within_bounds(x, y, mWidth, mHeight));

    int oldAmount = lightEmitted(x, y);
    int maxDist = find_distance_of_intensity(oldAmount);
    if (oldAmount == 0) {
        goto skip_removing_light;
    }
    for (int xx = x - maxDist; xx <= x + maxDist; ++xx) {
        for (int yy = y - maxDist; yy <= y + maxDist; ++yy) {
            int d = distance_squared(xx, yy, x, y);
            bool inside = within_bounds(xx, yy, mWidth, mHeight);
            if (d <= maxDist * maxDist && inside) {
                int i = find_intensity_at_distance(oldAmount, sqrt(d));
                mBrightness[yy * mWidth + xx] -= i;
            }
        }
    }

skip_removing_light:
    maxDist = find_distance_of_intensity(amount);
    for (int xx = x - maxDist; xx <= x + maxDist; ++xx) {
        for (int yy = y - maxDist; yy <= y + maxDist; ++yy) {
            int d = distance_squared(xx, yy, x, y);
            bool inside = within_bounds(xx, yy, mWidth, mHeight);
            if (d <= maxDist * maxDist && inside) {
                int i = find_intensity_at_distance(amount, sqrt(d));
                mBrightness[yy * mWidth + xx] += i;
            }
        }
    }

    mLightEmitted[y * mWidth + x] = amount;
}

void LightMatrix::emitEnough(int x, int y, int range)
{
    emitLight(x, y, find_intensity_for_distance(range));
}
