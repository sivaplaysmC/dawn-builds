// Copyright 2020 The Tint Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "src/tint/sem/test_helper.h"
#include "src/tint/sem/texture.h"

namespace tint::sem {
namespace {

using ArrayTest = TestHelper;

TEST_F(ArrayTest, CreateSizedArray) {
    auto* a = create<Array>(create<U32>(), create<type::ConstantArrayCount>(2u), 4u, 8u, 32u, 16u);
    auto* b = create<Array>(create<U32>(), create<type::ConstantArrayCount>(2u), 4u, 8u, 32u, 16u);
    auto* c = create<Array>(create<U32>(), create<type::ConstantArrayCount>(3u), 4u, 8u, 32u, 16u);
    auto* d = create<Array>(create<U32>(), create<type::ConstantArrayCount>(2u), 5u, 8u, 32u, 16u);
    auto* e = create<Array>(create<U32>(), create<type::ConstantArrayCount>(2u), 4u, 9u, 32u, 16u);
    auto* f = create<Array>(create<U32>(), create<type::ConstantArrayCount>(2u), 4u, 8u, 33u, 16u);
    auto* g = create<Array>(create<U32>(), create<type::ConstantArrayCount>(2u), 4u, 8u, 33u, 17u);

    EXPECT_EQ(a->ElemType(), create<U32>());
    EXPECT_EQ(a->Count(), create<type::ConstantArrayCount>(2u));
    EXPECT_EQ(a->Align(), 4u);
    EXPECT_EQ(a->Size(), 8u);
    EXPECT_EQ(a->Stride(), 32u);
    EXPECT_EQ(a->ImplicitStride(), 16u);
    EXPECT_FALSE(a->IsStrideImplicit());
    EXPECT_FALSE(a->Count()->Is<type::RuntimeArrayCount>());

    EXPECT_EQ(a, b);
    EXPECT_NE(a, c);
    EXPECT_NE(a, d);
    EXPECT_NE(a, e);
    EXPECT_NE(a, f);
    EXPECT_NE(a, g);
}

TEST_F(ArrayTest, CreateRuntimeArray) {
    auto* a = create<Array>(create<U32>(), create<type::RuntimeArrayCount>(), 4u, 8u, 32u, 32u);
    auto* b = create<Array>(create<U32>(), create<type::RuntimeArrayCount>(), 4u, 8u, 32u, 32u);
    auto* c = create<Array>(create<U32>(), create<type::RuntimeArrayCount>(), 5u, 8u, 32u, 32u);
    auto* d = create<Array>(create<U32>(), create<type::RuntimeArrayCount>(), 4u, 9u, 32u, 32u);
    auto* e = create<Array>(create<U32>(), create<type::RuntimeArrayCount>(), 4u, 8u, 33u, 32u);
    auto* f = create<Array>(create<U32>(), create<type::RuntimeArrayCount>(), 4u, 8u, 33u, 17u);

    EXPECT_EQ(a->ElemType(), create<U32>());
    EXPECT_EQ(a->Count(), create<type::RuntimeArrayCount>());
    EXPECT_EQ(a->Align(), 4u);
    EXPECT_EQ(a->Size(), 8u);
    EXPECT_EQ(a->Stride(), 32u);
    EXPECT_EQ(a->ImplicitStride(), 32u);
    EXPECT_TRUE(a->IsStrideImplicit());
    EXPECT_TRUE(a->Count()->Is<type::RuntimeArrayCount>());

    EXPECT_EQ(a, b);
    EXPECT_NE(a, c);
    EXPECT_NE(a, d);
    EXPECT_NE(a, e);
    EXPECT_NE(a, f);
}

TEST_F(ArrayTest, Hash) {
    auto* a = create<Array>(create<U32>(), create<type::ConstantArrayCount>(2u), 4u, 8u, 32u, 16u);
    auto* b = create<Array>(create<U32>(), create<type::ConstantArrayCount>(2u), 4u, 8u, 32u, 16u);
    auto* c = create<Array>(create<U32>(), create<type::ConstantArrayCount>(3u), 4u, 8u, 32u, 16u);
    auto* d = create<Array>(create<U32>(), create<type::ConstantArrayCount>(2u), 5u, 8u, 32u, 16u);
    auto* e = create<Array>(create<U32>(), create<type::ConstantArrayCount>(2u), 4u, 9u, 32u, 16u);
    auto* f = create<Array>(create<U32>(), create<type::ConstantArrayCount>(2u), 4u, 8u, 33u, 16u);
    auto* g = create<Array>(create<U32>(), create<type::ConstantArrayCount>(2u), 4u, 8u, 33u, 17u);

    EXPECT_EQ(a->Hash(), b->Hash());
    EXPECT_NE(a->Hash(), c->Hash());
    EXPECT_NE(a->Hash(), d->Hash());
    EXPECT_NE(a->Hash(), e->Hash());
    EXPECT_NE(a->Hash(), f->Hash());
    EXPECT_NE(a->Hash(), g->Hash());
}

TEST_F(ArrayTest, Equals) {
    auto* a = create<Array>(create<U32>(), create<type::ConstantArrayCount>(2u), 4u, 8u, 32u, 16u);
    auto* b = create<Array>(create<U32>(), create<type::ConstantArrayCount>(2u), 4u, 8u, 32u, 16u);
    auto* c = create<Array>(create<U32>(), create<type::ConstantArrayCount>(3u), 4u, 8u, 32u, 16u);
    auto* d = create<Array>(create<U32>(), create<type::ConstantArrayCount>(2u), 5u, 8u, 32u, 16u);
    auto* e = create<Array>(create<U32>(), create<type::ConstantArrayCount>(2u), 4u, 9u, 32u, 16u);
    auto* f = create<Array>(create<U32>(), create<type::ConstantArrayCount>(2u), 4u, 8u, 33u, 16u);
    auto* g = create<Array>(create<U32>(), create<type::ConstantArrayCount>(2u), 4u, 8u, 33u, 17u);

    EXPECT_TRUE(a->Equals(*b));
    EXPECT_FALSE(a->Equals(*c));
    EXPECT_FALSE(a->Equals(*d));
    EXPECT_FALSE(a->Equals(*e));
    EXPECT_FALSE(a->Equals(*f));
    EXPECT_FALSE(a->Equals(*g));
    EXPECT_FALSE(a->Equals(Void{}));
}

TEST_F(ArrayTest, FriendlyNameRuntimeSized) {
    auto* arr = create<Array>(create<I32>(), create<type::RuntimeArrayCount>(), 0u, 4u, 4u, 4u);
    EXPECT_EQ(arr->FriendlyName(Symbols()), "array<i32>");
}

TEST_F(ArrayTest, FriendlyNameStaticSized) {
    auto* arr = create<Array>(create<I32>(), create<type::ConstantArrayCount>(5u), 4u, 20u, 4u, 4u);
    EXPECT_EQ(arr->FriendlyName(Symbols()), "array<i32, 5>");
}

TEST_F(ArrayTest, FriendlyNameRuntimeSizedNonImplicitStride) {
    auto* arr = create<Array>(create<I32>(), create<type::RuntimeArrayCount>(), 0u, 4u, 8u, 4u);
    EXPECT_EQ(arr->FriendlyName(Symbols()), "@stride(8) array<i32>");
}

TEST_F(ArrayTest, FriendlyNameStaticSizedNonImplicitStride) {
    auto* arr = create<Array>(create<I32>(), create<type::ConstantArrayCount>(5u), 4u, 20u, 8u, 4u);
    EXPECT_EQ(arr->FriendlyName(Symbols()), "@stride(8) array<i32, 5>");
}

TEST_F(ArrayTest, IsConstructable) {
    auto* fixed_sized =
        create<Array>(create<U32>(), create<type::ConstantArrayCount>(2u), 4u, 8u, 32u, 16u);
    auto* named_override_sized = create<Array>(
        create<U32>(), create<sem::NamedOverrideArrayCount>(nullptr), 4u, 8u, 32u, 16u);
    auto* unnamed_override_sized = create<Array>(
        create<U32>(), create<sem::UnnamedOverrideArrayCount>(nullptr), 4u, 8u, 32u, 16u);
    auto* runtime_sized =
        create<Array>(create<U32>(), create<type::RuntimeArrayCount>(), 4u, 8u, 32u, 16u);

    EXPECT_TRUE(fixed_sized->IsConstructible());
    EXPECT_FALSE(named_override_sized->IsConstructible());
    EXPECT_FALSE(unnamed_override_sized->IsConstructible());
    EXPECT_FALSE(runtime_sized->IsConstructible());
}

TEST_F(ArrayTest, HasCreationFixedFootprint) {
    auto* fixed_sized =
        create<Array>(create<U32>(), create<type::ConstantArrayCount>(2u), 4u, 8u, 32u, 16u);
    auto* named_override_sized = create<Array>(
        create<U32>(), create<sem::NamedOverrideArrayCount>(nullptr), 4u, 8u, 32u, 16u);
    auto* unnamed_override_sized = create<Array>(
        create<U32>(), create<sem::UnnamedOverrideArrayCount>(nullptr), 4u, 8u, 32u, 16u);
    auto* runtime_sized =
        create<Array>(create<U32>(), create<type::RuntimeArrayCount>(), 4u, 8u, 32u, 16u);

    EXPECT_TRUE(fixed_sized->HasCreationFixedFootprint());
    EXPECT_FALSE(named_override_sized->HasCreationFixedFootprint());
    EXPECT_FALSE(unnamed_override_sized->HasCreationFixedFootprint());
    EXPECT_FALSE(runtime_sized->HasCreationFixedFootprint());
}

TEST_F(ArrayTest, HasFixedFootprint) {
    auto* fixed_sized =
        create<Array>(create<U32>(), create<type::ConstantArrayCount>(2u), 4u, 8u, 32u, 16u);
    auto* named_override_sized = create<Array>(
        create<U32>(), create<sem::NamedOverrideArrayCount>(nullptr), 4u, 8u, 32u, 16u);
    auto* unnamed_override_sized = create<Array>(
        create<U32>(), create<sem::UnnamedOverrideArrayCount>(nullptr), 4u, 8u, 32u, 16u);
    auto* runtime_sized =
        create<Array>(create<U32>(), create<type::RuntimeArrayCount>(), 4u, 8u, 32u, 16u);

    EXPECT_TRUE(fixed_sized->HasFixedFootprint());
    EXPECT_TRUE(named_override_sized->HasFixedFootprint());
    EXPECT_TRUE(unnamed_override_sized->HasFixedFootprint());
    EXPECT_FALSE(runtime_sized->HasFixedFootprint());
}

}  // namespace
}  // namespace tint::sem
