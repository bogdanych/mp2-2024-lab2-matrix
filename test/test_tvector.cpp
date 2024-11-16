#include "tmatrix.h"
#include <gtest.h>
TEST(TDynamicVector, can_create_vector_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicVector<int> v(5));
}
TEST(TDynamicVector, cant_create_too_large_vector)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}
TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}
TEST(TDynamicVector, can_create_copied_vector)
{
	TDynamicVector<int> v(10);
	ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v(10);
	for (auto i = 0; i < 10; i++) {
		v[i] = i;
	}
	TDynamicVector<int> copy = v;
	EXPECT_EQ(v, copy);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v1(10);
	for (auto i = 0; i < 10; i++) {
		v1[i] = i;
	}
	TDynamicVector<int> v2 = v1;
	for (auto i = 0; i < 10; i++) {
		v2[i] = i + 1;
	}
	EXPECT_NE(v2, v1);
}

TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v(1);
	EXPECT_EQ(1, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
	TDynamicVector<int> v(1);
	v[0] = 1;

	EXPECT_EQ(1, v[0]);
}
TEST(TDynamicVector, can_set_and_get_element_at)
{
	TDynamicVector<int> v(1);
	v.at(0) = 1;

	EXPECT_EQ(1, v.at(0));
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(1);
	ASSERT_ANY_THROW(v.at(-1) = 4);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(1);
	ASSERT_ANY_THROW(v.at(100) = 4);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(10);
	for (int i = 0; i < 10; i++) {
		v.at(i) = i;
	}
	ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v(10);
	for (int i = 0; i < 10; i++) {
		v[i] = i;
	}
	TDynamicVector<int> v1(10);
	ASSERT_NO_THROW(v1 = v);
	EXPECT_EQ(v1, v);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v(100), v1(200);
	for (auto i = 0; i < 200; i++) {
		v[i % 100] = 100 * i;
		v1[i] = i;
	}
	ASSERT_NO_THROW(v1 = v);
	EXPECT_EQ(v1.size(), v.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v(100), v1(200);
	for (auto i = 0; i < 200; i++) {
		v[i % 100] = 100 * i;
		v1[i] = i;
	}
	ASSERT_NO_THROW(v1 = v);
	EXPECT_EQ(v1, v);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v(100), v1(100);
	for (auto i = 0; i < 100; i++) {
		v[i] = i;
		v1[i] = i;
	}
	ASSERT_NO_THROW(v == v1);
	EXPECT_EQ(v1 == v, true);
}
TEST(TDynamicVector, compare_not_equal_vectors_return_false)
{
	TDynamicVector<int> v(100), v1(100);
	for (auto i = 0; i < 100; i++) {
		v[i] = i;
		v1[i] = i + 1;
	}
	ASSERT_NO_THROW(v == v1);
	EXPECT_EQ(v1 == v, false);
}
TEST(TDynamicVector, compare_not_equal_vectors_return_true)
{
	TDynamicVector<int> v(100), v1(100);
	for (auto i = 0; i < 100; i++) {
		v[i] = i;
		v1[i] = i + 1;
	}
	ASSERT_NO_THROW(v != v1);
	EXPECT_EQ(v1 != v, true);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(10);
	for (auto i = 0; i < 10; i++) {
		v[i] = i;
	}
	ASSERT_NO_THROW(v == v);
	EXPECT_EQ(v == v, true);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v(10), v1(11);

	ASSERT_NO_THROW(v == v1);
	EXPECT_EQ(v1 == v, false);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v(10), v1(10);
	for (auto i = 0; i < 10; i++) {
		v[i] = i;
		v1[i] = i + 5;
	}
	ASSERT_NO_THROW(v + 5);
	EXPECT_EQ(v + 5, v1);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v(10), v1(10);
	for (auto i = 0; i < 10; i++) {
		v[i] = i;
		v1[i] = i - 5;
	}
	ASSERT_NO_THROW(v - 5);
	EXPECT_EQ(v - 5, v1);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v(10), v1(10);
	for (auto i = 0; i < 10; i++) {
		v[i] = i;
		v1[i] = 5 * i * 5;
	}
	ASSERT_NO_THROW(v * 25);
	EXPECT_EQ(v * 25, v1);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v(100), v1(100), v2(100);
	for (int i = 0; i < 100; i++) {
		v[i] = i;
		v1[i] = i;
		v2[i] = i + i;
	}

	ASSERT_NO_THROW(v1 + v);
	EXPECT_EQ(v1 + v, v2);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(100), v1(1000);
	for (int i = 0; i < 100; i++) {
		v[i] = i;
		v1[i] = i;
	}

	ASSERT_ANY_THROW(v1 + v);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v(100), v1(100), v2(100);
	for (int i = 0; i < 100; i++) {
		v[i] = i;
		v1[i] = i;
		v2[i] = 0;
	}

	ASSERT_NO_THROW(v1 - v);
	EXPECT_EQ(v1 - v, v2);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(100), v1(1000);
	for (int i = 0; i < 100; i++) {
		v[i] = i;
		v1[i] = i;
	}

	ASSERT_ANY_THROW(v1 - v);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v(100), v1(100);
	int res = 0;
	for (int i = 0; i < 100; i++) {
		v[i] = rand() % 100;
		v1[i] = rand() % 100;
		res += v[i] * v1[i];
	}
	ASSERT_NO_THROW(v1 * v);
	EXPECT_EQ(res, v1 * v);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v(100), v1(101);
	for (int i = 0; i < 100; i++)
	{
		v[i] = i;
		v1[i] = i;
	}
	ASSERT_ANY_THROW(v1 * v);
}

TEST(TDynamicVector, initialization_constructor_overload)
{
	int n = 100;
	int* mas = new int[n];
	for (int i = 0; i < n; i++)
		mas[i] = i;
	TDynamicVector<int> v(mas, n);
	bool check = 1;
	for (int i = 0; i < n; i++)
		if (mas[i] != v[i])
			check = 0;
	EXPECT_EQ(1, check);
}
