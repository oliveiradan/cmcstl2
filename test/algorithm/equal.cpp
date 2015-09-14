// Range v3 library
//
//  Copyright Eric Niebler 2014
//
//  Use, modification and distribution is subject to the
//  Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// Project home: https://github.com/ericniebler/range-v3

//===----------------------------------------------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is dual licensed under the MIT and the University of Illinois Open
// Source Licenses. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include <stl2/detail/algorithm/equal.hpp>
#include "../simple_test.hpp"
#include "../test_iterators.hpp"

namespace ranges = __stl2;

void test()
{
    using namespace __stl2;
    int ia[] = {0, 1, 2, 3, 4, 5};
    constexpr unsigned s = size(ia);
    int ib[s] = {0, 1, 2, 5, 4, 5};
    CHECK(equal(input_iterator<const int*>(ia),
                 sentinel<const int*>(ia+s),
                 input_iterator<const int*>(ia)));
    CHECK(equal(input_iterator<const int*>(ia),
                 sentinel<const int*>(ia+s),
                 input_iterator<const int*>(ia),
                 sentinel<const int*>(ia+s)));
    CHECK(equal(random_access_iterator<const int*>(ia),
                 random_access_iterator<const int*>(ia+s),
                 random_access_iterator<const int*>(ia),
                 random_access_iterator<const int*>(ia + s)));
    CHECK(equal(random_access_iterator<const int*>(ia),
                 sentinel<const int*>(ia+s),
                 random_access_iterator<const int*>(ia),
                 sentinel<const int*>(ia + s)));
    CHECK(!equal(input_iterator<const int*>(ia),
                  sentinel<const int*>(ia+s),
                  input_iterator<const int*>(ib)));
    CHECK(!equal(input_iterator<const int*>(ia),
                  sentinel<const int*>(ia+s),
                  input_iterator<const int*>(ib),
                  sentinel<const int*>(ib + s)));
    CHECK(!equal(random_access_iterator<const int*>(ia),
                  random_access_iterator<const int*>(ia+s),
                  random_access_iterator<const int*>(ib),
                  random_access_iterator<const int*>(ib+s)));
    CHECK(!equal(random_access_iterator<const int*>(ia),
                  sentinel<const int*>(ia+s),
                  random_access_iterator<const int*>(ib),
                  sentinel<const int*>(ib + s)));
    CHECK(!equal(input_iterator<const int*>(ia),
                  sentinel<const int*>(ia+s),
                  input_iterator<const int*>(ia),
                  sentinel<const int*>(ia + s - 1)));
    CHECK(!equal(random_access_iterator<const int*>(ia),
                  random_access_iterator<const int*>(ia+s),
                  random_access_iterator<const int*>(ia),
                  random_access_iterator<const int*>(ia+s-1)));
    CHECK(!equal(random_access_iterator<const int*>(ia),
                  sentinel<const int*>(ia+s),
                  random_access_iterator<const int*>(ia),
                  sentinel<const int*>(ia + s - 1)));
}

#if 0
void test_rng()
{
    using namespace __stl2;
    using __stl2::ext::make_range;

    int ia[] = {0, 1, 2, 3, 4, 5};
    constexpr unsigned s = size(ia);
    int ib[s] = {0, 1, 2, 5, 4, 5};
    CHECK(equal(make_range(input_iterator<const int*>(ia),
                 sentinel<const int*>(ia+s)),
                 input_iterator<const int*>(ia)));
    CHECK(equal(make_range(input_iterator<const int*>(ia),
                 sentinel<const int*>(ia+s)),
                 make_range(input_iterator<const int*>(ia),
                 sentinel<const int*>(ia+s))));
    CHECK(equal(make_range(random_access_iterator<const int*>(ia),
                 random_access_iterator<const int*>(ia+s)),
                 make_range(random_access_iterator<const int*>(ia),
                 random_access_iterator<const int*>(ia + s))));
    CHECK(equal(make_range(random_access_iterator<const int*>(ia),
                 sentinel<const int*>(ia+s)),
                 make_range(random_access_iterator<const int*>(ia),
                 sentinel<const int*>(ia + s))));
    CHECK(!equal(make_range(input_iterator<const int*>(ia),
                  sentinel<const int*>(ia+s)),
                  input_iterator<const int*>(ib)));
    CHECK(!equal(make_range(input_iterator<const int*>(ia),
                  sentinel<const int*>(ia+s)),
                  make_range(input_iterator<const int*>(ib),
                  sentinel<const int*>(ib + s))));
    CHECK(!equal(make_range(random_access_iterator<const int*>(ia),
                  random_access_iterator<const int*>(ia+s)),
                  make_range(random_access_iterator<const int*>(ib),
                  random_access_iterator<const int*>(ib+s))));
    CHECK(!equal(make_range(random_access_iterator<const int*>(ia),
                  sentinel<const int*>(ia+s)),
                  make_range(random_access_iterator<const int*>(ib),
                  sentinel<const int*>(ib + s))));
    CHECK(!equal(make_range(input_iterator<const int*>(ia),
                  sentinel<const int*>(ia+s)),
                  make_range(input_iterator<const int*>(ia),
                  sentinel<const int*>(ia + s - 1))));
    CHECK(!equal(make_range(random_access_iterator<const int*>(ia),
                  random_access_iterator<const int*>(ia+s)),
                  make_range(random_access_iterator<const int*>(ia),
                  random_access_iterator<const int*>(ia+s-1))));
    CHECK(!equal(make_range(random_access_iterator<const int*>(ia),
                  sentinel<const int*>(ia+s)),
                  make_range(random_access_iterator<const int*>(ia),
                  sentinel<const int*>(ia + s - 1))));
}
#endif

int comparison_count = 0;

template <typename T>
bool counting_equals(const T &a, const T &b)
{
    ++comparison_count;
    return a == b;
}

void test_pred()
{
    using namespace __stl2;
    int ia[] = {0, 1, 2, 3, 4, 5};
    constexpr unsigned s = size(ia);
    int ib[s] = {0, 1, 2, 5, 4, 5};
    CHECK(equal(input_iterator<const int*>(ia),
                 sentinel<const int*>(ia+s),
                 input_iterator<const int*>(ia),
                 std::equal_to<int>()));
    CHECK(equal(input_iterator<const int*>(ia),
                 sentinel<const int*>(ia+s),
                 input_iterator<const int*>(ia),
                 sentinel<const int*>(ia + s),
                 std::equal_to<int>()));
    CHECK(equal(random_access_iterator<const int*>(ia),
                 random_access_iterator<const int*>(ia+s),
                 random_access_iterator<const int*>(ia),
                 random_access_iterator<const int*>(ia+s),
                 std::equal_to<int>()));
    CHECK(equal(random_access_iterator<const int*>(ia),
                 sentinel<const int*>(ia+s),
                 random_access_iterator<const int*>(ia),
                 sentinel<const int*>(ia + s),
                 std::equal_to<int>()));

    comparison_count = 0;
    CHECK(!equal(input_iterator<const int*>(ia),
                 sentinel<const int*>(ia+s),
                 input_iterator<const int*>(ia),
                 sentinel<const int*>(ia + s - 1),
                 counting_equals<int>));
    CHECK(comparison_count > 0);
    comparison_count = 0;
    CHECK(!equal(random_access_iterator<const int*>(ia),
                 random_access_iterator<const int*>(ia+s),
                 random_access_iterator<const int*>(ia),
                 random_access_iterator<const int*>(ia+s-1),
                 counting_equals<int>));
    CHECK(comparison_count == 0);
    comparison_count = 0;
    CHECK(!equal(random_access_iterator<const int*>(ia),
                 sentinel<const int*>(ia+s),
                 random_access_iterator<const int*>(ia),
                 sentinel<const int*>(ia + s - 1),
                 counting_equals<int>));
    CHECK(comparison_count > 0);
    CHECK(!equal(input_iterator<const int*>(ia),
                  sentinel<const int*>(ia+s),
                  input_iterator<const int*>(ib),
                  std::equal_to<int>()));
    CHECK(!equal(input_iterator<const int*>(ia),
                  sentinel<const int*>(ia+s),
                  input_iterator<const int*>(ib),
                  sentinel<const int*>(ib + s),
                  std::equal_to<int>()));
    CHECK(!equal(random_access_iterator<const int*>(ia),
                  random_access_iterator<const int*>(ia+s),
                  random_access_iterator<const int*>(ib),
                  random_access_iterator<const int*>(ib+s),
                  std::equal_to<int>()));
    CHECK(!equal(random_access_iterator<const int*>(ia),
                  sentinel<const int*>(ia+s),
                  random_access_iterator<const int*>(ib),
                  sentinel<const int*>(ib + s),
                  std::equal_to<int>()));
}

#if 0
void test_rng_pred()
{
    using namespace __stl2;
    using __stl2::ext::make_range;

    int ia[] = {0, 1, 2, 3, 4, 5};
    constexpr unsigned s = size(ia);
    int ib[s] = {0, 1, 2, 5, 4, 5};
    CHECK(equal(make_range(input_iterator<const int*>(ia),
                 sentinel<const int*>(ia+s)),
                 input_iterator<const int*>(ia),
                 std::equal_to<int>()));
    CHECK(equal(make_range(input_iterator<const int*>(ia),
                 sentinel<const int*>(ia+s)),
                 make_range(input_iterator<const int*>(ia),
                 sentinel<const int*>(ia + s)),
                 std::equal_to<int>()));
    CHECK(equal(make_range(random_access_iterator<const int*>(ia),
                 random_access_iterator<const int*>(ia+s)),
                 make_range(random_access_iterator<const int*>(ia),
                 random_access_iterator<const int*>(ia+s)),
                 std::equal_to<int>()));
    CHECK(equal(make_range(random_access_iterator<const int*>(ia),
                 sentinel<const int*>(ia+s)),
                 make_range(random_access_iterator<const int*>(ia),
                 sentinel<const int*>(ia + s)),
                 std::equal_to<int>()));

    comparison_count = 0;
    CHECK(!equal(make_range(input_iterator<const int*>(ia),
                 sentinel<const int*>(ia+s)),
                 make_range(input_iterator<const int*>(ia),
                 sentinel<const int*>(ia + s - 1)),
                 counting_equals<int>));
    CHECK(comparison_count > 0);
    comparison_count = 0;
    CHECK(!equal(make_range(random_access_iterator<const int*>(ia),
                 random_access_iterator<const int*>(ia+s)),
                 make_range(random_access_iterator<const int*>(ia),
                 random_access_iterator<const int*>(ia+s-1)),
                 counting_equals<int>));
    CHECK(comparison_count == 0);
    comparison_count = 0;
    CHECK(!equal(make_range(random_access_iterator<const int*>(ia),
                 sentinel<const int*>(ia+s)),
                 make_range(random_access_iterator<const int*>(ia),
                 sentinel<const int*>(ia + s - 1)),
                 counting_equals<int>));
    CHECK(comparison_count > 0);
    CHECK(!equal(make_range(input_iterator<const int*>(ia),
                  sentinel<const int*>(ia+s)),
                  input_iterator<const int*>(ib),
                  std::equal_to<int>()));
    CHECK(!equal(make_range(input_iterator<const int*>(ia),
                  sentinel<const int*>(ia+s)),
                  make_range(input_iterator<const int*>(ib),
                  sentinel<const int*>(ib + s)),
                  std::equal_to<int>()));
    CHECK(!equal(make_range(random_access_iterator<const int*>(ia),
                  random_access_iterator<const int*>(ia+s)),
                  make_range(random_access_iterator<const int*>(ib),
                  random_access_iterator<const int*>(ib+s)),
                  std::equal_to<int>()));
    CHECK(!equal(make_range(random_access_iterator<const int*>(ia),
                  sentinel<const int*>(ia+s)),
                  make_range(random_access_iterator<const int*>(ib),
                  sentinel<const int*>(ib + s)),
                  std::equal_to<int>()));
}
#endif

int main()
{
    ::test();
    //::test_rng();
    ::test_pred();
    //::test_rng_pred();

    return ::test_result();
}