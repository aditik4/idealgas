// Copyright (c) 2020 CS126SP20. All rights reserved.

#include "ll.h"

#include <cassert>
#include <utility>
#include <vector>

namespace cs126linkedlist {

template <typename ElementType>
LinkedList<ElementType>::LinkedList() {
  head_ = new Node;
  size_ = 0;
}

template <typename ElementType>
LinkedList<ElementType>::LinkedList(const std::vector<ElementType>& values) {
 for (ElementType element: values) {
   push_back(element);
 }
}

// Copy constructor
template <typename ElementType>
LinkedList<ElementType>::LinkedList(const LinkedList<ElementType>& source) {
  head_ = nullptr;
  if (source.head_ == nullptr) {
      head_ = nullptr;
  } else {
    for(LinkedList<ElementType>::const_iterator iterator = source.begin(); iterator != source.end(); ++iterator) {
      push_back(*iterator);
    }
  }
}

// Move constructor
template <typename ElementType>
LinkedList<ElementType>::LinkedList(LinkedList<ElementType>&& source) noexcept {
  head_ = source.head_;
  size_ = source.size_;
  source.head_ = nullptr;
  source.size_ = 0;
}

// Destructor
template <typename ElementType>
LinkedList<ElementType>::~LinkedList() {
  delete head_;
}

// Copy assignment operator
template <typename ElementType>
LinkedList<ElementType>& LinkedList<ElementType>::operator=(
    const LinkedList<ElementType>& source) {
  if (source.head_ == nullptr) {
    head_ = nullptr;
  } else {
    for(LinkedList<ElementType>::const_iterator iterator = source.begin(); iterator != source.end(); ++iterator) {
      push_back(*iterator);
    }
  }
  return *this;

}

// Move assignment operator
template <typename ElementType>
LinkedList<ElementType>& LinkedList<ElementType>::operator=(
    LinkedList<ElementType>&& source) noexcept {
  if(this != source) {
    delete head_;
    head_ = source.head_;
    size_ = source.size_;
    source.head_ = nullptr;
    source.size_ = 0;
  }
  return *this;
}

template <typename ElementType>
void LinkedList<ElementType>::push_front(const ElementType& value) {
  Node* newNode = new Node;
  newNode ->next_ = head_;
  newNode ->value_ = value;
  head_ = newNode;
  size_++;
}

template <typename ElementType>
void LinkedList<ElementType>::push_back(const ElementType& value) {
  Node* newNode = new Node;
  newNode->value_ = value;
  newNode->next_ = nullptr;
  if (empty()) {
    head_ = newNode;
  } else {
    Node* current = head_;
    while (current->next_ != nullptr) {
      current = current->next_;
    }
    current->next_ = newNode;
  }
  size_++;
}

template <typename ElementType>
ElementType LinkedList<ElementType>::front() const {
  if(head_ == nullptr || empty()) {
    throw std::invalid_argument("list is null");
  }
  return head_->value_;
}

template <typename ElementType>
ElementType LinkedList<ElementType>::back() const {
  if(empty() || head_ == nullptr) {
    throw std::invalid_argument("list is null");
  }
  Node* current = head_;
  while(current->next_ != nullptr) {
    current = current->next_;
  }
  return current->value_;
}

template <typename ElementType>
void LinkedList<ElementType>::pop_front() {
  if(empty() || head_ == nullptr) {
    throw std::invalid_argument("list is null");
  }
  if(size_ != 0) {
    Node* temp = head_;
    head_ = head_->next_;
    delete temp;
  }
  size_--;
}

template <typename ElementType>
void LinkedList<ElementType>::pop_back() {
  if(empty() || head_ == nullptr) {
    throw std::invalid_argument("list is null");
  }
  if(head_ != nullptr && head_->next_ == nullptr) {
    delete head_;
  } else  {
    Node* current = head_;
    while(current->next_->next_ != nullptr) {
      current = current->next_;
    }
    delete current->next_;
    current->next_ = nullptr;
  }
  size_--;
}

template <typename ElementType>
size_t LinkedList<ElementType>::size() const {
  return size_;
}

template <typename ElementType>
bool LinkedList<ElementType>::empty() const {
  return (size_ == 0);
}

template <typename ElementType>
void LinkedList<ElementType>::clear() {
  Node current = head_;
  size_t index = 0;
  while (current.next_ != nullptr){
    RemoveNth(index);
    index++;
  }
  head_ = nullptr;
}

template <typename ElementType>
std::ostream& operator<<(std::ostream& os,
                         const LinkedList<ElementType>& list) {
  return os;
}

template <typename ElementType>
void LinkedList<ElementType>::RemoveNth(size_t n) {
  if(n < 0 || n >= size_) {
    throw std::invalid_argument("list is null");
  }
  if(n == 0) {
    pop_front();
  } else if (n == size_ - 1) {
    pop_back();
  } else {
    Node* current = head_;
    size_t index = 0;
    while(index > n - 1 && current != nullptr) {
      current = current->next_;
      index++;
    }
    Node* temp = current->next_->next_;
    delete current->next_;
    current->next_ = temp;
    size_ --;
  }
}

template <typename ElementType>
void LinkedList<ElementType>::RemoveOdd() {
  size_t index = 0;
  Node* current = head_;
  while (current != nullptr && index < size_) {
    if (current->value_ % 2 != 0) {
      RemoveNth(index);
    }
    current = current->next_;
    index++;
  }
}

template <typename ElementType>
bool LinkedList<ElementType>::operator==(
    const LinkedList<ElementType>& rhs) const {
  if(size_ != rhs.size_) {
    return false;
  }
  Node* thisNode = head_;
  Node* rhsNode = rhs.head_;
  while (thisNode != nullptr && rhsNode != nullptr) {
    if(thisNode->value_ != rhsNode->value_) {
      return false;
    } else {
      thisNode = thisNode->next_;
      rhsNode = rhsNode->next_;
    }
  }
  return true;
}

template <typename ElementType>
bool LinkedList<ElementType>::operator!=(
    const LinkedList<ElementType>& rhs) const {
  if(size_ != rhs.size_) {
    return true;
  }
  Node* thisNode = head_;
  Node* rhsNode = rhs.head_;
  while (thisNode != nullptr && rhsNode != nullptr) {
    if(thisNode->value_ != rhsNode->value_) {
      return true;
    } else {
      thisNode = thisNode->next_;
      rhsNode = rhsNode->next_;
    }
  }
  return false;
}

template <typename ElementType>
typename LinkedList<ElementType>::iterator& LinkedList<ElementType>::iterator::
operator++() {
  if (current_ != nullptr) {
    current_ = current_->next_;
  }
  return *this;
}

template <typename ElementType>
ElementType& LinkedList<ElementType>::iterator::operator*() const {
  return current_->value_;
}

template <typename ElementType>
bool LinkedList<ElementType>::iterator::operator!=(
    const typename LinkedList<ElementType>::iterator& other) const {
  return current_ != other.current_;
}

template <typename ElementType>
typename LinkedList<ElementType>::iterator LinkedList<ElementType>::begin() {
  return head_;
}

template <typename ElementType>
typename LinkedList<ElementType>::iterator LinkedList<ElementType>::end() {
  return nullptr;
}

template <typename ElementType>
typename LinkedList<ElementType>::const_iterator&
LinkedList<ElementType>::const_iterator::operator++() {
  if (current_ != nullptr) {
    current_ = current_->next_;
  }
  return *this;
}

template <typename ElementType>
const ElementType& LinkedList<ElementType>::const_iterator::operator*() const {
  return current_->value_;
}

template <typename ElementType>
bool LinkedList<ElementType>::const_iterator::operator!=(
    const typename LinkedList<ElementType>::const_iterator& other) const {
 return current_ != other.current_;
}

template <typename ElementType>
typename LinkedList<ElementType>::const_iterator
LinkedList<ElementType>::begin() const {
 return const_iterator(head_);
}

template <typename ElementType>
typename LinkedList<ElementType>::const_iterator LinkedList<ElementType>::end() const {
  return nullptr;
}

}  // namespace cs126linkedlist
