// Copyright (c) 2020 [Your Name]. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include <cs126linkedlist/ll.h>


using cs126linkedlist::LinkedList;

// Read more on SECTIONs here:
// `https://github.com/catchorg/Catch2/tree/master/docs`
// in the "Test Cases and Sections" file.
TEST_CASE("Test Constructor") {
  std::vector<int> values;
  values.push_back(0);
  values.push_back(1);
  values.push_back(2);
  SECTION("fills values by vector") {
    LinkedList<int> testList = LinkedList<int>(values);
    REQUIRE(testList.size() == 3);
    REQUIRE(testList.front() == 0);
    REQUIRE(testList.back() == 2);
  }
  SECTION("copy constructor", "[==operator]") {
    LinkedList<int> list = LinkedList<int>(values);
    LinkedList<int> testCopyList = LinkedList<int>(list);
    REQUIRE(list.operator==(testCopyList));
    REQUIRE(testCopyList.front() == 0);
    REQUIRE(testCopyList.back() == 2);
  }
  //LinkedList<int> testList = LinkedList<int>(values);
  //LinkedList<int> testCopyList = LinkedList<int>(testList);
  //REQUIRE(testList.size() == 3);
  //REQUIRE(testList.front() == 0);
  //REQUIRE(testList.back() == 2);
  //REQUIRE(testList.operator==(testCopyList));
  // REQUIRE(testCopyList.front() == 0);
}

TEST_CASE("Copy Assignment Operator") {
  LinkedList<int> test;
  test.push_back(1);
  test.push_back(2);
  test.push_back(3);
  LinkedList<int> copy;
  copy.operator=(test);
  REQUIRE(copy == test);
  REQUIRE(copy.size() == test.size());
  REQUIRE(copy.front() == test.front());
  REQUIRE(copy.back() == test.back());

}
TEST_CASE("Test Move Assignment Operator") {
  LinkedList<int> test;
  test.push_back(1);
  test.push_back(10);
  LinkedList<int> list = std::move(test);
  REQUIRE(test.size() == 0);
  REQUIRE(list.size() == 2);

}
TEST_CASE("Test Move Constructor") {
  LinkedList<int> test;
  test.push_back(1);
  test.push_back(10);
  LinkedList<int> copy = LinkedList<int>(std::move(test));
  REQUIRE(copy == test);
}

TEST_CASE("Test Operators") {
  LinkedList<int> test;
  test.push_back(1);
  test.push_back(2);
  test.push_back(3);
  SECTION("operator==") {
    LinkedList<int> copy;
    copy.push_back(1);
    copy.push_back(2);
    copy.push_back(3);
    REQUIRE(test.operator==(copy));
  }
  SECTION("operator!=") {
    LinkedList<int> copy;
    copy.push_back(1);
    REQUIRE((test.operator!=(copy)));
  }
}
TEST_CASE("Test Iterator") {
  LinkedList<int> test;
  test.push_back(1);
  test.push_back(2);
  test.push_back(3);
  LinkedList<int> copy;
  SECTION("iterator begin, end, ++, * operations") {
    for(LinkedList<int>::iterator it = test.begin(); it != test.end(); ++it) {
      copy.push_back(it.operator*());
    }
    REQUIRE(copy == test);
  }
  SECTION("Iterator begin non const") {
    REQUIRE(test.begin().operator*() == 1);
  }
}

TEST_CASE("Push Back", "[constructor][push_back][size][empty]") {
  LinkedList<int> list;
  REQUIRE(list.size() == 0);
  REQUIRE(list.empty());
  SECTION("Push back one element") {
    list.push_back(1);
    REQUIRE(list.size() == 1);
    REQUIRE(list.front() == 1);
  }
  SECTION("Push back two elements") {
    list.push_back(-1);
    list.push_back(10000);
    REQUIRE(list.size() == 2);
    REQUIRE(list.front() == -1);
    REQUIRE(list.back() == 10000);
  }
}
TEST_CASE("Push Front", "[constructor][push_back][size][empty]") {
  LinkedList<int> list;
  REQUIRE(list.size() == 0);
  REQUIRE(list.empty());
  SECTION("Push front one element") {
    list.push_front(1);
    REQUIRE(list.front() == 1);
  }
  SECTION("Push front two elements") {
    list.push_front(1);
    list.push_front(2);
    REQUIRE(list.front() == 2);
  }
}
TEST_CASE("Remove Nth", "[constructor][push_back][size][empty]") {
  LinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  SECTION("Remove first element") {
    list.RemoveNth(0);
    REQUIRE(list.front() == 2);
    REQUIRE(list.size() == 2);
  }
  SECTION("Remove middle element") {
    list.RemoveNth(1);
    REQUIRE(list.front() == 1);
    REQUIRE(list.back() == 3);
    REQUIRE(list.size() ==2);
  }
  SECTION("Remove last element") {
    list.RemoveNth(2);
    REQUIRE(list.front() == 1);
    REQUIRE(list.back() == 2);
    REQUIRE(list.size() ==2);
  }
  SECTION("Remove at invalid index") {
    REQUIRE_THROWS_AS(list.RemoveNth(-2), std::invalid_argument);
  }
}
TEST_CASE("Pop back and pop front", "[constructor][push_back][size][empty]") {
  LinkedList<int> list;
  list.push_back(1);
  list.push_back(2);
  list.push_back(3);
  SECTION("Test Pop back") {
    list.pop_back();
    REQUIRE(list.back() == 2);
    REQUIRE(list.size() == 2);
  }
  SECTION("Test pop front") {
    list.pop_front();
    REQUIRE(list.front() == 2);
    REQUIRE(list.size() ==2);
  }
  SECTION("Test pop back empty list") {
    LinkedList<int> testEmpty;
    REQUIRE_THROWS_AS(testEmpty.pop_back(), std::invalid_argument);
  }
}
TEST_CASE("Remove Odd values") {
  LinkedList<int> list;
  list.push_front(7);
  list.push_front(4);
  list.push_front(32);
  list.RemoveOdd();
  REQUIRE(list.size() == 2);
  REQUIRE(list.front() == 4);
  REQUIRE(list.back() == 32);
}
