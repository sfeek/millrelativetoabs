#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ghcommon.h"

char *wheel_position (double x, double y, double dt)
{
    int xt,yt;
    int xr,yr;
    char *st = NULL;

    xt = (int)trunc(x/dt);
    xr = (int)round((x / dt - xt) * dt * 1000);
    yt = (int)trunc(y/dt);
    yr = (int)round((y / dt - yt) * dt * 1000);

    sprintf_string(&st,"(%dT + %d, %dT + %d)", xt,xr,yt,yr);

    return st;
}

int main (void)
{
    double sx,sy,a,ra,d,dx,dy,dt;
    char *wp = NULL;

    dt = get_double("\nEnter Distance Per Turn of Wheel: ");
    sx = get_double("\nEnter Starting X Position: ");
    sy = get_double("\nEnter Starting Y Position: ");

    
    while(TRUE)
    {
        d = get_double("\n\n\nEnter Distance (0 to Quit): ");
        if (d <= 0.0) break;
        
        a = get_double("\nEnter Angle: ");
       
        wp = wheel_position(sx,sy,dt);
        printf("\n\nStarting at \tX = %3.3f   Y = %3.3f   %s", sx,sy,wp);
        free_malloc(wp);

        ra = PI * a / 180.0;

        dx = sx + d * sin(ra);
        dy = sy - d * cos(ra);

        if (dx < 0.0 || dy < 0.0) 
        {
            printf("\n\nError... Outside of 0,0 bounds!");
            continue;
        }

        wp = wheel_position(dx,dy,dt);
        printf ("\n\nEnding at \tX = %3.3f   Y = %3.3f   %s", dx, dy,wp);
        free_malloc(wp);

        sx = dx;
        sy = dy;
    }

    return SUCCESS;
}
