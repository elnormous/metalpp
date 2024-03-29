#ifndef METALPP_DISPATCH_QUEUE_HPP
#define METALPP_DISPATCH_QUEUE_HPP

#include <dispatch/dispatch.h>

namespace dispatch
{
    class Queue final
    {
    public:
        [[nodiscard]] static auto current() noexcept
        {
            return Queue{dispatch_get_current_queue()};
        }

        [[nodiscard]] static auto main() noexcept
        {
            return Queue{dispatch_get_main_queue()};
        }

        explicit Queue(const char* name = nullptr) noexcept:
            queue{dispatch_queue_create(name, nullptr)}
        {
        }

        ~Queue()
        {
            if (queue) dispatch_release(queue);
        }

        Queue(Queue&& other) noexcept:
            queue{other.queue}
        {
            other.queue = nullptr;
        }

        Queue(const Queue& other) noexcept:
            queue{other.queue}
        {
            if (queue) dispatch_retain(queue);
        }

        Queue(const dispatch_queue_t q) noexcept: queue{q}
        {
            dispatch_retain(queue);
        }

        Queue& operator=(Queue&& other) noexcept
        {
            if (&other == this) return *this;
            if (queue) dispatch_release(queue);
            queue = other.queue;
            other.queue = nullptr;
            return *this;
        }

        Queue& operator=(const Queue& other) noexcept
        {
            if (&other == this) return *this;
            if (other.queue) dispatch_retain(other.queue);
            if (queue) dispatch_release(queue);
            queue = other.queue;
            return *this;
        }

        [[nodiscard]] operator dispatch_queue_t() const noexcept
        {
            return queue;
        }

        auto getLabel() const noexcept
        {
            return dispatch_queue_get_label(queue);
        }

    private:
        dispatch_queue_t queue = nullptr;
    };
}

#endif
