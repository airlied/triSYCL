#ifndef TRISYCL_SYCL_VEC_HPP
#define TRISYCL_SYCL_VEC_HPP

/** \file

    Implement the small OpenCL vector class

    Ronan at Keryell point FR

    This file is distributed under the University of Illinois Open Source
    License. See LICENSE.TXT for details.
*/

#include "CL/sycl/detail/array_tuple_helpers.hpp"
#include "CL/sycl/address_space.hpp"
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

#include "CL/sycl/detail/vec.hpp"

/** Accessors to access hex indexed members of a small array.
  * There are two macros, one for 0-9, one for A-F.
  */
#define TRISYCL_DECLARE_S(x)                                            \
  DataType& s##x() {                                                    \
    return (*this)[(x)];                                                \
  }

#define TRISYCL_DECLARE_Sx(x)                                           \
  DataType& s##x() {                                                    \
    return (*this)[(0x##x)];                                            \
  }

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

template <typename DataType>
class vec<DataType, 1> : public detail::base_vec<DataType, 1> {
  using basic_type = detail::base_vec<DataType, 1>;

public:

  // Inherit of all the constructors
  using basic_type::basic_type;

  operator DataType() const { return *this[0]; }

  /** An accessor to the first variable of a small array
   */
  DataType& x(){ return (*this)[0]; }

  TRISYCL_DECLARE_S(0);
};

#define TRISYCL_GEN_SWIZ2(str,idx0,idx1) __swizzled_vec__<DataType, 2> str() const { return swizzle<idx0, idx1>(); }
#define TRISYCL_GEN_SWIZ3(str,idx0,idx1,idx2) __swizzled_vec__<DataType, 3> str() const { return swizzle<idx0, idx1, idx2>(); }
#define TRISYCL_GEN_SWIZ4(str,idx0,idx1,idx2,idx3) __swizzled_vec__<DataType, 4> str() const { return swizzle<idx0, idx1, idx2, idx3>(); }

template <typename DataType>
class vec<DataType, 2> : public detail::base_vec<DataType, 2> {
  using basic_type = detail::base_vec<DataType, 2>;

public:

  // Inherit of all the constructors
  using basic_type::basic_type;

  /** An accessor to the first variable of a small array
   */
  DataType& x(){ return (*this)[0]; }

  /** An accessor to the second variable of a small array
  */
  DataType& y(){ return (*this)[1]; }

  TRISYCL_DECLARE_S(0);
  TRISYCL_DECLARE_S(1);

  template<int... swizzleIndexs>
  __swizzled_vec__<DataType, sizeof...(swizzleIndexs)> swizzle() const {
    return basic_type::do_swizzle(swizzleIndexs...);
  }
#include "CL/sycl/detail/swiz2.hpp"
};

template <typename DataType>
class vec<DataType, 3> : public detail::base_vec<DataType, 3> {
  using basic_type = detail::base_vec<DataType, 3>;

public:

  // Inherit of all the constructors
  using basic_type::basic_type;

  /** An accessor to the first variable of a small array
   */
  DataType& x(){ return (*this)[0]; }

  /** An accessor to the second variable of a small array
  */
  DataType& y(){ return (*this)[1]; }

  /** An accessor to the third variable of a small array
  */
  DataType& z(){ return (*this)[2]; }

  TRISYCL_DECLARE_S(0);
  TRISYCL_DECLARE_S(1);
  TRISYCL_DECLARE_S(2);

  template<int... swizzleIndexs>
  __swizzled_vec__<DataType, sizeof...(swizzleIndexs)> swizzle() const {
    return basic_type::do_swizzle(swizzleIndexs...);
  }
#include "CL/sycl/detail/swiz3.hpp"
};
  
template <typename DataType>
class vec<DataType, 4> : public detail::base_vec<DataType, 4> {
  using basic_type = detail::base_vec<DataType, 4>;

public:

  // Inherit of all the constructors
  using basic_type::basic_type;

public:
  /** An accessor to the first variable of a small array
   */
  DataType& x() { return (*this)[0]; }

  /** An accessor to the second variable of a small array
  */
  DataType& y() { return (*this)[1]; }

  /** An accessor to the third variable of a small array
  */
  DataType& z() { return (*this)[2]; }

  /** An accessor to the third variable of a small array
  */
  DataType& w() { return (*this)[3]; }

  DataType& r() { return (*this)[0]; }

  DataType& g() { return (*this)[1]; }

  DataType& b() { return (*this)[2]; }

  DataType& a() { return (*this)[3]; }

  TRISYCL_DECLARE_S(0);
  TRISYCL_DECLARE_S(1);
  TRISYCL_DECLARE_S(2);
  TRISYCL_DECLARE_S(3);

  template<int... swizzleIndexs>
  __swizzled_vec__<DataType, sizeof...(swizzleIndexs)> swizzle() const {
    return basic_type::do_swizzle(swizzleIndexs...);
  }
#include "CL/sycl/detail/swiz4.hpp"
#include "CL/sycl/detail/swiz_rgba.hpp"
};
#undef TRISYCL_GEN_SWIZ2
#undef TRISYCL_GEN_SWIZ3
#undef TRISYCL_GEN_SWIZ4

template <typename DataType>
class vec<DataType, 8> : public detail::base_vec<DataType, 8> {
  using basic_type = detail::base_vec<DataType, 8>;

public:

  // Inherit of all the constructors
  using basic_type::basic_type;

  TRISYCL_DECLARE_S(0);
  TRISYCL_DECLARE_S(1);
  TRISYCL_DECLARE_S(2);
  TRISYCL_DECLARE_S(3);
  TRISYCL_DECLARE_S(4);
  TRISYCL_DECLARE_S(5);
  TRISYCL_DECLARE_S(6);
  TRISYCL_DECLARE_S(7);
};

template <typename DataType>
class vec<DataType, 16> : public detail::base_vec<DataType, 16> {
  using basic_type = detail::base_vec<DataType, 16>;

public:

  // Inherit of all the constructors
  using basic_type::basic_type;

  TRISYCL_DECLARE_S(0);
  TRISYCL_DECLARE_S(1);
  TRISYCL_DECLARE_S(2);
  TRISYCL_DECLARE_S(3);
  TRISYCL_DECLARE_S(4);
  TRISYCL_DECLARE_S(5);
  TRISYCL_DECLARE_S(6);
  TRISYCL_DECLARE_S(7);
  TRISYCL_DECLARE_S(8);
  TRISYCL_DECLARE_S(9);
  TRISYCL_DECLARE_Sx(A);
  TRISYCL_DECLARE_Sx(B);
  TRISYCL_DECLARE_Sx(C);
  TRISYCL_DECLARE_Sx(D);
  TRISYCL_DECLARE_Sx(E);
  TRISYCL_DECLARE_Sx(F);
};

#undef TRISYCL_DECLARE_S
#undef TRISYCL_DECLARE_Sx

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
