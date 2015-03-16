
// DO NOT EDIT THIS FILE - it is machine generated -*- c++ -*-

#ifndef __gnu_CORBA_DynAn_gnuDynAnyFactory__
#define __gnu_CORBA_DynAn_gnuDynAnyFactory__

#pragma interface

#include <org/omg/CORBA/LocalObject.h>
extern "Java"
{
  namespace gnu
  {
    namespace CORBA
    {
      namespace DynAn
      {
          class gnuDynAnyFactory;
      }
      namespace Poa
      {
          class ORB_1_4;
      }
    }
  }
  namespace org
  {
    namespace omg
    {
      namespace CORBA
      {
          class Any;
          class TypeCode;
      }
      namespace DynamicAny
      {
          class DynAny;
          class DynArray;
          class DynEnum;
          class DynFixed;
          class DynSequence;
          class DynStruct;
          class DynUnion;
          class DynValue;
          class DynValueBox;
      }
    }
  }
}

class gnu::CORBA::DynAn::gnuDynAnyFactory : public ::org::omg::CORBA::LocalObject
{

public:
  gnuDynAnyFactory(::gnu::CORBA::Poa::ORB_1_4 *);
  virtual ::gnu::CORBA::Poa::ORB_1_4 * getOrb();
  virtual ::org::omg::DynamicAny::DynArray * create_array(::org::omg::CORBA::TypeCode *, ::org::omg::CORBA::TypeCode *);
  virtual ::org::omg::DynamicAny::DynSequence * create_sequence(::org::omg::CORBA::TypeCode *, ::org::omg::CORBA::TypeCode *);
  virtual ::org::omg::DynamicAny::DynStruct * create_structure(::org::omg::CORBA::TypeCode *, ::org::omg::CORBA::TypeCode *);
  virtual ::org::omg::DynamicAny::DynUnion * create_union(::org::omg::CORBA::TypeCode *, ::org::omg::CORBA::TypeCode *);
  virtual ::org::omg::DynamicAny::DynValue * create_value(::org::omg::CORBA::TypeCode *, ::org::omg::CORBA::TypeCode *);
  virtual ::org::omg::DynamicAny::DynValueBox * create_value_box(::org::omg::CORBA::TypeCode *, ::org::omg::CORBA::TypeCode *);
  virtual ::org::omg::DynamicAny::DynEnum * create_enumeration(::org::omg::CORBA::TypeCode *, ::org::omg::CORBA::TypeCode *);
  virtual ::org::omg::DynamicAny::DynFixed * create_fixed(::org::omg::CORBA::TypeCode *, ::org::omg::CORBA::TypeCode *);
  virtual ::org::omg::DynamicAny::DynAny * create_alias(::org::omg::CORBA::TypeCode *, ::org::omg::CORBA::TypeCode *);
  virtual ::org::omg::DynamicAny::DynAny * create_simple(::org::omg::CORBA::TypeCode *, ::org::omg::CORBA::TypeCode *);
  virtual ::org::omg::DynamicAny::DynAny * create_dyn_any_from_type_code(::org::omg::CORBA::TypeCode *);
  virtual ::org::omg::DynamicAny::DynAny * create_dyn_any_from_type_code(::org::omg::CORBA::TypeCode *, ::org::omg::CORBA::TypeCode *);
  virtual ::org::omg::DynamicAny::DynAny * create_dyn_any(::org::omg::CORBA::Any *);
private:
  static const jlong serialVersionUID = 1LL;
public: // actually package-private
  ::gnu::CORBA::Poa::ORB_1_4 * __attribute__((aligned(__alignof__( ::org::omg::CORBA::LocalObject)))) orb;
public:
  static ::java::lang::Class class$;
};

#endif // __gnu_CORBA_DynAn_gnuDynAnyFactory__