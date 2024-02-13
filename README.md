<h1 align="center">
	<p>
	push_swap
	</p>
	<img src="https://github.com/ayogun/42-project-badges/blob/main/badges/push_swape.png">
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

<!--
https://youtu.be/nN0gt9Yrt04
-->

Number of operations my algorithm produces out of 1000 randomized tests:
| INPUT SIZE | MIN  | MAX  | AVERAGE | REQUIREMENTS      |
|------------|------|------|---------|-------------------|
| 3          | 1    | 2    | 1.34    | 3                 |
| 5          | 1    | 9    | 6.55    | 12                |
| 100        | 495  | 616  | 560     | 700 for 5 points  |
| 500        | 3663 | 4277 | 3971    | 5500 for 5 points |

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

Program
* You have two stacks named a and b
* Upon launch, the input numbers are all in stack a in the same order as given from the command line
* The program must display the smallest stack of instructions possible to sort the stack a, the smallest number being at the top

Input numbers:
* must be a valid `int`egers
* can be given as just one argument or split up into multiple arguments
* cannot have duplicates
otherwise the program returns an Error

Operations:
- `sa` (swap a): Swap the first 2 elements at the top of stack a
- `sb` (swap b): Swap the first 2 elements at the top of stack b
- `ss` : sa and sb at the same time
- `pa` (push a): Take the first element at the top of b and put it at the top of a
- `pb` (push b): Take the first element at the top of a and put it at the top of b
- `ra` (rotate a): Shift up all elements of stack a by 1
- `rb` (rotate b): Shift up all elements of stack b by 1
- `rr` : ra and rb at the same time
- `rra` (reverse rotate a): Shift down all elements of stack a by 1
- `rrb` (reverse rotate b): Shift down all elements of stack b by 1
- `rrr` : rra and rrb at the same time

## ⭐️ My approach

