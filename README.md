# CompilerExample
 rev inter

part one is in the part-one branch.

part two is in the part-two branch.

part three is in the part-three branch.

### Setup

Generate ninja build files and build:

   ```sh
   $ cmake . -B build -G Ninja 
   $ cmake --build build
   ```
To run examples:

   ```sh
   $ ./build/examples/example
   $ ./build/examples/complex-example
   ```

To run tests:

   ```sh
   $ ./build/tests/test
   ```
