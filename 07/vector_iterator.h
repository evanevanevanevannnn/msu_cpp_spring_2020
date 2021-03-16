template <typename T>
class _Vector_iterator {
	T* ptr_;
public:
	using iterator_category = std::random_access_iterator_tag;
	using value_type = T;
	using difference_type = ptrdiff_t;
	using pointer = T*;
	using reference = T&;

	_Vector_iterator() {}
	explicit _Vector_iterator(T* ptr): ptr_(ptr) {}

	reference operator*() const {
		return *ptr_;
	}

	_Vector_iterator& operator++() {
		++ptr_;
		return *this;
	}

	_Vector_iterator& operator++(int) {
		return _Vector_iterator(ptr_++);
	}

	_Vector_iterator& operator--() {
		--ptr_;
		return *this;
	}

	_Vector_iterator& operator--(int) {
		return _Vector_iterator(ptr_--);
	}

	reference operator[](int n) const {
		return ptr_[n];
	}

	_Vector_iterator& operator+=(int n) {
		ptr_ += n;
		return *this;
	}

	_Vector_iterator operator+(int n) const {
		return _Vector_iterator(ptr_ + n);
	}

	_Vector_iterator operator-=(int n) {
		ptr_ -= n;
		return *this;
	}

	_Vector_iterator operator-(int n) const {
		return _Vector_iterator(ptr_ - n);
	}

	bool operator==(const _Vector_iterator& n) const {
		return ptr_ == n.ptr_;
	}

	bool operator!=(const _Vector_iterator& n) const {
		return ptr_ != n.ptr_;
	}

	bool operator<(const _Vector_iterator& n) const {
		return ptr_ < n.ptr_;
	}

	bool operator>(const _Vector_iterator& n) const {
		return ptr_ > n.ptr_;
	}

	bool operator<=(const _Vector_iterator& n) const {
		return ptr_ <= n.ptr_;
	}

	bool operator>=(const _Vector_iterator& n) const {
		return ptr_ >= n.ptr_;
	}
};

template <class _Iterator>
class _Vector_reverse_iterator {
	_Iterator iter_;
public:
	using iterator_type = _Iterator;
	using iterator_category = typename std::iterator_traits<_Iterator>::iterator_category;
	using value_type = typename std::iterator_traits<_Iterator>::value_type;
	using difference_type = typename std::iterator_traits<_Iterator>::difference_type;
	using pointer = typename std::iterator_traits<_Iterator>::pointer;
	using reference = typename std::iterator_traits<_Iterator>::reference;

	_Vector_reverse_iterator() {}
	explicit _Vector_reverse_iterator(iterator_type iter): iter_(iter) {}

	reference operator*() const {
		_Iterator tmp = iter_;
		return *--tmp;
	}

	_Vector_reverse_iterator& operator++() {
		--iter_;
		return *this;
	}

	_Vector_reverse_iterator operator++(int) {
		_Vector_reverse_iterator tmp = *this;
		--iter_;
		return tmp;
	}

	_Vector_reverse_iterator& operator--() {
		++iter_;
		return *this;
	}

	_Vector_reverse_iterator operator--(int) {
		_Vector_reverse_iterator tmp = *this;
		++iter_;
		return tmp;
	}

	reference operator[](int n) const {
		return iter_[n];
	}

	_Vector_reverse_iterator& operator+=(int n) {
		iter_ -= n;
		return *this;
	}

	_Vector_reverse_iterator operator+(int n) const {
		return _Vector_reverse_iterator(iter_ - n);
	}

	_Vector_reverse_iterator& operator-=(int n) {
		iter_ += n;
		return *this;
	}

	_Vector_reverse_iterator operator-(int n) const {
		return _Vector_reverse_iterator(iter_ + n);
	}

	bool operator==(const _Vector_reverse_iterator& n) const {
		return iter_ == n.iter_;
	}

	bool operator!=(const _Vector_reverse_iterator& n) const {
		return iter_ != n.iter_;
	}

	bool operator<(const _Vector_reverse_iterator& n) const {
		return iter_ < n.iter_;
	}

	bool operator>(const _Vector_reverse_iterator& n) const {
		return iter_ > n.iter_;
	}

	bool operator<=(const _Vector_reverse_iterator& n) const {
		return iter_ <= n.iter_;
	}

	bool operator>=(const _Vector_reverse_iterator& n) const {
		return iter_ >= n.iter_;
	}
};