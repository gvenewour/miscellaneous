#include <cstdint>
#include <iostream>
//#include <functional>
#include <memory>
#include <map>
#include <vector>
//#include <experimental/memory_resource>

namespace homework3 {

    using Key = int;
    using Val = int;

    class MemoryResource {
        public:

        virtual ~MemoryResource() = default;

        virtual bool available(size_t bytes) const = 0;

        virtual uint8_t* allocate(size_t bytes) = 0;
        virtual void deallocate(size_t bytes) = 0;
    };

    //no alignment, simple buffer, nothing interesting here
    class SimpleFixedArena : public MemoryResource {
        public:
            explicit SimpleFixedArena(size_t bytes): _buffer(bytes), _index{0} {}

            bool available(size_t bytes) const override{
                return (_buffer.size() - _index) >= bytes;
            }

            uint8_t* allocate(size_t bytes) override{
                if (available(bytes)) {
                    _index += bytes;
                    return (&_buffer[_index - bytes]);
                }
                throw std::bad_alloc{};
            }

            void deallocate(size_t bytes) override{}

        private:
            std::vector<uint8_t> _buffer;
            size_t _index;
    };

    template<typename T, int maxCount>
    class LinearAllocator {
    public:
        using value_type = T;
        //pointer types are inferred by std::allocator_traits<>

        template<class U> struct rebind {
            typedef LinearAllocator<U, maxCount> other;
        };

        auto allocate(size_t n) {
            if (!_arena) {
                _arena.reset(new SimpleFixedArena{maxCount * sizeof(T)});
            }

            const size_t bytes = n * sizeof(T);

            if (_arena->available(bytes)) {
                return reinterpret_cast<T*>(_arena->allocate(bytes));
            }

            throw std::bad_alloc{};
        }

        void deallocate(T *p, size_t n) {}

        //construct and destroy are deprecated since C++17

        LinearAllocator() = default;

//        template<typename U, int count>
//        explicit LinearAllocator(const LinearAllocator<U, count> &) noexcept {}

    private:
        std::shared_ptr<MemoryResource> _arena;
    };

    //Objects allocated from one instance may safely be freed on another
    template <typename T, typename U, int maxCount>
    inline bool operator==(const LinearAllocator<T, maxCount>&, const LinearAllocator<U, maxCount>&) {
        return false;
    }

    template <typename T, typename U, size_t maxCount>
    inline bool operator!=(const LinearAllocator<T, maxCount>& a, const LinearAllocator<U, maxCount>& b) {
        return !(a==b);
    }
}

constexpr int factorial (int n)
{
    return n > 0 ? n * factorial( n - 1 ) : 1;
}

int main(int argc, char *argv[])
{
    using Key = int;
    using Val = int;

    constexpr uint8_t maxCount = 10;

    auto simpleMap = std::map<Key, Val>{};
    for (auto i = 0; i < maxCount; ++i) {
        simpleMap[i] = factorial(i);    //or tgamma
    }

    auto map = std::map<Key, Val, std::less<>, homework3::LinearAllocator<std::pair<const Key, Val>, maxCount> >{};
    for (auto i = 0; i < maxCount; ++i) {
        map[i] = factorial(i);
    }

    for (const auto& it : map) {
        std::cout << it.first << " " << it.second << "\n";
    }


    return 0;
}
