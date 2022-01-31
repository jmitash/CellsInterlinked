
#ifdef _WIN32

#define FIELD_PAIRS \
    getDeviceName(), rhs.getDeviceName(), \
    getId(), rhs.getId(), \
    getHandle(), rhs.getHandle(), \
    getNumberOfButtons(), rhs.getNumberOfButtons(), \
    getSampleRate(), rhs.getSampleRate(), \
    getHasHorizontalScrollWheel(), rhs.getHasHorizontalScrollWheel()

#include "mouse/WindowsMouse.h"
#include "util/ComparisonUtil.h"

HANDLE WindowsMouse::getHandle() const {
    return mHandle;
}

std::string WindowsMouse::getDeviceName() const {
    return mDeviceName;
}

DWORD WindowsMouse::getId() const {
    return mId;
}

DWORD WindowsMouse::getNumberOfButtons() const {
    return mNumberOfButtons;
}

DWORD WindowsMouse::getSampleRate() const {
    return mSampleRate;
}

BOOL WindowsMouse::getHasHorizontalScrollWheel() const {
    return mHasHorizontalScrollWheel;
}

void WindowsMouse::setHandle(const HANDLE handle) {
    this->mHandle = handle;
}

void WindowsMouse::setDeviceName(const std::string &deviceName) {
    this->mDeviceName = deviceName;
}

void WindowsMouse::setId(const DWORD id) {
    this->mId = id;
}

void WindowsMouse::setNumberOfButtons(const DWORD numberOfButtons) {
    this->mNumberOfButtons = numberOfButtons;
}

void WindowsMouse::setSampleRate(const DWORD sampleRate) {
    this->mSampleRate = sampleRate;
}

void WindowsMouse::setHasHorizontalScrollWheel(const BOOL hasHorizontalScrollWheel) {
    this->mHasHorizontalScrollWheel = hasHorizontalScrollWheel;
}

bool WindowsMouse::operator<(const WindowsMouse &rhs) const {
    return ComparisonUtil::lessThan(FIELD_PAIRS);
}

bool WindowsMouse::operator==(const WindowsMouse &rhs) const {
    return ComparisonUtil::equalTo(FIELD_PAIRS);
}

std::string WindowsMouse::toString() const {
    return fmt::format(
            std::string("{{") +
            R"("Handle": "{}", )" +
            R"("DeviceName": "{}", )" +
            R"("Id": {}, )" +
            R"("NumberOfButtons": {}, )" +
            R"("SampleRate": {}, )" +
            R"("HasHorizontalScrollWheel": {})" +
            "}}",
            getHandle(),
            StringUtil::escape(getDeviceName()),
            getId(),
            getNumberOfButtons(),
            getSampleRate(),
            getHasHorizontalScrollWheel());
}

#endif