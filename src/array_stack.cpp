#include "assignment/array_stack.hpp"

#include <algorithm>  // copy, fill
#include <stdexcept>  // invalid_argument (НЕЛЬЗЯ ИСПОЛЬЗОВАТЬ)

namespace assignment {

  ArrayStack::ArrayStack(int capacity) {

    // выбрасываем ошибку, если указана неположительная емкость стека
    if (capacity <= 0) {
      throw std::invalid_argument("capacity is not positive");
    }
    size_ = 0;
    capacity_ = capacity;
    data_ = new int[capacity_]{0};
  }

  ArrayStack::~ArrayStack() {
    size_ = 0;
    capacity_ = 0;
    delete[] data_;
    data_ = nullptr;
  }

  void ArrayStack::Push(int value) {
    if (size_ < capacity_) {
      data_[size_] = value;
      size_++;
    } else {
      capacity_ += kCapacityGrowthCoefficient;
      int* dataNew = new int[capacity_]{0};

      dataNew[size_] = value;

      for (int i = 0; i < size_; i++) {
        dataNew[i] = data_[i];
      }

      delete[] data_;
      data_ = dataNew;
      size_ += 1;
    }
  }

  bool ArrayStack::Pop() {
    if (size_ != 0) {
      data_[size_ - 1] = 0;
      size_--;
      return true;
    }
    return false;
  }

  void ArrayStack::Clear() {
    size_ = 0;
  }

  std::optional<int> ArrayStack::Peek() const {
    if (size_ == 0) {
      return std::nullopt;
    }
    return data_[size_ - 1];
  }

  bool ArrayStack::IsEmpty() const {
    if (size_ == 0) return true;
    return false;
  }

  int ArrayStack::size() const {
    return size_;
  }

  int ArrayStack::capacity() const {
    return capacity_;
  }

  bool ArrayStack::Resize(int new_capacity) {
    if (new_capacity <= capacity_) return false;
    capacity_ = new_capacity;
    int* dataNew = new int[capacity_]{0};
    for (int i = 0; i < size_; i++) {
      dataNew[i] = data_[i];
    }
    delete[] data_;
    data_ = dataNew;
    return true;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  ArrayStack::ArrayStack(const std::vector<int>& values, int capacity) {

    size_ = static_cast<int>(values.size());
    capacity_ = capacity;

    data_ = new int[capacity]{};

    std::copy(values.data(), values.data() + size_, data_);
  }

  std::vector<int> ArrayStack::toVector(std::optional<int> size) const {

    if (capacity_ == 0 || data_ == nullptr) {
      return {};
    }

    if (size.has_value()) {
      return {data_, data_ + size.value()};
    }

    return {data_, data_ + capacity_};
  }

}  // namespace assignment
