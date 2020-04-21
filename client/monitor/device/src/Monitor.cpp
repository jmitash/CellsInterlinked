//
// Created by jacob on 4/20/2020.
//

#include "../Monitor.h"

std::string Monitor::getName() const {
    return mName;
}

void Monitor::setName(const std::string &name) {
    mName = name;
}

std::string Monitor::getContextName() const {
    return mContextName;
}

void Monitor::setContextName(const std::string &contextName) {
    mContextName = contextName;
}

int Monitor::getNumber() const {
    return mNumber;
}

void Monitor::setNumber(int number) {
    mNumber = number;
}

bool Monitor::isOn() const {
    return mOn;
}

void Monitor::setOn(bool on) {
    mOn = on;
}

bool Monitor::isReal() const {
    return mReal;
}

void Monitor::setReal(bool real) {
    mReal = real;
}

bool Monitor::isPrimary() const {
    return mPrimary;
}

void Monitor::setPrimary(bool primary) {
    mPrimary = primary;
}

int Monitor::getPixelWidth() const {
    return mPixelWidth;
}

void Monitor::setPixelWidth(int pixelWidth) {
    mPixelWidth = pixelWidth;
}

int Monitor::getPixelHeight() const {
    return mPixelHeight;
}

void Monitor::setPixelHeight(int pixelHeight) {
    mPixelHeight = pixelHeight;
}

float Monitor::getMillimeterWidth() const {
    return mMillimeterWidth;
}

void Monitor::setMillimeterWidth(float millimeterWidth) {
    mMillimeterWidth = millimeterWidth;
}

float Monitor::getMillimeterHeight() const {
    return mMillimeterHeight;
}

void Monitor::setMillimeterHeight(float millimeterHeight) {
    mMillimeterHeight = millimeterHeight;
}


