#pragma once
#include "std.hpp"

template <typename T, typename U>
ostream& operator<<(ostream& os, const pair<T, U>& p) {
    os << "(" << p.first << ", " << p.second << ")";
    return os;
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v) {
    os << "[";
    bool first = true;
    for (const auto& x : v) {
        if (first) {
            first = false;
        } else {
            os << ", ";
        }
        os << x;
    }
    os << "]";
    return os;
}

template <typename K, typename V>
ostream& operator<<(ostream& os, const map<K, V>& m) {
    os << "{";
    bool first = true;
    for (const auto& [k, v] : m) {
        if (first) {
            first = false;
        } else {
            os << ", ";
        }
        os << k << ": " << v;
    }
    os << "}";
    return os;
}

template <typename T>
ostream& operator<<(ostream& os, const set<T>& s) {
    os << "{";
    bool first = true;
    for (const auto& x : s) {
        if (first) {
            first = false;
        } else {
            os << ", ";
        }
        os << x;
    }
    os << "}";
    return os;
}

template <typename T>
ostream& operator<<(ostream& os, const optional<T>& v) {
    if (v)
        os << *v;
    else
        os << "nullopt";
    return os;
}

#ifdef ONLINE_JUDGE
#define DEBUG(code)
#else
#define DEBUG(code) code
#endif
