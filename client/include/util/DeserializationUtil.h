
#ifndef CELLSINTERLINKED_DESERIALIZATIONUTIL_H
#define CELLSINTERLINKED_DESERIALIZATIONUTIL_H

#include <sstream>
#include <queue>

class DeserializationUtil {
public:
    static std::string _string(std::queue<unsigned char> &buffer) {
        auto size = _ushort(buffer);
        std::stringstream ss;
        for (int i = 0; i < size; i++) {
            ss << (char) buffer.front();
            buffer.pop();
        }
        return ss.str();
    }

    static bool _bool(std::queue<unsigned char> &buffer) {
        return convert<bool>(buffer);
    }

    static short _short(std::queue<unsigned char> &buffer) {
        return convert<short>(buffer);
    }

    static unsigned short _ushort(std::queue<unsigned char> &buffer) {
        return convert<unsigned short>(buffer);
    }

    static int _int(std::queue<unsigned char> &buffer) {
        return convert<int>(buffer);
    }

    static unsigned int _uint(std::queue<unsigned char> &buffer) {
        return convert<unsigned int>(buffer);
    }

    static long long _longlong(std::queue<unsigned char> &buffer) {
        return convert<long long>(buffer);
    }

    static unsigned long long _ulonglong(std::queue<unsigned char> &buffer) {
        return convert<unsigned long long>(buffer);
    }

    static float _float(std::queue<unsigned char> &buffer) {
        return convert<float>(buffer);
    }

    static float _double(std::queue<unsigned char> &buffer) {
        return convert<double>(buffer);
    }

    template<typename T>
    static T convert(std::queue<unsigned char> &buffer) {
        constexpr unsigned short byteCount = sizeof(T) / sizeof(unsigned char);
        unsigned char bytes[byteCount];
        readBytes(buffer, byteCount, bytes);
        volatile auto t = *((T *) bytes);
        return t;
    }

    static void readBytes(std::queue<unsigned char> &buffer, unsigned short count, unsigned char *bytes) {
        for (unsigned short i = 0; i < count; i++) {
            bytes[i] = buffer.front();
            buffer.pop();
        }
    }
};

#endif //CELLSINTERLINKED_DESERIALIZATIONUTIL_H
