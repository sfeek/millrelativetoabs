#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ghcommon.h"

char *wheel_position(double x, double y, double dt)
{
    int xt, yt;
    int xr, yr;
    char *st = NULL;

    xt = (int)trunc(x / dt);
    xr = (int)round((x / dt - xt) * dt * 1000);
    yt = (int)trunc(y / dt);
    yr = (int)round((y / dt - yt) * dt * 1000);

    sprintf_string(&st, "(%dT + %d, %dT + %d)", xt, xr, yt, yr);

    return st;
}

void print_instructions(void)
{

    printf("\n\n\n0,0");
    printf("\n  ---------------");
    printf("\n  |      0      |");
    printf("\n  |             |");
    printf("\n  | 270      90 |");
    printf("\n  |             |");
    printf("\n  |     180     |");
    printf("\n  ---------------");

    printf("\n\n Always reference back left corner as 0,0");

    printf("\n\n\n");
}

int get_english_or_metric(void)
{
    int count, metric_flag;
    char *s = NULL;

    while (TRUE)
    {
        count = get_string(&s, "\n\nEnter <E>nglish or <M>etric");

        if (count == 0)
        {
            free_malloc(s);
            continue;
        }

        if (s[0] == 'E' || s[0] == 'e')
        {
            free_malloc(s);
            metric_flag = FALSE;
            break;
        }

        if (s[0] == 'M' || s[0] == 'm')
        {
            free_malloc(s);
            metric_flag = TRUE;
            break;
        }

        free_malloc(s);
    }

    return metric_flag;
}

int main(void)
{
    double sx, sy, a, ra, d, dx, dy, dt;
    int metric_flag;
    char *wp = NULL;

    print_instructions();

    metric_flag = get_english_or_metric();

    dt = get_fraction("\nEnter Distance Per Turn of Wheel in Inches: ");
    sx = get_fraction("\nEnter Starting X Position: ");
    sy = get_fraction("\nEnter Starting Y Position: ");

    if (metric_flag)
    {
        sx = sx * 0.03937008;
        sy = sy * 0.03937008;
    }

    wp = wheel_position(sx, sy, dt);
    printf("\n\nStarting at \tX = %3.4fin %3.2fmm   Y = %3.4fin %3.2fmm   %s", sx, sx / 0.03937008, sy, sy / 0.03937008, wp);
    free_malloc(wp);

    while (TRUE)
    {
        d = get_fraction("\n\n\nEnter Distance: (0 to Quit) ");
        if (d <= 0.0)
            break;

        if (metric_flag)
        {
            d = d * 0.03937008;
        }

        a = get_fraction("\nEnter Angle: ");

        ra = PI * a / 180.0;

        dx = sx + d * sin(ra);
        dy = sy - d * cos(ra);

        if (dx < 0.0 || dy < 0.0)
        {
            printf("\n\nError... Outside of 0,0 bounds!");
            continue;
        }

        wp = wheel_position(dx, dy, dt);
        printf("\n\nEnding at \tX = %3.4fin %3.2fmm   Y = %3.4fin %3.2fmm   %s", dx, dx / 0.03937008, dy, dy / 0.03937008, wp);
        free_malloc(wp);

        sx = dx;
        sy = dy;
    }

    return SUCCESS;
}
