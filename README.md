<h1 align="center">
	<p>
	push_swap
	</p>
	<img src="https://github.com/aaron-22766/aaron-22766/blob/main/42-badges/push_swape.png">
</h1>

<p align="center">
	<b><i>Because Swap_push isn’t as natural</i></b><br><br>
</p>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/aaron-22766/42_push_swap?color=lightblue" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/aaron-22766/42_push_swap?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/aaron-22766/42_push_swap?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/aaron-22766/42_push_swap?color=green" />
</p>

---

## 🗣 About

This project will make you sort data on a stack, with a limited set of instructions, using the lowest possible number of actions. To succeed you’ll have to manipulate various types of algorithms and choose the most appropriate solution (out of many) for an optimized data sorting.

[![Play Demo](https://github.com/aaron-22766/aaron-22766/blob/main/bin/gifs/push%20swap%20500.gif)](https://www.youtube.com/watch?v=nN0gt9Yrt04)

Number of operations my algorithm produces out of 1000 randomized tests:
| INPUT SIZE | MIN  | MAX  | AVERAGE | REQUIREMENTS         |
|------------|------|------|---------|----------------------|
| 3          | 1    | 2    | 1.34    | ≤ 3                 |
| 5          | 1    | 9    | 6.55    | ≤ 12                |
| 100        | 495  | 616  | 560     | ≤ 700 for 5 points  |
| 500        | 3663 | 4277 | 3971    | ≤ 5500 for 5 points |

## 🛠 Usage

The game is written in C language and thus needs the **`gcc` compiler** and some standard **C libraries** to run.
Run the executable with the numbers as argument(s) and it will print the required operations for sorting these numbers.

```shell
$> make
$> ./push_swap "42 21" 3 9
sa
ra
ra
```

## 💬 Description

Program:
* You have two stacks named `a` and `b`
* Upon launch, the input numbers are all in stack `a` in the same order as given from the command line
* The program must display the smallest stack of instructions possible to sort the stack `a`, the smallest number being at the top

Input numbers must follow these rules, otherwise the program just returns an Error:
* must be a valid integers
* can be given as just one argument or split up into multiple arguments
* cannot have duplicates

Operations:
- `sa` (swap a): Swap the first 2 elements at the top of stack `a`
- `sb` (swap b): Swap the first 2 elements at the top of stack `b`
- `ss` : sa and sb at the same time
- `pa` (push a): Take the first element at the top of `b` and put it at the top of `a`
- `pb` (push b): Take the first element at the top of `a` and put it at the top of `b`
- `ra` (rotate a): Shift up all elements of stack `a` by 1
- `rb` (rotate b): Shift up all elements of stack `b` by 1
- `rr` : ra and rb at the same time
- `rra` (reverse rotate a): Shift down all elements of stack `a` by 1
- `rrb` (reverse rotate b): Shift down all elements of stack `b` by 1
- `rrr` : rra and rrb at the same time

## ⭐️ My approach

### Stack

First things first, I needed to decide on a data structure for the two stacks. I did a lot of research to find the best one for this project. I considered an array but that would require shifting the whole array to do a rotation. Most people use a linked list because you can easily add an element to the front and back but it is slow on iteration (when checking for sort) and is honestly a bit overkill as we don't need to access elements in the middle and also requires more memory.

So what I decided on was a **circular array**. This is the struct I created:

```c
typedef struct s_stack
{
    char st; // either A or B macro depending on the stack
    int	*values; // heap allocated integer array
    int head; // index of the head of the stack in the array
    int tail; // index of the tail of the stack in the array
    int count; // number of elements on the stack
    int size; // total (allocated) size of the array
}   t_stack;
```

This structure made it really simple to just "push" and "pop" an element to/from the front or back by altering the `head` or `tail` variables. Then `pa` for example is as easy as popping the `head` of `b` and pushing it to the `head` of `a`; or `rb` is just pupping the `head` of `b` and pushing it to the `tail` of `b`.

A "peek" function makes it possible to retrieve the pointer to an element in the array that takes the stack index as argument. I used it to implament a "swap" function manually and it's also heavily used in the algorithms to check the value at a particular index.

### Algorithm

Because of the requirement to optimize for 3, 5, 100 and 500 input numbers, I decided to implement simple algorithms for 3 and 5 numbers and one more complex algorithm for bigger amounts. First, I check if stack `a` is already sorted, if it is, the program just exits. Then, if there are only 2 numbers on the stack, they are swapped and then the stack is sorted. Otherwise I run the different algorithms.

#### Sorting 3 numbers

This one is really simple. It just compares the 3 numbers and either rotates, reverse rotates or swaps the stack. It's a recursive function for simplicity sake but at most it needs 2 operations to sort it. It only takes into account the first 3 numbers because I use this function for sorting 5 numbers as well.

#### Sorting up to 5 numbers

The approach here is also quite simple. I `pb` until there are only 3 numbers on stack `a`, then call the "sort_three" function and insert the number(s) on `b` back into `a`. For inserting, I made a function "bring_to_top" that simply rotates in the direction that needs less operations to bring the desired number to the top of the stack. It is also quite useful in the bigger algorithm.

When I tested it, it worked quite well but there were a lot of cases where this algorithm performed poorly (10-11 operations). So I analyzed these cases and found out that most are a case where only one number is not in order. This number is rotated to, then pushed to `b` and then inserted back into the right spot. This quite improved the statistics for sorting 5 numbers.

#### Sorting large amounts of numbers

At this point I already worked on this project for a long time and just wanted to get a simple but good algorithm, so this is a kind of optimized brute force approach. I first push all numbers to `b` while pre-sorting them into 4 chunks in a K-shaped manner. Then I start at the chunk with the largest numbers and calculate how many operations each number would need to be inserted into stack `a`. Then the number with the lowest amount of operations is chosen to actually be moved. This gets repeated until the chunk is empty, at which point I continue to the next smaller chunk until `b` is empty.

### Optimization

One thing that I developed while working on the large algoritm was a bitmap for the operations:

* 00000001 A
* 00000010 B
* 00000100 SWAP
* 00001000 PUSH
* 00010000 ROT
* 00100000 REV
* 01000000 CLEAR

This made it possible to just bitwise-or the instructions together to form the different operations (`rrr` = `REV | A | B`).

Since it was now possible to store an operation in just 1 byte, I thought it would be cool to queue the operations while running the algorithm instead of actually printing them to the output immedately. So I implemented a lot of functions to detect and replace/delete unnecessary operations, those include:

* push, rotate and push back would be replaced by a simple swap (`pb` - `ra` - `pa` → `sa`)
* mixed push operations following immediately after each other can be deleted (`pb` - `pa` - `pb` → `pb`)
* double swap operations can be deleted (`sa` - `sa` - `sa` → `sa`)
* opposite rotations are cleaned (`ra` - `ra` - `rra` → `ra`)
* rotations in the less efficient direction are replaced by the more efficient direction (size 4: `ra` - `ra` - `ra` → `rra`)
* individual swaps on both stacks are combined (`sa` - `sb` → `ss`)
* individual rotations on both stacks are combined (`ra` - `rb` → `rr`)

These get repeated until the queue has reached the lowest number of operations. I had to be very careful about the implementation as a wrong code would basically unsort my stack again, but I got it to work. The optimizations brought down the average number of operations by up to **15% !!!**

## ⚡️ Testing

To run the visualizer (Mac only):
```shell
$> make vis
```

To run a tester script for multiple tests:
```shell
$> make 3
$> make 5
$> make 100
$> make 500
$> perl ps_tester.pl [amount of random numbers] [number of tests]
```
