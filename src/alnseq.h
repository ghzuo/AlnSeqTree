/*
 * Copyright (c) 2018  T-Life Research Center, Fudan University, Shanghai,
 * China. See the accompanying Manual for the contributors and the way to cite
 * this work. Comments and suggestions welcome. Please contact Dr. Guanghong Zuo
 * <ghzuo@fudan.edu.cn>
 *
 * @Author: Dr. Guanghong Zuo
 * @Date: 2016-04-19 11:37:42
 * @Last Modified By: Dr. Guanghong Zuo
 * @Last Modified Time: 2018-07-26 22:02:50
 */

#ifndef ALNSEQ_H
#define ALNSEQ_H

#include <cctype>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

#include "stringOpt.h"
using namespace std;

// Type for genome name
typedef string GenName;

// type for sequence
typedef string Sequence;

struct AlnSeq {
  vector<GenName> names;
  vector<Sequence> seqs;

  size_t readFasta(string &);
  string getseq(size_t ndx) const;

  size_t size() const;
  size_t length() const;
  string info() const;
};

#endif
