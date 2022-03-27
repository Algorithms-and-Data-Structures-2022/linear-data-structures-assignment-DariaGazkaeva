#include "assignment/linked_list.hpp"

namespace assignment {

  LinkedList::~LinkedList() {

    // эквивалентно очистке списка
    LinkedList::Clear();
  }

  void LinkedList::Add(int value) {
    if (size_ == 0) {
      back_ = new Node(value, nullptr);
      front_ = back_;
    } else {
      back_->next = new Node(value, nullptr);
      back_ = back_->next;
    }
    size_++;
  }

  bool LinkedList::Insert(int index, int value) {
    if (index > size_ || index < 0) return false;
    if (size_ == 0) {
      back_ = new Node(value, nullptr);
      front_ = back_;
      size_++;
      return true;
    }
    if (index == 0) {
      Node* newNode = new Node(value, front_);
      front_ = newNode;
      size_++;
      return true;
    }
    if (index == size_) {
      Node* newNode = new Node(value, nullptr);
      FindNode(index - 1)->next = newNode;
      back_ = newNode;
      size_++;
      return true;

    }
    Node* leftNode = FindNode(index - 1);
    Node* newNode = new Node(value, leftNode->next);
    FindNode(index - 1)->next = newNode;
    size_++;
    return true;
  }

  bool LinkedList::Set(int index, int new_value) {
    if (index >= size_ || index < 0) return false;
    FindNode(index)->value = new_value;
    return true;
  }

  std::optional<int> LinkedList::Remove(int index) {
    if (index >= size_ || size_ == 0 || index < 0) return std::nullopt;
    if (index == 0) {
      int output = front_->value;
      front_ = front_->next;
      size_--;
      return output;
    }
    if (index == size_ - 1) {
      int output = FindNode(index)->value;
      size_--;
      delete back_;
      back_ = FindNode(index - 1);
      back_->next = nullptr;
      return output;
    }
    int output = FindNode(index)->value;
    Node* node = FindNode(index)->next;
    delete FindNode(index);
    FindNode(index - 1)->next = node;
    size_--;
    return output;
  }

  void LinkedList::Clear() {
    for (int i = 0; i < size_; i++) {
      delete FindNode(i);
    }
    size_ = 0;
    front_ = nullptr;
    back_ = nullptr;
  }

  std::optional<int> LinkedList::Get(int index) const {
    if (index >= size_ || size_ == 0 || index < 0) return std::nullopt;
    return FindNode(index)->value;
  }

  std::optional<int> LinkedList::IndexOf(int value) const {
    if (size_ == 0) return std::nullopt;
    for (int i = 0; i < size_; i++) {
      if (FindNode(i)->value == value) {
        return i;
      }
    }
    return std::nullopt;
  }

  bool LinkedList::Contains(int value) const {
    if (size_ == 0) return false;
    for (int i = 0; i < size_; i++) {
      if (FindNode(i)->value == value) {
        return true;
      }
    }
    return false;
  }

  bool LinkedList::IsEmpty() const {
    if (size_ != 0) return false;
    return true;
  }

  int LinkedList::size() const {
    return size_;
  }

  std::optional<int> LinkedList::front() const {
    if (size_ == 0) return std::nullopt;
    return front_->value;
  }

  std::optional<int> LinkedList::back() const {
    if (size_ == 0) return std::nullopt;
    return back_->value;
  }

  Node* LinkedList::FindNode(int index) const {
    if (size_ == 0 || index >= size_ || index < 0) return nullptr;
    Node* node = front_;
    for (int i = 0; i < index; i++) {
      node = node->next;
    }
    return node;
  }

  // ДЛЯ ТЕСТИРОВАНИЯ
  LinkedList::LinkedList(const std::vector<int>& values) {

    if (values.empty()) {
      return;
    }

    auto* curr_node = new Node(values.front());
    front_ = curr_node;

    for (int index = 1; index < values.size() - 1; ++index) {
      curr_node->next = new Node(values[index]);
      curr_node = curr_node->next;
    }

    if (values.size() == 1) {
      back_ = front_;
    } else {
      curr_node->next = new Node(values.back());
      back_ = curr_node->next;
    }

    size_ = static_cast<int>(values.size());
  }

  std::vector<int> LinkedList::toVector() const {

    if (front_ == nullptr || size_ == 0) {
      return {};
    }

    std::vector<int> array;
    array.reserve(size_);

    for (auto* node = front_; node != nullptr; node = node->next) {
      array.push_back(node->value);
    }

    return array;
  }

}  // namespace assignment