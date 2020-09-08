
#include "util/SerializationUtil.h"

void SerializationUtil::convert(std::vector<unsigned char> &buffer, const std::string &str) {
    convert(buffer, (short) str.size());
    for (const char &c : str) {
        buffer.push_back(c);
    }
}

void SerializationUtil::convert(std::vector<unsigned char> &buffer, const bool _bool) {
    convert<bool>(buffer, _bool);
}

void SerializationUtil::convert(std::vector<unsigned char> &buffer, const short _short) {
    convert<short>(buffer, _short);
}

void SerializationUtil::convert(std::vector<unsigned char> &buffer, const int _int) {
    convert<int>(buffer, _int);
}

void SerializationUtil::convert(std::vector<unsigned char> &buffer, const long long _longlong) {
    convert<long long>(buffer, _longlong);
}

void SerializationUtil::convert(std::vector<unsigned char> &buffer, const float _float) {
    convert<float>(buffer, _float);
}

void SerializationUtil::convert(std::vector<unsigned char> &buffer, const double _double) {
    convert<double>(buffer, _double);
}

template<typename T>
void SerializationUtil::convert(std::vector<unsigned char> &buffer, T t) {
    auto *bytes = (unsigned char *) &t;
    unsigned char count = sizeof(T) / sizeof(unsigned char);

    for (int i = 0; i < count; i++) {
        buffer.push_back(bytes[i]);
    }
}

template<typename It, typename Serializer>
void SerializationUtil::convert(std::vector<unsigned char> &buffer, It begin, It end, Serializer serializer) {
    for (It cur = begin; cur != end; cur++) {
        std::vector<unsigned char> serialized = serializer(*cur);
        buffer.insert(buffer.end(), serialized.begin(), serialized.end());
    }
}