#include "vector_iterator.h"

template<
	typename T,
	class Alloc = std::allocator<T>>
class vector {
	T* data_;
	Alloc alloc_;

	size_t size_;
	size_t capacity_;

public:
	using size_type = size_t;
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
	using allocator_type = Alloc;

	using iterator = _Vector_iterator<T>;
	using const_iterator = _Vector_iterator<const T>;
	using reverse_iterator = _Vector_reverse_iterator<T>;
	using const_reverse_iterator = _Vector_reverse_iterator<const T>;

	explicit vector(size_type count = 15): capacity_(count) {
		data_ = alloc_.allocate(count);

		size_ = 0;
	}

    vector(size_type count, const value_type& defaultValue): capacity_(count), size_(count) {
    	data_ = alloc_.allocate(count);

    	for (size_t i = 0; i < count; ++i)
    		data_[i] = defaultValue;
    }

    vector(std::initializer_list<value_type> init) {
    	data_ = alloc_.allocate(init.size());

    	auto curr = init.begin(), end = init.end();
    	for (size_t i = 0; curr < end; ++i, ++curr)
    		data_[i] = *curr;

    	capacity_ = init.size();
    	size_ = init.size();
    }

    iterator begin() noexcept {
    	return iterator(data_);
    }

    reverse_iterator rbegin() noexcept {
    	return reverse_iterator(end());
    }

    const_iterator cbegin() const noexcept {
    	return const_iterator(data_);
    }

    const_reverse_iterator crbegin() const noexcept {
    	return const_reverse_iterator(begin());
    }

    iterator end() noexcept {
    	return iterator(data_ + capacity_);
    }

    reverse_iterator rend() noexcept {
    	return reverse_iterator(begin());
    }

    const_iterator cend() const noexcept {
    	return const_iterator(data_ + capacity_);
    }

    const_reverse_iterator crend() const noexcept {
    	return const_reverse_iterator(begin());
    }

    void push_back(value_type&& value) {
    	if (size_ == capacity_)
    		resize(capacity_ * 2);

    	data_[size_++] = value;
    }

    void push_back(const value_type& value) {
    	if (size_ == capacity_)
    		resize(capacity_ * 2);

    	data_[size_++] = value;
    }

    template<class... VT>
    void emplace_back(VT&&... values) {
    	T new_ = T(values);
    	push_back(new_);
    }

    iterator insert(const_iterator where, T&& value) {
    	auto it = cbegin();

    	for (size_t i = 0; i < capacity_; ++i) {
    		if (it + 1 == where) {
    			
    		}

    		++it;
    	}
    }

    iterator insert(const_iterator where, const T& value);

    template<class... VT>
    iterator emplace(const_iterator where, VT&&... values);

    void reserve(size_type count) {
    	if (count <= capacity_)
    		return;

    	resize(count);
    }
    
    size_type capacity() const noexcept {
    	return capacity_;
    }

    size_type size() const noexcept {
    	return size_;
    }

    void resize(size_type newSize) {
    	T* new_data_ = alloc_.allocate(newSize);
    	memcpy(new_data_, data_, std::min(newSize, size_) * sizeof(T));
    	alloc_.deallocate(data_, capacity_);
    	
    	data_ = new_data_;
    	capacity_ = newSize;
    	size_ = std::min(size_, newSize);
    }

    void resize(size_type newsize, const value_type& defaultValue) {
    	T* new_data_ = alloc_.allocate(newSize);
    	memcpy(new_data_, data_, std::min(newSize, size_) * sizeof(T));
    	alloc_.deallocate(data_, capacity_);
    	
    	if (newSize > capacity_)
    		for (size_t i = capacity_; i < newSize; ++i)
    			new_data_[i] = defaultValue;

    	data_ = new_data_;
    	capacity_ = newSize;
    	size_ = std::min(size_, newSize);
    }

    iterator erase(const_iterator where);

    // [from, to)
    iterator erase(const_iterator from, const_iterator to);

    void clear() noexcept;
};