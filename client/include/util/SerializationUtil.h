
#ifndef CELLSINTERLINKED_SERIALIZATIONUTIL_H
#define CELLSINTERLINKED_SERIALIZATIONUTIL_H

#include <string>
#include <vector>

class SerializationUtil {
public:
    static void convert(std::vector<unsigned char> &buffer, const std::string &str) {
        convert(buffer, (short) str.size());
        for (const char &c : str) {
            buffer.push_back(c);
        }
    }

    static void convert(std::vector<unsigned char> &buffer, const bool _bool) {
        buffer.push_back(_bool);
    }

    static void convert(std::vector<unsigned char> &buffer, const short _short) {
        auto *bytes = (unsigned char *) &_short;
        unsigned char count = sizeof(short) / sizeof(unsigned char);

        for (int i = 0; i < count; i++) {
            buffer.push_back(bytes[i]);
        }
    }

    static void convert(std::vector<unsigned char> &buffer, const int _int) {
        auto *bytes = (unsigned char *) &_int;
        unsigned char count = sizeof(int) / sizeof(unsigned char);

        for (int i = 0; i < count; i++) {
            buffer.push_back(bytes[i]);
        }
    }

    static void convert(std::vector<unsigned char> &buffer, const long long _longlong) {
        auto *bytes = (unsigned char *) &_longlong;
        unsigned char count = sizeof(long long) / sizeof(unsigned char);

        for (int i = 0; i < count; i++) {
            buffer.push_back(bytes[i]);
        }
    }

    static void convert(std::vector<unsigned char> &buffer, const float _float) {
        auto *bytes = (unsigned char *) &_float;
        unsigned char count = sizeof(float) / sizeof(unsigned char);

        for (int i = 0; i < count; i++) {
            buffer.push_back(bytes[i]);
        }
    }

    static void convert(std::vector<unsigned char> &buffer, const double _double) {
        auto *bytes = (unsigned char *) &_double;
        unsigned char count = sizeof(double) / sizeof(unsigned char);

        for (int i = 0; i < count; i++) {
            buffer.push_back(bytes[i]);
        }
    }

    template<typename It, typename Srlzr>
    static void convert(std::vector<unsigned char> &buffer, It begin, It end, Srlzr srlzr) {
        for (It cur = begin; cur != end; cur++) {
            std::vector<unsigned char> serialized = srlzr(*cur);
            buffer.insert(buffer.end(), serialized.begin(), serialized.end());
        }
    }
};

#endif //CELLSINTERLINKED_SERIALIZATIONUTIL_H
