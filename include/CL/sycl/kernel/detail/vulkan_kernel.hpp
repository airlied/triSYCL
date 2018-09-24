#ifndef TRISYCL_SYCL_KERNEL_DETAIL_VULKAN_KERNEL_HPP
#define TRISYCL_SYCL_KERNEL_DETAIL_VULKAN_KERNEL_HPP

namespace cl::sycl::detail {

class vulkan_kernel : public detail::kernel,
                      detail::debug<vulkan_kernel> {

};

}
#endif // TRISYCL_SYCL_KERNEL_DETAIL_VULKAN_KERNEL_HPP
