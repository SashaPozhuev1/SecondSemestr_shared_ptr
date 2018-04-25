#include <iostream>

template <typename T>
class shared_ptr {
	T * ptr_;
	std::size_t * count;
public:
    explicit shared_ptr (T * ptr = nullptr) {	
			ptr_ = ptr;

			if (ptr_) {
				count = new std::size_t(1);
			}
			else {
				count = nullptr;
			}
	}

	shared_ptr(shared_ptr<T> const & other) {
		ptr_ = other.ptr_;

		if (ptr_) {
			count = other.count;
			++*count;
		}
		else {
			count = nullptr;
		}
	}

	shared_ptr & operator=(shared_ptr const & other) {
		if (ptr_ != other.ptr_) {
			if (count && *count - 1 > 0) {
				--*count;
			}
			else if (count && *count - 1 == 0) {
				delete count;
				delete ptr_;
			}
			ptr_ = other.ptr_;
			count = other.count;
			if (count) {
				++*count;
			}
		}
		return *this;
	}

	~shared_ptr() {
		if (count && *count - 1 > 0) {
			--*count;
		}
		else {
			delete count;
			delete ptr_;
		}
	}

	T * operator->() {
		return ptr_;
	}

	T & operator* () {
		return *ptr_;
	}

	T * get() const {
		return ptr_;
	}

	void reset(T * ptr = nullptr);

	bool isEmpty();

	void swap(shared_ptr & other);
};

template <typename T>
void shared_ptr<T>::swap(shared_ptr & other) {
	if ((ptr_ || other.ptr_) && (ptr_ != other.ptr_)) {
		std::swap(ptr_, other.ptr_);
		std::swap(count, other.count);
	}
}

template <typename T>
bool shared_ptr<T>::isEmpty() {
	if (ptr_) {
		return false;
	}
	return true;
}

template <typename T>
void shared_ptr<T>::reset(T * ptr) {
	if (count && *count - 1 > 0) {
		--*count;
	}
	else if (count && *count - 1 == 0) {
		delete count;
		delete ptr_;
	}

	ptr_ = ptr;

	if (ptr_) {
		count = new std::size_t(1);
	}
	else {
		count = nullptr;
	} 
}
