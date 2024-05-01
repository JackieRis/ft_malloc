# ft_malloc

## WORK IN PROGRESS

We have to use mmap() instead of brk(), not like the real malloc does.

There are three types of allocations:
- TINY < 128 Bytes
- SMALL < 1024 Bytes
- LARGE everything upper than 1024 bytes

To create a malloc optimized, we have to allocate pages that are a multiple of getpagesize() function, so for TINY and SMALL allocations could fit 100 blocks of their size in a page.


So at First, I tried with no structure, just a global double pointer, was working, really hard to manage, and far harder to read.

Then I tried a structure like this:
```c
typedef struct	s_page
{
	struct s_page	*next;
	int			type;
	size_t		size;
	int			used;
	size_t		*blocks;
}				t_page;
```
Finally a basic structure, readable, and easier to use, but something was missing, I needed an easier way to get more informations about my blocks.

The final structure was then created:
```c
typedef struct	s_block
{
	struct s_block	*next;
	int			used;
	size_t		size;
}				t_block;

/*
	My allocation's page storage
	TYPE: type of the page, SMALL, TINY OR LARGE
	SIZE: only usefull for LARGE allocation, basically size allocated
	USED: number of blocks used in this page
	BLOCKS: block's list
*/
typedef struct	s_page
{
	struct s_page	*next;
	int			type;
	size_t		size;
	int			used;
	t_block		*blocks;
}				t_page;
```
In the future, I may add struct s_page *prev for free() or re-allocate.


I wasted too much time about a mistake, about how should I make my malloc segfault.
I explain, for example, you ask
```c
char *test = ft_malloc(42)
```
if the user tries
```c
test[45];
```
the real malloc makes you segfault, but here, I can't segfault, it's impossible because you are in a TINY case, so i've got an entire page allocated in wich you can fit 100 blocks of 128 Bytes.

And the second problem about it is....
```c
char *first = malloc(128);
char *second = malloc(42);

first[129] = "a";
```
Yes, I don't segfault, so I can write in my second pointer... I'm not happy but because of my school subjects, I can't find a way to counter that.

Fun fact, you can with the real malloc modify the others pointer you've ask to allocate.