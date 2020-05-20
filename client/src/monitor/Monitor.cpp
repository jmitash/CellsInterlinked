
#include <fmt/format.h>
#include "util/StringUtil.h"
#include "util/SerializationUtil.h"
#include "util/DeserializationUtil.h"
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
           isPrimary() == rhs.isPrimary() &&
           getPixelLeft() == rhs.getPixelLeft() &&
           getPixelTop() == rhs.getPixelTop() &&
           getPixelWidth() == rhs.getPixelWidth() &&
           getPixelHeight() == rhs.getPixelHeight() &&
           getMillimeterWidth() == rhs.getMillimeterWidth() &&
           getMillimeterHeight() == rhs.getMillimeterHeight();
}

std::vector<unsigned char> Monitor::serialize() const {
    std::vector<unsigned char> buffer;
    SerializationUtil::convert(buffer, getName());
    SerializationUtil::convert(buffer, getContextName());
    SerializationUtil::convert(buffer, getNumber());
    SerializationUtil::convert(buffer, isPrimary());
    SerializationUtil::convert(buffer, getPixelLeft());
    SerializationUtil::convert(buffer, getPixelTop());
    SerializationUtil::convert(buffer, getPixelWidth());
    SerializationUtil::convert(buffer, getPixelHeight());
    SerializationUtil::convert(buffer, getMillimeterWidth());
    SerializationUtil::convert(buffer, getMillimeterHeight());
    return buffer;
}

void Monitor::deserialize(Monitor &monitor, std::queue<unsigned char> &buffer) {
    monitor.setName(DeserializationUtil::_string(buffer));
    monitor.setContextName(DeserializationUtil::_string(buffer));
    monitor.setNumber(DeserializationUtil::_int(buffer));
    monitor.setPrimary(DeserializationUtil::_bool(buffer));
    monitor.setPixelLeft(DeserializationUtil::_int(buffer));
    monitor.setPixelTop(DeserializationUtil::_int(buffer));
    monitor.setPixelWidth(DeserializationUtil::_int(buffer));
    monitor.setPixelHeight(DeserializationUtil::_int(buffer));
    monitor.setMillimeterWidth(DeserializationUtil::_float(buffer));
    monitor.setMillimeterHeight(DeserializationUtil::_float(buffer));
}