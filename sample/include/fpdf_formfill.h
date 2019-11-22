// Copyright 2014 PDFium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// Original code copyright 2014 Foxit Software Inc. http://www.foxitsoftware.com

#ifndef PUBLIC_FPDF_FORMFILL_H_
#define PUBLIC_FPDF_FORMFILL_H_

// NOLINTNEXTLINE(build/include)
#include "fpdfview.h"

typedef void* FPDF_FORMHANDLE;

// These values are return values for a public API, so should not be changed
// other than the count when adding new values.
#define FORMTYPE_NONE 0            // Document contains no forms
#define FORMTYPE_ACRO_FORM 1       // Forms are specified using AcroForm spec
#define FORMTYPE_XFA_FULL 2        // Forms are specified using the entire XFA
                                   // spec
#define FORMTYPE_XFA_FOREGROUND 3  // Forms are specified using the XFAF subset
                                   // of XFA spec
#define FORMTYPE_COUNT 4           // The number of form types

// Exported Functions
#ifdef __cplusplus
extern "C" {
#endif

typedef struct _IPDF_JsPlatform {
  /**
  * Version number of the interface. Currently must be 2.
  **/
  int version;

  /* Version 1. */

  /**
  * Method: app_alert
  *           pop up a dialog to show warning or hint.
  * Interface Version:
  *           1
  * Implementation Required:
  *           yes
  * Parameters:
  *           pThis       -   Pointer to the interface structure itself
  *           Msg         -   A string containing the message to be displayed.
  *           Title       -   The title of the dialog.
  *           Type        -   The stype of button group.
  *                           0-OK(default);
  *                           1-OK,Cancel;
  *                           2-Yes,NO;
  *                           3-Yes, NO, Cancel.
  *           nIcon       -   The Icon type.
  *                           0-Error(default);
  *                           1-Warning;
  *                           2-Question;
  *                           3-Status.
  *                           4-Asterisk
  * Return Value:
  *           The return value could be the folowing type:
  *                           1-OK;
  *                           2-Cancel;
  *                           3-NO;
  *                           4-Yes;
  */
  int (*app_alert)(struct _IPDF_JsPlatform* pThis,
                   FPDF_WIDESTRING Msg,
                   FPDF_WIDESTRING Title,
                   int Type,
                   int Icon);

  /**
  * Method: app_beep
  *           Causes the system to play a sound.
  * Interface Version:
  *           1
  * Implementation Required:
  *           yes
  * Parameters:
  *           pThis       -   Pointer to the interface structure itself
  *           nType       -   The sound type.
  *                           0 - Error
  *                           1 - Warning
  *                           2 - Question
  *                           3 - Status
  *                           4 - Default (default value)
  * Return Value:
  *           None
  */
  void (*app_beep)(struct _IPDF_JsPlatform* pThis, int nType);

  /**
  * Method: app_response
  *           Displays a dialog box containing a question and an entry field for
  * the user to reply to the question.
  * Interface Version:
  *           1
  * Implementation Required:
  *           yes
  * Parameters:
  *           pThis       -   Pointer to the interface structure itself
  *           Question    -   The question to be posed to the user.
  *           Title       -   The title of the dialog box.
  *           Default     -   A default value for the answer to the question. If
  * not specified, no default value is presented.
  *           cLabel      -   A short string to appear in front of and on the
  * same line as the edit text field.
  *           bPassword   -   If true, indicates that the user's response should
  * show as asterisks (*) or bullets (?) to mask the response, which might be
  * sensitive information. The default is false.
  *           response    -   A string buffer allocated by SDK, to receive the
  * user's response.
  *           length      -   The length of the buffer, number of bytes.
  * Currently, It's always be 2048.
  * Return Value:
  *       Number of bytes the complete user input would actually require, not
  * including trailing zeros, regardless of the value of the length
  *       parameter or the presence of the response buffer.
  * Comments:
  *       No matter on what platform, the response buffer should be always
  * written using UTF-16LE encoding. If a response buffer is
  *       present and the size of the user input exceeds the capacity of the
  * buffer as specified by the length parameter, only the
  *       first "length" bytes of the user input are to be written to the
  * buffer.
  */
  int (*app_response)(struct _IPDF_JsPlatform* pThis,
                      FPDF_WIDESTRING Question,
                      FPDF_WIDESTRING Title,
                      FPDF_WIDESTRING Default,
                      FPDF_WIDESTRING cLabel,
                      FPDF_BOOL bPassword,
                      void* response,
                      int length);

  /*
  * Method: Doc_getFilePath
  *           Get the file path of the current document.
  * Interface Version:
  *           1
  * Implementation Required:
  *           yes
  * Parameters:
  *           pThis       -   Pointer to the interface structure itself
  *           filePath    -   The string buffer to receive the file path. Can be
  * NULL.
  *           length      -   The length of the buffer, number of bytes. Can be
  * 0.
  * Return Value:
  *       Number of bytes the filePath consumes, including trailing zeros.
  * Comments:
  *       The filePath should be always input in local encoding.
  *
  *       The return value always indicated number of bytes required for the
  *       buffer , even when there is no buffer specified, or the buffer size is
  *       less than required. In this case, the buffer will not be modified.
  */
  int (*Doc_getFilePath)(struct _IPDF_JsPlatform* pThis,
                         void* filePath,
                         int length);

  /*
  * Method: Doc_mail
  *           Mails the data buffer as an attachment to all recipients, with or
  * without user interaction.
  * Interface Version:
  *           1
  * Implementation Required:
  *           yes
  * Parameters:
  *           pThis       -   Pointer to the interface structure itself
  *           mailData    -   Pointer to the data buffer to be sent.Can be NULL.
  *           length      -   The size,in bytes, of the buffer pointed by
  * mailData parameter.Can be 0.
  *           bUI         -   If true, the rest of the parameters are used in a
  * compose-new-message window that is displayed to the user. If false, the cTo
  * parameter is required and all others are optional.
  *           To          -   A semicolon-delimited list of recipients for the
  * message.
  *           Subject     -   The subject of the message. The length limit is 64
  * KB.
  *           CC          -   A semicolon-delimited list of CC recipients for
  * the message.
  *           BCC         -   A semicolon-delimited list of BCC recipients for
  * the message.
  *           Msg         -   The content of the message. The length limit is 64
  * KB.
  * Return Value:
  *           None.
  * Comments:
  *           If the parameter mailData is NULL or length is 0, the current
  * document will be mailed as an attachment to all recipients.
  */
  void (*Doc_mail)(struct _IPDF_JsPlatform* pThis,
                   void* mailData,
                   int length,
                   FPDF_BOOL bUI,
                   FPDF_WIDESTRING To,
                   FPDF_WIDESTRING Subject,
                   FPDF_WIDESTRING CC,
                   FPDF_WIDESTRING BCC,
                   FPDF_WIDESTRING Msg);

  /*
  * Method: Doc_print
  *           Prints all or a specific number of pages of the document.
  * Interface Version:
  *           1
  * Implementation Required:
  *           yes
  * Parameters:
  *           pThis       -   Pointer to the interface structure itself.
  *           bUI         -   If true, will cause a UI to be presented to the
  * user to obtain printing information and confirm the action.
  *           nStart      -   A 0-based index that defines the start of an
  * inclusive range of pages.
  *           nEnd        -   A 0-based index that defines the end of an
  * inclusive page range.
  *           bSilent     -   If true, suppresses the cancel dialog box while
  * the document is printing. The default is false.
  *           bShrinkToFit    -   If true, the page is shrunk (if necessary) to
  * fit within the imageable area of the printed page.
  *           bPrintAsImage   -   If true, print pages as an image.
  *           bReverse    -   If true, print from nEnd to nStart.
  *           bAnnotations    -   If true (the default), annotations are
  * printed.
  */
  void (*Doc_print)(struct _IPDF_JsPlatform* pThis,
                    FPDF_BOOL bUI,
                    int nStart,
                    int nEnd,
                    FPDF_BOOL bSilent,
                    FPDF_BOOL bShrinkToFit,
                    FPDF_BOOL bPrintAsImage,
                    FPDF_BOOL bReverse,
                    FPDF_BOOL bAnnotations);

  /*
  * Method: Doc_submitForm
  *           Send the form data to a specified URL.
  * Interface Version:
  *           1
  * Implementation Required:
  *           yes
  * Parameters:
  *           pThis       -   Pointer to the interface structure itself
  *           formData    -   Pointer to the data buffer to be sent.
  *           length      -   The size,in bytes, of the buffer pointed by
  * formData parameter.
  *           URL         -   The URL to send to.
  * Return Value:
  *           None.
  *
  */
  void (*Doc_submitForm)(struct _IPDF_JsPlatform* pThis,
                         void* formData,
                         int length,
                         FPDF_WIDESTRING URL);

  /*
  * Method: Doc_gotoPage
  *           Jump to a specified page.
  * Interface Version:
  *           1
  * Implementation Required:
  *           yes
  * Parameters:
  *           pThis       -   Pointer to the interface structure itself
  *           nPageNum    -   The specified page number, zero for the first
  * page.
  * Return Value:
  *           None.
  *
  */
  void (*Doc_gotoPage)(struct _IPDF_JsPlatform* pThis, int nPageNum);
  /*
  * Method: Field_browse
  *           Show a file selection dialog, and return the selected file path.
  * Interface Version:
  *           1
  * Implementation Required:
  *           yes
  * Parameters:
  *           pThis       -   Pointer to the interface structure itself.
  *           filePath    -   Pointer to the data buffer to receive the file
  * path.Can be NULL.
  *           length      -   The length of the buffer, number of bytes. Can be
  * 0.
  * Return Value:
  *       Number of bytes the filePath consumes, including trailing zeros.
  * Comments:
  *       The filePath shoule be always input in local encoding.
  */
  int (*Field_browse)(struct _IPDF_JsPlatform* pThis,
                      void* filePath,
                      int length);

  /**
  *   pointer to FPDF_FORMFILLINFO interface.
  **/
  void* m_pFormfillinfo;

  /* Version 2. */

  void* m_isolate;               /* Unused in v3, retain for compatibility. */
  unsigned int m_v8EmbedderSlot; /* Unused in v3, retain for compatibility. */

  /* Version 3. */
  /* Version 3 moves m_Isolate and m_v8EmbedderSlot to FPDF_LIBRARY_CONFIG. */
} IPDF_JSPLATFORM;

// Flags for Cursor type
#define FXCT_ARROW 0
#define FXCT_NESW 1
#define FXCT_NWSE 2
#define FXCT_VBEAM 3
#define FXCT_HBEAM 4
#define FXCT_HAND 5

/**
 * Function signature for the callback function passed to the FFI_SetTimer
 * method.
 * Parameters:
 *          idEvent     -   Identifier of the timer.
 * Return value:
 *          None.
 **/
typedef void (*TimerCallback)(int idEvent);

/**
 * Declares of a struct type to the local system time.
**/
typedef struct _FPDF_SYSTEMTIME {
  unsigned short wYear;         /* years since 1900 */
  unsigned short wMonth;        /* months since January - [0,11] */
  unsigned short wDayOfWeek;    /* days since Sunday - [0,6] */
  unsigned short wDay;          /* day of the month - [1,31] */
  unsigned short wHour;         /* hours since midnight - [0,23] */
  unsigned short wMinute;       /* minutes after the hour - [0,59] */
  unsigned short wSecond;       /* seconds after the minute - [0,59] */
  unsigned short wMilliseconds; /* milliseconds after the second - [0,999] */
} FPDF_SYSTEMTIME;

#ifdef PDF_ENABLE_XFA
// XFA
/**
 * @name Pageview  event flags
 */
/*@{*/
/** @brief After a new pageview is added. */
#define FXFA_PAGEVIEWEVENT_POSTADDED 1
/** @brief After a pageview is removed. */
#define FXFA_PAGEVIEWEVENT_POSTREMOVED 3
/*@}*/

// menu
/**
 * @name Macro Definitions for Right Context Menu Features Of XFA Fields
 */
/*@{*/
#define FXFA_MENU_COPY 1
#define FXFA_MENU_CUT 2
#define FXFA_MENU_SELECTALL 4
#define FXFA_MENU_UNDO 8
#define FXFA_MENU_REDO 16
#define FXFA_MENU_PASTE 32
/*@}*/

// file type
/**
 * @name Macro Definitions for File Type.
 */
/*@{*/
#define FXFA_SAVEAS_XML 1
#define FXFA_SAVEAS_XDP 2
/*@}*/
#endif  // PDF_ENABLE_XFA

typedef struct _FPDF_FORMFILLINFO {
  /**
   * Version number of the interface. Currently must be 1 (when PDFium is built
   *  without the XFA module) or must be 2 (when built with the XFA module).
   **/
  int version;

  /* Version 1. */
  /**
   *Method: Release
   *         Give implementation a chance to release any data after the
   *         interface is no longer used
   *Interface Version:
   *         1
   *Implementation Required:
   *         No
   *Comments:
   *         Called by Foxit SDK during the final cleanup process.
   *Parameters:
   *         pThis       -   Pointer to the interface structure itself
   *Return Value:
   *         None
   */
  void (*Release)(struct _FPDF_FORMFILLINFO* pThis);

  /**
   * Method: FFI_Invalidate
   *          Invalidate the client area within the specified rectangle.
   * Interface Version:
   *          1
   * Implementation Required:
      *           yes
   * Parameters:
   *          pThis       -   Pointer to the interface structure itself.
   *          page        -   Handle to the page. Returned by FPDF_LoadPage
   *function.
   *          left        -   Left position of the client area in PDF page
   *coordinate.
   *          top         -   Top  position of the client area in PDF page
   *coordinate.
   *          right       -   Right position of the client area in PDF page
   *coordinate.
   *          bottom      -   Bottom position of the client area in PDF page
   *coordinate.
   * Return Value:
   *          None.
   *
   *comments:
   *          All positions are measured in PDF "user space".
   *          Implementation should call FPDF_RenderPageBitmap() function for
   *repainting a specified page area.
  */
  void (*FFI_Invalidate)(struct _FPDF_FORMFILLINFO* pThis,
                         FPDF_PAGE page,
                         double left,
                         double top,
                         double right,
                         double bottom);

  /**
   * Method: FFI_OutputSelectedRect
   *          When user is taking the mouse to select texts on a form field,
   * this callback function will keep
   *          returning the selected areas to the implementation.
   *
   * Interface Version:
   *          1
   * Implementation Required:
   *          No
   * Parameters:
   *          pThis       -   Pointer to the interface structure itself.
   *          page        -   Handle to the page. Returned by FPDF_LoadPage
   * function.
   *          left        -   Left position of the client area in PDF page
   * coordinate.
   *          top         -   Top  position of the client area in PDF page
   * coordinate.
   *          right       -   Right position of the client area in PDF page
   * coordinate.
   *          bottom      -   Bottom position of the client area in PDF page
   * coordinate.
   * Return Value:
   *          None.
   *
   * comments:
   *          This CALLBACK function is useful for implementing special text
   * selection effect. Implementation should
   *          first records the returned rectangles, then draw them one by one
   * at the painting period, last,remove all
   *          the recorded rectangles when finish painting.
  */
  void (*FFI_OutputSelectedRect)(struct _FPDF_FORMFILLINFO* pThis,
                                 FPDF_PAGE page,
                                 double left,
                                 double top,
                                 double right,
                                 double bottom);

  /**
  * Method: FFI_SetCursor
  *           Set the Cursor shape.
  * Interface Version:
  *           1
  * Implementation Required:
  *           yes
  * Parameters:
  *       pThis       -   Pointer to the interface structure itself.
  *       nCursorType -   Cursor type. see Flags for Cursor type for the
  * details.
  *   Return value:
  *       None.
  * */
  void (*FFI_SetCursor)(struct _FPDF_FORMFILLINFO* pThis, int nCursorType);

  /**
  * Method: FFI_SetTimer
  *       This method installs a system timer. An interval value is specified,
  *       and every time that interval elapses, the system must call into the
  *       callback function with the timer ID as returned by this function.
  * Interface Version:
  *       1
  * Implementation Required:
  *       yes
  * Parameters:
  *       pThis       -   Pointer to the interface structure itself.
  *       uElapse     -   Specifies the time-out value, in milliseconds.
  *       lpTimerFunc -   A pointer to the callback function-TimerCallback.
  * Return value:
  *       The timer identifier of the new timer if the function is successful.
  *       An application passes this value to the FFI_KillTimer method to kill
  *       the timer. Nonzero if it is successful; otherwise, it is zero.
  * */
  int (*FFI_SetTimer)(struct _FPDF_FORMFILLINFO* pThis,
                      int uElapse,
                      TimerCallback lpTimerFunc);

  /**
  * Method: FFI_KillTimer
  *       This method uninstalls a system timer identified by nIDEvent, as
  *       set by an earlier call to FFI_SetTimer.
  * Interface Version:
  *       1
  * Implementation Required:
  *       yes
  * Parameters:
  *       pThis       -   Pointer to the interface structure itself.
  *       nTimerID    -   The timer ID returned by FFI_SetTimer function.
  * Return value:
  *       None.
  * */
  void (*FFI_KillTimer)(struct _FPDF_FORMFILLINFO* pThis, int nTimerID);

  /**
  * Method: FFI_GetLocalTime
  *           This method receives the current local time on the system.
  * Interface Version:
  *           1
  * Implementation Required:
  *           yes
  * Parameters:
  *       pThis       -   Pointer to the interface structure itself.
  *   Return value:
  *       None.
  * */
  FPDF_SYSTEMTIME (*FFI_GetLocalTime)(struct _FPDF_FORMFILLINFO* pThis);

  /**
  * Method: FFI_OnChange
  *           This method will be invoked to notify implementation when the
  * value of any FormField on the document had been changed.
  * Interface Version:
  *           1
  * Implementation Required:
  *           no
  * Parameters:
  *       pThis       -   Pointer to the interface structure itself.
  *   Return value:
  *       None.
  * */
  void (*FFI_OnChange)(struct _FPDF_FORMFILLINFO* pThis);

  /**
  * Method: FFI_GetPage
  *           This method receives the page pointer associated with a specified
  * page index.
  * Interface Version:
  *           1
  * Implementation Required:
  *           yes
  * Parameters:
  *       pThis       -   Pointer to the interface structure itself.
  *       document    -   Handle to document. Returned by FPDF_LoadDocument
  * function.
  *       nPageIndex  -   Index number of the page. 0 for the first page.
  * Return value:
  *       Handle to the page. Returned by FPDF_LoadPage function.
  * Comments:
  *       In some cases, the document-level JavaScript action may refer to a
  * page which hadn't been loaded yet.
  *       To successfully run the javascript action, implementation need to load
  * the page for SDK.
  * */
  FPDF_PAGE (*FFI_GetPage)(struct _FPDF_FORMFILLINFO* pThis,
                             FPDF_DOCUMENT document,
                             int nPageIndex);

  /**
  * Method: FFI_GetCurrentPage
  *       This method receives the current page pointer.
  * Interface Version:
  *           1
  * Implementation Required:
  *           yes
  * Parameters:
  *       pThis       -   Pointer to the interface structure itself.
  *       document    -   Handle to document. Returned by FPDF_LoadDocument
  * function.
  * Return value:
  *       Handle to the page. Returned by FPDF_LoadPage function.
  * */
  FPDF_PAGE (*FFI_GetCurrentPage)(struct _FPDF_FORMFILLINFO* pThis,
                                    FPDF_DOCUMENT document);

  /**
  * Method: FFI_GetRotation
  *           This method receives currently rotation of the page view.
  * Interface Version:
  *           1
  * Implementation Required:
  *           yes
  * Parameters:
  *       pThis       -   Pointer to the interface structure itself.
  *       page        -   Handle to page. Returned by FPDF_LoadPage function.
  * Return value:
  *       The page rotation. Should be 0(0 degree),1(90 degree),2(180
  * degree),3(270 degree), in a clockwise direction.
  *
  * Note: Unused.
  * */
  int (*FFI_GetRotation)(struct _FPDF_FORMFILLINFO* pThis, FPDF_PAGE page);

  /**
  * Method: FFI_ExecuteNamedAction
  *           This method will execute an named action.
  * Interface Version:
  *           1
  * Implementation Required:
  *           yes
  * Parameters:
  *       pThis           -   Pointer to the interface structure itself.
  *       namedAction     -   A byte string which indicates the named action,
  * terminated by 0.
  * Return value:
  *       None.
  * Comments:
  *       See the named actions description of <<PDF Reference, version 1.7>>
  * for more details.
  * */
  void (*FFI_ExecuteNamedAction)(struct _FPDF_FORMFILLINFO* pThis,
                                 FPDF_BYTESTRING namedAction);
  /**
  * @brief This method will be called when a text field is getting or losing a
  * focus.
  *
  * @param[in] pThis      Pointer to the interface structure itself.
  * @param[in] value      The string value of the form field, in UTF-16LE
  * format.
  * @param[in] valueLen   The length of the string value, number of characters
  * (not bytes).
  * @param[in] is_focus   True if the form field is getting a focus, False for
  * losing a focus.
  *
  * @return None.
  *
  * @note Currently,only support text field and combobox field.
  * */
  void (*FFI_SetTextFieldFocus)(struct _FPDF_FORMFILLINFO* pThis,
                                FPDF_WIDESTRING value,
                                FPDF_DWORD valueLen,
                                FPDF_BOOL is_focus);

  /**
  * Method: FFI_DoURIAction
  *           This action resolves to a uniform resource identifier.
  * Interface Version:
  *           1
  * Implementation Required:
  *           No
  * Parameters:
  *       pThis           -   Pointer to the interface structure itself.
  *       bsURI           -   A byte string which indicates the uniform resource
  * identifier, terminated by 0.
  * Return value:
  *       None.
  * Comments:
  *       See the URI actions description of <<PDF Reference, version 1.7>> for
  * more details.
  * */
  void (*FFI_DoURIAction)(struct _FPDF_FORMFILLINFO* pThis,
                          FPDF_BYTESTRING bsURI);

  /**
  * Method: FFI_DoGoToAction
  *           This action changes the view to a specified destination.
  * Interface Version:
  *           1
  * Implementation Required:
  *           No
  * Parameters:
  *       pThis           -   Pointer to the interface structure itself.
  *       nPageIndex      -   The index of the PDF page.
  *       zoomMode        -   The zoom mode for viewing page. See below.
  *       fPosArray       -   The float array which carries the position info.
  *       sizeofArray     -   The size of float array.
  *
  * PDFZoom values:
  *   - XYZ = 1
  *   - FITPAGE = 2
  *   - FITHORZ = 3
  *   - FITVERT = 4
  *   - FITRECT = 5
  *   - FITBBOX = 6
  *   - FITBHORZ = 7
  *   - FITBVERT = 8
  *
  * Return value:
  *       None.
  * Comments:
  *       See the Destinations description of <<PDF Reference, version 1.7>> in
  *8.2.1 for more details.
  **/
  void (*FFI_DoGoToAction)(struct _FPDF_FORMFILLINFO* pThis,
                           int nPageIndex,
                           int zoomMode,
                           float* fPosArray,
                           int sizeofArray);

  /**
  *   pointer to IPDF_JSPLATFORM interface
  **/
  IPDF_JSPLATFORM* m_pJsPlatform;

#ifdef PDF_ENABLE_XFA
  /* Version 2. */
  /**
    * Method: FFI_DisplayCaret
    *           This method will show the caret at specified position.
    * Interface Version:
    *           2
    * Implementation Required:
    *           yes
    * Parameters:
    *       pThis           -   Pointer to the interface structure itself.
    *       page            -   Handle to page. Returned by FPDF_LoadPage
    *function.
    *       left            -   Left position of the client area in PDF page
    *coordinate.
    *       top             -   Top position of the client area in PDF page
    *coordinate.
    *       right           -   Right position of the client area in PDF page
    *coordinate.
    *       bottom          -   Bottom position of the client area in PDF page
    *coordinate.
    * Return value:
    *       None.
    **/
  void (*FFI_DisplayCaret)(struct _FPDF_FORMFILLINFO* pThis,
                           FPDF_PAGE page,
                           FPDF_BOOL bVisible,
                           double left,
                           double top,
                           double right,
                           double bottom);

  /**
  * Method: FFI_GetCurrentPageIndex
  *           This method will get the current page index.
  * Interface Version:
  *           2
  * Implementation Required:
  *           yes
  * Parameters:
  *       pThis           -   Pointer to the interface structure itself.
  *       document        -   Handle to document. Returned by FPDF_LoadDocument
  *function.
  * Return value:
  *       The index of current page.
  **/
  int (*FFI_GetCurrentPageIndex)(struct _FPDF_FORMFILLINFO* pThis,
                                 FPDF_DOCUMENT document);

  /**
  * Method: FFI_SetCurrentPage
  *           This method will set the current page.
  * Interface Version:
  *           2
  * Implementation Required:
  *           yes
  * Parameters:
  *       pThis           -   Pointer to the interface structure itself.
  *       document        -   Handle to document. Returned by FPDF_LoadDocument
  *function.
  *       iCurPage        -   The index of the PDF page.
  * Return value:
  *       None.
  **/
  void (*FFI_SetCurrentPage)(struct _FPDF_FORMFILLINFO* pThis,
                             FPDF_DOCUMENT document,
                             int iCurPage);

  /**
  * Method: FFI_GotoURL
  *           This method will link to the specified URL.
  * Interface Version:
  *           2
  * Implementation Required:
  *           no
  * Parameters:
  *       pThis           -   Pointer to the interface structure itself.
  *       document        -   Handle to document. Returned by FPDF_LoadDocument
  *function.
  *       wsURL           -   The string value of the URL, in UTF-16LE format.
  * Return value:
  *       None.
  **/
  void (*FFI_GotoURL)(struct _FPDF_FORMFILLINFO* pThis,
                      FPDF_DOCUMENT document,
                      FPDF_WIDESTRING wsURL);

  /**
  * Method: FFI_GetPageViewRect
  *           This method will get the current page view rectangle.
  * Interface Version:
  *           2
  * Implementation Required:
  *           yes
  * Parameters:
  *       pThis           -   Pointer to the interface structure itself.
  *       page            -   Handle to page. Returned by FPDF_LoadPage
  *function.
  *       left            -   The pointer to receive left position of the page
  *view area in PDF page coordinate.
  *       top             -   The pointer to receive top position of the page
  *view area in PDF page coordinate.
  *       right           -   The pointer to receive right position of the
  *client area in PDF page coordinate.
  *       bottom          -   The pointer to receive bottom position of the
  *client area in PDF page coordinate.
  * Return value:
  *       None.
  **/
  void (*FFI_GetPageViewRect)(struct _FPDF_FORMFILLINFO* pThis,
                              FPDF_PAGE page,
                              double* left,
                              double* top,
                              double* right,
                              double* bottom);

  /**
  * Method: FFI_PageEvent
  *     This method fires when pages have been added to or deleted from the XFA
  *     document.
  * Interface Version:
  *     2
  * Implementation Required:
  *     yes
  * Parameters:
  *     pThis       -   Pointer to the interface structure itself.
  *     page_count  -   The number of pages to be added to or deleted from the
  *                     document.
  *     event_type  -   See FXFA_PAGEVIEWEVENT_* above.
  * Return value:
  *       None.
  * Comments:
  *           The pages to be added or deleted always start from the last page
  *           of document. This means that if parameter page_count is 2 and
  *           event type is FXFA_PAGEVIEWEVENT_POSTADDED, 2 new pages have been
  *           appended to the tail of document; If page_count is 2 and
  *           event type is FXFA_PAGEVIEWEVENT_POSTREMOVED, the last 2 pages
  *           have been deleted.
  **/
  void (*FFI_PageEvent)(struct _FPDF_FORMFILLINFO* pThis,
                        int page_count,
                        FPDF_DWORD event_type);

  /**
  * Method: FFI_PopupMenu
  *           This method will track the right context menu for XFA fields.
  * Interface Version:
  *           2
  * Implementation Required:
  *           yes
  * Parameters:
  *       pThis           -   Pointer to the interface structure itself.
  *       page            -   Handle to page. Returned by FPDF_LoadPage
  *function.
  *       hWidget         -   Handle to XFA fields.
  *       menuFlag        -   The menu flags. Please refer to macro definition
  *of FXFA_MENU_XXX and this can be one or a combination of these macros.
  *       x               -   X position of the client area in PDF page
  *coordinate.
  *       y               -   Y position of the client area in PDF page
  *coordinate.
  * Return value:
  *       TRUE indicates success; otherwise false.
  **/
  FPDF_BOOL (*FFI_PopupMenu)(struct _FPDF_FORMFILLINFO* pThis,
                             FPDF_PAGE page,
                             FPDF_WIDGET hWidget,
                             int menuFlag,
                             float x,
                             float y);

  /**
  * Method: FFI_OpenFile
  *           This method will open the specified file with the specified mode.
  * Interface Version
  *           2
  * Implementation Required:
  *           yes
  * Parameters:
  *       pThis           -   Pointer to the interface structure itself.
  *       fileFlag        -   The file flag.Please refer to macro definition of
  *FXFA_SAVEAS_XXX and this can be one of these macros.
  *       wsURL           -   The string value of the file URL, in UTF-16LE
  *format.
  *       mode            -   The mode for open file.
  * Return value:
  *       The handle to FPDF_FILEHANDLER.
  **/
  FPDF_FILEHANDLER* (*FFI_OpenFile)(struct _FPDF_FORMFILLINFO* pThis,
                                    int fileFlag,
                                    FPDF_WIDESTRING wsURL,
                                    const char* mode);

  /**
  * Method: FFI_EmailTo
  *           This method will email the specified file stream to the specified
  *contacter.
  * Interface Version:
  *           2
  * Implementation Required:
  *           yes
  * Parameters:
  *       pThis           -   Pointer to the interface structure itself.
  *       pFileHandler    -   Handle to the FPDF_FILEHANDLER.
  *       pTo             -   A semicolon-delimited list of recipients for the
  *message,in UTF-16LE format.
  *       pSubject        -   The subject of the message,in UTF-16LE format.
  *       pCC             -   A semicolon-delimited list of CC recipients for
  *the message,in UTF-16LE format.
  *       pBcc            -   A semicolon-delimited list of BCC recipients for
  *the message,in UTF-16LE format.
  *       pMsg            -   Pointer to the data buffer to be sent.Can be
  *NULL,in UTF-16LE format.
  * Return value:
  *       None.
  **/
  void (*FFI_EmailTo)(struct _FPDF_FORMFILLINFO* pThis,
                      FPDF_FILEHANDLER* fileHandler,
                      FPDF_WIDESTRING pTo,
                      FPDF_WIDESTRING pSubject,
                      FPDF_WIDESTRING pCC,
                      FPDF_WIDESTRING pBcc,
                      FPDF_WIDESTRING pMsg);

  /**
  * Method: FFI_UploadTo
  *           This method will get upload the specified file stream to the
  *specified URL.
  * Interface Version:
  *           2
  * Implementation Required:
  *           yes
  * Parameters:
  *       pThis           -   Pointer to the interface structure itself.
  *       pFileHandler    -   Handle to the FPDF_FILEHANDLER.
  *       fileFlag        -   The file flag.Please refer to macro definition of
  *FXFA_SAVEAS_XXX and this can be one of these macros.
  *       uploadTo        -   Pointer to the URL path, in UTF-16LE format.
  * Return value:
  *       None.
  **/
  void (*FFI_UploadTo)(struct _FPDF_FORMFILLINFO* pThis,
                       FPDF_FILEHANDLER* fileHandler,
                       int fileFlag,
                       FPDF_WIDESTRING uploadTo);

  /**
  * Method: FFI_GetPlatform
  *           This method will get the current platform.
  * Interface Version:
  *           2
  * Implementation Required:
  *           yes
  * Parameters:
  *       pThis           -   Pointer to the interface structure itself.
  *       platform        -   Pointer to the data buffer to receive the
  *platform.Can be NULL,in UTF-16LE format.
  *       length          -   The length of the buffer, number of bytes. Can be
  *0.
  * Return value:
  *       The length of the buffer, number of bytes.
  **/
  int (*FFI_GetPlatform)(struct _FPDF_FORMFILLINFO* pThis,
                         void* platform,
                         int length);

  /**
  * Method: FFI_GetLanguage
  *           This method will get the current language.
  * Interface Version:
  *           2
  * Implementation Required:
  *           yes
  * Parameters:
  *       pThis           -   Pointer to the interface structure itself.
  *       language        -   Pointer to the data buffer to receive the current
  *language.Can be NULL.
  *       length          -   The length of the buffer, number of bytes. Can be
  *0.
  * Return value:
  *       The length of the buffer, number of bytes.
  **/
  int (*FFI_GetLanguage)(struct _FPDF_FORMFILLINFO* pThis,
                         void* language,
                         int length);

  /**
  * Method: FFI_DownloadFromURL
  *           This method will download the specified file from the URL.
  * Interface Version:
  *           2
  * Implementation Required:
  *           yes
  * Parameters:
  *       pThis           -   Pointer to the interface structure itself.
  *       URL             -   The string value of the file URL, in UTF-16LE
  *format.
  * Return value:
  *       The handle to FPDF_FILEHANDLER.
  **/
  FPDF_LPFILEHANDLER (*FFI_DownloadFromURL)(struct _FPDF_FORMFILLINFO* pThis,
                                             FPDF_WIDESTRING URL);
  /**
  * Method: FFI_PostRequestURL
  *           This method will post the request to the server URL.
  * Interface Version:
  *           2
  * Implementation Required:
  *           yes
  * Parameters:
  *       pThis           -   Pointer to the interface structure itself.
  *       wsURL           -   The string value of the server URL, in UTF-16LE
  *format.
  *       wsData          -   The post data,in UTF-16LE format.
  *       wsContentType   -   The content type of the request data,in UTF-16LE
  *format.
  *       wsEncode        -   The encode type,in UTF-16LE format.
  *       wsHeader        -   The request header,in UTF-16LE format.
  *       response        -   Pointer to the FPDF_BSTR to receive the response
  *data from server,,in UTF-16LE format.
  * Return value:
  *       TRUE indicates success, otherwise FALSE.
  **/
  FPDF_BOOL (*FFI_PostRequestURL)(struct _FPDF_FORMFILLINFO* pThis,
                                    FPDF_WIDESTRING wsURL,
                                    FPDF_WIDESTRING wsData,
                                    FPDF_WIDESTRING wsContentType,
                                    FPDF_WIDESTRING wsEncode,
                                    FPDF_WIDESTRING wsHeader,
                                    FPDF_BSTR* respone);

  /**
  * Method: FFI_PutRequestURL
  *           This method will put the request to the server URL.
  * Interface Version:
  *           2
  * Implementation Required:
  *           yes
  * Parameters:
  *       pThis           -   Pointer to the interface structure itself.
  *       wsURL           -   The string value of the server URL, in UTF-16LE
  *format.
  *       wsData          -   The put data, in UTF-16LE format.
  *       wsEncode        -   The encode type, in UTR-16LE format.
  * Return value:
  *       TRUE indicates success, otherwise FALSE.
  **/
  FPDF_BOOL (*FFI_PutRequestURL)(struct _FPDF_FORMFILLINFO* pThis,
                                   FPDF_WIDESTRING wsURL,
                                   FPDF_WIDESTRING wsData,
                                   FPDF_WIDESTRING wsEncode);
#endif  // PDF_ENABLE_XFA
} FPDF_FORMFILLINFO;

/**
 * Function: FPDFDOC_InitFormFillEnvironment
 *          Init form fill environment.
 * Comments:
 *          This function should be called before any form fill operation.
 * Parameters:
 *          document        -   Handle to document. Returned by
 *FPDF_LoadDocument function.
 *          pFormFillInfo   -   Pointer to a FPDF_FORMFILLINFO structure.
 * Return Value:
 *          Return handler to the form fill module. NULL means fails.
 **/
FPDF_EXPORT FPDF_FORMHANDLE FPDF_CALLCONV
FPDFDOC_InitFormFillEnvironment(FPDF_DOCUMENT document,
                                FPDF_FORMFILLINFO* formInfo);

/**
 * Function: FPDFDOC_ExitFormFillEnvironment
 *          Exit form fill environment.
 * Parameters:
 *          hHandle     -   Handle to the form fill module. Returned by
 *FPDFDOC_InitFormFillEnvironment.
 * Return Value:
 *          NULL.
 **/
FPDF_EXPORT void FPDF_CALLCONV
FPDFDOC_ExitFormFillEnvironment(FPDF_FORMHANDLE hHandle);

/**
 * Function: FORM_OnAfterLoadPage
 *          This method is required for implementing all the form related
 *functions. Should be invoked after user
 *          successfully loaded a PDF page, and method
 *FPDFDOC_InitFormFillEnvironment had been invoked.
 * Parameters:
 *          hHandle     -   Handle to the form fill module. Returned by
 *FPDFDOC_InitFormFillEnvironment.
 * Return Value:
 *          NONE.
 **/
FPDF_EXPORT void FPDF_CALLCONV FORM_OnAfterLoadPage(FPDF_PAGE page,
                                                    FPDF_FORMHANDLE hHandle);

/**
 * Function: FORM_OnBeforeClosePage
 *          This method is required for implementing all the form related
 *functions. Should be invoked before user
 *          close the PDF page.
 * Parameters:
 *          page        -   Handle to the page. Returned by FPDF_LoadPage
 *function.
 *          hHandle     -   Handle to the form fill module. Returned by
 *FPDFDOC_InitFormFillEnvironment.
 * Return Value:
 *          NONE.
 **/
FPDF_EXPORT void FPDF_CALLCONV FORM_OnBeforeClosePage(FPDF_PAGE page,
                                                      FPDF_FORMHANDLE hHandle);

/**
* Function: FORM_DoDocumentJSAction
*           This method is required for performing Document-level JavaScript
*action. It should be invoked after the PDF document
*           had been loaded.
* Parameters:
*           hHandle     -   Handle to the form fill module. Returned by
*FPDFDOC_InitFormFillEnvironment.
* Return Value:
*           NONE
* Comments:
*           If there is Document-level JavaScript action embedded in the
*document, this method will execute the javascript action;
*           otherwise, the method will do nothing.
**/
FPDF_EXPORT void FPDF_CALLCONV FORM_DoDocumentJSAction(FPDF_FORMHANDLE hHandle);

/**
* Function: FORM_DoDocumentOpenAction
*           This method is required for performing open-action when the document
*is opened.
* Parameters:
*           hHandle     -   Handle to the form fill module. Returned by
*FPDFDOC_InitFormFillEnvironment.
* Return Value:
*           NONE
* Comments:
*           This method will do nothing if there is no open-actions embedded in
*the document.
**/
FPDF_EXPORT void FPDF_CALLCONV
FORM_DoDocumentOpenAction(FPDF_FORMHANDLE hHandle);

// additional actions type of document.
#define FPDFDOC_AACTION_WC \
  0x10  // WC, before closing document, JavaScript action.
#define FPDFDOC_AACTION_WS \
  0x11  // WS, before saving document, JavaScript action.
#define FPDFDOC_AACTION_DS 0x12  // DS, after saving document, JavaScript
                                 // action.
#define FPDFDOC_AACTION_WP \
  0x13  // WP, before printing document, JavaScript action.
#define FPDFDOC_AACTION_DP \
  0x14  // DP, after printing document, JavaScript action.

/**
* Function: FORM_DoDocumentAAction
*           This method is required for performing the document's
*additional-action.
* Parameters:
*           hHandle     -   Handle to the form fill module. Returned by
*FPDFDOC_InitFormFillEnvironment.
*           aaType      -   The type of the additional-actions which defined
*above.
* Return Value:
*           NONE
* Comments:
*           This method will do nothing if there is no document
*additional-action corresponding to the specified aaType.
**/

FPDF_EXPORT void FPDF_CALLCONV FORM_DoDocumentAAction(FPDF_FORMHANDLE hHandle,
                                                      int aaType);

// Additional-action types of page object
#define FPDFPAGE_AACTION_OPEN \
  0  // /O -- An action to be performed when the page is opened
#define FPDFPAGE_AACTION_CLOSE \
  1  // /C -- An action to be performed when the page is closed

/**
* Function: FORM_DoPageAAction
*           This method is required for performing the page object's
*additional-action when opened or closed.
* Parameters:
*           page        -   Handle to the page. Returned by FPDF_LoadPage
*function.
*           hHandle     -   Handle to the form fill module. Returned by
*FPDFDOC_InitFormFillEnvironment.
*           aaType      -   The type of the page object's additional-actions
*which defined above.
* Return Value:
*           NONE
* Comments:
*           This method will do nothing if no additional-action corresponding to
*the specified aaType exists.
**/
FPDF_EXPORT void FPDF_CALLCONV FORM_DoPageAAction(FPDF_PAGE page,
                                                  FPDF_FORMHANDLE hHandle,
                                                  int aaType);

/**
 * Function: FORM_OnMouseMove
 *          You can call this member function when the mouse cursor moves.
 * Parameters:
 *          hHandle     -   Handle to the form fill module. Returned by
 *FPDFDOC_InitFormFillEnvironment.
 *          page        -   Handle to the page. Returned by FPDF_LoadPage
 *function.
 *          modifier        -   Indicates whether various virtual keys are down.
 *          page_x      -   Specifies the x-coordinate of the cursor in PDF user
 *space.
 *          page_y      -   Specifies the y-coordinate of the cursor in PDF user
 *space.
 * Return Value:
 *          TRUE indicates success; otherwise false.
 **/
FPDF_EXPORT FPDF_BOOL FPDF_CALLCONV FORM_OnMouseMove(FPDF_FORMHANDLE hHandle,
                                                     FPDF_PAGE page,
                                                     int modifier,
                                                     double page_x,
                                                     double page_y);

/**
 * Function: FORM_OnFocus
 *          This function focuses the form annotation at a given point. If the
 *          annotation at the point already has focus, nothing happens. If there
 *          is no annotation at the point, remove form focus.
 * Parameters:
 *          hHandle     -   Handle to the form fill module. Returned by
 *                          FPDFDOC_InitFormFillEnvironment.
 *          page        -   Handle to the page. Returned by FPDF_LoadPage.
 *          modifier    -   Indicates whether various virtual keys are down.
 *          page_x      -   Specifies the x-coordinate of the cursor in PDF user
 *                          space.
 *          page_y      -   Specifies the y-coordinate of the cursor in PDF user
 *                          space.
 * Return Value:
 *          TRUE if there is an annotation at the given point and it has focus.
 **/
FPDF_EXPORT FPDF_BOOL FPDF_CALLCONV FORM_OnFocus(FPDF_FORMHANDLE hHandle,
                                                 FPDF_PAGE page,
                                                 int modifier,
                                                 double page_x,
                                                 double page_y);

/**
 * Function: FORM_OnLButtonDown
 *          You can call this member function when the user presses the left
 *mouse button.
 * Parameters:
 *          hHandle     -   Handle to the form fill module. Returned by
 *FPDFDOC_InitFormFillEnvironment.
 *          page        -   Handle to the page. Returned by FPDF_LoadPage
 *function.
 *          modifier        -   Indicates whether various virtual keys are down.
 *          page_x      -   Specifies the x-coordinate of the cursor in PDF user
 *space.
 *          page_y      -   Specifies the y-coordinate of the cursor in PDF user
 *space.
 * Return Value:
 *          TRUE indicates success; otherwise false.
 **/
FPDF_EXPORT FPDF_BOOL FPDF_CALLCONV FORM_OnLButtonDown(FPDF_FORMHANDLE hHandle,
                                                       FPDF_PAGE page,
                                                       int modifier,
                                                       double page_x,
                                                       double page_y);

/**
 * Function: FORM_OnLButtonUp
 *          You can call this member function when the user releases the left
 *mouse button.
 * Parameters:
 *          hHandle     -   Handle to the form fill module. Returned by
 *FPDFDOC_InitFormFillEnvironment.
 *          page        -   Handle to the page. Returned by FPDF_LoadPage
 *function.
 *          modifier    -   Indicates whether various virtual keys are down.
 *          page_x      -   Specifies the x-coordinate of the cursor in device.
 *          page_y      -   Specifies the y-coordinate of the cursor in device.
 * Return Value:
 *          TRUE indicates success; otherwise false.
 **/
FPDF_EXPORT FPDF_BOOL FPDF_CALLCONV FORM_OnLButtonUp(FPDF_FORMHANDLE hHandle,
                                                     FPDF_PAGE page,
                                                     int modifier,
                                                     double page_x,
                                                     double page_y);

#ifdef PDF_ENABLE_XFA
FPDF_EXPORT FPDF_BOOL FPDF_CALLCONV FORM_OnRButtonDown(FPDF_FORMHANDLE hHandle,
                                                       FPDF_PAGE page,
                                                       int modifier,
                                                       double page_x,
                                                       double page_y);
FPDF_EXPORT FPDF_BOOL FPDF_CALLCONV FORM_OnRButtonUp(FPDF_FORMHANDLE hHandle,
                                                     FPDF_PAGE page,
                                                     int modifier,
                                                     double page_x,
                                                     double page_y);
#endif  // PDF_ENABLE_XFA

/**
 * Function: FORM_OnKeyDown
 *          You can call this member function when a nonsystem key is pressed.
 * Parameters:
 *          hHandle     -   Handle to the form fill module. Returned by
 *FPDFDOC_InitFormFillEnvironment.
 *          page        -   Handle to the page. Returned by FPDF_LoadPage
 *function.
 *          nKeyCode    -   Indicates whether various virtual keys are down.
 *          modifier    -   Contains the scan code, key-transition code,
 *previous key state, and context code.
 * Return Value:
 *          TRUE indicates success; otherwise false.
 **/
FPDF_EXPORT FPDF_BOOL FPDF_CALLCONV FORM_OnKeyDown(FPDF_FORMHANDLE hHandle,
                                                   FPDF_PAGE page,
                                                   int nKeyCode,
                                                   int modifier);

/**
 * Function: FORM_OnKeyUp
 *          You can call this member function when a nonsystem key is released.
 * Parameters:
 *          hHandle     -   Handle to the form fill module. Returned by
 *FPDFDOC_InitFormFillEnvironment.
 *          page        -   Handle to the page. Returned by FPDF_LoadPage
 *function.
 *          nKeyCode    -   The virtual-key code of the given key.
 *          modifier    -   Contains the scan code, key-transition code,
 *previous key state, and context code.
 * Return Value:
 *          TRUE indicates success; otherwise false.
 **/
FPDF_EXPORT FPDF_BOOL FPDF_CALLCONV FORM_OnKeyUp(FPDF_FORMHANDLE hHandle,
                                                 FPDF_PAGE page,
                                                 int nKeyCode,
                                                 int modifier);

/**
 * Function: FORM_OnChar
 *          You can call this member function when a keystroke translates to a
 *nonsystem character.
 * Parameters:
 *          hHandle     -   Handle to the form fill module. Returned by
 *FPDFDOC_InitFormFillEnvironment.
 *          page        -   Handle to the page. Returned by FPDF_LoadPage
 *function.
 *          nChar       -   The character code value of the key.
 *          modifier    -   Contains the scan code, key-transition code,
 *previous key state, and context code.
 * Return Value:
 *          TRUE indicates success; otherwise false.
 **/
FPDF_EXPORT FPDF_BOOL FPDF_CALLCONV FORM_OnChar(FPDF_FORMHANDLE hHandle,
                                                FPDF_PAGE page,
                                                int nChar,
                                                int modifier);

/**
 * Experimental API
 * Function: FORM_GetFocusedText
 *          You can call this function to obtain the text within the current
 *          focused field, if any.
 * Parameters:
 *          hHandle     -   Handle to the form fill module. Returned by
 *                          FPDFDOC_InitFormFillEnvironment.
 *          page        -   Handle to the page. Returned by FPDF_LoadPage
 *                          function.
 *          buffer      -   Buffer for holding the form text, encoded in
 *                          UTF16-LE. If NULL, |buffer| is not modified.
 *          buflen      -   Length of |buffer| in bytes. If |buflen| is less
                            than the length of the form text string, |buffer| is
                            not modified.
 * Return Value:
 *          Length in bytes for the text in the focused field.
 **/
FPDF_EXPORT unsigned long FPDF_CALLCONV
FORM_GetFocusedText(FPDF_FORMHANDLE hHandle,
                    FPDF_PAGE page,
                    void* buffer,
                    unsigned long buflen);

/**
 * Function: FORM_GetSelectedText
 *          You can call this function to obtain selected text within
 *          a form text field or form combobox text field.
 * Parameters:
 *          hHandle     -   Handle to the form fill module. Returned by
 *                          FPDFDOC_InitFormFillEnvironment.
 *          page        -   Handle to the page. Returned by FPDF_LoadPage
 *                          function.
 *          buffer      -   Buffer for holding the selected text, encoded in
 *                          UTF16-LE. If NULL, |buffer| is not modified.
 *          buflen      -   Length of |buffer| in bytes. If |buflen| is less
                            than the length of the selected text string,
                            |buffer| is not modified.
 * Return Value:
 *          Length in bytes of selected text in form text field or form combobox
 *          text field.
 **/
FPDF_EXPORT unsigned long FPDF_CALLCONV
FORM_GetSelectedText(FPDF_FORMHANDLE hHandle,
                     FPDF_PAGE page,
                     void* buffer,
                     unsigned long buflen);

/**
 * Function: FORM_ReplaceSelection
 *          You can call this function to replace the selected text in a form
 *          text field or user-editable form combobox text field with another
 *          text string (which can be empty or non-empty). If there is no
 *          selected text, this function will append the replacement text after
 *          the current caret position.
 * Parameters:
 *          hHandle     -   Handle to the form fill module. Returned by
 *                          FPDFDOC_InitFormFillEnvironment.
 *          page        -   Handle to the page. Returned by FPDF_LoadPage
 *                          function.
 *          wsText      -   The text to be inserted, in UTF-16LE format.
 * Return Value:
 *          None.
 **/
FPDF_EXPORT void FPDF_CALLCONV FORM_ReplaceSelection(FPDF_FORMHANDLE hHandle,
                                                     FPDF_PAGE page,
                                                     FPDF_WIDESTRING wsText);

/**
 * Function: FORM_CanUndo
 *          Find out if it is possible for the current focused widget in a given
 *          form to perform an undo operation.
 * Parameters:
 *          hHandle     -   Handle to the form fill module. Returned by
 *                          FPDFDOC_InitFormFillEnvironment.
 *          page        -   Handle to the page. Returned by FPDF_LoadPage
 *                          function.
 * Return Value:
 *          True if it is possible to undo.
 **/
FPDF_EXPORT FPDF_BOOL FPDF_CALLCONV FORM_CanUndo(FPDF_FORMHANDLE hHandle,
                                                 FPDF_PAGE page);

/**
 * Function: FORM_CanRedo
 *          Find out if it is possible for the current focused widget in a given
 *          form to perform a redo operation.
 * Parameters:
 *          hHandle     -   Handle to the form fill module. Returned by
 *                          FPDFDOC_InitFormFillEnvironment.
 *          page        -   Handle to the page. Returned by FPDF_LoadPage
 *                          function.
 * Return Value:
 *          True if it is possible to redo.
 **/
FPDF_EXPORT FPDF_BOOL FPDF_CALLCONV FORM_CanRedo(FPDF_FORMHANDLE hHandle,
                                                 FPDF_PAGE page);

/**
 * Function: FORM_Undo
 *          Make the current focussed widget perform an undo operation.
 * Parameters:
 *          hHandle     -   Handle to the form fill module. Returned by
 *                          FPDFDOC_InitFormFillEnvironment.
 *          page        -   Handle to the page. Returned by FPDF_LoadPage
 *                          function.
 * Return Value:
 *          True if the undo operation succeeded.
 **/
FPDF_EXPORT FPDF_BOOL FPDF_CALLCONV FORM_Undo(FPDF_FORMHANDLE hHandle,
                                              FPDF_PAGE page);

/**
 * Function: FORM_Redo
 *          Make the current focussed widget perform a redo operation.
 * Parameters:
 *          hHandle     -   Handle to the form fill module. Returned by
 *                          FPDFDOC_InitFormFillEnvironment.
 *          page        -   Handle to the page. Returned by FPDF_LoadPage
 *                          function.
 * Return Value:
 *          True if the redo operation succeeded.
 **/
FPDF_EXPORT FPDF_BOOL FPDF_CALLCONV FORM_Redo(FPDF_FORMHANDLE hHandle,
                                              FPDF_PAGE page);

/**
 * Function: FORM_ForceToKillFocus.
 *          You can call this member function to force to kill the focus of the
 *form field which got focus.
 *          It would kill the focus on the form field, save the value of form
 *field if it's changed by user.
 * Parameters:
 *          hHandle     -   Handle to the form fill module. Returned by
 *FPDFDOC_InitFormFillEnvironment.
 * Return Value:
 *          TRUE indicates success; otherwise false.
 **/
FPDF_EXPORT FPDF_BOOL FPDF_CALLCONV
FORM_ForceToKillFocus(FPDF_FORMHANDLE hHandle);

// Form Field Types
// The names of the defines are stable, but the specific values associated with
// them are not, so do not hardcode their values.
#define FPDF_FORMFIELD_UNKNOWN 0      // Unknown.
#define FPDF_FORMFIELD_PUSHBUTTON 1   // push button type.
#define FPDF_FORMFIELD_CHECKBOX 2     // check box type.
#define FPDF_FORMFIELD_RADIOBUTTON 3  // radio button type.
#define FPDF_FORMFIELD_COMBOBOX 4     // combo box type.
#define FPDF_FORMFIELD_LISTBOX 5      // list box type.
#define FPDF_FORMFIELD_TEXTFIELD 6    // text field type.
#define FPDF_FORMFIELD_SIGNATURE 7    // text field type.
#ifdef PDF_ENABLE_XFA
#define FPDF_FORMFIELD_XFA 8              // Generic XFA type.
#define FPDF_FORMFIELD_XFA_CHECKBOX 9     // XFA check box type.
#define FPDF_FORMFIELD_XFA_COMBOBOX 10    // XFA combo box type.
#define FPDF_FORMFIELD_XFA_IMAGEFIELD 11  // XFA image field type.
#define FPDF_FORMFIELD_XFA_LISTBOX 12     // XFA list box type.
#define FPDF_FORMFIELD_XFA_PUSHBUTTON 13  // XFA push button type.
#define FPDF_FORMFIELD_XFA_SIGNATURE 14   // XFA signture field type.
#define FPDF_FORMFIELD_XFA_TEXTFIELD 15   // XFA text field type.
#endif                                    // PDF_ENABLE_XFA

#ifndef PDF_ENABLE_XFA
#define FPDF_FORMFIELD_COUNT 8
#else
#define FPDF_FORMFIELD_COUNT 16
#endif  // PDF_ENABLE_XFA

#ifdef PDF_ENABLE_XFA
#define IS_XFA_FORMFIELD(type)                                              \
  ((type == FPDF_FORMFIELD_XFA) || (type == FPDF_FORMFIELD_XFA_CHECKBOX) || \
   (type == FPDF_FORMFIELD_XFA_COMBOBOX) ||                                 \
   (type == FPDF_FORMFIELD_XFA_IMAGEFIELD) ||                               \
   (type == FPDF_FORMFIELD_XFA_LISTBOX) ||                                  \
   (type == FPDF_FORMFIELD_XFA_PUSHBUTTON) ||                               \
   (type == FPDF_FORMFIELD_XFA_SIGNATURE) ||                                \
   (type == FPDF_FORMFIELD_XFA_TEXTFIELD))
#endif  // PDF_ENABLE_XFA

/**
 * Function: FPDFPage_HasFormFieldAtPoint
 *     Get the form field type by point.
 * Parameters:
 *     hHandle     -   Handle to the form fill module. Returned by
 *                     FPDFDOC_InitFormFillEnvironment().
 *     page        -   Handle to the page. Returned by FPDF_LoadPage().
 *     page_x      -   X position in PDF "user space".
 *     page_y      -   Y position in PDF "user space".
 * Return Value:
 *     Return the type of the form field; -1 indicates no field.
 *     See field types above.
 **/
FPDF_EXPORT int FPDF_CALLCONV
FPDFPage_HasFormFieldAtPoint(FPDF_FORMHANDLE hHandle,
                             FPDF_PAGE page,
                             double page_x,
                             double page_y);

/**
 * Function: FPDFPage_FormFieldZOrderAtPoint
 *     Get the form field z-order by point.
 * Parameters:
 *     hHandle     -   Handle to the form fill module. Returned by
 *                     FPDFDOC_InitFormFillEnvironment().
 *     page        -   Handle to the page. Returned by FPDF_LoadPage().
 *     page_x      -   X position in PDF "user space".
 *     page_y      -   Y position in PDF "user space".
 * Return Value:
 *     Return the z-order of the form field; -1 indicates no field.
 *     Higher numbers are closer to the front.
 **/
FPDF_EXPORT int FPDF_CALLCONV
FPDFPage_FormFieldZOrderAtPoint(FPDF_FORMHANDLE hHandle,
                                FPDF_PAGE page,
                                double page_x,
                                double page_y);

/**
 * Function: FPDF_SetFormFieldHighlightColor
 *          Set the highlight color of specified or all the form fields in the
 *document.
 * Parameters:
 *          hHandle     -   Handle to the form fill module. Returned by
 *FPDFDOC_InitFormFillEnvironment.
 *          doc         -   Handle to the document. Returned by
 *FPDF_LoadDocument function.
 *          fieldType   -   A 32-bit integer indicating the type of a form
 *field(defined above).
 *          color       -   The highlight color of the form field.Constructed by
 *0xxxrrggbb.
 * Return Value:
 *          NONE.
 * Comments:
 *          When the parameter fieldType is set to FPDF_FORMFIELD_UNKNOWN, the
 *          highlight color will be applied to all the form fields in the
 *          document.
 *          Please refresh the client window to show the highlight immediately
 *          if necessary.
 **/
FPDF_EXPORT void FPDF_CALLCONV
FPDF_SetFormFieldHighlightColor(FPDF_FORMHANDLE hHandle,
                                int fieldType,
                                unsigned long color);

/**
 * Function: FPDF_SetFormFieldHighlightAlpha
 *          Set the transparency of the form field highlight color in the
 *document.
 * Parameters:
 *          hHandle     -   Handle to the form fill module. Returned by
 *FPDFDOC_InitFormFillEnvironment.
 *          doc         -   Handle to the document. Returned by
 *FPDF_LoadDocument function.
 *          alpha       -   The transparency of the form field highlight color.
 *between 0-255.
 * Return Value:
 *          NONE.
 **/
FPDF_EXPORT void FPDF_CALLCONV
FPDF_SetFormFieldHighlightAlpha(FPDF_FORMHANDLE hHandle, unsigned char alpha);

/**
 * Function: FPDF_RemoveFormFieldHighlight
 *          Remove the form field highlight color in the document.
 * Parameters:
 *          hHandle     -   Handle to the form fill module. Returned by
 *FPDFDOC_InitFormFillEnvironment.
 * Return Value:
 *          NONE.
 * Comments:
 *          Please refresh the client window to remove the highlight immediately
 *if necessary.
 **/
FPDF_EXPORT void FPDF_CALLCONV
FPDF_RemoveFormFieldHighlight(FPDF_FORMHANDLE hHandle);

/**
* Function: FPDF_FFLDraw
*           Render FormFields and popup window on a page to a device independent
*bitmap.
* Parameters:
*           hHandle     -   Handle to the form fill module. Returned by
*FPDFDOC_InitFormFillEnvironment.
*           bitmap      -   Handle to the device independent bitmap (as the
*output buffer).
*                           Bitmap handle can be created by FPDFBitmap_Create
*function.
*           page        -   Handle to the page. Returned by FPDF_LoadPage
*function.
*           start_x     -   Left pixel position of the display area in the
*device coordinate.
*           start_y     -   Top pixel position of the display area in the device
*coordinate.
*           size_x      -   Horizontal size (in pixels) for displaying the page.
*           size_y      -   Vertical size (in pixels) for displaying the page.
*           rotate      -   Page orientation: 0 (normal), 1 (rotated 90 degrees
*clockwise),
*                               2 (rotated 180 degrees), 3 (rotated 90 degrees
*counter-clockwise).
*           flags       -   0 for normal display, or combination of flags
*defined above.
* Return Value:
*           None.
* Comments:
*           This function is designed to render annotations that are
*user-interactive, which are widget annotation (for FormFields) and popup
*annotation.
*           With FPDF_ANNOT flag, this function will render popup annotation
*when users mouse-hover on non-widget annotation. Regardless of FPDF_ANNOT flag,
*this function will always render widget annotations for FormFields.
*           In order to implement the FormFill functions, implementation should
*call this function after rendering functions, such as FPDF_RenderPageBitmap or
*FPDF_RenderPageBitmap_Start, finish rendering the page contents.
**/
FPDF_EXPORT void FPDF_CALLCONV FPDF_FFLDraw(FPDF_FORMHANDLE hHandle,
                                            FPDF_BITMAP bitmap,
                                            FPDF_PAGE page,
                                            int start_x,
                                            int start_y,
                                            int size_x,
                                            int size_y,
                                            int rotate,
                                            int flags);

#ifdef _SKIA_SUPPORT_
FPDF_EXPORT void FPDF_CALLCONV FPDF_FFLRecord(FPDF_FORMHANDLE hHandle,
                                              FPDF_RECORDER recorder,
                                              FPDF_PAGE page,
                                              int start_x,
                                              int start_y,
                                              int size_x,
                                              int size_y,
                                              int rotate,
                                              int flags);
#endif

/**
 * Experimental API
 * Function: FPDF_GetFormType
 *           Returns the type of form contained in the PDF document.
 * Parameters:
 *           document - Handle to document.
 * Return Value:
 *           Integer value representing one of the FORMTYPE_ values.
 * Comments:
 *           If |document| is NULL, then the return value is FORMTYPE_NONE.
 **/
FPDF_EXPORT int FPDF_CALLCONV FPDF_GetFormType(FPDF_DOCUMENT document);

#ifdef PDF_ENABLE_XFA
/**
 * Function: FPDF_LoadXFA
 *          If the document consists of XFA fields, there should call this
 *method to load XFA fields.
 * Parameters:
 *          document        -   Handle to document. Returned by
 *FPDF_LoadDocument function.
 * Return Value:
 *          TRUE indicates success,otherwise FALSE.
 **/
FPDF_EXPORT FPDF_BOOL FPDF_CALLCONV FPDF_LoadXFA(FPDF_DOCUMENT document);
#endif  // PDF_ENABLE_XFA

#ifdef __cplusplus
}
#endif

#endif  // PUBLIC_FPDF_FORMFILL_H_