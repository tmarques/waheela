
/*
 *
 * This software is released under the provisions of the GPL version 2.
 * see file "COPYING".  If that file is not available, the full statement 
 * of the license can be found at
 *
 * http://www.fsf.org/licensing/licenses/gpl.txt
 *
 * Portions Copyright (c) 1995-2004 RealNetworks, Inc. All Rights Reserved.
 *
 */

#ifndef _HXAUTH_H_
#define _HXAUTH_H_

/*
 * Forward declarations of some interfaces defined or used here-in.
 */
typedef _INTERFACE  IHXAuthenticator		    IHXAuthenticator;
typedef _INTERFACE  IHXAuthenticatorResponse	    IHXAuthenticatorResponse;
typedef _INTERFACE  IHXAuthenticatorRequest	    IHXAuthenticatorRequest;
typedef _INTERFACE  IHXPassword		    IHXPassword;
typedef _INTERFACE  IHXAuthenticationManagerResponse IHXAuthenticationManagerResponse;
typedef _INTERFACE  IHXValues			    IHXValues;
typedef _INTERFACE  IHXBuffer			    IHXBuffer;

/****************************************************************************
 * 
 *  Interface:
 * 
 *      IHXAuthenticator
 * 
 *  Purpose:
 * 
 *      Provide a means of authenticating users.
 *
 *  IID_IHXAuthenticator:
 * 
 *      {00001800-0901-11d1-8B06-00A024406D59}
 * 
 */

DEFINE_GUID(IID_IHXAuthenticator, 0x00001800, 0x901, 0x11d1, 0x8b, 0x6, 0x0, 
			0xa0, 0x24, 0x40, 0x6d, 0x59);

#define CLSID_IHXAuthenticator IID_IHXAuthenticator

#undef  INTERFACE
#define INTERFACE IHXAuthenticator

DECLARE_INTERFACE_(IHXAuthenticator, IUnknown)
{
    STDMETHOD(QueryInterface)           (THIS_
					REFIID riid,
					void** ppvObj) PURE;

    STDMETHOD_(ULONG32,AddRef)          (THIS) PURE;

    STDMETHOD_(ULONG32,Release)         (THIS) PURE;

    /*
     * InitAuthenticator is called by the creator of the Authenticator
     * object in order to pass it an IHXAuthenticatorRequest object,
     * usually implemented by the creator itself.
     */
    STDMETHOD(InitAuthenticator) (THIS_ 
				  IHXAuthenticatorRequest* pRequest) PURE;
    /*
     * Authenticate is called by a file object (and others??)
     * when it wants to ask the creator, presumably an FS Manager,
     * for authorization to open it's file.
     *
     * Authenticate will call IHXAuthenticateResponse::AuthenticateDone
     * when done with HXR_OK or an error.
     *
     * File objects will presumably perform the Authenticate response as
     * part of their Init() call, and not call InitDone until they receive
     * a response one way or the other.
     */
    STDMETHOD(Authenticate) (THIS_
			     IHXValues* pValues,
			     IHXAuthenticatorResponse* pResponse) PURE;

    /* GenerateAuthRequest is called by the creator of this object
     * when they want to send an authentication request to someone.
     */
    STDMETHOD(GenerateAuthRequest) (THIS_
				    UINT32 authType,
				    REF(IHXValues*) pValues) PURE;
    /*
     * AuthValuesReady is called by IHXAuthenticatorRequest when it
     * is ready to respond to a GetAuthValues request.
     */
    STDMETHOD(AuthValuesReady) (THIS_ 
				HX_RESULT result,
				IHXValues* pValues) PURE;
};


/****************************************************************************
 * 
 *  Interface:
 * 
 *      IHXAuthenticatorResponse
 * 
 *  Purpose:
 *
 *      Response object for the Authenticator class.
 * 
 *  IID_IHXAuthenticatorResponse:
 * 
 *      {00001801-0901-11d1-8B06-00A024406D59}
 * 
 */

DEFINE_GUID(IID_IHXAuthenticatorResponse, 0x00001801, 0x901, 0x11d1, 0x8b, 0x6, 0x0, 
			0xa0, 0x24, 0x40, 0x6d, 0x59);

#undef  INTERFACE
#define INTERFACE IHXAuthenticatorResponse

DECLARE_INTERFACE_(IHXAuthenticatorResponse, IUnknown)
{
    STDMETHOD(QueryInterface)           (THIS_
					REFIID riid,
					void** ppvObj) PURE;

    STDMETHOD_(ULONG32,AddRef)          (THIS) PURE;

    STDMETHOD_(ULONG32,Release)         (THIS) PURE;

    /* AuthenticateDone is called by an IHXAuthenticator when it has
     * finished it's authorization steps.  If the result is HXR_OK,
     * then the values contain authorization information as generated by
     * IHXPassword.
     */
    STDMETHOD(AuthenticateDone) (THIS_ HX_RESULT result,
				IHXValues* pAuthResponseValues) PURE;
};


/****************************************************************************
 * 
 *  Interface:
 * 
 *      IHXAuthenticatorRequest
 * 
 *  Purpose:
 *
 *      Request object for the Authenticator class.
 * 
 *  IID_IHXAuthenticatorRequest:
 * 
 *      {00001802-0901-11d1-8B06-00A024406D59}
 * 
 */

DEFINE_GUID(IID_IHXAuthenticatorRequest, 0x00001802, 0x901, 0x11d1, 0x8b, 0x6, 0x0, 
			0xa0, 0x24, 0x40, 0x6d, 0x59);

#undef  INTERFACE
#define INTERFACE IHXAuthenticatorRequest

DECLARE_INTERFACE_(IHXAuthenticatorRequest, IUnknown)
{
    STDMETHOD(QueryInterface)           (THIS_
					REFIID riid,
					void** ppvObj) PURE;

    STDMETHOD_(ULONG32,AddRef)          (THIS) PURE;

    STDMETHOD_(ULONG32,Release)         (THIS) PURE;

    /* GetAuthValues is called by the Authenticator object when it
     * needs to know the authorization info for this transaction.
     *
     * This object should call AuthValuesReady when ready.
     */
    STDMETHOD(GetAuthValues) (THIS_ IHXValues* pOrigValues) PURE;
};


/****************************************************************************
 * 
 *  Interface:
 * 
 *      IHXPassword
 * 
 *  Purpose:
 * 
 *      Provides a general password facility for storing of passwords in
 *	an encrypted form and a facility for verifying passwords securely
 *	over the network.
 * 
 *  IID_IHXPassword:
 * 
 *      {00001700-0901-11d1-8B06-00A024406D59}
 * 
 */

#define HX_AUTH_BASIC	1
#define HX_AUTH_DIGEST	2
#define PN_AUTH_HX5	3
#define HX_AUTH_NTLM	4

DEFINE_GUID(IID_IHXPassword, 0x00001700, 0x901, 0x11d1, 0x8b, 0x6, 0x0, 
			0xa0, 0x24, 0x40, 0x6d, 0x59);

#undef  INTERFACE
#define INTERFACE IHXPassword

DECLARE_INTERFACE_(IHXPassword, IUnknown)
{
    /*
     *  IUnknown methods
     */
    STDMETHOD(QueryInterface)           (THIS_
					REFIID riid,
					void** ppvObj) PURE;

    STDMETHOD_(ULONG32,AddRef)          (THIS) PURE;

    STDMETHOD_(ULONG32,Release)         (THIS) PURE;

    /*
     *  IHXPassword methods
     */

    STDMETHOD(Crypt) (THIS_ IHXValues* pAuthentication) PURE;
    STDMETHOD(Verify) (THIS_ IHXValues* pAuth1, IHXValues* pAuth2) PURE;

    STDMETHOD(AsString) (THIS_ IHXValues* pAuth, REF(IHXBuffer*) pBuffer) PURE;
    STDMETHOD(AsValues) (THIS_ const char* str, IHXValues* pValues) PURE;

    /*
     * CreateBuffer is provided for the convenince of external users,
     * who would otherwise have to get a context and common class factory
     * just to create IHXBuffers.  This method can be used instead, but
     * is not advisable if other means are available.
     */
    STDMETHOD(CreateBuffer) (THIS_ REF(IHXBuffer*) pBuffer) PURE;

    /*
     * Ditto for CreateValues
     */
    STDMETHOD(CreateValues) (THIS_ REF(IHXValues*) pValues) PURE;
};


/****************************************************************************
 * 
 *  Interface:
 * 
 *      IHXAuthenticationManager
 * 
 *  Purpose:
 * 
 *      Provide a means of authenticating users.
 *
 *  IID_IHXAuthenticator:
 * 
 *      {00001a00-0901-11d1-8B06-00A024406D59}
 * 
 */

DEFINE_GUID(IID_IHXAuthenticationManager, 0x00001a00, 0x901, 0x11d1,
	    0x8b, 0x6, 0x0, 0xa0, 0x24, 0x40, 0x6d, 0x59);

#undef  INTERFACE
#define INTERFACE IHXAuthenticationManager

DECLARE_INTERFACE_(IHXAuthenticationManager, IUnknown)
{
    STDMETHOD(QueryInterface)           (THIS_
					REFIID riid,
					void** ppvObj) PURE;
    STDMETHOD_(ULONG32,AddRef)          (THIS) PURE;
    STDMETHOD_(ULONG32,Release)         (THIS) PURE;

    /* HandleAuthenticationRequest is called when the core wants us to get
     * a username and password.
     */
    STDMETHOD(HandleAuthenticationRequest) (
	THIS_ IHXAuthenticationManagerResponse* pResponse) PURE;
};


/****************************************************************************
 * 
 *  Interface:
 * 
 *      IHXAuthenticationManager2
 * 
 *  Purpose:
 * 
 *      Provide a means of authenticating users.
 *
 *      Includes sending an IHXValues list to the
 *      authentication manager, for support of proxy
 *      authentication, for example, which may include
 *      a "pseudonym" header or something.
 *
 *  IID_IHXAuthenticator2:
 * 
 *      {34e171d2-a8f0-4832-bc7d-06dfe3ae58fd}
 * 
 */

DEFINE_GUID(IID_IHXAuthenticationManager2,
	 0x34e171d2,  0xa8f0,  0x4832,  0xbc,  0x7d,  0x06,
	 0xdf,  0xe3,  0xae,  0x58,  0xfd);

#undef  INTERFACE
#define INTERFACE IHXAuthenticationManager2

DECLARE_INTERFACE_(IHXAuthenticationManager2, IUnknown)
{
    STDMETHOD(QueryInterface)           (THIS_
					REFIID riid,
					void** ppvObj) PURE;
    STDMETHOD_(ULONG32,AddRef)          (THIS) PURE;
    STDMETHOD_(ULONG32,Release)         (THIS) PURE;

    /* HandleAuthenticationRequest2 is called when the core wants us to get
     * a username and password.
     */
    STDMETHOD(HandleAuthenticationRequest2) (
			THIS_
			IHXAuthenticationManagerResponse* pResponse,
			IHXValues* pHeader) PURE;
};


/****************************************************************************
 * 
 *  Interface:
 * 
 *      IHXAuthenticationManagerResponse
 * 
 *  Purpose:
 * 
 *      Response object for IHXAuthenticationManager.
 *
 *  IID_IHXAuthenticator:
 * 
 *      {00001a01-0901-11d1-8B06-00A024406D59}
 * 
 */

DEFINE_GUID(IID_IHXAuthenticationManagerResponse, 0x00001a01, 0x901, 0x11d1,
            0x8b, 0x6, 0x0, 0xa0, 0x24, 0x40, 0x6d, 0x59); 


#undef  INTERFACE
#define INTERFACE IHXAuthenticationManagerResponse

DECLARE_INTERFACE_(IHXAuthenticationManagerResponse, IUnknown)
{
    STDMETHOD(QueryInterface)           (THIS_
					REFIID riid,
					void** ppvObj) PURE;
    STDMETHOD_(ULONG32,AddRef)          (THIS) PURE;
    STDMETHOD_(ULONG32,Release)         (THIS) PURE;

    /* HandleAuthenticationRequest is called when the core wants us to get
     * a username and password.
     */
    STDMETHOD(AuthenticationRequestDone) (THIS_
					  HX_RESULT result,
					  const char* pUserName,
					  const char* pPassword) PURE;
};

#ifdef _MACINTOSH
#pragma export on
#endif

STDAPI CreatePassword(IUnknown** /* OUT */ ppIUnknown);

#ifdef _MACINTOSH
#pragma export off
#endif

#endif /* _HXAUTH_H_ */
