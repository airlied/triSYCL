#ifndef TRISYCL_SYCL_PROGRAM_HPP
#define TRISYCL_SYCL_PROGRAM_HPP

/** \file The OpenCL SYCL program

    Dave Airlie

    This file is distributed under the University of Illinois Open Source
    License. See LICENSE.TXT for details.
*/

#ifdef TRISYCL_OPENCL
#include <boost/compute.hpp>
#endif

#include <map>
#include "CL/sycl/detail/debug.hpp"
#include "CL/sycl/detail/shared_ptr_implementation.hpp"
#include "CL/sycl/detail/unimplemented.hpp"
#include "CL/sycl/kernel.hpp"
#include "CL/sycl/program/detail/host_program.hpp"
#ifdef TRISYCL_OPENCL
#include "CL/sycl/program/detail/opencl_program.hpp"
#endif
#include "CL/sycl/program/detail/program.hpp"
#include "CL/sycl/info/program.hpp"


namespace cl {
namespace sycl {

enum class program_state {
  none,
  compiled,
  linked
};

/** SYCL program

    \todo To be implemented

*/

class kernel;
class contxet;
class program
    /* Use the underlying kernel implementation that can be shared in
     the SYCL model */
  : public detail::shared_ptr_implementation<program, detail::program> {

  // The type encapsulating the implementation
  using implementation_t = typename program::shared_ptr_implementation;

  // The handler class uses the implementation
  friend class handler;

  context c;
  // Allows the comparison operation to access the implementation
  friend implementation_t;
  std::map<::size_t, shared_ptr_class<kernel>> kernels;

  vector_class<device> dev_list;
 public:

  // Make the implementation member directly accessible in this class
  using implementation_t::implementation;

  program() = delete;

#ifdef TRISYCL_OPENCL

  explicit program(const context &context) : c(context) {
    if (c.is_host())
      implementation = std::shared_ptr<detail::program> { new detail::host_program } ;
    else
      implementation = std::shared_ptr<detail::program> { new detail::opencl_program };
  }
  
  program(const context &context, cl_program p) : implementation_t { new detail::opencl_program(p) }, c(context) {}

  program(const context &context, vector_class<device> deviceList) : c(context), dev_list(deviceList) {}

  program(vector_class<program> programList, string_class linkOptions = "") {
    if (programList.size() == 0)
      throw cl::sycl::invalid_object_error("Empty programList");

    c = programList[0].get_context();
  }
    
  cl_program get() const {
    return implementation->get();
  }

  bool is_host() const {
    return implementation->is_host();
  }
  
  template <typename kernelT>
  bool has_kernel() const { return false; }

  bool has_kernel(string_class kernelName) const { return false; }

  template <typename kernelT>
  void compile_with_kernel_type(string_class compileOptions = "")
  {

  }

  void compile_with_source(string_class kernelSource, string_class compileOptions = "")
  {
    
  }
  
  template <typename kernelT>
  void build_with_kernel_type(string_class buildOptions = "")
  {
    compile_with_kernel_type<kernelT>(buildOptions);
    link();
  }

  void build_with_source(string_class kernelSource, string_class buildOptions = "")
  {
    compile_with_source(kernelSource, buildOptions);
    link();
  }

  void link(string_class linkOptions = "")
  {
  }
      
  template <typename kernelT>
  cl::sycl::kernel get_kernel() const;

  cl::sycl::kernel get_kernel(string_class kernelName) const;

  vector_class<vector_class<char>> get_binaries() const { return vector_class<vector_class<char>>('a');}

  context get_context() const { return c; }
  vector_class<device> get_devices() const { return dev_list.size() ? dev_list : c.get_devices(); }

  string_class get_compile_options() const { return ""; }
  string_class get_link_options() const { return ""; }
  string_class get_build_options() const { return ""; }

  program_state get_state() const { return program_state::none; }
#endif

  template <info::program param>
  inline auto get_info() const;
};

template<>
inline auto program::get_info<info::program::reference_count>() const {
  return implementation->get_reference_count();
}

template<>
inline auto program::get_info<info::program::context>() const {
  return context();
}

template<>
inline auto program::get_info<info::program::devices>() const {
  return vector_class<device>();
}

}

}

namespace std {

template <> struct hash<cl::sycl::program> {

  auto operator()(const cl::sycl::program &k) const {
    // Forward the hashing to the implementation
    return k.hash();
  }

};

}
/*
    # Some Emacs stuff:
    ### Local Variables:
    ### ispell-local-dictionary: "american"
    ### eval: (flyspell-prog-mode)
    ### End:
*/

#endif
