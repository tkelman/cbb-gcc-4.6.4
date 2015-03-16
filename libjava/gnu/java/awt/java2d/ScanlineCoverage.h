
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __gnu_java_awt_java2d_ScanlineCoverage__
#define __gnu_java_awt_java2d_ScanlineCoverage__

#pragma interface

#include <java/lang/Object.h>
extern "Java"
{
  namespace gnu
  {
    namespace java
    {
      namespace awt
      {
        namespace java2d
        {
            class ScanlineCoverage;
            class ScanlineCoverage$Coverage;
            class ScanlineCoverage$Iterator;
        }
      }
    }
  }
}

class gnu::java::awt::java2d::ScanlineCoverage : public ::java::lang::Object
{

public:
  ScanlineCoverage();
  void rewind();
  void clear();
  void add(jint, jint, jint);
  jint getMaxCoverage();
public: // actually package-private
  void setMaxCoverage(jint);
public:
  jint getMaxX();
  jint getMinX();
private:
  ::gnu::java::awt::java2d::ScanlineCoverage$Coverage * findOrInsert(jint);
public:
  ::gnu::java::awt::java2d::ScanlineCoverage$Iterator * iterate();
  jboolean isEmpty();
public: // actually package-private
  static ::gnu::java::awt::java2d::ScanlineCoverage$Coverage * access$0(::gnu::java::awt::java2d::ScanlineCoverage *);
  static ::gnu::java::awt::java2d::ScanlineCoverage$Coverage * access$1(::gnu::java::awt::java2d::ScanlineCoverage *);
private:
  ::gnu::java::awt::java2d::ScanlineCoverage$Coverage * __attribute__((aligned(__alignof__( ::java::lang::Object)))) head;
  ::gnu::java::awt::java2d::ScanlineCoverage$Coverage * current;
  ::gnu::java::awt::java2d::ScanlineCoverage$Coverage * currentPrev;
  ::gnu::java::awt::java2d::ScanlineCoverage$Coverage * last;
  ::gnu::java::awt::java2d::ScanlineCoverage$Coverage * lastPrev;
  jint minX;
  jint maxX;
  jint maxCoverage;
  ::gnu::java::awt::java2d::ScanlineCoverage$Iterator * iterator;
public: // actually package-private
  static jboolean $assertionsDisabled;
public:
  static ::java::lang::Class class$;
};

#endif // __gnu_java_awt_java2d_ScanlineCoverage__
