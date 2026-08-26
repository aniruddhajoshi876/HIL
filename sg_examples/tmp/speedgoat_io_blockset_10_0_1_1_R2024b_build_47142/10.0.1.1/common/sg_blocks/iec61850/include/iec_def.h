#ifndef __IEC_DEF_H
#define __IEC_DEF_H

#include "stdint.h"
#include <map>
#include <list>
#include "iec61850_server.h"
#include <vector>

#pragma pack(push, 1)

#ifndef MATLAB_MEX_FILE

#ifndef NULL
#ifdef __cplusplus
#define NULL 0
#else
#define NULL ((void*)0)
#endif
#endif

#endif

/* Suppress Warnings for GCC and CLANG*/
#define DO_PRAGMA(X) _Pragma(#X)

#define DISABLE_WARNING_PUSH /*<-- Begin with this line before ignoring code*/ _Pragma("GCC diagnostic push")

/* Choose warnings to disable (put before ignoring code) */
#define DISABLE_WARNING(warningName) DO_PRAGMA(GCC diagnostic ignored #warningName) //put warning between parenthesis-> DISABLE_WARNING(-Wunused-variable)

#define DISABLE_WARNING_POP /*<-- End with this line (after ignoring code*/ _Pragma("GCC diagnostic pop")
/* ************************** */

#define IEC_MAX_NUM_BLOCKS           1024

#define IEC_MODULE_TYPE_UNDEF    0x00000000
#define IEC_NODE_TYPE_CLIENT     0x00000001
#define IEC_NODE_TYPE_SERVER     0x00000002
#define IEC_NODE_TYPE_GOOSE      0x00000003
#define IEC_NODE_TYPE_SV		 0x00000004

#define IEC_BLOCK_TYPE_UNDEF             	0x00000000
#define IEC_BLOCK_TYPE_SERVER_SETUP      	0x00000001
#define IEC_BLOCK_TYPE_SERVER_READ       	0x00000002
#define IEC_BLOCK_TYPE_GOOSE_PUB           	0x00000003
#define IEC_BLOCK_TYPE_GOOSE_SUB           	0x00000004
#define IEC_BLOCK_TYPE_CLIENT_SETUP      	0x00000005
#define IEC_BLOCK_TYPE_CLIENT_CONNECTION	0x00000006
#define IEC_BLOCK_TYPE_CLIENT_TRANSCEIVER	0x00000007
#define IEC_BLOCK_TYPE_SV_PUB           	0x00000008
#define IEC_BLOCK_TYPE_SV_SUB           	0x00000009

#define IEC_DOUBLE 	8
#define IEC_FLOAT 	4
#define IEC_INT8 	1
#define IEC_UINT8 	1
#define IEC_INT16 	2
#define IEC_UINT16	2
#define IEC_INT32 	4
#define IEC_UINT32 	4
#define IEC_BOOLEAN	1

#define IEC_ERROR_OFFSET                 -500

#define IEC_REQUEST_DATAMODEL			 -99

#define IEC_READ						 0
#define IEC_WRITE						 1

#define IEC_NO_ERROR                     0
#define IEC_ERROR_GENERAL                IEC_ERROR_OFFSET-1
#define IEC_ERROR_NODE_NOT_FOUND         IEC_ERROR_OFFSET-2
#define IEC_ERROR_MODULE_NOT_INIT        IEC_ERROR_OFFSET-4
#define IEC_ERROR_REMOTE_NOT_INIT        IEC_ERROR_OFFSET-5
#define IEC_ERROR_LICENSE                IEC_ERROR_OFFSET-6

#define IEC_ERROR_CODE_BASE              0x80
#define IEC_EXEPTION_FC                  0x01
#define IEC_EXEPTION_INDEX               0x02
#define IEC_EXEPTION_LENGTH              0x03
#define IEC_EXEPTION_PROCESS             0x04

#define IEC_MAX_STRING_SIZE				255
#define IEC_MAX_REPORTING_PORTS			100

#define IEC_MAX_RX_LOAD                  TCP_MAXWIN
#define IEC_MAX_TX_LOAD                  1500

#define IEC_IDLE_DELAY                  10000 // ~10us
#define IEC_SV_DELAY                      100 // ~100ns
#define IEC_GO_DELAY                     1000 // ~1us

#ifndef SS_DOUBLE
#define SS_DOUBLE 0 /* real_T    */
#endif

#ifndef SS_SINGLE
#define SS_SINGLE 1 /* real32_T  */
#endif

#ifndef SS_INT8
#define SS_INT8 2   /* int8_T    */
#endif

#ifndef SS_UINT8
#define SS_UINT8 3  /* uint8_T   */
#endif

#ifndef SS_INT16
#define SS_INT16 4  /* int16_T   */
#endif

#ifndef SS_UINT16
#define SS_UINT16 5 /* uint16_T  */
#endif

#ifndef SS_INT32
#define SS_INT32 6  /* int32_T   */
#endif

#ifndef SS_UINT32
#define SS_UINT32 7 /* uint32_T  */
#endif

#ifndef SS_BOOLEAN
#define SS_BOOLEAN 8 /* boolean_T */
#endif

#ifndef SS_VISIBLE_STRING_UINT8
#define SS_VISIBLE_STRING_UINT8 9 /* uint8_T vector */ //ASCII
#endif

#ifndef SS_BIT_STRING
#define SS_BIT_STRING 10 /* uint32_T  */
#endif

#ifndef SS_STRING_UINT8
#define SS_STRING_UINT8 11 /* uint8_T vector */ //UNICODE
#endif

#ifndef SS_ARRAY
#define SS_ARRAY 12
#endif

#ifndef SS_STRUCTURE
#define SS_STRUCTURE 13
#endif

#ifndef SS_OCTET_STRING
#define SS_OCTET_STRING 14 /* boolean_T */
#endif

#ifndef SS_UTC_TIME
#define SS_UTC_TIME 15 /* uint64_T */ // Time in [ms]
#endif

namespace iec61850
{

struct iedArgs{
	std::vector<DataObject> *DAControl;
	IedModel iecModel;
	IedServer iedServer;
};

struct SVSubPar{
	int8_t* DataIn;
	uint32_t DataType;
	uint8_t NumVars;
};

}

//template<typename Iterator, typename T>
//void replace(Iterator begin, Iterator end, const T& old_val, const T& new_val)
//{
//    for (; begin != end; ++begin)
//        if (*begin == old_val) *begin = new_val;
//}

/******************************************************************************/
/*
 * (C) Copyright Christopher Diggins 2005-2011
 * (C) Copyright Pablo Aguilar 2005
 * (C) Copyright Kevlin Henney 2001
 *
 * Distributed under the Boost Software License, Version 1.0. (See
 * accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt
 */

#include <stdexcept>

namespace cdiggins
{
namespace anyimpl {

     struct empty_any {
        };

     struct base_any_policy {

        virtual void static_delete(void** x) = 0;

        virtual void copy_from_value(void const* src, void** dest) = 0;

        virtual void clone(void* const* src, void** dest) = 0;

        virtual void move(void* const* src, void** dest) = 0;

        virtual void* get_value(void** src) = 0;

        virtual void* get_value(void* const * src) const = 0;

        virtual size_t get_size() = 0;

        };

     template<typename T>
     struct typed_base_any_policy : base_any_policy {
        virtual size_t get_size() { return sizeof(T); }
        };

     template<typename T>
     struct small_any_policy : typed_base_any_policy<T> {

        virtual void static_delete(void** x) override { }

        virtual void copy_from_value(void const* src, void** dest) {
           //This used to be:
           //new(dest) T(*reinterpret_cast<T const*>(src));
           //But this is the small_any_policy, and ints and other small objects
           //shouldn't need to be pointed to by an object.  So a simple 'clone',
           //or move will suffice, so use the same code as them:
           //*dest = const_cast<void*>(src);
           //In this case, we are really receiving the address of the the 'object' variable
            *dest = *(reinterpret_cast<void**>((const_cast<void*>(src))));
           }

        virtual void clone(void* const* src, void** dest) { *dest = *src; }

        virtual void move(void* const* src, void** dest) { *dest = *src; }

        virtual void* get_value(void** src) { return reinterpret_cast<void*>(src); }

        void* get_value(void* const * src) const override {
           return reinterpret_cast<void*>(const_cast<void**>(src));
           }

        };

     template<typename T>
     struct big_any_policy : typed_base_any_policy<T> {
        virtual void static_delete(void** x) override {
           if (*x)
              delete(*reinterpret_cast<T**>(x));
           *x = NULL;
           }

        virtual void copy_from_value(void const* src, void** dest) {
           *dest = new T(*reinterpret_cast<T const*>(src));
           }

        virtual void clone(void* const* src, void** dest) {
           *dest = new T(**reinterpret_cast<T* const*>(src));
           }

        virtual void move(void* const* src, void** dest) {
          (*reinterpret_cast<T**>(dest))->~T();
          **reinterpret_cast<T**>(dest) = **reinterpret_cast<T* const*>(src);
          }

        virtual void* get_value(void** src) { return *src; }

        void* get_value(void* const * src) const override { return *const_cast<void**>(src); }

     };

     template<typename T>
     struct choose_policy {
        typedef big_any_policy<T> type;
        };

     template<typename T>
     struct choose_policy<T*> {
        typedef small_any_policy<T*> type;
        };

     struct any; //Forward declaration

     /// Choosing the policy for an any type is illegal, but should never happen.
     /// This is designed to throw a compiler error.
     template<>
     struct choose_policy<any> {
        typedef void type;
        };

     /// Specializations for small types.
     #define SMALL_POLICY(TYPE) template<> struct choose_policy<TYPE> { \
                 typedef small_any_policy<TYPE> type; };

     SMALL_POLICY(signed char);
     SMALL_POLICY(unsigned char);
     SMALL_POLICY(signed short);
     SMALL_POLICY(unsigned short);
     SMALL_POLICY(signed int);
     SMALL_POLICY(unsigned int);
     SMALL_POLICY(signed long);
     SMALL_POLICY(unsigned long);
     SMALL_POLICY(float);
     SMALL_POLICY(bool);

     #undef SMALL_POLICY

     /// This function will return a different policy for each type.
     template<typename T>
     base_any_policy* get_policy() {
        static typename choose_policy<T>::type policy;
        return &policy;
        };

     }  //End of anyimpl namespace

     struct any {
        private:
           // fields
           anyimpl::base_any_policy* policy;
           void* object;

        public:
           /// Initializing constructor.
           template <typename T>
           //This used to be:
           //any(const T& x) : policy(anyimpl::get_policy<anyimpl::empty_any>()),
           //          object(NULL) {
           //I am changing it to force the initial construction to use the small_policy:
           any(const T& x) : policy(anyimpl::get_policy<unsigned int>()), object(NULL) { // @suppress("Symbol is not resolved")
              assign(x);
              }

           /// Empty constructor.
           //This used to be:
           //any() : policy(anyimpl::get_policy<anyimpl::empty_any>()), object(NULL) {
           //But why should an empty 'any' receive a default 'big_any_policy'???
           //This starts calling 'new' and 'delete' under the hood.
           //So let's try the following to force a small_policy:
           any() : policy(anyimpl::get_policy<unsigned int>()), object(NULL) { // @suppress("Symbol is not resolved")
              }

           /// Special initializing constructor for string literals.
           any(const char* x) : policy(anyimpl::get_policy<anyimpl::empty_any>()),
                       object(NULL) { // @suppress("Symbol is not resolved")

              assign(x);
              }

           /// Copy constructor.
           any(const any& x) : policy(anyimpl::get_policy<anyimpl::empty_any>()),
                       object(NULL) { // @suppress("Symbol is not resolved")

              assign(x);
              }

           /// Destructor.
           ~any() {
              policy->static_delete(&object);
              }

           /// Assignment function from another any.
           any& assign(const any& x) {
              reset();
              policy = x.policy;
              policy->clone(&x.object, &object);
              return *this;
              }

           /// Assignment function.
           template <typename T>
           any& assign(const T& x) {
              reset();
              policy = anyimpl::get_policy<T>();
              policy->copy_from_value(&x, &object);
              return *this;
              }

           /// Assignment operator.
           template<typename T>
           any& operator=(const T& x) {
              return assign(x);
              }

           any& operator=(const any & x) {
              //Was:
              //policy = x.policy;
              //policy->copy_from_value(&x.object, &object);
              //return *this;
              //reset();
              return assign(x);
              }

           any& operator()(const any & x) {
              policy = x.policy;
              policy->copy_from_value(&x.object, &object);
              return *this;
              }

           /// Assignment operator, specialed for literal strings.
           /// They have types like const char [6] which don't work as expected.
           any& operator=(const char* x) {
              return assign(x);
              }

           /// Utility functions
           any& swap(any& x) {
              std::swap(policy, x.policy);
              std::swap(object, x.object);
              return *this;
              }

           /// Cast operator. You can only cast to the original type.
           template<typename T>
           T& cast() {
              if (policy != anyimpl::get_policy<T>()) {
            	  //was:
            	  //throw anyimpl::bad_any_cast();
                 }

              T* r = reinterpret_cast<T*>(policy->get_value(&object));
              return *r;
              }

           /// Returns true if the any contains no value.
           bool empty() const {
              return policy == anyimpl::get_policy<anyimpl::empty_any>();
              }

           /// Frees any allocated memory, and sets the value to NULL.
           void reset() {
              policy->static_delete(&object);
              //The following used to be:
              //policy = anyimpl::get_policy<anyimpl::empty_any>();
              //But why should the policy default to the big_any_policy?  Therefore,:
              policy = anyimpl::get_policy<unsigned int>();
              }

           /// Returns true if the two types are the same.
           template<typename T>
           bool isA() {
              return policy == anyimpl::get_policy<T>();
              }

            template <typename T> operator T&() { return cast<T>(); }
            template <typename T> operator T&() const { return cast<T>(); }

            template<typename T>
            T& cast() const {
                if (policy != anyimpl::get_policy<T>()) {
                	//was:
					//throw anyimpl::bad_any_cast();
                   }
                T* r = reinterpret_cast<T*>(policy->get_value(&object));
                return *r;
               }

        }; //End of 'any' struct definition

}
/******************************************************************************/

#pragma pack(pop)

#endif
