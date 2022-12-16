#ifndef COMPARATOR_GUARD
#define COMPARATOR_GUARD 1

//comparators (2 args based):
template<typename T>
inline bool equal(const T& a, const T& b){ return a==b; }
template<typename T>
inline bool not_equal(const T& a, const T& b){ return a!=b; }
template<typename T>
inline bool greater(const T& a, const T& b){ return a>b; }
template<typename T>
inline bool lesser(const T& a, const T& b){ return a<b; }
template<typename T>
inline bool greater_equal(const T& a, const T& b){ return a>=b; }
template<typename T>
inline bool lesser_equal(const T& a, const T& b){ return a<=b; }

//comparators (3 args based or range based):	
template<typename T>
inline bool is_in_range(const T& a, const T& b, const T& c){ return a>=b&&a<=c; }
template<typename T>
inline bool isnt_in_range(const T& a, const T& b, const T& c){ return a<b||a>c; }

#endif
