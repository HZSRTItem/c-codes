#include "srtrun.h"

int main_calres(int argc, char* argv[])
{
    if (argc == 1)
    {
        printf("srt_calres angle\n     RESOLUTION_ANGLE = 0.000089831529294\n");
        return 0;
    }

    double d1 = atof(argv[1]);
   
    double d2 = d1 / 0.000089831529294 * 10;
    printf("%.6fm", d2);

    return 0;
}
