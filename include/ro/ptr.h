#ifndef READONLY_PTR_HEADER_FILE
#define READONLY_PTR_HEADER_FILE

#if __cplusplus >= 201103L
#include <memory>
#endif

namespace readonly {
    /** @class ro_ptr ptr.h "ro/ptr.h"
     * @brief Wrapper structure around a raw pointer signaling only read access.
     *
     * This is essentially the same as passing const T* into an API call but it allows implicit
     * conversions from the the major two smart pointers and a unified interface for accessing
     * the pointer even when raw pointers are used.
     *
     * @note This does no synchronization or any other checking on the pointer whatsoever.
     * If you need synchronized access to the underlying resource it is recommended to wrap it
     * in a synchronizing structure and pass the pointer to that around.
     *
     * @include doc.cc
     */
    template<typename T>
    struct ro_ptr {
#if __cplusplus >= 201103L
    using element_type = T;
    using pointer = element_type*;

    using const_type = const element_type;
    using const_pointer = const element_type*;
#else
    typedef T element_type;
    typedef element_type* pointer;

    typedef const element_type const_type;
    typedef const element_type* const_pointer;
#endif

        /**
         * @brief Contract breaking call for interfaces out of your control
         *
         * You may have to deal with external interfaces which don't adhere to const-correctness.
         * This call allows you to get a mutable pointer so you can call methods not marked const.
         *
         * @attention This is only intended for external interfaces and you're violating the API contract if you modify the state of the pointer.
         */
        pointer unsafe_get() const {
            return ptr_;
        }

        /**
         * @brief Get a const reference to the wrapped type
         */
        const_type& operator*() const {
            return *ptr_;
        }

        /**
         * @brief Access the const pointer to the original data
         */
        const_pointer operator->() const {
            return ptr_;
        }

#if __cplusplus >= 201103L
        /**
         * @brief Create a readonly pointer from a shared_ptr
         */
        ro_ptr(const std::shared_ptr<T>& p)
            : ptr_(p.get()) {}
        /**
         * @brief Create a readonly pointer from a unique_ptr
         */
        ro_ptr(const std::unique_ptr<T>& p)
            : ptr_(p.get()) {}
#endif
        /**
         * @brief Create a readonly pointer from a raw pointer
         */
        ro_ptr(pointer p)
            : ptr_(p) {}
    private:
        pointer ptr_;
    };
}

#endif
