
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
        convert < bool > (buffer, _bool);
    }

    static void convert(std::vector<unsigned char> &buffer, const short _short) {
        convert < short > (buffer, _short);
    }

    static void convert(std::vector<unsigned char> &buffer, const int _int) {
        convert < int > (buffer, _int);
    }

    static void convert(std::vector<unsigned char> &buffer, const long long _longlong) {
        convert < long long > (buffer, _longlong);
    }

    static void convert(std::vector<unsigned char> &buffer, const float _float) {
        convert < float > (buffer, _float);
    }

    static void convert(std::vector<unsigned char> &buffer, const double _double) {
        convert < double > (buffer, _double);
    }

    template<typename T>
    static void convert(std::vector<unsigned char> &buffer, T t) {
        auto *bytes = (unsigned char *) &t;
        unsigned char count = sizeof(T) / sizeof(unsigned char);

        for (int i = 0; i < count; i++) {
            buffer.push_back(bytes[i]);
        }
    }

    template<typename It, typename Serializer>
    static void convert(std::vector<unsigned char> &buffer, It begin, It end, Serializer serializer) {
        for (It cur = begin; cur != end; cur++) {
            std::vector<unsigned char> serialized = serializer(*cur);
            buffer.insert(buffer.end(), serialized.begin(), serialized.end());
        }
    }
};

#endif //CELLSINTERLINKED_SERIALIZATIONUTIL_H
