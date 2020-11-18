# AlnSeqTree

AlnSeqTree stands for `Aligned Sequence Tree` which is the implementation
of building phylogenetic tree based on aligned sequences by distance method.
It is derived version from our alignment-free phylogeny project, CVTree.

## Main Programs

- astree: the main program, it get the phylogeny tree based on aligned fasta file of genomes.
- as2dm: Get the distance matrix based on the aligned fastas
- dm2tree: Get the phylogeny tree from the distance matrix by neighbor-joint method.
- mconv: convert format of dissimilarity matrix file
- getdist: Show select distances from the distamce matrix
- diffmtx: compare two distance matrixes

## Installation

### Compile with CMake

#### Preparation

- cmake >= 3.0
- g++ >= 4.8 or other compiler supporting C++11 standard
- require ligrary: libz
- compiler with support openmp for parallel (_option_)
- Library (_option_): netcdf, netcdf_cpp
- Library (_option_): libhdf5 for c++ (*Please don't use the hdf5 libraries in Anaconda*)

#### Compiling

1. unzip the package file and change into it
2. mkdir build and change into it
3. cmake .. or add some options you wanted
4. make
5. make install (_option_)

## License

This software is free for non-commercial use. For commercial use,
a software agreement is required.
