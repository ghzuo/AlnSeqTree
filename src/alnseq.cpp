/*
 * Copyright (c) 2018  T-Life Research Center, Fudan University, Shanghai,
 * China. See the accompanying Manual for the contributors and the way to cite
 * this work. Comments and suggestions welcome. Please contact Dr. Guanghong Zuo
 * <ghzuo@fudan.edu.cn>
 *
 * @Author: Dr. Guanghong Zuo
 * @Date: 2016-04-19 11:37:42
 * @Last Modified By: Dr. Guanghong Zuo
 * @Last Modified Time: 2018-07-26 22:02:45
 */

#include "alnseq.h"

size_t AlnSeq::readFasta(string &file) {
  ifstream infile(file.c_str());
  if (!infile) {
    cerr << "Cannot found the input file " << file << endl;
    exit(4);
  }
  // cout << " Read file: " << file << endl;

  for (string line; getline(infile, line);) {
    line = trim(line);
    if (line.empty() || line[0] == ';') {

    } else if (line[0] == '>') {
      names.emplace_back(line.substr(line.find_first_not_of("> ")));
      seqs.emplace_back();
    } else if (!seqs.empty()) {
      seqs.back().append(line);
    }
  }
  infile.close();

  // check the name
  for (auto &s : names) {
    transform(
        s.begin(), s.end(), s.begin(),
        [](unsigned char c) -> unsigned char { return c == '/' ? '_' : c; });
  }

  // check the sequence
  for (auto &s : seqs) {
    if (s.size() == 0) {
      cerr << "Some empty sequence in your file: " << file << endl;
      exit(5);
    } else {
      transform(s.begin(), s.end(), s.begin(),
                [](unsigned char c) -> unsigned char { return toupper(c); });
    }
  }
  return size();
};

string AlnSeq::getseq(size_t ndx) const { return seqs[ndx]; };

size_t AlnSeq::size() const { return names.size(); };

size_t AlnSeq::length() const { return seqs.front().size(); }

string AlnSeq::info() const {
  string str;
  str = "There are " + to_string(size()) + " sequecnes with length equal " +
        to_string(length()) + " letters";
  return str;
};
