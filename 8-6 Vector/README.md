# 8-6 Vector (20 分)

**Requirements**

Given the declaration of a class template `Vector` below, write the bodies of the functions, and a main() to test all the facilities `Vector` provides.

```c++
template <class T>
class Vector {
public:
  Vector();                      // creates an empty vector
  Vector(int size);              // creates a vector for holding 'size' elements
  Vector(const Vector& r);       // the copy ctor
  ~Vector();                     // destructs the vector 
  T& operator[](int index);      // accesses the specified element without bounds checking
  T& at(int index);              // accesses the specified element, throws an exception of type 'std::out_of_range' when index <0 or >=m_nSize
  int size() const;         // return the size of the container
  void push_back(const T& x);    // adds an element to the end 
  void clear();                  // clears the contents
  bool empty() const;            // checks whether the container is empty 
private:
  void inflate();                // expand the storage of the container to a new capacity, e.g. 2*m_nCapacity
  T *m_pElements;                // pointer to the dynamically allocated storage
  int m_nSize;                   // the number of elements in the container
  int m_nCapacity;               // the number of elements that can be held in currently allocated storage
};
```

**Evaluation standard**

1. c++ code quality (clean, compact and reasonable)
2. comments quality
3. test coverage

**Files to submit**

Please prepare a .zip package including the following items：

1. the source code (including the Vector class, and various test cases for its usage)
2. makefile (for Mac or Linux users) or .exes (for Windows users) or CMakeLists.txt