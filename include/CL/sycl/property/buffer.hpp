#ifndef TRISYCL_SYCL_BUFFER_QUEUE_HPP
#define TRISYCL_SYCL_BUFFER_QUEUE_HPP

namespace cl::sycl::property::buffer {

class use_host_ptr : public detail::property {
public:
  use_host_ptr() {}
};

class use_mutex : public detail::property {
  mutex_class *mutex_ptr;
public:
  use_mutex(mutex_class &mutexRef) : mutex_ptr { &mutexRef } {}
  mutex_class *get_mutex_ptr() const { return mutex_ptr; };
};

class context_bound : public detail::property {
  context bound_context;

public:
  context_bound(context boundContext) : bound_context { boundContext } {}
  context get_context() const { return bound_context; };
};

}

#endif
