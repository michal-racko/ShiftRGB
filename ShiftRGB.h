//
// Created by mikos on 17. 1. 2022.
//

#ifndef SHIFTRGB_SHIFTRGB_H
#define SHIFTRGB_SHIFTRGB_H

#include "ShiftRegisterPWM.h"

ShiftRegisterPWM shiftRegisters = ShiftRegisterPWM(3, 255);


class ShiftRGB {
public:
    ShiftRGB(bool invertValues);

    void setup();

    void setSingleRGB(int ledNumber, int r, int g, int b);

private:
    bool m_invertValues = true;

    int m_ledPins[8][3] = {
            {7,  6,  5},
            {4,  3,  2},
            {1,  0,  15},
            {14, 13, 12},
            {11, 10, 9},
            {8,  23, 22},
            {21, 20, 19},
            {18, 17, 16}
    };
};

void ShiftRGB::setup() {
    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);

    shiftRegisters.interrupt(ShiftRegisterPWM::UpdateFrequency::Medium);
}

ShiftRGB::ShiftRGB(bool invertValues) {
    m_invertValues = invertValues;
}

void ShiftRGB::setSingleRGB(int ledNumber, int r, int g, int b) {
    int currentR, currentG, currentB;

    if (m_invertValues) {
        currentR = 255 - r;
        currentG = 255 - g;
        currentB = 255 - b;
    } else {
        currentR = r;
        currentG = g;
        currentB = b;
    }

    shiftRegisters.set(m_ledPins[ledNumber][0], currentR);
    shiftRegisters.set(m_ledPins[ledNumber][1], currentG);
    shiftRegisters.set(m_ledPins[ledNumber][2], currentB);
}


#endif //SHIFTRGB_SHIFTRGB_H
