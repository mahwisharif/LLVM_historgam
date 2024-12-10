# LLVM_historgam
### Building LLVM Pass 
`BBHistogram` directory contains LLVM pass that calculates the histogram basic blocks based on the number of instructions. 
- Copy `BBHistogram` directory under `your-llvm-top-directory/llvm/lib/Transforms`
- add the following line to `your-llvm-top-directory/llvm/lib/Transforms/CMakeLists.txt`
   ```
   add_subdirectory(BBHistogram)
   ```
- Now you can build it with "``make``" or "``ninja``" from the top level of your build directory. It will generate a file
"``lib/LLVMHistogram.so``" under build directory.

### Running the pass on a testcase
convert testcase c/c++ file to LLVM IR 
```
clang -O0 -emit-llvm -c test-unrolled.cpp -o test-unrolled.bc
```
run the following command to LLVM pass on the generated *.bc file from top level llvm directory
```
opt -load ./build/lib/LLVMHistorgam.so  -histogram-pass test-unrolled.bc > /dev/null

```
this will generate a `histo.csv` file, that can be then used by `histo.plt` script to plot histogram using gnuplot. 

### Plotting the histogram with gnuplot 
```
gnuplot histo.plt
```
