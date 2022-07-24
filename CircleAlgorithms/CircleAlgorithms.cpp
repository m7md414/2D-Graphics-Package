int getRadius(Point center, Point point) {
    return hypot(point.x - center.x, point.y - center.y);
}

void drawEightPoints(Point center, Point point) {
    SetPixel(hdc, center.x + point.x, center.y + point.y, color);
    SetPixel(hdc, center.x - point.x, center.y + point.y, color);
    SetPixel(hdc, center.x - point.x, center.y - point.y, color);
    SetPixel(hdc, center.x + point.x, center.y - point.y, color);
    SetPixel(hdc, center.x + point.y, center.y + point.x, color);
    SetPixel(hdc, center.x - point.y, center.y + point.x, color);
    SetPixel(hdc, center.x - point.y, center.y - point.x, color);
    SetPixel(hdc, center.x + point.y, center.y - point.x, color);
}

//x^2 + y^2 = R^2
void DirectCartesian(Point center, Point point) {
    int radius = getRadius(center, point);
    int x = radius;
    int y = 0;
    drawEightPoints(center, Point(x, y));
    while (y < x) {
        y++;
        x = Round(sqrt(radius * radius - y * y));
        drawEightPoints(center, Point(x, y));
    }
}

// x = RCos(theta)  -   y = Rsin(theta)
void Polar(Point center, Point point) {
    int radius = getRadius(center, point);
    double dtheta = 1.0 / radius;
    for (double theta = 0; theta <= 0.785; theta += dtheta) {
        int x = Round(radius * cos(theta));
        int y = Round(radius * sin(theta));
        drawEightPoints(center, Point(x, y));
    }
}

void IterativePolar(Point center, Point point) {
    int radius = getRadius(center, point);
    double dtheta = 1.0 / radius;
    double ctheta = cos(dtheta);
    double stheta = sin(dtheta);
    double x = radius;
    double y = 0.0;
    SetPixel(hdc, x, y, color);
    for (double theta = 0; theta <= 6.28; theta += dtheta) {
        double x1 = x * ctheta - y * stheta;
        y = x * stheta + y * ctheta;
        x = x1;
        SetPixel(hdc, Round(x + center.x), Round(y + center.y), color);
    }
}

void midpoint(Point center, Point point) {
    int radius = getRadius(center, point);
    int x = radius;
    int y = 0;
    drawEightPoints(center, Point(x, y));
    int d = 1 - radius;
    while (y < x) {
        if (d >= 0) {
            d += (2 * (y - x) + 5);
            x--;
        } else {
            d += (2 * y + 3);
        }
        y++;
        drawEightPoints(center, Point(x, y));
    }
}
void modifiedMidpoint(Point center, Point point) {
    int radius = getRadius(center, point);
    int x = radius;
    int y = 0;
    drawEightPoints(center, Point(x, y));
    int d = 1 - radius;
    int change1 = 5 - 2 * radius;
    int change2 = 3;
    while (y < x) {
        if (d >= 0) {
            d += change1;
            change1 += 4;
            x--;
        } else {
            d += change2;
            change1 += 2;
        }
        change2 += 2;
        y++;
        drawEightPoints(center, Point(x, y));
    }
}

// void draw(Point center, Point point) {
//     if (ID == CIRCLE_DIRECT_CARTESIAN) {
//         DirectCartesian(center, point);
//     } else if (ID == CIRCLE_POLAR) {
//         Polar(center, point);
//     } else if (ID == CIRCLE_IMPROVED_POLAR) {
//         IterativePolar(center, point);
//     } else if (ID == CIRCLE_BRESENHAM) {
//         midpoint(center, point);
//     } else modifiedMidpoint(center, point);
// }