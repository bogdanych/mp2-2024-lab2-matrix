#include "tmatrix.h"
#include <ctime>
#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
	ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}
TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}
TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
	ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}
TEST(TDynamicMatrix, can_create_copied_matrix)
{
	TDynamicMatrix<int> m(5);
	ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> A(10);
	for (int i = 0; i < 10; i++)
		for (auto j = 0; j < 10; j++) {
			A[i][j] = rand();
		}
	TDynamicMatrix<int> copy = A;
	EXPECT_EQ(A, copy);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	int n = 10;
	TDynamicMatrix<int> A(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			A[i][j] = i * n + j;
	TDynamicMatrix<int> copy = A;
	copy[0][0] += 1;

	EXPECT_NE(A, copy);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(8020);
	EXPECT_NO_THROW(m.size());
	EXPECT_EQ(m.size(), 8020);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(1000);
	int i = rand() % 1000, j = rand() % 1000;
	m[i][j] = 5;
	EXPECT_EQ(5, m[i][j]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index_out)
{
	TDynamicMatrix<int> m(1000);
	ASSERT_ANY_THROW(m.at(-1).at(32));
}
TEST(TDynamicMatrix, throws_when_set_element_with_negative_index_in)
{
	TDynamicMatrix<int> m(1000);
	ASSERT_ANY_THROW(m.at(2).at(-4));
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index_out_eq_sz)
{
	int n = 10;
	TDynamicMatrix<int> m(n);
	ASSERT_ANY_THROW(m.at(n).at(n - 1));
}
TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index_in_eq_sz)
{
	int n = 10;
	TDynamicMatrix<int> m(n);
	ASSERT_ANY_THROW(m.at(n - 1).at(n));
}
TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index_out_gr_sz)
{
	int n = 10;
	TDynamicMatrix<int> m(n);
	ASSERT_ANY_THROW(m.at(n + 1).at(n - 1));
}
TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index_in_gr_sz)
{
	int n = 10;
	TDynamicMatrix<int> m(n);
	ASSERT_ANY_THROW(m.at(n - 1).at(n + 1));
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(10);
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++) {
			m[i][j] = rand();
		}
	ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	int n = 10;
	TDynamicMatrix<int> A(n);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			A[i][j] = rand();
		}
	TDynamicMatrix<int> copy(n);
	ASSERT_NO_THROW(copy = A);
	EXPECT_EQ(copy, A);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	int n1 = 10, n2 = 20;
	TDynamicMatrix<int> A(n1);
	TDynamicMatrix<int> B(n2);
	for (int i = 0; i < n2; i++)
		for (int j = 0; j < n2; j++) {
			A[i % n1][j % n1] = i + j * n1;
			B[i][j] = i + j * n2;
		}
	ASSERT_NO_THROW(A = B);
	EXPECT_EQ(A.size(), B.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	int n1 = 10;
	int n2 = 20;
	TDynamicMatrix<int> a(n1);
	TDynamicMatrix<int> b(n2);
	for (int i = 0; i < n2; i++)
		for (int j = 0; j < n2; j++) {
			a[i % n1][j % n1] = i + j * n1;
			b[i][j] = i + j * n2;
		}
	ASSERT_NO_THROW(a = b);
	EXPECT_EQ(a, b);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> a(10), b(10);
	for (auto i = 0; i < 10; i++)
		for (auto j = 0; j < 10; j++) {
			a[i][j] = i + j * 10;;
		}
	b = a;
	ASSERT_NO_THROW(a == b);
	EXPECT_EQ(a == b, 1);
}
TEST(TDynamicMatrix, compare_not_equal_matrices_return_false)
{
	TDynamicMatrix<int> a(1);
	TDynamicMatrix<int> b(1);
	a[0][0] = 0;
	b[0][0] = 1;
	ASSERT_NO_THROW(a == b);
	EXPECT_EQ(a == b, false);
}
TEST(TDynamicMatrix, compare_not_equal_matrices_return_true)
{
	TDynamicMatrix<int> a(1);
	TDynamicMatrix<int> b(1);
	a[0][0] = 0;
	b[0][0] = 1;
	ASSERT_NO_THROW(a != b);
	EXPECT_EQ(a != b, 1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m(10);
	for (auto i = 0; i < 10; i++)
		for (auto j = 0; j < 10; j++) {
			m[i][j] = i * 10 + j;
		}

	ASSERT_NO_THROW(m == m);
	EXPECT_EQ(m == m, 1);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> a(1);
	TDynamicMatrix<int> b(5);
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			b[i][j] = 0;
	a[0][0] = 0;
	ASSERT_NO_THROW(a != b);
	EXPECT_EQ(a != b, 1);
	EXPECT_NE(a == b, 1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> a(10);
	TDynamicMatrix<int> b(10);
	TDynamicMatrix<int> c(10);
	for (auto i = 0; i < 10; i++)
		for (auto j = 0; j < 10; j++) {
			a[i][j] = i + j * 10;
			b[i][j] = i + j * 10;
			c[i][j] = 2 * (i + j * 10);
		}

	ASSERT_NO_THROW(a + b);

	EXPECT_EQ(a + b, c);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> a(10);
	TDynamicMatrix<int> b(11);
	ASSERT_ANY_THROW(a + b);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> a(10);
	TDynamicMatrix<int> b(10);
	TDynamicMatrix<int> res(10);
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++) {
			a[i][j] = i + j * 10;
			b[i][j] = i + j * 10;
			res[i][j] = 0;
		}

	ASSERT_NO_THROW(a - b);
	EXPECT_EQ(a - b, res);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> a(10);
	TDynamicMatrix<int> b(11);
	ASSERT_ANY_THROW(a - b);
}
