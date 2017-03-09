# malloc-simulator

# Introduction

This program will simulate the C library calls malloc() and free() using a 5000
byte block of memory. Although it is not perfect, it attempts to tackle the major problems outlined below:

  1. free()ing pointers that weren't malloc()'d
  2. free()ing items that aren't pointers
  3. double free()ing
  4. memory block is not free to malloc()
  5. user requests size larger than what's available
  
# Usage

import "mymalloc.h" and call malloc() and free() like you normally would.
