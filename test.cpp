//
// Created by yhwach on 10/16/25.
//

#include <valarray>
#include <llvm/Support/Allocator.h>
#include <vector>


template<typename>
struct is_ref : std::false_type {
};

template<typename T>
struct is_ref<T &> : std::true_type {
};

template<typename T>
using is_ref_t = typename is_ref<T>::type;

template<typename T>
struct vec_trait {
    using type = T[];
};


template<typename T, template<typename> typename K>
struct s {
    K<T> key;

    template<typename U, template<typename> typename V>
    struct rebind {
        using other = s<U, V>;
    };

    using A = s<int, K>;
    using B = typename A::template rebind<double, int>::other;
};

template<typename T,
    typename Allocator = MyAllocator<T> >
class Vec {
public:
    using value_type = T;
    using allocator_type = Allocator;
    using pointer = typename std::allocator_traits<T>::pointer;
    using const_pointer = typename std::allocator_traits<T>::const_pointer;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type &;
    using iterator = pointer;
    using const_iterator = const pointer;
    using reverse_iterator = std::reverse_iterator<iterator>;

    typename vec_trait<T>::type data;

    Allocator allocator_;
    size_type size_;
    size_type capacity_;
#define growth_factor 1.5


    Vec() noexcept(false)
        : data() {
        auto n = noexcept(false);
    }

    explicit Vec(std::initializer_list<T> &&init) noexcept {
    }

    Vec(const Vec &other) noexcept
        : allocator_(other.allocator_),
          size_(other.size_),
          capacity_(other.capacity_) {
        data = allocator_.allocate(size_ * sizeof(T), alignof(T));
        fill_with(begin(), end(), other.begin());
    }

    Vec(Vec &&other) noexcept {
    }

    ~Vec() noexcept {
    }

    Vec &operator=(const Vec &other) noexcept {
    }

    Vec &operator=(Vec &&other) noexcept {
    }

    void push_back(T &&t) noexcept {
        if (size() + 1 > capacity_) {
            resize();
        }

        data[size_++] = std::move(t);
    }

    void push_back(T t) {
    }

    void push_front(T t) {
    }

    T pop_back() noexcept {
    }

    [[nodiscard]] size_type size() const noexcept {
        return size_;
    }

    [[nodiscard]] size_type capacity() const noexcept {
        return capacity_;
    }

    [[nodiscard]] bool empty() const noexcept {
        return size() == 0;
    }

    iterator at(size_type position) {
    }

    iterator begin() {
    }

    iterator end() {
    }

    reverse_iterator rbegin() {
    }

    reverse_iterator rend() {
    }

    void reserve(size_type n) {
        data = allocator_.allocate(n);
    }

    void resize(const size_type n) {
        auto new_cap = std::max(capacity_ + n,
                                static_cast<size_type>(std::ceil(growth_factor * capacity_)));

        allocator_.allocate(new_cap);
    }

    void insert(iterator place, T t, after_tag tag) {
    }

    void insert(iterator place, T t, before_tag tag) {
    }

    void insert(iterator place, T t) {
        insert(place, t, after_tag{});
    }
};

template<typename T,
    typename Allocator = std::allocator<T> >
class Collection {
    Vec<T, Allocator> vec_;

    using size_type = std::size_t;
    using vec_type = Vec<T, Allocator>;

public:
    Collection(std::initializer_list<T> &&list)
        : vec_(std::forward<std::initializer_list<T> >(list)) {
    }

    Collection(const Collection &other)
        : vec_(other.vec_) {
    }

    Collection(Collection &&other) noexcept
        : vec_(std::move(other.vec_)) {
        other.clear();
    }

    Collection &operator=(const Collection &other) {
    }

    Collection &operator=(Collection &&other) noexcept {
    }

    ~Collection() {
    }

    void clear() noexcept {
    }

    void reserve(std::size_t n) {
    }

    [[nodiscard]] size_type size() const noexcept {
        return vec_.size();
    }

    [[nodiscard]] bool empty() const noexcept {
        return size() == 0;
    }

    vec_type &vec() noexcept {
        return vec_;
    }
};

int main() {
    llvm::BumpPtrAllocator a;
    using CharAllocator = BumpAllocatorAdaptor<char>;
    std::vector<char, CharAllocator> vec{CharAllocator(&a)};
}
