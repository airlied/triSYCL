#ifndef TRISYCL_SYCL_VEC_HPP
#define TRISYCL_SYCL_VEC_HPP

/** \file

    Implement the small OpenCL vector class

    Ronan at Keryell point FR

    This file is distributed under the University of Illinois Open Source
    License. See LICENSE.TXT for details.
*/

#include "CL/sycl/detail/array_tuple_helpers.hpp"

namespace cl {
namespace sycl {

/** Rounding mode for vector conversions.
 */
enum class rounding_mode {
  automatic, /// Default rounding mode, rtz for integers, rte for floating-point
  rte,       /// Round to nearest even
  rtz,       /// Round towards zero
  rtp,       /// Round towards positive infinity
  rtn        /// Round towards negative infinity
};

/** Series of values to specify named swizzle indexes
 *  Used when calling the swizzle member function template.
 */
struct elem {
  static constexpr int x = 0;
  static constexpr int y = 1;
  static constexpr int z = 2;
  static constexpr int w = 3;
  static constexpr int r = 0;
  static constexpr int g = 1;
  static constexpr int b = 2;
  static constexpr int a = 3;
  static constexpr int s0 = 0;
  static constexpr int s1 = 1;
  static constexpr int s2 = 2;
  static constexpr int s3 = 3;
  static constexpr int s4 = 4;
  static constexpr int s5 = 5;
  static constexpr int s6 = 6;
  static constexpr int s7 = 7;
  static constexpr int s8 = 8;
  static constexpr int s9 = 9;
  static constexpr int sA = 10;
  static constexpr int sB = 11;
  static constexpr int sC = 12;
  static constexpr int sD = 13;
  static constexpr int sE = 14;
  static constexpr int sF = 15;
};

/** \addtogroup vector Vector types in SYCL

    @{
*/
template <typename, int>
class vec;

template <typename dataT, int numElements>
using __swizzled_vec__ = vec<dataT, numElements>;

/** Small OpenCL vector class

    \todo add [] operator

    \todo add iterators on elements, with begin() and end()

    \todo having vec<> sub-classing array<> instead would solve the
    previous issues

    \todo move the implementation elsewhere

    \todo simplify the helpers by removing some template types since there
    are now inside the vec<> class.

    \todo rename in the specification element_type to value_type
*/
template <typename DataType, int NumElements>
class vec : public detail::small_array<DataType,
                                       vec<DataType, NumElements>,
                                       NumElements> {
  using basic_type = typename detail::small_array<DataType,
                                                  vec<DataType, NumElements>,
                                                  NumElements>;

  static const int out_dims = (NumElements + 1) / 2;

public:

  /** Construct a vec from anything from a scalar (to initialize all the
      elements with this value) up to an aggregate of scalar and vector
      types (in this case the total number of elements must match the size
      of the vector)
  */
  template <typename... Types>
  vec(const Types... args)
    : basic_type { detail::expand<vec>(flatten_to_tuple<vec>(args...)) } { }


/// Use classical constructors too
  vec() = default;


  // Inherit of all the constructors
  using basic_type::basic_type;

private:

  /** Flattening helper that does not change scalar values but flatten a
      vec<T, n> v into a tuple<T, T,..., T>{ v[0], v[1],..., v[n-1] }

      If we have a vector, just forward its array content since an array
      has also a tuple interface :-) (23.3.2.9 Tuple interface to class
      template array [array.tuple])
  */
  template <typename V, typename Element, int s>
  static auto flatten(const vec<Element, s> i) {
    static_assert(s <= V::dimension,
                  "The element i will not fit in the vector");
    return static_cast<std::array<Element, s>>(i);
  }


  /** If we do not have a vector, just forward it as a tuple up to the
      final initialization.

      \return typically tuple<double>{ 2.4 } from 2.4 input for example
  */
  template <typename V, typename Type>
  static auto flatten(const Type i) {
    return std::make_tuple(i);
  }


 /** Take some initializer values and apply flattening on each value

      \return a tuple of scalar initializer values
   */
  template <typename V, typename... Types>
  static auto flatten_to_tuple(const Types... i) {
    // Concatenate the tuples returned by each flattening
    return std::tuple_cat(flatten<V>(i)...);
  }


  /// \todo To implement
#if 0
  vec<dataT,
      numElements>
  operator+(const vec<dataT, numElements> &rhs) const;
  vec<dataT, numElements>
  operator-(const vec<dataT, numElements> &rhs) const;
  vec<dataT, numElements>
  operator*(const vec<dataT, numElements> &rhs) const;
  vec<dataT, numElements>
  operator/(const vec<dataT, numElements> &rhs) const;
  vec<dataT, numElements>
  operator+=(const vec<dataT, numElements> &rhs);
  vec<dataT, numElements>
  operator-=(const vec<dataT, numElements> &rhs);
  vec<dataT, numElements>
  operator*=(const vec<dataT, numElements> &rhs);
  vec<dataT, numElements>
  operator/=(const vec<dataT, numElements> &rhs);
  vec<dataT, numElements>
  operator+(const dataT &rhs) const;
  vec<dataT, numElements>
  operator-(const dataT &rhs) const;
  vec<dataT, numElements>
  operator*(const dataT &rhs) const;
  vec<dataT, numElements>
  operator/(const dataT &rhs) const;
  vec<dataT, numElements>
  operator+=(const dataT &rhs);
  vec<dataT, numElements>
  operator-=(const dataT &rhs);
  vec<dataT, numElements>
  operator*=(const dataT &rhs);
  vec<dataT, numElements>
  operator/=(const dataT &rhs);
  vec<dataT, numElements> &operator=(const vec<dataT, numElements> &rhs);
  vec<dataT, numElements> &operator=(const dataT &rhs);
  bool operator==(const vec<dataT, numElements> &rhs) const;
  bool operator!=(const vec<dataT, numElements> &rhs) const;



#endif

public:

  template<typename convertT, rounding_mode roundingMode>
  vec<convertT, NumElements> convert() const;

  template<typename asT> asT as() const;
  // Swizzle methods (see notes)
  template<int... swizzleIndexs>
  __swizzled_vec__<DataType, NumElements> swizzle() const;//<int s1, ...>();
  __swizzled_vec__<DataType, 4> XYZW_ACCESS() const;
  __swizzled_vec__<DataType, 4> RGBA_ACCESS() const;
  __swizzled_vec__<DataType, 4> INDEX_ACCESS() const;
  __swizzled_vec__<DataType, 4> XYZW_SWIZZLE() const;
  __swizzled_vec__<DataType, 4> RGBA_SWIZZLE() const;

  __swizzled_vec__<DataType, out_dims> lo() const;
  __swizzled_vec__<DataType, out_dims> hi() const;
  __swizzled_vec__<DataType, out_dims> odd() const;
  __swizzled_vec__<DataType, out_dims> even() const;

#define GEN_SWIZ2(str,idx0,idx1) __swizzled_vec__<DataType, 2> str() const { return swizzle<idx0, idx1>(); }
#define GEN_SWIZ3(str,idx0,idx1,idx2) __swizzled_vec__<DataType, 3> str() const { return swizzle<idx0, idx1, idx2>(); }
#define GEN_SWIZ4(str,idx0,idx1,idx2,idx3) __swizzled_vec__<DataType, 4> str() const { return swizzle<idx0, idx1, idx2, idx3>(); }

#include "CL/sycl/vec_swiz.hpp"
};


  /** A macro to define type alias, such as for type=uchar, size=4 and
      actual_type=unsigned char, uchar4 is equivalent to vec<unsigned char, 4>
  */
#define TRISYCL_DEFINE_VEC_TYPE_SIZE(type, size, actual_type) \
  using type##size = vec<actual_type, size>;

  /// Declare the vector types of a type for all the sizes
#define TRISYCL_DEFINE_VEC_TYPE(type, actual_type)           \
  TRISYCL_DEFINE_VEC_TYPE_SIZE(type, 1, actual_type)         \
  TRISYCL_DEFINE_VEC_TYPE_SIZE(type, 2, actual_type)         \
  TRISYCL_DEFINE_VEC_TYPE_SIZE(type, 3, actual_type)         \
  TRISYCL_DEFINE_VEC_TYPE_SIZE(type, 4, actual_type)         \
  TRISYCL_DEFINE_VEC_TYPE_SIZE(type, 8, actual_type)         \
  TRISYCL_DEFINE_VEC_TYPE_SIZE(type, 16, actual_type)

  /// Declare all the possible vector type aliases
  TRISYCL_DEFINE_VEC_TYPE(char, char)
  TRISYCL_DEFINE_VEC_TYPE(uchar, unsigned char)
  TRISYCL_DEFINE_VEC_TYPE(short, short int)
  TRISYCL_DEFINE_VEC_TYPE(ushort, unsigned short int)
  TRISYCL_DEFINE_VEC_TYPE(int, int)
  TRISYCL_DEFINE_VEC_TYPE(uint, unsigned int)
  TRISYCL_DEFINE_VEC_TYPE(long, long int)
  TRISYCL_DEFINE_VEC_TYPE(ulong, unsigned long int)
  TRISYCL_DEFINE_VEC_TYPE(float, float)
  TRISYCL_DEFINE_VEC_TYPE(double, double)

/// @} End the vector Doxygen group


}
}

/*
    # Some Emacs stuff:
    ### Local Variables:
    ### ispell-local-dictionary: "american"
    ### eval: (flyspell-prog-mode)
    ### End:
*/

#endif // TRISYCL_SYCL_VEC_HPP
