#ifndef METALPP_DISPATCH_DATA_HPP
#define METALPP_DISPATCH_DATA_HPP

#include <dispatch/dispatch.h>

namespace dispatch
{
    class Data final
    {
    public:
        explicit Data(const void* buffer,
                      const size_t size,
                      const dispatch_queue_t queue,
                      const dispatch_block_t destructor) noexcept:
            data{dispatch_data_create(buffer, size, queue, destructor)}
        {
        }

        ~Data()
        {
            if (data) dispatch_release(data);
        }

        Data(Data&& other) noexcept:
            data{other.data}
        {
            other.data = nullptr;
        }

        Data(const Data& other) noexcept:
            data{other.data}
        {
            if (data) dispatch_retain(data);
        }

        Data(const dispatch_data_t d) noexcept: data{d}
        {
            dispatch_retain(data);
        }

        Data& operator=(Data&& other) noexcept
        {
            if (&other == this) return *this;
            if (data) dispatch_release(data);
            data = other.data;
            other.data = nullptr;
            return *this;
        }

        Data& operator=(const Data& other) noexcept
        {
            if (&other == this) return *this;
            if (other.data) dispatch_retain(other.data);
            if (data) dispatch_release(data);
            data = other.data;
            return *this;
        }

        [[nodiscard]] operator dispatch_data_t() const noexcept
        {
            return data;
        }

        [[nodiscard]] auto get() const noexcept
        {
            return data;
        }

        [[nodiscard]] auto getSize() const noexcept
        {
            return dispatch_data_get_size(data);
        }

    private:
        dispatch_data_t data = nullptr;
    };
}

#endif
