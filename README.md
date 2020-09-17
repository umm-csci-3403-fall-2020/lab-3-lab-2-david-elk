# Background

This lab is a collection of several C programming exercises with an
emphasis on arrays, pointers, and memory management.

For more information (including information on how to use ```valgrind```), see
the [C programming pre-lab assignment](https://classroom.github.com/a/304sWPd4).

* [Background](#background)
  * [Testing and the Google Test framework](#testing-and-the-google-test-framework)
  * [Fixing memory problems](#fixing-memory-problems)
  * [Getting started](#getting-started)
  * [The problems](#the-problems)
    * [Mergesort](#mergesort)
    * [Array merge](#array-merge)
  * [Final Words](#final-words)

---

## Testing and the Google Test framework

Each of these exercises comes with a set of tests implemented using [the
Google Test framework for C](https://github.com/google/googletest), aka
`gtest`. You won't have to learn anything about `gtest`, but you
will need to be able to compile and run the tests that we provide.

We think the tests are pretty reasonable, but make *no* promises that
they are in any way complete. Obviously you want your code to pass at
least these tests, but you shouldn't assume that passing these tests
guarantees any kind of correctness. You're welcome to read the tests
and extend them if you'd like. You may even need to make changes to the
test code to handle memory leaks
[(see "fixing memory problems" below)](#fixing-memory-problems).
Do be careful to not remove or weaken the tests, though; at a minimum
you definitely want to be able to pass the tests as given.

## Fixing memory problems

Passing the tests is arguably just the first half of each of these problems,
as it's entirely possible to pass the tests but still have substantial memory
management problems. You could, for example, have an illegal memory access
that passes the tests through happenstance, because the right value happens
to be in the necessary location. Or you could have memory leaks because you
never free up any of the memory you allocated while solving the problem-- even if your
solution is otherwise entirely correct. This is where `valgrind` is extremely
helpful, as it will identify these kinds
of memory problems even if the tests pass.

:bangbang: One non-obvious, but important, place to look for memory leaks is
in the test code. If the test code calls some function `f()` that returns an
array or string that is allocated somewhere in `f` (or a function `f` calls),
then that memory is lost if the test code doesn't free up that returned array.
So if `valgrind` says there's a leak where some memory is allocated in a function
and then returned to the test code, then the fix is _in the test code_. In general
we don't encourage you to fiddle with the
test code (you could always just change the test code to say everything
passes!), but if the memory leaks to the test code, then that's where the
fix has to be made (and you should do so).

## Getting started

There are several directories here, one for each project.
We would recommend doing them in the order listed below; there's no
overwhelming reason that you need to do them in any particular order,
however, and it would be far better to move on to the
next one rather than get stuck in one and not make any progress.

The basic structure for each project is (for an imaginary project
`foo`):

* `foo.h`, which specifies the name, arguments, and return
  type of the function you're supposed to write.
  * In every case we wrote one or more helper functions, but these
    don't have to be included in the `.h` file unless you
    want to include them in the tests.
* `foo.c`, which includes the initial stub (or an incorrect version)
  of the program you're working with in that part.
* `foo_test.cpp`, which is the test file we wrote using `gtest`. The
  `.cpp` ending is because this is actually a C++ file not a strict
  C file. That will affect how you compile the test code, but you
  won't have to know/learn anything about C++ for this lab.

Your job then is typically to complete or fix `foo.c`, which provides
the implementation of the function listed in `foo.h`.

To compile the test code use the following:

```bash
g++ -Wall -g -o foo_test foo.c foo_test.cpp -lgtest -pthread -std=c++0x
```

_Notice that this uses `g++` instead of `gcc`._ This because the `gtest`
is technically a C++ library, but it also works for "plain" C code, which
is all we need it for here. The `-g` flag isn't strictly necessary; it
causes a variety of useful debugging information to be included in
the executable, however, which can be *extremely* helpful when using
tools like `valgrind` or the `gdb` debugger. If you don't include it,
for example, then those tools won't be able to report accurate or useful
line numbers or function names. The `-lgtest` tells the compiler to include
the `gtest` library (that's the `-l` part) when generating the executable.

---

## The problems

:bangbang: Remember: For each problem you should at a minimum

* Pass our tests, and
* Have _no_ memory leaks, as confirmed by `valgrind`.
* Remove any print statements, comments, or other code that you used to debug your code before you turn it in.

Also, please don't lose your brains and forget good programming practices just because you're working in a new language. C can be quite difficult to read under the best of circumstances, and using miserable names like `res`, `res2`, and `res3` doesn't help. *Use functions* to break up complicated bits of logic; it's really not fun when a group turns in a solution that is one huge function, especially when there are several instances of repeated logic.

Some things to watch our for:

* In the past there has been strong inverse correlation between length
  and correctness on these problem. If you find yourself wandering off into 2
  or more pages of code for any of these, you've likely lost the plot
  and should probably ask for some help.
* Make sure you initialize all variables (including variables used to index arrays in
  loops). C won't give you an error if you fail to initialize something, and
  sometimes you can get lucky and your tests will accidentally pass because, at least
  that one time, you happened to get the "right" initial value. That doesn't mean
  your code is correct, though.
* Make sure you allocate space for the null terminator `\0` when allocating 
  space for strings.

There are more comprehensive tips and suggestions in `Tips_and_suggestions.md` in the repository.

### Mergesort

Your task here is to implement a well known sorting algorithm in C,
e.g.,

```C
void mergesort(int size, int values[]);
```

This is a
_destructive_ sorting operation, i.e., it should alter the array that it's
given by rearranging the elements in that that array. Note that since C
doesn't know how large arrays are, we pass in
the size as an argument.

To simplify the process, we've provided you with [Java implementations of
Quicksort and
Mergesort](https://github.umn.edu/gist/mcphee/83e9818b21ef9cb3cde4) that
you can use as models. We strongly
recommend you take advantage of these; doing so will help ensure
that you focus on the C issues on these problems, and it'll make
them easier to grade. (Having to figure out some crazy, unexpected
approach is much more time consuming than reading a "standard"
solution.)

Common approaches to Mergesort require allocating temporary arrays
(e.g., [this allocation in the Java code](https://gist.github.umn.edu/mcphee/83e9818b21ef9cb3cde4#file-mergesort-java-L29)); you
should make a point of freeing these up when they're no longer needed,
as you certainly wouldn't want a common operation like sorting to leak a
bunch of memory every time it's called. Again, `valgrind` should be your
friend.

:bangbang: C has "fancied up" over the years so you can dynamically allocate
arrays without using `malloc` or `calloc`. For this lab **do not do that**.
Make sure that in your recursive calls to `mergesort` that you use `calloc`
(or `malloc` if you prefer) to allocate the necessary temporary arrays.
This arguably over-complicates the problem, but the point of this exercise
is to make sure you understand the allocation and freeing of memory its
important that you use `malloc` and `free`. Thanks.

### Array merge

Your task here is to implement

```C
int* array_merge(int num_arrays, int* sizes, int** values);
```

Here `values` is an array of arrays
of integers, where each of the sub-arrays can have different length (so
it's not really a standard 2-D array). Because C doesn't know the size
of arrays, we need to provide all that information in the arguments:
`num_arrays` is the number of arrays in `values`, and `sizes` is an
array of ints that should also have `num_arrays` entries, each of which
is the length of the corresponding sub-array in `values`. If
`sizes[3]==10`, for example, then `values[3]` will be an array of 10
integers.

_Note how inherently icky it is to have to pass all this bookkeeping
information around, and how many wonderfully unpleasant errors can
result from doing this incorrectly. It's a **lot** safer if arrays know
how big they are._

`array_merge` should then generate a single sorted list (small to large) of the
unique values (i.e., no duplicates) in `values`. Since we haven't yet
learned how to return multiple values in C, we're going to use a
slightly cheesy hack and return the `k` unique values in an array of
size `k+1`, where the first element will hold the value `k`. If, for
example, there were 3 unique values (5, 8, and 9), then the result array
would contain [3, 5, 8, 9]. The caller can then use the first element of
the array to determine how long the array actually is.

As a fuller example, consider the following input:

* `num_arrays = 3`
* `sizes = [4, 2, 5]`
* `values = [[3, 2, 0, 5], [8, 9], [6, 3, 2, 0, 5]]`

Then the result should be `[7, 0, 2, 3, 5, 6, 8, 9]`.

There are ways to write this that waste a lot of memory when the set of
unique values is much smaller than the number of entries in `values`;
your solution should make a point of freeing up any unused memory.

You might also find your sorting algorithm from above useful in sorting
your results. With a little care, you can put all the unique values in an unsorted
array, and then ask your sorting algorithm to sort the desired bit of
the array without messing with that important first element.

## Final Words

Be sure that:

* [ ] You follow our instructions
* [ ] Your canvas group matches your github classroom group
* [ ] You submit your repository URL to canvas (if your canvas groups are set up correctly this will only need to be done once)
