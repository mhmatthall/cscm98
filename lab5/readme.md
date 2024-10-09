# OS & Architectures: Lab 5

> Last updated on 9th November 2023

## Overview

In this lab, you'll learn about how single instruction multiple data (SIMD) instructions can be used to speed up programs by performing the same operation on multiple pieces of data at once.

## Setup

### A brief history of processor architectures

First released in 1978, the [x86 architecture](https://en.wikipedia.org/wiki/X86) is the processor instruction set found at the core of most modern computers from the past few decades. It started as a 16-bit instruction set, but later supported 32-bit and then 64-bit instructions. Most new computers have either an Intel or AMD processor that will use the 64-bit version of the x86 instruction set (x86-64).

However, in recent years, the [ARM architecture](https://en.wikipedia.org/wiki/ARM_architecture_family) has exploded in popularity. iPhones, Android phones, Raspberry Pis, and lots of other small devices all use ARM-based processors due to them being significantly cheaper to produce and much more power efficient than traditional x86 processors. ARM processors for a long time were regarded as 'not powerful enough' to be used in laptop and desktop computers, but this changed when Apple released their [M1 chip](https://en.wikipedia.org/wiki/Apple_M1) for the MacBook Pro and iMac in 2020. The M1 demonstrated that ARM could be used in professional computers, with the new ARM-based Macs having much greater processor performance and battery life than the old Intel x86-based Macs.

### Why do we care about architecture?

Different processor architectures have different instruction sets. That means that programs compiled for one architecture **cannot** be executed on another architecture. This is why the new Macs can't run old software made for the old Macs, and why sometimes a website will ask you what type of installer you want for a piece of software. For example:

![Example of having to choose an architecture when downloading a file (from the Alpine Linux download site)](./img/image-1.png)

This example uses some short codes to represent different architectures:

- `aarch64` is for **64-bit** ARM-based processors
- `armv7` is for **32-bit** ARM-based processors
- `x86` is for **32-bit** x86-based processors
- `x86_64` is for **64-bit** x86-based processors
- The other two are for more obscure architectures

Because of the different instruction sets used by the different architectures, we need to make sure that the code we write is compatible with the architecture we want to use.

### Programming for different architectures

The code that we write in most languages is not dependent on any particular architecture. That's the beauty of high-level programming languages - we abstract ourselves away from dealing with the machine code or processor assembly code by using easy to read and write languages like Python, C/C++, or Java. As long as we build or compile the code for or on the machine we want to run it on, we're all good to go.

Sometimes, when performance or absolute control is required, we can dig deeper with our code and interface directly with the processor. However, when we do this in our code, we need to know the architecture of the processor we're interfacing with; we need to speak its language.

### What you need to know for this lab

In this lab, you will be interfacing directly with the processor in your computer. We will use instructions from the x86 processor architecture as it is still the dominant architecture in modern processors.

If you do not have an x86-based processor in your computer (e.g. you have an M1/M2/M3 MacBook), don't worry, the lab should still work for you (thanks to [some technical magic](https://github.com/DLTcollab/sse2neon)).

## Task 0: Introduction to SIMD

Single instruction, multiple data (SIMD) is a paradigm in parallel processing which refers to single instructions which perform operations on multiple pieces of data at the same time. They can significantly improve performance at the lowest level of computation by increasing the amount of calculations the processor can perform per-clock.

SIMD instructions utilise the vector-based nature of modern processors, and so we will need to represent our calculations as vectors rather than as single (scalar) numbers. For this lab, we'll be using instructions that operate on four floating-point numbers at a time, so we just need to think in terms of four-dimensional vectors, like this:

```c++
{1.6, 2.5, 3.7, 4.9}
```

To represent one of these SIMD vectors in C++, we use a special type: `__m128`, which represents a vector of four 32-bit floating-point values. This type is part of [SSE](https://en.wikipedia.org/wiki/Streaming_SIMD_Extensions), which is the SIMD specification we're using for this lab, and it allows us to store values in the processor's internal SSE registers.

```c++
// Create a new SSE vector named `my_vector`
__m128 my_vector;
```

To assign some values to this vector, we must use the correct SSE instructions (called 'intrinsics') to put values into the processor register in which the vector resides. The SSE intrinsics we use can be looked up on [Intel's Intrinsics Guide](https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#techs=SSE_ALL). To assign values to our vector, we use the [`_mm_set_ps`](https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#techs=SSE_ALL&ig_expand=155,5860,5863,5917,5860,5860&text=_mm_set_ps) intrinsic as follows:

```c++
my_vector = _mm_set_ps(1, 2, 3, 4);
```

Remember that the vector is four-dimensional, so we give it four values. If we want to set all four values of a vector at the same time, we can also use the [`_mm_set1_ps`](https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#techs=SSE_ALL&ig_expand=155,5860,5863,5917,5860,5860,5917&text=_mm_set1_ps) intrinsic:

```c++
my_vector = _mm_set1_ps(0);
```

## Task 1: Basic addition with SIMD

Open [`task1.cpp`](./task1.cpp). You are shown how to use SSE intrinsics to sum two vectors together and print the result.

## Task 2: Mathematical operations

Open [`task2.cpp`](./task2.cpp). You are given four nearly-completed functions for the basic add, subtract, multiply, divide operations. You need to fill in the gaps in each function body to use the correct SSE intrinsic, which you can look up using [Intel's Intrinsics Guide](https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#techs=SSE_ALL).

## Task 3: Advanced operations

Task 3 isn't finished yet.

## Task 4: A real-world example

Open [`task4.cpp`](./task4.cpp). You are given an implementation of the [Leibniz formula](https://en.wikipedia.org/wiki/Leibniz_formula_for_π) for estimating Pi - just like a few weeks ago in [lab 1, task 4](../lab1/task4.cpp). You need to implement a version of the formula which is optimised using SIMD instructions. There is a blank function in which to do this.
