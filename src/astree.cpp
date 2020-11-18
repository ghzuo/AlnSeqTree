/*
 * Copyright (c) 2018  T-Life Research Center, Fudan University, Shanghai,
 * China. See the accompanying Manual for the contributors and the way to cite
 * this work. Comments and suggestions welcome. Please contact Dr. Guanghong Zuo
 * <ghzuo@fudan.edu.cn>
 *
 * @Author: Dr. Guanghong Zuo
 * @Date: 2018-04-26 10:40:55
 * @Last Modified By: Dr. Guanghong Zuo
 * @Last Modified Time: 2018-07-16 19:50:27
 */

#include "astree.h"

// for output infomation
Info theInfo;

int main(int argc, char *argv[]) {
  // get the input arguments
  Args myargs(argc, argv);

  // read aligned sequences
  AlnSeq seqs;
  seqs.readFasta(myargs.fasta);
  theInfo(seqs.info());

  // init domains
  Mdist dm;
  dm.init(seqs.names, false);
  dm.assign(myargs.refdm);
  theInfo(dm.info());

  // Calculate the NAN distance
  if (dm.hasNAN()) {
    theInfo("Start calculate");
    myargs.dmeth->execute(seqs, dm);
    theInfo("End the calculate distance");
  }

  // output the distance matrix
  mkpath(myargs.dmName);
  dm.writemtx(myargs.dmName);
  theInfo("DM Section: All Distance Matrices obtained");

  // check the genome number bigger than 3
  if (seqs.size() < 3) {
    theInfo("There are only " + to_string(seqs.size()) +
            " genomes, no tree will output");
    exit(2);
  }

  // get the nwk tree
  // do the NJ algorithm and return the NJ tree
  theInfo("Start Neighbor Joint to Get Tree");
  Node *aTree = myargs.tmeth->tree(dm);

  // output the Tree
  mkpath(myargs.treeName);
  ofstream nwk(myargs.treeName.c_str());
  (*aTree).outnwk(nwk);
  nwk.close();
  theInfo("TREE Section: All Phylogenetic Tree obtained");
}

/*********************************************************************/
/******************** End of Main programin **************************/
/*********************************************************************/

Args::Args(int argc, char **argv)
    : fasta("input.fasta"), treeName(""), dmName("") {

  program = argv[0];
  bool refself(false);
  string methStr("Qdist:NJ");

  char ch;
  while ((ch = getopt(argc, argv, "i:d:t:m:r:g:Rqh")) != -1) {
    switch (ch) {
    case 'i':
      fasta = optarg;
      break;
    case 'r':
      refdm = optarg;
      break;
    case 'R':
      refself = true;
      break;
    case 'm':
      methStr = optarg;
      break;
    case 'd':
      dmName = optarg;
      break;
    case 't':
      treeName = optarg;
      break;
    case 'q':
      theInfo.quiet = true;
      break;
    case 'h':
      usage();
    case '?':
      usage();
    }
  }

  // set the method
  vector<string> mlist;
  separateWord(mlist, methStr, ":");
  dmeth = DistMeth::create(mlist[0]);
  if (mlist.size() > 1) {
    tmeth = TreeMeth::create(mlist[1]);
  } else {
    tmeth = TreeMeth::create("NJ");
  }

  // set the output tree name format
  if (treeName.empty()) {
    treeName = methStr + ".nwk";
  }

  // set the output dm name format
  if (dmName.empty()) {
#ifdef _NETCDF
    dmName = methStr + ".nc";
#elif _HDF5
    dmName = methStr + ".h5";
#else
    dmName = methStr + ".txt";
#endif
  }

  // refer self distance matrix
  if (refself) {
    if (refdm.empty()) {
      refdm = dmName;
    } else {
      refdm += "," + dmName;
    }
  }
}

void Args::usage() {
  cerr << "\nProgram Usage: \n\n"
       << program << "\n"
       << " [ -d <dm> ]      Output distance matrix name, default: "
          "<Method>.<suffix>\n"
       << " [ -t <nwk> ]     Output newick file name, default: "
          "<Method>.nwk\n"
       << " [ -i input.fasta ] Genome list for calculating, default: list\n"
       << " [ -r <matrix> ]  Reference distance matrices, split with ','\n"
       << " [ -R ]           Refer the output distance matrix\n"
       << " [ -m Qdist:NJ ]  Method for astree, default: Qdist:NJ\n"
       << " [ -q ]           Run command in quiet mode\n"
       << " [ -h ]           Display this information\n"
       << endl;
  exit(1);
}

void mkpath(const string &nm) {
  size_t npos = 0;
  while ((npos = nm.find("/", npos)) != std::string::npos) {
    string dir = nm.substr(0, npos);
    mkdir(dir.c_str(), 0755);
    npos++;
  }
}