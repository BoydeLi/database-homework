//===----------------------------------------------------------------------===//
//
//
//
// p0_starter.h
//
// Identification: src/include/primer/p0_starter.h
//
//
//
//===----------------------------------------------------------------------===//

#pragma once

#include <memory>
#include <stdexcept>
#include <vector>



namespace scudb {

/**
 * The Matrix type defines a common
 * interface for matrix operations.
 */
template <typename T>
class Matrix {
 protected:
  /**
   * TODO(P0): Add implementation
   * 
   * Construct a new Matrix instance.
   * @param rows The number of rows
   * @param cols The number of columns
   *
   */
  Matrix(int rows, int cols)
  { 
      linear_ = new T[rows*cols];
      rows_= rows;
      cols_= cols;
      memset(linear_, 0, sizeof(T) * rows * cols);
  }

  /** The number of rows in the matrix */
  int rows_;
  /** The number of columns in the matrix */
  int cols_;

  /**
   * TODO(P0): Allocate the array in the constructor.
   * TODO(P0): Deallocate the array in the destructor.
   * A flattened array containing the elements of the matrix.
   */
  T *linear_;

 public:
  /** @return The number of rows in the matrix */
  virtual int GetRowCount() const = 0;

  /** @return The number of columns in the matrix */
  virtual int GetColumnCount() const = 0;

  /**
   * Get the (i,j)th matrix element.
   *
   * Throw OUT_OF_RANGE if either index is out of range.
   *
   * @param i The row index
   * @param j The column index
   * @return The (i,j)th matrix element
   * @throws OUT_OF_RANGE if either index is out of range
   */
  virtual T GetElement(int i, int j) const = 0;

  /**
   * Set the (i,j)th matrix element.
   *
   * Throw OUT_OF_RANGE if either index is out of range.
   *
   * @param i The row index
   * @param j The column index
   * @param val The value to insert
   * @throws OUT_OF_RANGE if either index is out of range
   */
  virtual void SetElement(int i, int j, T val) = 0;

  /**
   * Fill the elements of the matrix from `source`.
   *
   * Throw OUT_OF_RANGE in the event that `source`
   * does not contain the required number of elements.
   *
   * @param source The source container
   * @throws OUT_OF_RANGE if `source` is incorrect size
   */
  virtual void FillFrom(const std::vector<T> &source) = 0;

  /**
   * Destroy a matrix instance.
   * TODO(P0): Add implementation
   */
  virtual ~Matrix()
  {
      delete []linear_;
  }
};



/**
 * The RowMatrix type is a concrete matrix implementation.
 * It implements the interface defined by the Matrix type.
 */
template <typename T>
class RowMatrix : public Matrix<T> {
 public:
  /**
   * TODO(P0): Add implementation
   *
   * Construct a new RowMatrix instance.
   * @param rows The number of rows
   * @param cols The number of columns
   */
  RowMatrix(int rows, int cols) : Matrix<T>(rows, cols) 
  {
      data_ = new T * [rows];
      for (int i = 0; i < this->rows_; i++)
      {
          data_[i] =&this->linear_[i*this->cols_];
      }
  }

  /**
   * TODO(P0): Add implementation
   * @return The number of rows in the matrix
   */
  int GetRowCount() const override { 
      return this->rows_; 
  }

  /**
   * TODO(P0): Add implementation
   * @return The number of columns in the matrix
   */
  int GetColumnCount() const override {
      return this->cols_; 
  }

  /**
   * TODO(P0): Add implementation
   *
   * Get the (i,j)th matrix element.
   *
   * Throw OUT_OF_RANGE if either index is out of range.
   *
   * @param i The row index
   * @param j The column index
   * @return The (i,j)th matrix element
   * @throws OUT_OF_RANGE if either index is out of range
   */
  T GetElement(int i, int j) const override {
      if (i > this->rows_ || j > this->cols_)
          throw NotImplementedException{ "RowMatrix::GetElement() not implemented." };
      return this->data_[i][j];
  }

  /**
   * Set the (i,j)th matrix element.
   *
   * Throw OUT_OF_RANGE if either index is out of range.
   *
   * @param i The row index
   * @param j The column index
   * @param val The value to insert
   * @throws OUT_OF_RANGE if either index is out of range
   */
  void SetElement(int i, int j, T val) override 
  {
      if (i > this->rows_|| j>this->cols_)
      throw NotImplementedException{ "RowMatrix::GetElement() not implemented." };
      data_[i][j] = val;
  }

  /**
   * TODO(P0): Add implementation
   *
   * Fill the elements of the matrix from `source`.
   *
   * Throw OUT_OF_RANGE in the event that `source`
   * does not contain the required number of elements.
   *
   * @param source The source container
   * @throws OUT_OF_RANGE if `source` is incorrect size
   */
  void FillFrom(const std::vector<T> &source) override 
  {
      if(source.size() < this->rows_*this->cols_)
    throw NotImplementedException{"RowMatrix::FillFrom() not implemented."};
      else
      {
          auto x = source.begin();
          for (int i = 0; i < this->rows_; i++)
          {
              for (int j = 0 ; j < this->cols_; j++)
              {
                  if (x < source.end())
                      data_[i][j] = *x;
                  x++;
              }
          }
     }
  }

  /**
   * TODO(P0): Add implementation
   *
   * Destroy a RowMatrix instance.
   */
  ~RowMatrix() override
  {
     
      delete[] data_;
  }

 private:
  /**
   * A 2D array containing the elements of the matrix in row-major format.
   *
   * TODO(P0):
   * - Allocate the array of row pointers in the constructor.
   * - Use these pointers to point to corresponding elements of the `linear` array.
   * - Don't forget to deallocate the array in the destructor.
   */
  T **data_;
};

/**
 * The RowMatrixOperations class defines operations
 * that may be performed on instances of `RowMatrix`.
 */
template <typename T>
class RowMatrixOperations {
 public:
  /**
   * Compute (`matrixA` + `matrixB`) and return the result.
   * Return `nullptr` if dimensions mismatch for input matrices.
   * @param matrixA Input matrix
   * @param matrixB Input matrix
   * @return The result of matrix addition
   */
  static std::unique_ptr<RowMatrix<T>> Add(const RowMatrix<T> *matrixA, const RowMatrix<T> *matrixB) {
    // TODO(P0): Add implementation
      if(matrixA->GetRowCount() != matrixB->GetRowCount() || matrixA->GetColumnCount() != matrixB->GetColumnCount())
    return std::unique_ptr<RowMatrix<T>>(nullptr);
      else
      {
 
          std::unique_ptr<RowMatrix<T>> AddResult(new RowMatrix<T>(matrixA->GetRowCount(),matrixA->GetColumnCount()));
          for (int i = 0; i < matrixA->GetRowCount(); i++)
          {
              for (int j = 0; j < matrixA->GetColumnCount(); j++)
              {
                  AddResult->SetElement(i, j, matrixA->GetElement(i, j) + matrixB->GetElement(i, j));
              }
          }
          return  AddResult;
      }
  }

  /**
   * Compute the matrix multiplication (`matrixA` * `matrixB` and return the result.
   * Return `nullptr` if dimensions mismatch for input matrices.
   * @param matrixA Input matrix
   * @param matrixB Input matrix
   * @return The result of matrix multiplication
   */
  static std::unique_ptr<RowMatrix<T>> Multiply(const RowMatrix<T> *matrixA, const RowMatrix<T> *matrixB) {
    // TODO(P0): Add implementation
      if(matrixA->GetColumnCount() != matrixB->GetRowCount())
    return std::unique_ptr<RowMatrix<T>>(nullptr);
      else
      {
          std::unique_ptr<RowMatrix<T>> MultiResult(new RowMatrix<T>(matrixA->GetRowCount(), matrixB->GetColumnCount()));
          for (int i = 0; i < matrixA->GetRowCount(); i++)
          {
              for (int j =0 ; j < matrixB->GetColumnCount(); j++)
              {
                  T multi = 0;
                  for (int x = 0; x < matrixA->GetColumnCount(); x++)
                  {
                      multi = multi + matrixA->GetElement(i, x) * matrixB->GetElement(x, j);
                  }
                  MultiResult->SetElement(i, j, multi);
              }
          }
          return MultiResult;
      }
  }

  /**
   * Simplified General Matrix Multiply operation. Compute (`matrixA` * `matrixB` + `matrixC`).
   * Return `nullptr` if dimensions mismatch for input matrices.
   * @param matrixA Input matrix
   * @param matrixB Input matrix
   * @param matrixC Input matrix
   * @return The result of general matrix multiply
   */
  static std::unique_ptr<RowMatrix<T>> GEMM(const RowMatrix<T> *matrixA, const RowMatrix<T> *matrixB,
                                            const RowMatrix<T> *matrixC) {
    // TODO(P0): Add implementation
      if (matrixA->GetColumnCount() != matrixB->GetRowCount()||matrixA->GetRowCount() != matrixC->GetRowCount() || matrixB->GetColumnCount() != matrixC->GetColumnCount() )
    return std::unique_ptr<RowMatrix<T>>(nullptr);
      else
      {
          std::unique_ptr<RowMatrix<T>> g_multi = Multiply(matrixA, matrixB);
          RowMatrix<T> G_multi(matrixA->GetRowCount(), matrixB->GetColumnCount());
          for (int i = 0; i < matrixA->GetRowCount(); i++)
          {
              for (int j = 0; j < matrixB->GetColumnCount(); j++)
              {
                  G_multi.SetElement(i, j, g_multi->GetElement(i, j));
              }
          }
          return Add(&G_multi, matrixC);
      }
  }
};
}  // namespace scudb
