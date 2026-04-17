# Readers–Writers System with Shared Memory & Semaphores

## About

This repository contains coursework developed for the *Operating Systems* course at the Department of Informatics and Telecommunications, National and Kapodistrian University of Athens (NKUA).

The project implements a **starvation-free Readers–Writers synchronization system** using processes, shared memory, and POSIX semaphores.

## Main Idea

The goal of this project is to solve the classical **Readers–Writers problem** while avoiding starvation for both readers and writers.

The system consists of independent programs that run concurrently:

- **open**
  - initializes shared memory
  - creates and initializes semaphores
  - sets up shared data structures and statistics

- **reader**
  - reads one or more records from a shared binary file
  - computes statistics (e.g., average balance)
  - respects synchronization constraints

- **writer**
  - updates a record’s balance
  - ensures exclusive access during writes
  - updates shared statistics

- **close**
  - prints final statistics
  - destroys semaphores and shared memory

## Synchronization Design

The implementation ensures:

- multiple readers can access data simultaneously
- only one writer can access data at a time
- no starvation for readers or writers

This is achieved using:

- **POSIX Semaphores**
- **Shared Memory**
- a carefully designed synchronization protocol

Key components include:

- `rcnt` → reader counter synchronization  
- `rdwr` → critical section control  
- `addt` → fairness mechanism (avoids starvation)  
- `r_counter` → number of waiting readers  

## Project Structure

- `src/` – source files (`.c`)
- `include/` – header files (`.h`)
- `build/` – compiled executables
- `scripts/` – shell scripts for automated execution scenarios
- `docs/` – additional notes and design explanations
- `Makefile` – build automation

## Input Data

The project uses binary account files stored in the [`data/`](data) directory, including:

- `accounts50.bin`
- `accounts5000.bin`
- `accounts50000.bin`
- `accounts100000.bin`

These files contain customer records used by readers and writers during execution.

## Example Scripts

The [`scripts/`](scripts) directory contains example shell scripts that automate concurrent execution scenarios for readers and writers.

### Available scripts

- `run_example01.sh` – demonstrates concurrent writers and readers operating on overlapping records
- `run_example02.sh` – demonstrates a mixed sequence of readers and writers with staggered arrival times
- `run_example03.sh` – demonstrates heavier reader concurrency combined with interleaved writer operations

These scripts:
- initialize the shared memory segment through `open`
- launch multiple readers and writers in the background
- introduce delays using `sleep` to simulate different arrival times
- wait for all processes to finish
- call `close` to print statistics and release shared resources


### Run a script

Before running any script, compile the project:

```make```

Then execute a script, for example:

```
bash ./scripts/run_example01.sh
bash ./scripts/run_example02.sh
bash ./scripts/run_example03.sh
```

## Usage

### Compile

```make```

### Run

Example execution:

```
./build/open ./data/accounts50.bin
./build/reader -f ./data/accounts50.bin -l 1,5 -d 10 -s <shmid>
./build/writer -f ./data/accounts50.bin -l 3 -v 100 -d 5 -s <shmid>
./build/close <shmid> ./data/accounts50.bin
```

## Data Format

Each record contains:

- Customer ID (```int```)
- Last Name (```char[20]```)
- First Name (```char[20]```)
- Balance (```int```)

## Technologies

- C
- POSIX Semaphores
- Shared Memory (IPC)
- Process synchronization
- Linux system programming