// Tencent is pleased to support the open source community by making RapidJSON available.
// 
// Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip. All rights reserved.
//
// Licensed under the MIT License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// http://opensource.org/licenses/MIT
//
// Unless required by applicable law or agreed to in writing, software distributed 
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
// CONDITIONS OF ANY KIND, either express or implied. See the License for the 
// specific language governing permissions and limitations under the License.

#include "unittest.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"

using namespace rapidjson;

TEST(StringBuffer, InitialSize) {
    StringBuffer buffer;
    EXPECT_EQ(0u, buffer.GetSize());
    EXPECT_STREQ("", buffer.GetString());
}

TEST(StringBuffer, Put) {
    StringBuffer buffer;
    buffer.Put('A');

    EXPECT_EQ(1u, buffer.GetSize());
    EXPECT_STREQ("A", buffer.GetString());
}

TEST(StringBuffer, Clear) {
    StringBuffer buffer;
    buffer.Put('A');
    buffer.Put('B');
    buffer.Put('C');
    buffer.Clear();

    EXPECT_EQ(0u, buffer.GetSize());
    EXPECT_STREQ("", buffer.GetString());
}

TEST(StringBuffer, Push) {
    StringBuffer buffer;
    buffer.Push(5);

    EXPECT_EQ(5u, buffer.GetSize());

    // Causes sudden expansion to make the stack's capacity equal to size
    buffer.Push(65536u);
    EXPECT_EQ(5u + 65536u, buffer.GetSize());
}

TEST(StringBuffer, Pop) {
    StringBuffer buffer;
    buffer.Put('A');
    buffer.Put('B');
    buffer.Put('C');
    buffer.Put('D');
    buffer.Put('E');
    buffer.Pop(3);

    EXPECT_EQ(2u, buffer.GetSize());
    EXPECT_STREQ("AB", buffer.GetString());
}

#if RAPIDJSON_HAS_CXX11_RVALUE_REFS

#include <type_traits>

TEST(StringBuffer, Traits) {
    static_assert( std::is_constructible<StringBuffer>::value, "");
    static_assert( std::is_default_constructible<StringBuffer>::value, "");
#ifndef _MSC_VER
    static_assert(!std::is_copy_constructible<StringBuffer>::value, "");
#endif
    static_assert( std::is_move_constructible<StringBuffer>::value, "");

    static_assert(!std::is_nothrow_constructible<StringBuffer>::value, "");
    static_assert(!std::is_nothrow_default_constructible<StringBuffer>::value, "");

#if !defined(_MSC_VER) || _MSC_VER >= 1800
    static_assert(!std::is_nothrow_copy_constructible<StringBuffer>::value, "");
    static_assert(!std::is_nothrow_move_constructible<StringBuffer>::value, "");
#endif

    static_assert( std::is_assignable<StringBuffer,StringBuffer>::value, "");
#ifndef _MSC_VER
    static_assert(!std::is_copy_assignable<StringBuffer>::value, "");
#endif
    static_assert( std::is_move_assignable<StringBuffer>::value, "");

#if !defined(_MSC_VER) || _MSC_VER >= 1800
    static_assert(!std::is_nothrow_assignable<StringBuffer, StringBuffer>::value, "");
#endif

    static_assert(!std::is_nothrow_copy_assignable<StringBuffer>::value, "");
    static_assert(!std::is_nothrow_move_assignable<StringBuffer>::value, "");

    static_assert( std::is_destructible<StringBuffer>::value, "");
#ifndef _MSC_VER
    static_assert(std::is_nothrow_destructible<StringBuffer>::value, "");
#endif
}

TEST(StringBuffer, MoveConstructor) {
    StringBuffer x;
    x.Put('A');
    x.Put('B');
    x.Put('C');
    x.Put('D');

    EXPECT_EQ(4u, x.GetSize());
    EXPECT_STREQ("ABCD", x.GetString());

    // StringBuffer y(x); // does not compile (!is_copy_constructible)
    StringBuffer y(std::move(x));
    EXPECT_EQ(0u, x.GetSize());
    EXPECT_EQ(4u, y.GetSize());
    EXPECT_STREQ("ABCD", y.GetString());

    // StringBuffer z = y; // does not compile (!is_copy_assignable)
    StringBuffer z = std::move(y);
    EXPECT_EQ(0u, y.GetSize());
    EXPECT_EQ(4u, z.GetSize());
    EXPECT_STREQ("ABCD", z.GetString());
}

TEST(StringBuffer, MoveAssignment) {
    StringBuffer x;
    x.Put('A');
    x.Put('B');
    x.Put('C');
    x.Put('D');

    EXPECT_EQ(4u, x.GetSize());
    EXPECT_STREQ("ABCD", x.GetString());

    StringBuffer y;
    // y = x; // does not compile (!is_copy_assignable)
    y = std::move(x);
    EXPECT_EQ(0u, x.GetSize());
    EXPECT_EQ(4u, y.GetSize());
    EXPECT_STREQ("ABCD", y.GetString());
}

#endif // RAPIDJSON_HAS_CXX11_RVALUE_REFS
