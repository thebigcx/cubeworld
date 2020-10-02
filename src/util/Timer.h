#pragma once

#include <chrono>
#include <iostream>

class Timer
{
    public:

        Timer()
        {
            m_startTime = std::chrono::high_resolution_clock::now();
        }

        ~Timer()
        {
            stop();
        }

        void stop()
        {
            auto endTime = std::chrono::high_resolution_clock::now();

            auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_startTime).time_since_epoch().count();
            auto stop = std::chrono::time_point_cast<std::chrono::microseconds>(endTime).time_since_epoch().count();

            auto duration = stop - start;
            double ms = duration * 0.001;

            std::cout << duration << "us (" << ms << "ms)\n";
        }

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
};