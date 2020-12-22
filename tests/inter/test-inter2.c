// RUN: %clam -O0 --crab-inter --crab-inter-recursive-functions --crab-dom=zones --crab-track=mem --crab-check=assert --crab-sanity-checks "%s" 2>&1 | OutputCheck %s
// CHECK: ^3  Number of total safe checks$

extern int int_nd(void);
extern void __CRAB_assert(int);
extern void __CRAB_assume(int);

int foo(int);
int bar(int);

// Example of mutually recursive functions

int foo(int x) {
  if (x > 0) {
    return 1 + bar(x-1);
  } else {
    return x;
  }
}

int bar(int x) {
  int y = foo(x);
  __CRAB_assert(y == x);  
  return y;
}

int main () {

  int x1 = int_nd();
  int y1 = foo(x1);
  __CRAB_assert(y1 == x1);

  int x2 = 1000;
  int y2 = foo(x2);
  __CRAB_assert(y2 == 1000);
  
  return 0;
}
