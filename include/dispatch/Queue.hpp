#ifndef METALPP_DISPATCH_QUEUE_HPP
#define METALPP_DISPATCH_QUEUE_HPP

#include <dispatch/dispatch.h>

namespace dispatch
{
    class Queue final
    {
    public:
        explicit Queue(const char* name = nullptr):
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

        operator dispatch_queue_t() const noexcept
        {
            return queue;
        }

    private:
        dispatch_queue_t queue = nullptr;
    };
}


#endif
