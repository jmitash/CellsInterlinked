
#include <fmt/format.h>
#include <util/StringUtil.h>
#include "monitor/Monitor.h"

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

int Monitor::getPixelLeft() const {
    return mPixelLeft;
}

void Monitor::setPixelLeft(int pixelLeft) {
    mPixelLeft = pixelLeft;
}

int Monitor::getPixelTop() const {
    return mPixelTop;
}

void Monitor::setPixelTop(int pixelTop) {
    mPixelTop = pixelTop;
}

int Monitor::getPixelRight() const {
    return getPixelLeft() + getPixelWidth();
}

int Monitor::getPixelBottom() const {
    return getPixelTop() + getPixelHeight();
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

std::string Monitor::toString() const {
    return fmt::format(
            std::string("{{") +
            R"("Name": "{}", )" +
            R"("ContextName": "{}", )" +
            R"("Number": {}, )" +
            R"("On": {}, )" +
            R"("Real": {}, )" +
            R"("Primary": {}, )" +
            R"("PixelLeft": {}, )" +
            R"("PixelTop": {}, )" +
            R"("PixelWidth": {}, )" +
            R"("PixelHeight": {}, )" +
            R"("MillimeterWidth": {}, )" +
            R"("MillimeterHeight": {})" +
            "}}",
            StringUtil::escape(getName()),
            StringUtil::escape(getContextName()),
            getNumber(),
            isOn(),
            isReal(),
            isPrimary(),
            getPixelLeft(),
            getPixelTop(),
            getPixelWidth(),
            getPixelHeight(),
            getMillimeterWidth(),
            getMillimeterHeight());
}

bool Monitor::operator<(const Monitor &rhs) const {
    return getName() < rhs.getName() ||
           getContextName() < rhs.getContextName() ||
           getNumber() < rhs.getNumber() ||
           isOn() < rhs.isOn() ||
           isReal() < rhs.isReal() ||
           isPrimary() < rhs.isPrimary() ||
           getPixelLeft() < rhs.getPixelLeft() ||
           getPixelTop() < rhs.getPixelTop() ||
           getPixelWidth() < rhs.getPixelWidth() ||
           getPixelHeight() < rhs.getPixelHeight() ||
           getMillimeterWidth() < rhs.getMillimeterWidth() ||
           getMillimeterHeight() < rhs.getMillimeterHeight();
}

bool Monitor::operator==(const Monitor &rhs) const {
    return getName() == rhs.getName() &&
           getContextName() == rhs.getContextName() &&
           getNumber() == rhs.getNumber() &&
           isOn() == rhs.isOn() &&
           isReal() == rhs.isReal() &&
           isPrimary() == rhs.isPrimary() &&
           getPixelLeft() == rhs.getPixelLeft() &&
           getPixelTop() == rhs.getPixelTop() &&
           getPixelWidth() == rhs.getPixelWidth() &&
           getPixelHeight() == rhs.getPixelHeight() &&
           getMillimeterWidth() == rhs.getMillimeterWidth() &&
           getMillimeterHeight() == rhs.getMillimeterHeight();
}

std::string Monitor::stringify(const Monitor &monitor) {
    return monitor.toString();
}
