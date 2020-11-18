/*
 * Copyright (c) 2018  T-Life Research Center, Fudan University, Shanghai,
 * China. See the accompanying Manual for the contributors and the way to cite
 * this work. Comments and suggestions welcome. Please contact Dr. Guanghong Zuo
 * <ghzuo@fudan.edu.cn>
 *
 * @Author: Dr. Guanghong Zuo
 * @Date: 2017-03-08 20:30:43
 * @Last Modified By: Dr. Guanghong Zuo
 * @Last Modified Time: 2018-07-26 21:55:04
 */

#ifndef ASTREE_H
#define ASTREE_H

#include "distmeth.h"
#include "treemeth.h"
#include "info.h"
#ifdef _OPENMP
#include <omp.h>
#endif

using namespace std;

// read arguments
struct Args {
  string program, fasta, dmName, treeName;
  string refdm;
  bool refself;

  DistMeth *dmeth;
  TreeMeth *tmeth;
  
  Args(int, char **); 
  void usage();
};

void mkpath(const string &);

#endif
