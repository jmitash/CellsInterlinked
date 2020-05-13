
#ifndef CELLSINTERLINKED_DESERIALIZATIONUTIL_H
#define CELLSINTERLINKED_DESERIALIZATIONUTIL_H

#include <string>
#include <queue>

class DeserializationUtil {
public:
    static std::string _string(std::queue<unsigned char> &buffer);

    static bool _bool(std::queue<unsigned char> &buffer);

    static short _short(std::queue<unsigned char> &buffer);

    static unsigned short _ushort(std::queue<unsigned char> &buffer);

    static int _int(std::queue<unsigned char> &buffer);

    static unsigned int _uint(std::queue<unsigned char> &buffer);

    static long long _longlong(std::queue<unsigned char> &buffer);

    static unsigned long long _ulonglong(std::queue<unsigned char> &buffer);

    static float _float(std::queue<unsigned char> &buffer);

    static float _double(std::queue<unsigned char> &buffer);

    template<typename T>
    static T convert(std::queue<unsigned char> &buffer);

    static void readBytes(std::queue<unsigned char> &buffer, unsigned short count, unsigned char *bytes);
};

#endif //CELLSINTERLINKED_DESERIALIZATIONUTIL_H
