/*
 * Copyright (c) 2018  T-Life Research Center, Fudan University, Shanghai,
 * China. See the accompanying Manual for the contributors and the way to cite
 * this work. Comments and suggestions welcome. Please contact Dr. Guanghong Zuo
 * <ghzuo@fudan.edu.cn>
 *
 * @Author: Dr. Guanghong Zuo
 * @Date: 2018-07-31 15:50:49
 * @Last Modified By: Dr. Guanghong Zuo
 * @Last Modified Time: 2018-07-31 15:50:50
 */

#include "distmeth.h"
extern Info theInfo;

/// the create function
DistMeth *DistMeth::create(const string &methStr) {

  // create the distance method
  DistMeth *meth;
  if (methStr == "Qdist") {
    meth = new Qdist();
  } else {
    cerr << "Unknow Distance Method: " << methStr << endl;
    exit(3);
  }
  return meth;
}

void DistMeth::execute(AlnSeq &seqs, Mdist &dm) {
  // for the intro-distances between the genomes
  vector<pair<size_t, size_t>> nanList;
  for (auto i = 0; i < dm.size(); ++i) {
    for (auto j = i + 1; j < dm.size(); ++j) {
      if (dm.isNAN(i, j)) {
        nanList.emplace_back(make_pair(i, j));
      }
    }
  }

#pragma omp parallel for
  for (auto i = 0; i < nanList.size(); ++i) {
    dm.setdist(
        nanList[i].first, nanList[i].second,
        dist(seqs.getseq(nanList[i].first), seqs.getseq(nanList[i].second)));
  }
  return;
};

///.........................
/// Three method based on vector
double Qdist::dist(const Sequence &sa, const Sequence &sb) {

  double dist(0.0);
  for (int i = 0; i < sa.size(); ++i) {
    if (sa[i] != sb[i]) {
      ++dist;
    }
  }

  return dist;
};