/**
 * @file Matrix.inc
 * @brief Implementation of the Matrix class template.
 *
 * This file contains the implementation of the Matrix class template, which represents a mathematical matrix.
 * The Matrix class provides various operations and functionalities for manipulating matrices, such as addition, subtraction, multiplication, and solving linear equations.
 * The template parameters M and N represent the number of rows and columns of the matrix, respectively.
 * The Matrix class is implemented using a std::array of std::array, providing a fixed-size matrix with compile-time dimensions.
 *
 * @date 13-03-2024
 * @author S Selten
 * @version 1.0
 */


#include <cassert>
#include <stdexcept>
#include <numeric>
#include <cmath>
#include <utility>
#include <iomanip>

/**
 * Constructor for the Matrix class.
 * 
 * @param value The value to initialize all elements of the matrix with.
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, M, N >::Matrix( T value)
{
	for (std::size_t row = 0; row < M; ++row)
	{
		for (std::size_t column = 0; column < N; ++column)
		{
			matrix.at( row).at( column) = value;
		}
	}
}

/**
 * @brief Constructs a Matrix object using an initializer list.
 * 
 * @tparam T The type of elements in the Matrix.
 * @tparam M The number of rows in the Matrix.
 * @tparam N The number of columns in the Matrix.
 * @param aList The initializer list containing the elements of the Matrix.
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, M, N >::Matrix( const std::initializer_list< T >& aList)
{
	// Check the arguments
	assert( aList.size() == M * N);

	auto row_iter = aList.begin();
	for (std::size_t row = 0; row < M; ++row)
	{
		for (std::size_t column = 0; column < N; ++column, ++row_iter)
		{
			matrix.at( row).at( column) = *row_iter;
		}
	}
}

/**
 * @brief Constructs a Matrix object using an initializer list.
 * 
 * This constructor takes an initializer list of initializer lists and creates a Matrix object.
 * The outer initializer list represents the rows of the matrix, and the inner initializer lists
 * represent the elements of each row.
 * 
 * @param aList The initializer list of initializer lists.
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, M, N >::Matrix( const std::initializer_list< std::initializer_list< T > >& aList)
{
	// Check the arguments, the static assert assures that there is at least 1 M and 1 N!
	assert( aList.size() == M && (*aList.begin()).size() == N);

	auto row_iter = aList.begin();
	for (std::size_t row = 0; row < aList.size(); ++row, ++row_iter)
	{
		auto column_iter = (*row_iter).begin();
		for (std::size_t column = 0; column < (*row_iter).size(); ++column, ++column_iter)
		{
			matrix.at( row).at( column) = *column_iter;
		}
	}
}

/**
 * @brief Copy constructor for the Matrix class.
 * 
 * @tparam T The type of elements in the matrix.
 * @tparam M The number of rows in the matrix.
 * @tparam N The number of columns in the matrix.
 * @param aMatrix The matrix to be copied.
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, M, N >::Matrix( const Matrix< T, M, N >& aMatrix) :
				matrix( aMatrix.matrix)
{
}

/**
 * Returns a reference to the element at the specified row index.
 *
 * @param aRowIndex The index of the row.
 * @return A reference to the element at the specified row index.
 */
template< class T, std::size_t M, std::size_t N >
std::array< T, N >& Matrix< T, M, N >::at( std::size_t aRowIndex)
{
	return matrix.at( aRowIndex);
}

/**
 * Returns a reference to the element at the specified row index in the matrix.
 *
 * @param aRowIndex The index of the row.
 * @return A const reference to the element at the specified row index.
 */
template< class T, std::size_t M, std::size_t N >
const std::array< T, N >& Matrix< T, M, N >::at( std::size_t aRowIndex) const
{
	return matrix.at( aRowIndex);
}

/**
 * Returns a reference to the element at the specified row and column index.
 *
 * @param aRowIndex The index of the row.
 * @param aColumnIndex The index of the column.
 * @return A reference to the element at the specified row and column index.
 */
template< class T, std::size_t M, std::size_t N >
T& Matrix< T, M, N >::at( 	std::size_t aRowIndex,
							std::size_t aColumnIndex)
{
	return matrix.at( aRowIndex).at( aColumnIndex);
}

/**
 * Returns a reference to the element at the specified row and column index.
 *
 * @param aRowIndex The index of the row.
 * @param aColumnIndex The index of the column.
 * @return A reference to the element at the specified row and column index.
 */
template< class T, std::size_t M, std::size_t N >
const T& Matrix< T, M, N >::at( std::size_t aRowIndex,
								std::size_t aColumnIndex) const
{
	return matrix.at( aRowIndex).at( aColumnIndex);
}

/**
 * Accesses the specified row of the matrix using the subscript operator.
 *
 * @param aRowIndex The index of the row to access.
 * @return A reference to the specified row.
 */
template< class T, std::size_t M, std::size_t N >
std::array< T, N >& Matrix< T, M, N >::operator[]( std::size_t aRowIndex)
{
	return matrix[aRowIndex];
}

/**
 * Returns a reference to the row at the specified index in the matrix.
 *
 * @param aRowIndex The index of the row.
 * @return A reference to the row at the specified index.
 */
template< class T, std::size_t M, std::size_t N >
const std::array< T, N >& Matrix< T, M, N >::operator[]( std::size_t aRowIndex) const
{
	return matrix[aRowIndex];
}

/**
 * Assignment operator overload for Matrix class.
 * Assigns the values of the right-hand side matrix to the left-hand side matrix.
 *
 * @param rhs The matrix to be assigned.
 * @return A reference to the left-hand side matrix after assignment.
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, M, N >& Matrix< T, M, N >::operator=( const Matrix< T, M, N >& rhs)
{
	if (this != &rhs)
	{
		matrix = rhs.matrix;
	}
	return *this;
}

/**
 * @brief Overloaded equality operator for comparing two matrices.
 *
 * This operator compares the current matrix with another matrix and returns true if they are equal, and false otherwise.
 *
 * @param rhs The matrix to compare with.
 * @return True if the matrices are equal, false otherwise.
 */
template< class T, std::size_t M, std::size_t N >
bool Matrix< T, M, N >::operator==( const Matrix< T, M, N >& rhs) const
{
	return matrix == rhs.matrix;
}

/**
 * Multiplies the matrix by a scalar value and assigns the result to the matrix.
 *
 * @tparam T The type of the matrix elements.
 * @tparam M The number of rows in the matrix.
 * @tparam N The number of columns in the matrix.
 * @tparam T2 The type of the scalar value.
 * @param scalar The scalar value to multiply the matrix by.
 * @return A reference to the modified matrix.
 */
template< class T, std::size_t M, std::size_t N >
template< class T2 >
Matrix< T, M, N >& Matrix< T, M, N >::operator*=( const T2& scalar)
{
	static_assert( std::is_arithmetic<T2>::value, "Value T2 must be arithmetic, see http://en.cppreference.com/w/cpp/types/is_arithmetic");

	for (std::size_t row = 0; row < M; ++row)
	{
		for (std::size_t column = 0; column < N; ++column)
		{
			matrix.at( row).at( column) *= scalar;
		}
	}
	return *this;
}

/**
 * Multiplies the matrix by a scalar value.
 *
 * @param scalar The scalar value to multiply the matrix by.
 * @return The resulting matrix after multiplication.
 */
template< class T, std::size_t M, std::size_t N >
template< class T2 >
Matrix< T, M, N > Matrix< T, M, N >::operator*( const T2& scalar) const
{
	static_assert( std::is_arithmetic<T2>::value, "Value T2 must be arithmetic, see http://en.cppreference.com/w/cpp/types/is_arithmetic");

	Matrix< T, M, N > result( *this);
	return result *= scalar;
}


/**
 * Divides each element of the matrix by a scalar value.
 * 
 * @tparam T The type of the matrix elements.
 * @tparam M The number of rows in the matrix.
 * @tparam N The number of columns in the matrix.
 * @tparam T2 The type of the scalar value.
 * 
 * @param aScalar The scalar value to divide the matrix elements by.
 * 
 * @return A reference to the modified matrix.
 */
template< class T, std::size_t M, std::size_t N >
template< class T2 >
Matrix< T, M, N >& Matrix< T, M, N >::operator/=( const T2& aScalar)
{
	static_assert( std::is_arithmetic<T2>::value, "Value T2 must be arithmetic, see http://en.cppreference.com/w/cpp/types/is_arithmetic");

	for (std::size_t row = 0; row < M; ++row)
	{
		for (std::size_t column = 0; column < N; ++column)
		{
			matrix.at( row).at( column) /= aScalar;
		}
	}
	return *this;
}

/**
 * Overloaded division operator for Matrix class.
 * Divides each element of the matrix by a scalar value.
 *
 * @tparam T The type of the matrix elements.
 * @tparam M The number of rows in the matrix.
 * @tparam N The number of columns in the matrix.
 * @tparam T2 The type of the scalar value.
 * @param aScalar The scalar value to divide the matrix elements by.
 * @return A new matrix with each element divided by the scalar value.
 */
template< class T, std::size_t M, std::size_t N >
template< class T2 >
Matrix< T, M, N > Matrix< T, M, N >::operator/( const T2& aScalar) const
{
	static_assert( std::is_arithmetic<T2>::value, "Value T2 must be arithmetic, see http://en.cppreference.com/w/cpp/types/is_arithmetic");

	Matrix< T, M, N > result( *this);
	return result /= aScalar;
}

/**
 * @brief Overloaded addition assignment operator for Matrix class.
 * 
 * This operator adds the elements of the right-hand side matrix to the elements of the left-hand side matrix.
 * The result is stored in the left-hand side matrix itself.
 * 
 * @tparam T The type of elements in the matrix.
 * @tparam M The number of rows in the matrix.
 * @tparam N The number of columns in the matrix.
 * @param rhs The right-hand side matrix to be added.
 * @return A reference to the modified left-hand side matrix.
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, M, N >& Matrix< T, M, N >::operator+=( const Matrix< T, M, N >& rhs)
{
	for (std::size_t row = 0; row < M; ++row)
	{
		for (std::size_t column = 0; column < N; ++column)
		{
			matrix[row][column] += rhs.at( row, column);
		}
	}
	return *this;
}

/**
 * @brief Overloaded addition operator for Matrix class.
 * 
 * This operator adds two matrices of the same size element-wise and returns the result.
 * 
 * @tparam T The type of elements in the matrix.
 * @tparam M The number of rows in the matrix.
 * @tparam N The number of columns in the matrix.
 * @param rhs The matrix to be added.
 * @return The resulting matrix after addition.
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, M, N > Matrix< T, M, N >::operator+( const Matrix< T, M, N >& rhs) const
{
	Matrix< T, M, N > result( *this);
	return result += rhs;
}

/**
 * Subtracts the elements of the given matrix from the current matrix.
 *
 * @param rhs The matrix to subtract.
 * @return A reference to the current matrix after subtraction.
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, M, N >& Matrix< T, M, N >::operator-=( const Matrix< T, M, N >& rhs)
{
	for (std::size_t row = 0; row < M; ++row)
	{
		for (std::size_t column = 0; column < N; ++column)
		{
			matrix[row][column] -= rhs.at( row, column);
		}
	}
	return *this;
}

/**
 * Subtracts the given matrix from the current matrix.
 *
 * @param rhs The matrix to subtract.
 * @return The resulting matrix after subtraction.
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, M, N > Matrix< T, M, N >::operator-( const Matrix< T, M, N >& rhs) const
{
	Matrix< T, M, N > result( *this);
	return result -= rhs;
}

/**
 * Multiplies the current matrix with the given matrix.
 *
 * @tparam T The type of the matrix elements.
 * @tparam M The number of rows in the current matrix.
 * @tparam N The number of columns in the current matrix and the number of rows in the given matrix.
 * @tparam columns The number of columns in the given matrix.
 * @param rhs The matrix to multiply with.
 * @return The resulting matrix after multiplication.
 */
template< typename T, std::size_t M, std::size_t N >
template< std::size_t columns >
Matrix< T, M, columns > Matrix< T, M, N >::operator*( const Matrix< T, N, columns >& rhs) const
{
    Matrix<T, M, columns> result;

    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 0; j < columns; ++j) {
            for (std::size_t k = 0; k < N; ++k) {
                result[i][j] += matrix[i][k] * rhs[k][j];
            }
        }
    }

    return result;
}

/**
 * Transposes the matrix.
 *
 * @return The transposed matrix.
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, N, M > Matrix< T, M, N >::transpose() const
{
Matrix<T, N, M> result;

    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            result[j][i] = matrix[i][j];
        }
    }

    return result;
}

/**
 * Returns the identity matrix of the same size as the current matrix.
 *
 * @return The identity matrix.
 */
template<class T, std::size_t M, std::size_t N>
Matrix<T, M, N> Matrix<T, M, N>::identity() const {
    static_assert(M == N, "Identity matrix is only defined for square matrices.");

    Matrix<T, M, N> result;

    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            result[i][j] = (i == j) ? static_cast<T>(1) : static_cast<T>(0);
        }
    }

    return result;
}

/**
 * Performs Gaussian elimination on the matrix.
 *
 * @return The matrix after Gaussian elimination.
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, M, N > Matrix< T, M, N >::gauss() const
{
   Matrix<T, M, N> result(*this); // Copy constructor to initialize result with current matrix

    // Gaussian elimination algorithm implementation
    for (std::size_t i = 0; i < M; ++i) {
        // Find pivot element
        std::size_t pivotRow = i;
        for (std::size_t k = i + 1; k < M; ++k) {
            if (std::abs(result[k][i]) > std::abs(result[pivotRow][i]))
                pivotRow = k;
        }

        // Swap current row with pivot row
        if (pivotRow != i) {
            std::swap(result.matrix[i], result.matrix[pivotRow]);
        }

        // Make the diagonal element 1
        T pivot = result[i][i];
        if (pivot != 0) {
            for (std::size_t j = i; j < N; ++j) {
                result[i][j] /= pivot;
            }
        }

        // Make elements below the diagonal zero
        for (std::size_t k = i + 1; k < M; ++k) {
            T factor = result[k][i];
            for (std::size_t j = i; j < N; ++j) {
                result[k][j] -= factor * result[i][j];
            }
        }
    }

    return result;
}

/**
 * Performs the Gauss-Jordan elimination on the matrix.
 * 
 * @tparam T The type of the matrix elements.
 * @tparam M The number of rows in the matrix.
 * @tparam N The number of columns in the matrix.
 * 
 * @return The matrix after Gauss-Jordan elimination.
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, M, N > Matrix< T, M, N >::gaussJordan() const
{
Matrix<T, M, N> result(*this); // Copy constructor to initialize result with current matrix

    // Gauss-Jordan elimination algorithm implementation
    for (std::size_t i = 0; i < M; ++i) {
        // Find pivot element
        std::size_t pivotRow = i;
        for (std::size_t k = i + 1; k < M; ++k) {
            if (std::abs(result[k][i]) > std::abs(result[pivotRow][i]))
                pivotRow = k;
        }

        // Swap current row with pivot row
        if (pivotRow != i) {
            for (std::size_t j = 0; j < N; ++j) {
                std::swap(result[i][j], result[pivotRow][j]);
            }
        }

        // Make pivot element 1
        T pivot = result[i][i];
        if (pivot != 0) {
            for (std::size_t j = 0; j < N; ++j) {
                result[i][j] /= pivot;
            }
        }

        // Make elements above and below the pivot zero
        for (std::size_t k = 0; k < M; ++k) {
            if (k != i) {
                T factor = result[k][i];
                for (std::size_t j = 0; j < N; ++j) {
                    result[k][j] -= factor * result[i][j];
                }
            }
        }
    }

    return result;
}

/**
 * Solves the matrix equation represented by this Matrix object.
 *
 * @return The solution of the matrix equation.
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, M, 1 > Matrix< T, M, N >::solve() const
{

    if (N != M + 1) {
        throw std::invalid_argument("Matrix dimensions are not compatible with solving a system of linear equations.");
    }

    Matrix<T, M, 1> result;

    // Perform Gaussian elimination with back substitution
    Matrix<T, M, N> augmentedMatrix(*this);
    augmentedMatrix = augmentedMatrix.gauss();

    // Adjusted tolerance level to account for rounding errors
    constexpr T tolerance = std::numeric_limits<T>::epsilon() * 100;

    if constexpr (M > 0) { // Check if M is not zero to prevent underflow in the loop below
        for (std::size_t i = M; i-- > 0; ) {
            T sum = 0;
            for (std::size_t j = i + 1; j < M; ++j) {
                sum += augmentedMatrix[i][j] * result[j][0];
            }
            result[i][0] = std::abs(augmentedMatrix[i][i]) > tolerance ? (augmentedMatrix[i][M] - sum) / augmentedMatrix[i][i] : T(0);
        }
    }

    return result;    }

/**
 * Calculates the inverse of the matrix.
 *
 * @return The inverse of the matrix.
 */
template< class T, std::size_t M, std::size_t N >
Matrix< T, M, N > Matrix< T, M, N >::inverse() const
{
    static_assert(M == N, "Inverse can only be calculated for square matrices.");

        // Create an augmented matrix [A|I], where A is *this and I is the identity matrix
        Matrix<T, M, 2*N> augmented;

        // Initialize augmented matrix with this matrix and identity matrix
        for (std::size_t i = 0; i < M; ++i) {
            for (std::size_t j = 0; j < N; ++j) {
                augmented[i][j] = (*this)[i][j]; // Copy the original matrix
                augmented[i][j+N] = (i == j) ? 1 : 0; // Append the identity matrix
            }
        }

        // Apply Gauss-Jordan elimination on augmented to get [I|A^-1]
        for (std::size_t col = 0; col < N; ++col) {
            // Find the pivot row
            std::size_t pivot = col;
            for (std::size_t row = col + 1; row < M; ++row) {
                if (std::abs(augmented[row][col]) > std::abs(augmented[pivot][col])) {
                    pivot = row;
                }
            }

            if (augmented[pivot][col] == 0) {
                throw std::runtime_error("Matrix is singular and cannot be inverted.");
            }

            // Swap the current row with the pivot row
            if (pivot != col) {
                for (std::size_t j = 0; j < 2*N; ++j) {
                    std::swap(augmented[col][j], augmented[pivot][j]);
                }
            }

            // Normalize the pivot row
            T pivotVal = augmented[col][col];
            for (std::size_t j = 0; j < 2*N; ++j) {
                augmented[col][j] /= pivotVal;
            }

            // Eliminate the current column in all other rows
            for (std::size_t row = 0; row < M; ++row) {
                if (row != col) {
                    T factor = augmented[row][col];
                    for (std::size_t j = 0; j < 2*N; ++j) {
                        augmented[row][j] -= augmented[col][j] * factor;
                    }
                }
            }
        }

        // Extract the inverse matrix from the augmented matrix
        Matrix<T, M, N> inverse;
        for (std::size_t i = 0; i < M; ++i) {
            for (std::size_t j = 0; j < N; ++j) {
                inverse[i][j] = augmented[i][j+N];
            }
        }

        return inverse;
}

/**
 * Converts the Matrix object to a string representation.
 *
 * @return The string representation of the Matrix object.
 */
template< class T, std::size_t M, std::size_t N >
std::string Matrix< T, M, N >::to_string() const
{
	std::string result = "Matrix<" + std::to_string( N) + "," + std::to_string( M) + ">\n{\n";
	for (std::size_t i = 0; i < M; ++i)
	{
		for (std::size_t j = 0; j < N; ++j)
		{
			result += std::to_string( matrix[i][j]) + ",";
		}
		result += "\n";
	}
	result += "}";
	return result;
}

/**
 * Compares two matrices for equality.
 *
 * @param lhs The first matrix to compare.
 * @param rhs The second matrix to compare.
 * @return True if the matrices are equal, false otherwise.
 */
template< typename T, const std::size_t N >
bool equals(	const Matrix< T, 1, N >& lhs,
				const Matrix< T, 1, N >& rhs,
				const T aPrecision /*= std::numeric_limits<T>::epsilon()*/,
				const unsigned long aFactor /*= 1*/)
{
// Implementation of the equals function

    for (std::size_t i = 0; i < N; ++i) {
        // Apply the specified factor to the precision
        T precision = aPrecision * aFactor;

        // Check if the absolute difference between corresponding elements is within the precision
        if (std::abs(lhs[0][i] - rhs[0][i]) > precision) {
            return false;
        }
    }

    return true;
}

/**
 * Compares two matrices for equality.
 *
 * @param lhs The first matrix to compare.
 * @param rhs The second matrix to compare.
 * @return True if the matrices are equal, false otherwise.
 */
template< typename T, const std::size_t M >
bool equals(	const Matrix< T, M, 1 >& lhs,
				const Matrix< T, M, 1 >& rhs,
				const T aPrecision /*= std::numeric_limits<T>::epsilon()*/,
				const unsigned long aFactor /*= 1*/)
{
// Implementation of the equals function

    for (std::size_t i = 0; i < M; ++i) {
        // Apply the specified factor to the precision
        T precision = aPrecision * aFactor;

        // Check if the absolute difference between corresponding elements is within the precision
        if (std::abs(lhs[i][0] - rhs[i][0]) > precision) {
            return false;
        }
    }

    return true;
}

/**
 * Compares two matrices for equality.
 *
 * @param lhs The first matrix to compare.
 * @param rhs The second matrix to compare.
 * @return True if the matrices are equal, false otherwise.
 */
template< typename T, const std::size_t M, const std::size_t N >
bool equals(	const Matrix< T, M, N >& lhs,
				const Matrix< T, M, N >& rhs,
				const T aPrecision /*= std::numeric_limits<T>::epsilon()*/,
				const unsigned long aFactor /*= 1*/)
{
// Implementation of the equals function

    for (std::size_t i = 0; i < M; ++i) {
        for (std::size_t j = 0; j < N; ++j) {
            // Apply the specified factor to the precision
            T precision = aPrecision * aFactor;

            // Check if the absolute difference between corresponding elements is within the precision
            if (std::abs(lhs[i][j] - rhs[i][j]) > precision) {
                return false;
            }
        }
    }

    return true;
}
