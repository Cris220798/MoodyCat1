#pragma once

#define max(a, b) ((a)>(b)? (a) : (b))
#define min(a, b) ((a)<(b)? (a) : (b))

// Clamp Vector2 value with min and max and return a new vector2
// NOTE: Required for virtual mouse, to clamp inside virtual game size
Vector2 ClampValue(Vector2 value, Vector2 min, Vector2 max) {
    Vector2 result = value;
    result.x = (result.x > max.x) ? max.x : result.x;
    result.x = (result.x < min.x) ? min.x : result.x;
    result.y = (result.y > max.y) ? max.y : result.y;
    result.y = (result.y < min.y) ? min.y : result.y;
    return result;
}
