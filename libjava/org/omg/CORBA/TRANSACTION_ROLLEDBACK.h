
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __org_omg_CORBA_TRANSACTION_ROLLEDBACK__
#define __org_omg_CORBA_TRANSACTION_ROLLEDBACK__

#pragma interface

#include <org/omg/CORBA/SystemException.h>
extern "Java"
{
  namespace org
  {
    namespace omg
    {
      namespace CORBA
      {
          class CompletionStatus;
          class TRANSACTION_ROLLEDBACK;
      }
    }
  }
}

class org::omg::CORBA::TRANSACTION_ROLLEDBACK : public ::org::omg::CORBA::SystemException
{

public:
  TRANSACTION_ROLLEDBACK(::java::lang::String *);
  TRANSACTION_ROLLEDBACK();
  TRANSACTION_ROLLEDBACK(jint, ::org::omg::CORBA::CompletionStatus *);
  TRANSACTION_ROLLEDBACK(::java::lang::String *, jint, ::org::omg::CORBA::CompletionStatus *);
private:
  static const jlong serialVersionUID = -343903462439281571LL;
public:
  static ::java::lang::Class class$;
};

#endif // __org_omg_CORBA_TRANSACTION_ROLLEDBACK__