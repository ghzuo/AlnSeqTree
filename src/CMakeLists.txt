###
# Copyright (c) 2018  T-Life Research Center, Fudan University, Shanghai, China.
# See the accompanying Manual for the contributors and the way to cite this work.
# Comments and suggestions welcome. Please contact
# Dr. Guanghong Zuo <ghzuo@fudan.edu.cn>
# 
# @Author: Dr. Guanghong Zuo
# @Date: 2017-09-01 15:55:03
# @Last Modified By: Dr. Guanghong Zuo
# @Last Modified Time: 2018-04-26 19:51:32
###

LINK_LIBRARIES(libastr.a)

SET(ASTREEHEADS 
  alnseq.h stringOpt.h
  distmatrix.h info.h
  treemeth.h distmeth.h)

SET(LIBASTREE_SRC ${ASTREEHEADS}
  alnseq.cpp  stringOpt.cpp 
  distmatrix.cpp tree.cpp
  info.cpp treemeth.cpp 
  distmeth.cpp)

SET(DIST_SRC ${ASTREEHEADS}
  as2dm.h as2dm.cpp)

SET(GETDIST_SRC ${ASTREEHEADS}
  getdist.cpp)

SET(MCONV_SRC ${ASTREEHEADS}
  mconv.cpp)

SET(DIFFMTX_SRC ${ASTREEHEADS} diffMatrix.cpp)

SET(NJ_SRC ${ASTREEHEADS}
  dm2tree.h dm2tree.cpp)

SET(ASTREE_SRC ${ASTREEHEADS}
  astree.h astree.cpp)

ADD_LIBRARY(astr STATIC ${LIBASTREE_SRC})

ADD_EXECUTABLE(as2dm ${DIST_SRC})
TARGET_LINK_LIBRARIES(as2dm astr)

ADD_EXECUTABLE(getdist ${GETDIST_SRC})
TARGET_LINK_LIBRARIES(getdist astr)

ADD_EXECUTABLE(mconv ${MCONV_SRC})
TARGET_LINK_LIBRARIES(mconv astr)

ADD_EXECUTABLE(diffmtx ${DIFFMTX_SRC})
TARGET_LINK_LIBRARIES(diffmtx astr)

ADD_EXECUTABLE(dm2tree ${NJ_SRC})
TARGET_LINK_LIBRARIES(dm2tree astr)

ADD_EXECUTABLE(astree ${ASTREE_SRC})
TARGET_LINK_LIBRARIES(astree astr)

INSTALL(TARGETS as2dm getdist diffmtx dm2tree astree mconv
   RUNTIME DESTINATION bin)
