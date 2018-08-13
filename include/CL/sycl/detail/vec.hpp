#ifndef TRISYCL_SYCL_DETAIL_VEC_HPP
#define TRISYCL_SYCL_DETAIL_VEC_HPP

/** \file

    Implement the internals and common code of vec class

    This file is distributed under the University of Illinois Open Source
    License. See LICENSE.TXT for details.
*/
namespace detail {
template <typename, int>
class base_vec;
}

template <typename, int>
class vec;  

template <typename dataT, int numElements>
using __swizzled_base_vec__ = detail::base_vec<dataT, numElements>;

template <typename dataT, int numElements>
using __swizzled_vec__ = vec<dataT, numElements>;

/* this file is included from cl::sycl namespace already */
namespace detail {
template <typename DataType, int NumElements>
     class base_vec : public small_array<DataType,
					 cl::sycl::vec<DataType, NumElements>,
					    NumElements> {
  using basic_type = small_array<DataType,
					  cl::sycl::vec<DataType, NumElements>,
                                                  NumElements>;
  using basic_type::basic_type;

  static const int out_dims = (NumElements + 1) / 2;
public:
  /** Construct a vec from anything from a scalar (to initialize all the
      elements with this value) up to an aggregate of scalar and vector
      types (in this case the total number of elements must match the size
      of the vector)
  */
  /// Use classical constructors too
  base_vec() : basic_type {} {
  }


  template <typename... Types>
  base_vec(const Types... args)
    : basic_type { detail::expand<base_vec>(flatten_to_tuple<base_vec>(args...)) } {
  }

private:

  /** Flattening helper that does not change scalar values but flatten a
      vec<T, n> v into a tuple<T, T,..., T>{ v[0], v[1],..., v[n-1] }

      If we have a vector, just forward its array content since an array
      has also a tuple interface :-) (23.3.2.9 Tuple interface to class
      template array [array.tuple])
  */
  template <typename V, typename Element, int s>
  static auto flatten(const base_vec<Element, s> i) {
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

protected:  
  __swizzled_base_vec__<DataType, 1>do_swizzle(int first) const {
    return (*this)[first];
  }

  template<typename T, typename... Ts>
  __swizzled_base_vec__<DataType, sizeof...(Ts) + 1>do_swizzle(T first, Ts... swizzleIndexes) const {
    return __swizzled_base_vec__<DataType, sizeof...(Ts) + 1> {do_swizzle(first), do_swizzle(swizzleIndexes...) };
  }

public:

  __swizzled_vec__<DataType, out_dims> lo() const {
    static_assert (NumElements > 1);
    __swizzled_base_vec__<DataType, out_dims> newarray;
    for (unsigned idx = 0; idx < out_dims; idx++)
      newarray[idx] = (*this)[idx];
    return newarray;
  }

  __swizzled_vec__<DataType, out_dims> hi() const {
    static_assert (NumElements > 1);
    __swizzled_base_vec__<DataType, out_dims> newarray;
    for (unsigned idx = 0; idx < out_dims; idx++)
      newarray[idx] = (*this)[out_dims + idx];
    return newarray;
  }

  __swizzled_vec__<DataType, out_dims> odd() const {
    static_assert (NumElements > 1);
    __swizzled_base_vec__<DataType, out_dims> newarray;
    for (unsigned idx = 0; idx < out_dims; idx++)
      newarray[idx] = (*this)[idx * 2 + 1];
    return newarray;
  }

  __swizzled_vec__<DataType, out_dims> even() const {
    static_assert (NumElements > 1);
    __swizzled_base_vec__<DataType, out_dims> newarray;
    for (unsigned idx = 0; idx < out_dims; idx++)
      newarray[idx] = (*this)[idx * 2];
    return newarray;
  }

  template<typename convertT, rounding_mode roundingMode>
  vec<convertT, NumElements> convert() const {
    TRISYCL_UNIMPL;
    return {};
  };

  template<typename asT> asT as() const {
    TRISYCL_UNIMPL;
    return {};
  };
  // Swizzle methods (see notes)
  template<int... swizzleIndexs>
  __swizzled_base_vec__<DataType, sizeof...(swizzleIndexs)> swizzle() const {
    return do_swizzle(swizzleIndexs...);
  }
  template <cl::sycl::access::address_space addressSpace>
  void load(size_t offset, multi_ptr<DataType, addressSpace> ptr) {
    TRISYCL_UNIMPL;
  }

  template <cl::sycl::access::address_space addressSpace>
  void store(size_t offset, multi_ptr<DataType, addressSpace> ptr) const {
    TRISYCL_UNIMPL;
  }

};
}
#endif
