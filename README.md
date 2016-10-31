# Terminal Quest
![travis build status]
(https://travis-ci.org/jm-janzen/termq.svg?branch=master)
[![license](https://img.shields.io/github/license/mashape/apistatus.svg)](https://github.com/jm-janzen/termq/blob/master/LICENSE.md)

A personal adventure with ncurses.

## Requirements

Requires (`g++ 4.3` or `clang++ 3.8`), `libncurses5-dev`, `cmake 2.8.12.2`.

---

## Installation instructions

```bash
# Copy the source files
git clone https://github.com/jm-janzen/termq.git

# Navigate to project's build directory
cd termq/build

# Build the project locally
cmake .. && make -j4  # or cmake --build .

# Execute the compiled binary
../bin/termq
```

## Testing instructions
```bash
cd termq/build

# Run all tests
ctest -V

# Run specific test binaries
./test/Test_[GROUP]  # Eg: ./test/Test_entity  (BUG: ncurses may interfere with terminal output)
```


## Future Plans

For a vulgar summary of where this project is going, please see [the roadmap](https://github.com/jm-janzen/termq/blob/master/docs/roadmap-to-release.md).

