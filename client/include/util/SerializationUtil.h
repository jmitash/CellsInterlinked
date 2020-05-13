
#ifndef CELLSINTERLINKED_SERIALIZATIONUTIL_H
#define CELLSINTERLINKED_SERIALIZATIONUTIL_H

#include <string>
#include <vector>

class SerializationUtil {
public:
    static void convert(std::vector<unsigned char> &buffer, const std::string &str);

    static void convert(std::vector<unsigned char> &buffer, bool _bool);

    static void convert(std::vector<unsigned char> &buffer, short _short);

    static void convert(std::vector<unsigned char> &buffer, int _int);

    static void convert(std::vector<unsigned char> &buffer, long long _longlong);

    static void convert(std::vector<unsigned char> &buffer, float _float);

    static void convert(std::vector<unsigned char> &buffer, double _double);

    template<typename T>
    static void convert(std::vector<unsigned char> &buffer, T t);

    template<typename It, typename Serializer>
    static void convert(std::vector<unsigned char> &buffer, It begin, It end, Serializer serializer) {
        for (It cur = begin; cur != end; cur++) {
            std::vector<unsigned char> serialized = serializer(*cur);
            buffer.insert(buffer.end(), serialized.begin(), serialized.end());
        }
    }
};

#endif //CELLSINTERLINKED_SERIALIZATIONUTIL_H
