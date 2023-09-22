#pragma once

float PI = 3.141592653589793116f;
int RAY = 1200;

float radian(float degrees)
{
    return degrees * PI / 180.0f;
}

float FOV = radian(70);
float LENGTHRAY = 200;
float WALLHEIGHT = 100;
float ARAY = FOV / (RAY - 1);

float distance(Vector2f vec1, Vector2f vec2)
{
    float dx = vec1.x - vec2.x;
    float dy = vec1.y - vec2.y;
    return std::sqrt(dx * dx + dy * dy);
}
Vertex intersection(Vector2f origin, Vector2f end, Vector2f originRay, Vector2f endRay)
{
    Vector2f dir1 = end - origin;
    Vector2f dir2 = endRay - originRay;
    float a1 = -dir1.y;
    float b1 = +dir1.x;
    float d1 = -(a1 * origin.x + b1 * origin.y);

    float a2 = -dir2.y;
    float b2 = +dir2.x;
    float d2 = -(a2 * originRay.x + b2 * originRay.y);
    float seg1_line2_start = a2 * origin.x + b2 * origin.y + d2;
    float seg1_line2_end = a2 * end.x + b2 * end.y + d2;
    float seg2_line1_start = a1 * originRay.x + b1 * originRay.y + d1;
    float seg2_line1_end = a1 * endRay.x + b1 * endRay.y + d1;
    if (seg1_line2_start * seg1_line2_end >= 0 || seg2_line1_start * seg2_line1_end >= 0)
    {
        return endRay;
    }
    float u = seg1_line2_start / (seg1_line2_start - seg1_line2_end);
    Vector2f pin_out = Vector2f(u * dir1.x, u * dir1.y);
    return origin + pin_out;
}