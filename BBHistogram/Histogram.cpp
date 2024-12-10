//===- Histogram.cpp - Pass for calculating a histogram of instructions in each basicblock" ---------------===//
//
//===----------------------------------------------------------------------===//

#include <iostream>
#include <fstream>
#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

#define DEBUG_TYPE "histo"

#define TOTAL_BUCKETS 4
namespace {
    struct Histogram : public ModulePass {
    static char ID; // Pass identification, replacement for typeid
    Histogram() : ModulePass(ID) {}
    
    int getBucketIdx(int count){
        if(count < 10) return 0;        //for count [1,10)
        if(count < 100) return 1;       //for count [10,100)
        if(count < 1000) return 2;      //for count [100,1000)
        return 3;                       //for count [1000, inf]
    }
    bool runOnModule(Module &M) override {
       int histo_buckets[TOTAL_BUCKETS] = {0};
        // Iterate through all functions and basic blocks
       for (Function &F : M) {
          for (BasicBlock &BB : F) {
             int instrCount = BB.size(); // Get the number of instructions
             assert(instrCount > 0);
             int bucketIndex = getBucketIdx(instrCount);
             histo_buckets[bucketIndex]++;
          }
       }
        // Print the histogram
        errs() << "Histogram of instruction counts in basic blocks:\n";
        errs() << "1-10:   " << histo_buckets[0] << "\n";
        errs() << "10-100:  " << histo_buckets[1] << "\n";
        errs() << "100-1000:  " << histo_buckets[2] << "\n";
        errs() << "1000-inf: " << histo_buckets[3] << "\n";
        std::ofstream Outfile("/home/ma843/histo.csv");
        if (!Outfile.is_open()) {
            std::cerr << "Could not open file." << std::endl;
            return 1;
        }
        //write histogram values to csv file
        for (int i = 0; i < TOTAL_BUCKETS; ++i) {
           Outfile << histo_buckets[i] <<"\n";
        }
        Outfile.close();
        return false;
    }
    void getAnalysisUsage(AnalysisUsage &AU) const override {
      AU.setPreservesAll();
    }
  };
}

char Histogram::ID = 0;
static RegisterPass<Histogram> X("histogram-pass", "BB Histogram pass");

