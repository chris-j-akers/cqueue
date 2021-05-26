# QDCQueue

- [Introduction](#introduction)
- [Storage Considerations](#storage-considerations)
  - [Too Many Items in the Queue?](#too-many-items-in-the-queue)
  - [Shrinking the Queue](#shrinking-the-queue)
  - [Type Considerations](#type-considerations)
- [What's in this Repo?](#whats-in-this-repo)
  - [Repo Contents](#repo-contents)
- [Building QDCQueue](#building-qdcqueue)
- [Testing QDCQueue](#testing-qdcqueue)


## Introduction

QDCQueue (or Quick and Dirty C Queue) is a bare-bones implementation of a standard queue data-structure written in `C`.

A Queue is a First-In-First-Out structure (FIFO) in which items are removed in the order they were added. This is definitely CompSci 101 territory and more information about queues can be found all over the internet.

This whole thing started as a brief set of notes written before and during the implementation of a simple queue data-structure in C to assist with another project. It struck me as interesting that, even when building this very simple, foundational data-structure there were still a number of considerations to be made, especially when using a lower-level language. Some of these considerations are below.

## Storage Considerations

Data added to a queue is usually ephemeral - it's unlikely a developer will enqueue items if they have no intention of removing them at some point - and this is important when considering how memory is to be allocated and freed during our queue operations.

Memory could be allocated when an item is enqueued and freed when it is dequeued, but what if the queue grows to a million items? That would mean a million calls to `malloc()` and, as all the items are dequeued, another million calls to `free()`.  Memory operations can be expensive so it's better to try and find ways to avoid too many of them.

Instead, when the queue is created, some memory will be pre-allocated. How much, exactly, will be left to the user who will provide an `initial_capacity` argument to the queue constructor function. This argument will store the number of items the user wants to pre-allocate space for when the queue is created. If the user is thinking properly about how the queue is going to be used, they should have a good idea of what this should be. Yes, if they have overestimated, it could mean the queue never reaches capacity and some memory goes to waste<sup>*</sup>, but wasting a small amount of space is forgivable if the trade-off is avoiding excessive system calls to allocate and free memory.

<sup>* Or does it? For instance, both Linux and Windows use Virtual Memory schemes in which addresses returned by calls to functions like `malloc()` are virtual and it's only once those addresses are written to that they are backed with actual physical RAM pages by the OS. For instance, a request to `malloc()` for 16KB of memory will return 4 pages** of Virtual Address space ready to be written to by the program, but if it turns out only 8KB of that space is used, it does not necessarily mean that 8KB of physical RAM has gone to waste. In theory, only 2 pages** of physical RAM will have been used, leaving the rest free.</sup>

<sup>**assuming the (fairly) standard page-size of 4KB</sup>

### Too Many Items in the Queue?

What happens when the queue reaches capacity and there's an attempt to enqueue another item? 

The `enqueue()` function will contain logic to check capacity and automatically expand the queue when necessary.  In these cases, `enqueue()` will allocate another block of memory, the size of which will be determined by the `grow_by` parameter passed to the queue constructor. This parameter will inform `enqueue()` how much extra space to allocate when the queue grows. Again, it requires the user to think about how their queue is going to be used. Is it likely that the queue will only grow by a couple of extra items, or could it double in size? 

There are probably a number of far cleverer ways to automatically increase queue capacity. For example, `enqueue()` could record a timestamp the first time it's used and then again when the queue is at capacity. The time between the two could be a factor in how much more space to add. If the time span was a matter of nanoseconds then it's likely there's a lot more data to come immediately, so the newly allocated block needs to be quite large. If the time span was days, then the additional block could probably be quite small. `CDCQueue` is intended as a basic implementation, though, so no need to get too complicated with the auto-grow method.

### Shrinking the Queue

It's already been stated that freeing memory each time an item is dequeued may be inefficient, but the fact is a dequeued item is effectively deleted from the queue. If the queue is large and a number of items have already been dequeued then there is potentially a lot of memory to be freed.

A `shrink_queue()` function will recover space no longer required at the top of the queue by reducing the capacity to the items already in the queue. This function will be called by the user at suitable points in their program. On the one hand, it means the user has to remember this function if they ever want memory to be recovered from their queue, but on the other it means they are in control of when this operation is run. For instance, say their program can detect when it is not being used frequently - the shrink could automatically run when this happens, or it could run it after a certain number of `dequeue()` operations.

### Type Considerations

What types will `QDCQueue` store?

First (and perhaps, obviously), pointers. Items are not going to be copied into queues - that just wouldn't make sense (as well as being incredibly inefficient).  Storing pointers is fast and keeps the queue compact. Their fixed size also means it's  a lot simpler to allocate storage. 

So, pointers to what?

The queue could be hard-coded to use a pointer to a particular type such as `char*` or `int*` but that does limit the use of the queue. A module could be written for each literal `C` type: `QDCIntQueue*` or `QDCCharQueue*` or `QDCLongQueue*`, but that means having to maintain separate source files which is a headache, and what if users want to store their own `struct` types?

Instead, the queue will store items of type `void*`.

The generic pointer or `void*` pointer in `C` is a pointer with no associated data-type. It can point to *anything*.  This suits our purposes perfectly because the queue is just a container, it's not going to perform any operations on its contents, so it shouldn't care what type they are.

Still, though, `void*` is a long way away from the built in polymorphism provided by a lot of high-level languages, so care must be taken. For instance, it's perfectly acceptable for a developer to load an `int*` to the queue as a `void*`, then dequeue it as a `struct myStruct*` and attempt to treat the data it's pointing to as this type. Both the compiler and run-time will permit this and the program will go into an undefined state.

## What's in this Repo?

This repo contains a basic implementation of a Queue written in C.

### Repo Contents

| ARTIFACT  | DESCRIPTION  |
|---|---|
| `./qdcqueue-test/` | Directory containing a small test program and associated artefacts    |
| `qdcqueue.h`  | Header file   |
| `qdcqueue.c`  | Source  |
| `README.md`  | This README file  |

## Building QDCQueue

Simply add an `include` directive to your own project (with the correct location)

`#include "qdcqueue.h"`

Then add the C source file to your compilation command:

`gcc -o myprogram myprogram.c qdcqueue.c`

Alternatively, you could build it as a static library:

`➜ gcc -c -o qdcqueue.o qdcqueue.c`

`➜ ar rcs qdcqueuelib.a qdcqueue.o`


## Testing QDCQueue

The `./qdcqueue-test/` directory contains source and artefacts to run a couple of tests on the queue. It also includes test data.