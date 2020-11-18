/*
 * Copyright (c) 2018  T-Life Research Center, Fudan University, Shanghai,
 * China. See the accompanying Manual for the contributors and the way to cite
 * this work. Comments and suggestions welcome. Please contact Dr. Guanghong Zuo
 * <ghzuo@fudan.edu.cn>
 *
 * @Author: Dr. Guanghong Zuo
 * @Date: 2018-07-31 15:49:27
 * @Last Modified By: Dr. Guanghong Zuo
 * @Last Modified Time: 2018-07-31 15:49:27
 */

#ifndef DISTMETH_H
#define DISTMETH_H

#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <regex>
#include <set>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

#ifdef _OPENMP
#include <omp.h>
#endif

#include "alnseq.h"
#include "distmatrix.h"
#include "info.h"
#include "stringOpt.h"

using namespace std;

struct DistMeth {
  // the create function
  static DistMeth *create(const string &);

  // execute the calculation
  void execute(AlnSeq &, Mdist &);

  // the virtual function for different methods
  virtual double dist(const Sequence &, const Sequence &) = 0;
};

// ... son class for different method
struct Qdist : public DistMeth {
  Qdist() = default;
  double dist(const Sequence &, const Sequence &) override;
};

#endif