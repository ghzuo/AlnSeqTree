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

#include "as2dm.h"
Info theInfo;

int main(int argc, char *argv[]) {
  // get the input arguments
  Args myargs(argc, argv);

  // read aligned sequences
  AlnSeq as;
  as.readFasta(myargs.infile);
  theInfo(as.info());

  // init the distance matrix by species list
  Mdist dm;
  dm.init(as.names);

  // assign the dm by reference DMs
  dm.assign(myargs.refdm);
  theInfo(dm.info());

  if (dm.hasNAN()) {
    theInfo("Start distance calculate");

    // do the calculation of distance
    myargs.meth->execute(as, dm);

    theInfo("End the distance calculate");
  }

  // output the distance matrix
  dm.writemtx(myargs.outfile);
}

/*********************************************************************/
/******************** End of Main programin **************************/
/*********************************************************************/

Args::Args(int argc, char **argv) : outfile(""), infile("input.fasta") {

  program = argv[0];
  string methStr("Qdist");

  char ch;
  while ((ch = getopt(argc, argv, "i:o:m:r:qh")) != -1) {
    switch (ch) {
    case 'r':
      refdm = optarg;
      break;
    case 'm':
      methStr = optarg;
      break;
    case 'o':
      outfile = optarg;
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
  meth = DistMeth::create(methStr);

  // set the outfile name
  if (outfile.empty()) {
#ifdef _NETCDF
    outfile = methStr + ".nc";
#elif _HDF5
    outfile = methStr + ".h5";
#else
    outfile = methStr + ".txt";
#endif
  }
}

void Args::usage() {
  cerr << "\nProgram Usage: \n\n"
       << program << "\n"
       << " [ -o <dm> ]       Output distance matrix, default: <Method>.h5\n"
       << " [ -i input.fasta ]  Genome list for distance matrix\n"
       << " [ -r <matrix> ]   Reference distance matrices, split with ','\n"
       << " [ -m Qdist ]      Method for distance, default: Qdist\n"
       << " [ -q ]            Run command in quiet mode\n"
       << " [ -h ]            Display this information\n"
       << endl;
  exit(1);
}