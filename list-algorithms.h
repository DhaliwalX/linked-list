#ifndef LIST_ALGORITHMS_H_
#define LIST_ALGORITHMS_H_

#include "forward-list.h"

#include <algorithm>
#include <iostream>
#include <functional>

namespace list {

// rotate a doubly linked list towards left
// for e.g. 1 <--> 2 <--> 3 <--> 4 <--> 5
// --->     2 <--> 3 <--> 4 <--> 5 <--> 1
template <typename ListType>
void rotate_left_d(ListType &list) {
  auto head = list.begin()._Ptr();
  auto last = list.end()._Ptr();
  if (list.size() > ListType::size_type(1)) {
    // rotation occurs only if size is greater than 1
    auto save = head->next_;
    head->next_ = save->next_;
    head->next_->prev_ = head;
    last->prev_->next_ = save;
    save->prev_ = last->prev_;
    last->prev_ = save;
    save->next_ = last;
  }
}

// rotate a doubly linked list towards left by n positions
template <typename ListType>
void rotate_left_d(ListType &list, unsigned int n) {
  while (n--)
    rotate_left_d(list);
}


// rotate a doubly linked list towards right
// for e.g. 1 <--> 2 <--> 3 <--> 4 <--> 5
// --->     5 <--> 1 <--> 2 <--> 3 <--> 4
template <typename ListType>
void rotate_right_d(ListType &list) {
  auto head = list.begin()._Ptr();
  auto last = list.end()._Ptr();
  if (list.size() > ListType::size_type(1)) {
    auto save = last->prev_;
    last->prev_ = save->prev_;
    last->prev_->next_ = last;
    head->next_->prev_ = save;
    save->next_ = head->next_;
    save->prev_ = head;
    head->next_ = save;
  }
}

// rotate a doubly linked list towards left by n positions
template <typename ListType>
void rotate_right_d(ListType &list, unsigned int n) {
  while (n--)
    rotate_right_d(list);
}

// finds the first element satisfying a particular predicate
template <typename Iterator, typename Key, typename Predicate>
static inline auto find_if(Iterator begin, Iterator end, const Key &key,
                        Predicate pred) -> decltype(begin) {
  for (; begin != end; ++begin)
    if (pred(*begin, key))
      return begin;
  return begin;
}

// finds the first element satisfying a particular predicate
template <typename Iterator, typename Key>
static inline auto find_if(Iterator begin, Iterator end,
                        const Key &key) -> decltype(begin) {
  return find_if(begin, end, key, std::equal_to<Key>());
}

// erases all the elements satisfying particular predicate
template <typename Container, typename Predicate>
static void erase_if(Container &cont, Predicate pred) {
  for (auto begin = cont.begin(); begin != cont.end();)
    if (pred(*begin))
      begin = cont.erase(begin);
    else  ++begin;
}

//
//      singly linked list algorithms
//     -------------------------------


template <typename ForwardListType>
static inline void rotate_left_s(ForwardListType &list) {
  ForwardListType::NodePtr &head = list.GetHead();
  ForwardListType::NodePtr &end = list.GetEnd();
  decltype(head) it = head, save;
  save = it;
  // go to (last - 1)th node
  while (it->next_ != end) {
    save = it;
    it = it->next_;
  }

  save->next_ = head->next_;
  head->next_ = head->next_->next_;
  head->next_->next_ = end;
}

template <typename ForwardListType, typename Predicate>
static inline void erase_if(ForwardListType &list, Predicate pred) {
  ForwardListType::iterator it = list.begin();
  ForwardListType::iterator save = it;
  while (pred(*it)) {
    list.pop_front();
    it = list.begin();
  }
  save = it++;
  while (it != list.end()) {
    if (pred(it))
      list.erase_after(save);
    save = it++;
  }
}

}
#endif // LIST_ALGORITHMS_H_
