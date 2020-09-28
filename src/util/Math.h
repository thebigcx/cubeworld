#pragma once

#include <math.h>
#include <ctime>
#include <cstdlib>

struct Math {
    public:
        static double map(double value, double istart, double istop, double ostart, double ostop)
        {
            return ostart + (ostop - ostart) * ((value - istart) / (istop - istart));
        }

        static double random(int min, int max)
        {
            std::srand(std::time(nullptr));
            int rand = std::rand();
            return rand % max + min;
        }

        static double clamp(double value, double min, double max)
        {
            if (value < min)
            {
                return min;
            }

            if (value > max)
            {
                return max;
            }

            return value;
        }
};
