#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ghcommon.h"

int main (void)
{
    double sx,sy,a,ra,d,dx,dy;

    sx = get_double("\nEnter Starting X Position: ");
    sy = get_double("\nEnter Starting Y Position: ");

    while(TRUE)
    {
        a = get_double("\n\n\nEnter Angle: ");
        d = get_double("\nEnter Distance (0 to Quit): ");

        if (d == 0.0) break;

        ra = PI * a / 180.0;

        dx = sx + d * sin(ra);
        dy = sy - d * cos(ra);

        printf ("\n\nX = %3.4f    Y = %3.4f", dx, dy);

        sx = dx;
        sy = dy;
    }

    return SUCCESS;
}
