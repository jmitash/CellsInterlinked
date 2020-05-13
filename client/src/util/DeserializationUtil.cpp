
#include <sstream>
#include "util/DeserializationUtil.h"

std::string DeserializationUtil::_string(std::queue<unsigned char> &buffer) {
    auto size = _ushort(buffer);
    std::stringstream ss;
    for (int i = 0; i < size; i++) {
        ss << (char) buffer.front();
        buffer.pop();
    }
    return ss.str();
}

bool DeserializationUtil::_bool(std::queue<unsigned char> &buffer) {
    return convert<bool>(buffer);
}

short DeserializationUtil::_short(std::queue<unsigned char> &buffer) {
    return convert<short>(buffer);
}

unsigned short DeserializationUtil::_ushort(std::queue<unsigned char> &buffer) {
    return convert<unsigned short>(buffer);
}

int DeserializationUtil::_int(std::queue<unsigned char> &buffer) {
    return convert<int>(buffer);
}

unsigned int DeserializationUtil::_uint(std::queue<unsigned char> &buffer) {
    return convert<unsigned int>(buffer);
}

long long DeserializationUtil::_longlong(std::queue<unsigned char> &buffer) {
    return convert<long long>(buffer);
}

unsigned long long DeserializationUtil::_ulonglong(std::queue<unsigned char> &buffer) {
    return convert<unsigned long long>(buffer);
}

float DeserializationUtil::_float(std::queue<unsigned char> &buffer) {
    return convert<float>(buffer);
}

float DeserializationUtil::_double(std::queue<unsigned char> &buffer) {
    return convert<double>(buffer);
}

template<typename T>
T DeserializationUtil::convert(std::queue<unsigned char> &buffer) {
    constexpr unsigned short byteCount = sizeof(T) / sizeof(unsigned char);
    unsigned char bytes[byteCount];
    readBytes(buffer, byteCount, bytes);
    volatile auto t = *((T *) bytes);
    return t;
}

void DeserializationUtil::readBytes(std::queue<unsigned char> &buffer, unsigned short count, unsigned char *bytes) {
    for (unsigned short i = 0; i < count; i++) {
        bytes[i] = buffer.front();
        buffer.pop();
    }
}