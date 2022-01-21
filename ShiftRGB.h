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

    void setAllRGB(int r, int g, int b);

private:
    bool _invertValues = true;

    int _ledPins[8][3] = {
            {5,  6,  7},
            {2,  3,  4},
            {15, 0,  1},
            {12, 13, 14},
            {9,  10, 11},
            {22, 23, 8},
            {19, 20, 21},
            {16, 17, 18}
    };
};

void ShiftRGB::setup() {
    Serial.begin(9600);

    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(4, OUTPUT);

    shiftRegisters.interrupt(ShiftRegisterPWM::UpdateFrequency::Slow);
}

ShiftRGB::ShiftRGB(bool invertValues) {
    _invertValues = invertValues;
}

void ShiftRGB::setSingleRGB(int ledNumber, int r, int g, int b) {
    int currentR, currentG, currentB;

    if (this->_invertValues) {
        currentR = 255 - r % 256;
        currentG = 255 - g % 256;
        currentB = 255 - b % 256;
    } else {
        currentR = r % 256;
        currentG = g % 256;
        currentB = b % 256;
    }

    shiftRegisters.set(this->_ledPins[ledNumber][0], currentR);
    shiftRegisters.set(this->_ledPins[ledNumber][1], currentG);
    shiftRegisters.set(this->_ledPins[ledNumber][2], currentB);
}

void ShiftRGB::setAllRGB(int r, int g, int b) {
    for (int i = 0; i < 8; i++) {
        this->setSingleRGB(i, r, g, b);
    }
}


#endif //SHIFTRGB_SHIFTRGB_H
