#ifndef MATRIX_H
#define MATRIX_H


#include <vector>
#include <iostream>

class Matrix{
 public:
  Matrix();
  Matrix(int height, int width);
  Matrix(std::vector<std::vector<double>> const &array);

  Matrix multiply(double const &value);

  Matrix add(Matrix const &m) const;
  Matrix subtract(Matrix const &m) const;
  Matrix multiply(Matrix const &m) const;
  

  Matrix dot(Matrix const &m) const;
  Matrix transpose() const;
  double sum() const;  

  Matrix applyFunction(double (*function)(double)) const;

  void print(std::ostream &flux) const;

 private:
  std::vector<std::vector<double>> array;
  int height;
  int width;
};

std::ostream& operator<<(std::ostream &flux, Matrix const &m);

#endif
