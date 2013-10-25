/*
 * @(#)mclcommain.h    generated by: makeheader 5.1.5  Thu Jan 15 20:32:38 2009
 *
 *		built from:	../../src/include/copyright.h
 *				../../src/include/pragma_interface.h
 *				mclcommain.cpp
 */

#if defined(_MSC_VER) || __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ > 3)
#pragma once
#endif

#ifndef mclcommain_h
#define mclcommain_h


/*
 * Copyright 1984-2003 The MathWorks, Inc.
 * All Rights Reserved.
 */



/* Copyright 2003-2006 The MathWorks, Inc. */

/* Only define EXTERN_C if it hasn't been defined already. This allows
 * individual modules to have more control over managing their exports.
 */
#ifndef EXTERN_C

#ifdef __cplusplus
  #define EXTERN_C extern "C"
#else
  #define EXTERN_C extern
#endif

#endif


#ifdef __cplusplus
    extern "C" {
#endif


/* Register a MatLab Excel Builder component */
extern HRESULT mclRegisterMatLabComponent(const char* szModuleName,     /* DLL module handle */
                                const CLSID* clsid,           /* Class ID */
                                const GUID* libid,            /* GUID of TypeLib */
                                unsigned short wMajorRev,     /* Major rev of type lib */
                                unsigned short wMinorRev,     /* Minor rev of type lib */
                                const char* szFriendlyName,   /* Friendly Name */
                                const char* szVerIndProgID,   /* Programmatic */
                                const char* szProgID)         /* IDs */;


/* Unregister a MatLab Excel Builder component */
extern HRESULT mclUnRegisterMatLabComponent(const CLSID* clsid,         /* Class ID */
                                  const char* szVerIndProgID, /* Programmatic */
                                  const char* szProgID)       /* IDs */;


/* 
   Aquire global lock. Returns 0 for successful aquisition, -1 otherwise.
   If the global mutex is not initialized, or if the wait function fails,
   -1 is returned.
*/
extern int RequestGlobalLock(void);


/* 
   Release global lock. Returns 0. If the global mutex is not initialized,
   -1 is returned.
*/
extern int ReleaseGlobalLock(void);


extern HRESULT GetConversionFlags(IMWFlags* pFlags, MCLCONVERSION_FLAGS flags);


/* Converts an mxArray to a Variant */
extern int mxArray2Variant(const mxArray* px, VARIANT* pvar, const MCLCONVERSION_FLAGS flags);


/* Converts a Variant to an mxArray */
extern int Variant2mxArray(const VARIANT* pvar, mxArray** ppx, const MCLCONVERSION_FLAGS flags);


/* 
   If input VARIANT is VT_ERROR && v->scode == DISP_E_PARAMNOTFOUND, returns true. 
   Returns false otherwise. If input variant is *|VT_BYREF and reference is NULL, returns true. 
   If input variant pointer is NULL, returns true.
*/
extern bool IsVisualBasicDefault(const VARIANT *v);


extern void InitConversionFlags(MCLCONVERSION_FLAGS flags);


extern const char* GetCOMErrorMessage(int ret);


extern bool mclComCheckMWComUtil();


extern bool mclComCheckMWComMgr();


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* mclcommain_h */
