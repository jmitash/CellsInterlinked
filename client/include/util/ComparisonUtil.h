
#ifndef CELLSINTERLINKED_COMPARISONUTIL_H
#define CELLSINTERLINKED_COMPARISONUTIL_H

#include <string>

/**
 * Utility class for comparing types.
 */
class ComparisonUtil {
public:
    /**
     * Tells if the left hand side is less than the right hand side by comparing a pair of fields.
     *
     * @tparam T any type
     * @param lhs the left hand side
     * @param rhs the right hand side
     * @return true if the left hand side is less than the right hand side
     */
    template<typename T>
    static bool lessThan(const T &lhs, const T &rhs) {
        return lhs < rhs;
    }

    /**
     * Tells if the left hand side is less than the right hand side by comparing pairs of fields.
     *
     * @tparam T any type
     * @tparam Args the remaining field pairs to compare
     * @param lhs the left hand side field
     * @param rhs the right hand side field
     * @param args the remaining pairs of fields to compare
     * @return true if the left hand side is less than the right hand side
     */
    template<typename T, typename... Args>
    static bool lessThan(const T &lhs, const T &rhs, Args... args) {
        if (lhs < rhs) {
            return true;
        } else if (rhs < lhs) {
            return false;
        } else {
            return lessThan(args...);
        }
    }

    /**
     * Tells if the left hand side is greater than the right hand side by comparing a pair of fields.
     *
     * @tparam T any type
     * @param lhs the left hand side
     * @param rhs the right hand side
     * @return true if the left hand side is greater than the right hand side
     */
    template<typename T>
    static bool greaterThan(const T &lhs, const T &rhs) {
        return lhs > rhs;
    }

    /**
     * Tells if the left hand side is greater than the right hand side by comparing pairs of fields.
     *
     * @tparam T any type
     * @tparam Args the remaining field pairs to compare
     * @param lhs the left hand side field
     * @param rhs the right hand side field
     * @param args the remaining pairs of fields to compare
     * @return true if the left hand side is greater than the right hand side
     */
    template<typename T, typename... Args>
    static bool greaterThan(const T &lhs, const T &rhs, Args... args) {
        if (lhs > rhs) {
            return true;
        } else if (rhs > lhs) {
            return false;
        } else {
            return greaterThan(args...);
        }
    }

    /**
     * Tells if the left hand side is equal to the right hand side by comparing a pair of fields.
     *
     * @tparam T any type
     * @param lhs the left hand side
     * @param rhs the right hand side
     * @return true if the left hand side is equal to the right hand side
     */
    template<typename T>
    static bool equalTo(const T &lhs, const T &rhs) {
        return lhs == rhs;
    }

    /**
     * Tells if the left hand side is less than the right hand side by comparing pairs of fields.
     *
     * @tparam T any type
     * @tparam Args the remaining field pairs to compare
     * @param lhs the left hand side field
     * @param rhs the right hand side field
     * @param args the remaining pairs of fields to compare
     * @return true if the left hand side is less than the right hand side
     */
    template<typename T, typename... Args>
    static bool equalTo(const T &lhs, const T &rhs, Args... args) {
        if (lhs == rhs) {
            return equalTo(args...);
        } else {
            return false;
        }
    }

};


#endif //CELLSINTERLINKED_COMPARISONUTIL_H
