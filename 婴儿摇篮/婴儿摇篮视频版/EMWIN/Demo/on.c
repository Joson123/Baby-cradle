/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                           www.segger.com                           *
**********************************************************************
*                                                                    *
* C-file generated by                                                *
*                                                                    *
*        Bitmap Converter (ST) for emWin V5.26.                      *
*        Compiled Aug  8 2014, 14:49:30                              *
*                                                                    *
*        (c) 1998 - 2014 Segger Microcontroller GmbH & Co. KG        *
*                                                                    *
**********************************************************************
*                                                                    *
* Source file: on                                                    *
* Dimensions:  74 * 30                                               *
* NumColors:   16bpp: 65536                                          *
*                                                                    *
**********************************************************************
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
#define GUI_CONST_STORAGE const
#endif

extern GUI_CONST_STORAGE GUI_BITMAP bmon;

static GUI_CONST_STORAGE unsigned short _acon[] =
{
    0x3985, 0x5269, 0x5269, 0x4A27, 0x49E5, 0x49E5, 0x49E5, 0x2103, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x8AC1, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x8AC1, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x8AC1, 0x8AC1, 0x6A63,
    0x6A63, 0x6A63, 0x6A63, 0x8AC1, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x8AC1, 0x8AC1, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x8AC1, 0x8AC1, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x49E5, 0x6A63, 0x8389, 0x8389, 0x8389, 0x5269, 0x8389, 0x5269, 0x5269,
    0x5269, 0x8389, 0x8389, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x3985, 0x3985, 0x3985, 0x3985,
    0x4A27, 0x5269, 0x5269, 0x4A27, 0x49E5, 0x6A63, 0x6A63, 0x6A63, 0x8AC1, 0x6A63, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x6A63, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1,
    0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8389, 0x8389, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269,
    0x5269, 0x5269, 0x5269, 0x8389, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x3985, 0x3985, 0x3985, 0x3985,
    0x5269, 0x4A27, 0x4A27, 0x49E5, 0x49E5, 0x6A63, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0xB382, 0xB382, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1,
    0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0xB382, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x9B43, 0x8AC1, 0x6A63, 0x8AC1, 0x8389, 0x8389, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269,
    0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x3985, 0x3985, 0x3985,
    0x4A27, 0x4A27, 0x49E5, 0x49E5, 0x6A63, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0xB382, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0xB382, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0xB382, 0xB382, 0xB382, 0x8AC1, 0x8AC1, 0xB382, 0x8AC1, 0xB382,
    0xB382, 0x8AC1, 0x8AC1, 0xB382, 0x8AC1, 0xB382, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0xB382, 0xB382, 0x8AC1, 0x8AC1, 0x8AC1, 0xB382, 0x8AC1, 0x9B43, 0x8AC1, 0x8AC1, 0x8389, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269,
    0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x3985, 0x3985,
    0x4A27, 0x4A27, 0x6A63, 0x6A63, 0x8AC1, 0x8AC1, 0x8AC1, 0xB382, 0x8AC1, 0x8AC1, 0x8AC1, 0xB382, 0xB382, 0x8AC1, 0xB382, 0x8AC1, 0x8AC1, 0xB382, 0xB382, 0x8AC1, 0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0x8AC1, 0xC3E2, 0x8AC1, 0xB382, 0xB382, 0xC3E2,
    0x8AC1, 0xB382, 0x8AC1, 0xB382, 0x8AC1, 0xB382, 0x8AC1, 0xB382, 0xB382, 0x8AC1, 0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0x8AC1, 0xB382, 0x9B43, 0x9B43, 0x8389, 0x6A63, 0x5269, 0x5269, 0x5269, 0x4A27, 0x5269, 0x5269, 0x5269, 0x3985, 0x5269,
    0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x3985, 0x5269, 0x3985, 0x3985,
    0x4A27, 0x49E5, 0x6A63, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0xC3E2, 0xB382, 0xC3E2, 0x8AC1, 0xB382, 0xB382, 0xB382, 0xC3E2, 0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0x8AC1, 0xB382, 0xB382, 0xB382, 0xC3E2, 0x8AC1, 0xB382, 0xB382, 0xB382, 0x8AC1,
    0xB382, 0xC3E2, 0xB382, 0xC3E2, 0xB382, 0xB382, 0xB382, 0xC3E2, 0x8AC1, 0xB382, 0xB382, 0x8AC1, 0xC3E2, 0xB382, 0xB382, 0xB382, 0xB382, 0x8AC1, 0x8389, 0x8389, 0x5269, 0x4A27, 0x5269, 0x5269, 0x4A27, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269,
    0x5269, 0x5269, 0x5269, 0x3985, 0x5269, 0x3985, 0x5269, 0x5269, 0x5269, 0x5269, 0x3985, 0x5269, 0x3985,
    0x49E5, 0x6A63, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0xC3E2, 0xB382, 0xB382, 0xB382,
    0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0xC3E2, 0xB382, 0xB382, 0xC3E2, 0xC3E2, 0xB382, 0xB382, 0xC3E2, 0xB382, 0xB382, 0xB382, 0xB382, 0x8389, 0x8389, 0x5269, 0x5269, 0x5269, 0x5269, 0x4A27, 0x4A27, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269,
    0x5269, 0x5269, 0x3985, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x3985, 0x3985, 0x3985,
    0x6A63, 0x6A63, 0x8AC1, 0x8AC1, 0x8AC1, 0xB382, 0xB382, 0xB382, 0xB382, 0xC3E2, 0xB382, 0xB382, 0xC3E2, 0xC3E2, 0xB382, 0xB382, 0xC3E2, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0xB382, 0xC3E2, 0xC3E2, 0xB382, 0xC3E2, 0x8AC1, 0x8AC1, 0xC3E2, 0xB382, 0xB382,
    0xC3E2, 0xC3E2, 0x8AC1, 0x8AC1, 0xB382, 0xC3E2, 0xB382, 0xC3E2, 0xB382, 0xB382, 0xC3E2, 0xB382, 0xB382, 0xB382, 0xC3E2, 0x9B43, 0x9B43, 0x9B43, 0x5269, 0x5269, 0x6A63, 0x5269, 0x6A63, 0x5269, 0x4A27, 0x3985, 0x5269, 0x5269, 0x5269, 0x5269,
    0x5269, 0x3985, 0x3985, 0x3985, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x3985, 0x3985, 0x5269,
    0x6A63, 0x8AC1, 0x8AC1, 0x8AC1, 0x8AC1, 0xB382, 0xB382, 0xB382, 0xC3E2, 0xB382, 0xB382, 0xC3E2, 0xB382, 0xB382, 0xC3E2, 0xB382, 0x6A63, 0xBC68, 0xDE34, 0xDE34, 0x8389, 0x6A63, 0xB382, 0xC3E2, 0xC3E2, 0xB382, 0x8389, 0x8389, 0x9B43, 0xB382, 0xC403,
    0xB382, 0xC3E2, 0x8389, 0xBC68, 0xC3E2, 0xB382, 0xC3E2, 0xC3E2, 0xB382, 0xC3E2, 0xB382, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xB382, 0x8AC1, 0x6A63, 0x5269, 0x5269, 0x5269, 0x3985, 0x5269, 0x5269, 0x3985, 0x3985, 0x5269, 0x5269, 0x5269, 0x5269,
    0x5269, 0x3985, 0x3985, 0x3985, 0x5269, 0x5269, 0x3985, 0x5269, 0x5269, 0x5269, 0x5269, 0x3985, 0x3985,
    0x8AC1, 0x8AC1, 0x8AC1, 0xB382, 0xB382, 0xB382, 0xB382, 0xC3E2, 0xC3E2, 0xB382, 0xC3E2, 0xB382, 0xC3E2, 0xC3E2, 0xC3E2, 0x8AC1, 0xEF3A, 0xEF3A, 0xEF3A, 0xEF3A, 0xEF3A, 0xEF3A, 0x8389, 0xB382, 0xB382, 0xBC68, 0xEF3A, 0xEF3A, 0xDE34, 0x9B43, 0xC403,
    0xB382, 0xBC68, 0xEF3A, 0xDE34, 0xB382, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xB382, 0xC3E2, 0xC3E2, 0xB382, 0x8389, 0x5269, 0x4A27, 0x5269, 0x4A27, 0x5269, 0x5269, 0x5269, 0x5269, 0x3985, 0x5269, 0x3985, 0x5269, 0x3985,
    0x5269, 0x3985, 0x3985, 0x3985, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x3985, 0x3985,
    0x8AC1, 0x8AC1, 0x8AC1, 0xB382, 0xB382, 0xC3E2, 0xB382, 0xB382, 0xB382, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xB382, 0x8AC1, 0xDE34, 0xEF3A, 0xEF3A, 0xEF3A, 0xDE34, 0xEF3A, 0xEF3A, 0xEF3A, 0x8389, 0xC3E2, 0xBC68, 0xEF3A, 0xEF3A, 0xEF3A, 0x9B43, 0xC403,
    0xC403, 0xDE34, 0xEF3A, 0xDE34, 0xB382, 0xB382, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xB382, 0xB382, 0x8389, 0x6A63, 0x5269, 0x5269, 0x5269, 0x5269, 0x3985, 0x5269, 0x3985, 0x3985, 0x3985, 0x5269, 0x5269, 0x5269,
    0x3985, 0x3985, 0x3985, 0x5269, 0x3985, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x4A27, 0x3985,
    0x8AC1, 0x8AC1, 0x8AC1, 0xB382, 0xB382, 0xB382, 0xB382, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xB382, 0xBC68, 0xEF3A, 0xEF3A, 0xBC68, 0xB382, 0xC3E2, 0xBC68, 0xEF3A, 0xEF3A, 0xBC68, 0xB382, 0xBC68, 0xEF3A, 0xEF3A, 0xEF3A, 0xDE34, 0x9B43,
    0xB382, 0xBC68, 0xEF3A, 0xDE34, 0xBC68, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0x9B43, 0x6A63, 0x8389, 0x5269, 0x5269, 0x3985, 0x5269, 0x5269, 0x3985, 0x5269, 0x3985, 0x5269, 0x5269, 0x3985, 0x3985,
    0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x5269, 0x3985, 0x5269, 0x3985, 0x5269, 0x4A27, 0x2103,
    0x8AC1, 0x8AC1, 0xB382, 0xB382, 0xB382, 0xB382, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xB382, 0xDE34, 0xEF3A, 0xDE34, 0x9B43, 0xC3E2, 0xC3E2, 0xC3E2, 0xDE34, 0xEF3A, 0xDE34, 0xBC68, 0xBC68, 0xEF3A, 0xEF3A, 0xEF3A, 0xEF3A, 0x9B43,
    0xB382, 0xDE34, 0xEF3A, 0xDE34, 0xC3E2, 0xB382, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0x9B43, 0x5269, 0x6A63, 0x4A27, 0x4A27, 0x4A27, 0x5269, 0x5269, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x5269, 0x5269,
    0x3985, 0x3985, 0x3985, 0x3985, 0x5269, 0x5269, 0x3985, 0x5269, 0x3985, 0x3985, 0x5269, 0x3985, 0x3985,
    0x8AC1, 0x8AC1, 0xB382, 0xB382, 0xB382, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xB382, 0xDE34, 0xEF3A, 0xDE34, 0xC3E2, 0xB382, 0xC3E2, 0xC3E2, 0xBC68, 0xEF3A, 0xEF3A, 0x9B43, 0xBC68, 0xEF3A, 0xEF3A, 0xDE34, 0xEF3A, 0xDE34,
    0x9B43, 0xDE34, 0xEF3A, 0xDE34, 0xB382, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0x9B43, 0x5269, 0x5269, 0x4A27, 0x4A27, 0x4A27, 0x3985, 0x5269, 0x3985, 0x5269, 0x3985, 0x3985, 0x5269, 0x3985, 0x3985,
    0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x5269, 0x2103,
    0x8AC1, 0x8AC1, 0x8AC1, 0xC3E2, 0xB382, 0xB382, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xB382, 0xBC68, 0xEF3A, 0xEF3A, 0xBC68, 0xB382, 0xC3E2, 0xC3E2, 0xC3E2, 0xBC68, 0xEF3A, 0xEF3A, 0x8389, 0xBC68, 0xEF3A, 0xEF3A, 0x8389, 0xEF3A, 0xEF3A,
    0x8389, 0xDE34, 0xEF3A, 0xDE34, 0xBC68, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0x8AC1, 0x6A63, 0x4A27, 0x4A27, 0x4A27, 0x4A27, 0x5269, 0x3985, 0x5269, 0x3985, 0x5269, 0x3985, 0x3985, 0x5269, 0x3985,
    0x2103, 0x3985, 0x3985, 0x3985, 0x5269, 0x3985, 0x5269, 0x3985, 0x5269, 0x5269, 0x3985, 0x4A27, 0x2103,
    0x8AC1, 0x8AC1, 0xB382, 0xB382, 0xB382, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0x9B43, 0xEF3A, 0xEF3A, 0xBC68, 0xC3E2, 0xBC68, 0xC3E2, 0xC3E2, 0xBC68, 0xEF3A, 0xEF3A, 0xB382, 0xBC68, 0xEF3A, 0xEF3A, 0x9B43, 0xDE34, 0xEF3A,
    0xDE34, 0x8389, 0xEF3A, 0xDE34, 0xB382, 0xC3E2, 0xBC68, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0xC3E2, 0x8AC1, 0x5269, 0x4A27, 0x4A27, 0x4A27, 0x4A27, 0x3985, 0x5269, 0x3985, 0x3985, 0x3985, 0x3985, 0x5269, 0x3985, 0x5269,
    0x3985, 0x2103, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x5269, 0x3985, 0x3985, 0x5269, 0x3985, 0x2103,
    0x8AC1, 0xB382, 0x8AC1, 0xC3E2, 0xB382, 0xB382, 0xC3E2, 0xC3E2, 0xC403, 0xC403, 0xC403, 0xC403, 0xB382, 0xBC68, 0xDE34, 0xEF3A, 0xBC68, 0xBC68, 0xC403, 0xC403, 0xB382, 0xBC68, 0xEF3A, 0xEF3A, 0xB382, 0xBC68, 0xEF3A, 0xEF3A, 0xB382, 0xBC68, 0xDE34,
    0xEF3A, 0xDE34, 0xEF3A, 0xDE34, 0xBC68, 0xC403, 0xB382, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0x6A63, 0x8389, 0x4A27, 0x4A27, 0x4A27, 0x49E5, 0x4A27, 0x4A27, 0x3985, 0x4A27, 0x3985, 0x3985, 0x3985, 0x4A27, 0x3985,
    0x2103, 0x3985, 0x3985, 0x3985, 0x3985, 0x4A27, 0x3985, 0x5269, 0x3985, 0x5269, 0x3985, 0x3985, 0x2103,
    0x8AC1, 0x8AC1, 0xB382, 0x9B43, 0xB382, 0xC3E2, 0xC3E2, 0xC3E2, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xB382, 0xDE34, 0xEF3A, 0xDE34, 0x9B43, 0xB382, 0x9B43, 0x9B43, 0xDE34, 0xEF3A, 0xDE34, 0xB382, 0xBC68, 0xEF3A, 0xEF3A, 0xBC68, 0xB382, 0xDE34,
    0xEF3A, 0xEF3A, 0xEF3A, 0xDE34, 0x9B43, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xB382, 0xC403, 0xC403, 0xC403, 0x9B43, 0x6A63, 0x6A63, 0x4A27, 0x4A27, 0x3985, 0x3985, 0x4A27, 0x3985, 0x3985, 0x3985, 0x3985, 0x4A27, 0x3985, 0x4A27,
    0x3985, 0x3985, 0x2103, 0x3985, 0x3985, 0x3985, 0x5269, 0x3985, 0x5269, 0x3985, 0x5269, 0x3985, 0x3985,
    0x8AC1, 0x9B43, 0x9B43, 0xB382, 0xB382, 0xB382, 0xB382, 0xC3E2, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xBC68, 0xEF3A, 0xEF3A, 0xDE34, 0x6A63, 0x8389, 0xDE34, 0xEF3A, 0xEF3A, 0xBC68, 0xC403, 0xBC68, 0xEF3A, 0xEF3A, 0xB382, 0xC403, 0xBC68,
    0xDE34, 0xEF3A, 0xEF3A, 0xDE34, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0x9B43, 0x5269, 0x4A27, 0x49E5, 0x3985, 0x4A27, 0x49E5, 0x3985, 0x3985, 0x49E5, 0x3985, 0x3985, 0x3985, 0x4A27, 0x3985,
    0x3985, 0x2103, 0x3985, 0x3985, 0x3985, 0x3985, 0x4A27, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x2103,
    0x8AC1, 0x9B43, 0xB382, 0xB382, 0xB382, 0xB382, 0xC3E2, 0xC3E2, 0xC403, 0xC403, 0xC403, 0xB382, 0xC403, 0xC403, 0xBC68, 0xDE34, 0xEF3A, 0xEF3A, 0xEF3A, 0xDE34, 0xEF3A, 0xEF3A, 0xDE34, 0xBC68, 0xC403, 0xBC68, 0xEF3A, 0xEF3A, 0xB382, 0xC403, 0xC403,
    0xDE34, 0xEF3A, 0xEF3A, 0xDE34, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0x9B43, 0x6A63, 0x6A63, 0x4A27, 0x49E5, 0x3985, 0x4A27, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985,
    0x3985, 0x2103, 0x2103, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x5269, 0x5269, 0x3985, 0x2103, 0x3985,
    0x6A63, 0x8AC1, 0x9B43, 0x9B43, 0xB382, 0xC3E2, 0xB382, 0xC3E2, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xDE34, 0xEF3A, 0xEF3A, 0xEF3A, 0xEF3A, 0xDE34, 0xC403, 0xC403, 0xC403, 0xBC68, 0xEF3A, 0xEF3A, 0x9B43, 0xC403, 0xC403,
    0xBC68, 0xEF3A, 0xEF3A, 0xDE34, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xB382, 0x6A63, 0x4A27, 0x49E5, 0x3985, 0x4A27, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x5269, 0x3985,
    0x3985, 0x2103, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x4A27, 0x3985, 0x3985, 0x3985, 0x2103, 0x2103,
    0x6A63, 0x8AC1, 0x8AC1, 0x9B43, 0x9B43, 0xB382, 0xB382, 0xC3E2, 0xB382, 0xC403, 0xC403, 0xB382, 0xB382, 0xC403, 0xC403, 0xC403, 0xC403, 0xBC68, 0xBC68, 0xBC68, 0x8389, 0x9B43, 0xC403, 0xC403, 0xC403, 0xBC68, 0x9B43, 0x9B43, 0xBC68, 0xC403, 0xC403,
    0xB382, 0x8389, 0xB382, 0xBC68, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0x6A63, 0x6A63, 0x49E5, 0x49E5, 0x49E5, 0x3985, 0x49E5, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985,
    0x5269, 0x3985, 0x2103, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x4A27, 0x3985, 0x2103, 0x2103,
    0x6A63, 0x6A63, 0x9B43, 0x9B43, 0x9B43, 0xB382, 0x9B43, 0xB382, 0xC403, 0xB382, 0xB382, 0xC403, 0xC403, 0xB382, 0xB382, 0xBC68, 0xB382, 0xC403, 0xC403, 0xC403, 0xB382, 0xC403, 0xB382, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xC403, 0xB382, 0xBC68,
    0xC403, 0xB382, 0xB382, 0xB382, 0xB382, 0x9B43, 0xC403, 0xB382, 0xC403, 0xC403, 0xB382, 0xB382, 0xC403, 0xC403, 0xB382, 0xC403, 0x9B43, 0x8AC1, 0x4A27, 0x4A27, 0x3985, 0x49E5, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985,
    0x3985, 0x2103, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x2103, 0x3985, 0x2103,
    0x49E5, 0x6A63, 0x8AC1, 0x9B43, 0x9B43, 0x9B43, 0x9B43, 0xC3E2, 0xC403, 0x9B43, 0xC403, 0xB382, 0xB382, 0xC403, 0xC403, 0xB382, 0xB382, 0xC403, 0xB382, 0xB382, 0xC403, 0xC403, 0xB382, 0xB382, 0xC403, 0x9B43, 0xC403, 0xC403, 0x9B43, 0xC403, 0xC403,
    0xB382, 0xC403, 0xC403, 0xB382, 0xC403, 0xC403, 0xB382, 0xC403, 0xC403, 0xB382, 0xC403, 0xC403, 0xB382, 0xB382, 0xC403, 0xC403, 0x9B43, 0x6A63, 0x6A63, 0x49E5, 0x49E5, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985,
    0x3985, 0x3985, 0x2103, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x2103, 0x2103, 0x2103, 0x2103,
    0x3985, 0x6A63, 0x6A63, 0x8AC1, 0x8AC1, 0x9B43, 0xB382, 0xB382, 0x9B43, 0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0xC403, 0xB382, 0x9B43, 0xC403, 0xB382, 0xB382, 0xB382, 0xC403, 0xB382, 0xC403, 0xC403, 0xB382, 0xB382, 0xC403, 0x9B43, 0xC403,
    0xC403, 0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0xC403, 0xB382, 0x9B43, 0xB382, 0xB382, 0xB382, 0xB382, 0xC403, 0xB382, 0xB382, 0xC403, 0x8AC1, 0x6A63, 0x49E5, 0x49E5, 0x49E5, 0x2103, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985,
    0x3985, 0x3985, 0x3985, 0x2103, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x2103, 0x2103, 0x2103, 0x2103,
    0x3985, 0x4A27, 0x49E5, 0x6A63, 0x8AC1, 0x9B43, 0x9B43, 0x9B43, 0xB382, 0x9B43, 0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0x9B43, 0xC403, 0x9B43, 0xB382, 0xB382, 0xB382, 0x9B43, 0xB382, 0x9B43, 0x9B43, 0x9B43, 0xB382, 0x9B43, 0xC403, 0x9B43,
    0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0xC403, 0x9B43, 0x9B43, 0xC403, 0xB382, 0xB382, 0xB382, 0xB382, 0xB382, 0x9B43, 0xB382, 0xB382, 0x9B43, 0x8AC1, 0x6A63, 0x49E5, 0x49E5, 0x49E5, 0x3985, 0x3985, 0x3985, 0x3985, 0x2103, 0x3985, 0x3985,
    0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x2103, 0x2103, 0x2103, 0x2103, 0x3985,
    0x3985, 0x3985, 0x49E5, 0x4A27, 0x6A63, 0x6A63, 0x8AC1, 0x9B43, 0x9B43, 0xB382, 0x9B43, 0x9B43, 0xB382, 0x9B43, 0x9B43, 0xB382, 0xB382, 0x9B43, 0xB382, 0x9B43, 0x9B43, 0xB382, 0x9B43, 0xB382, 0x9B43, 0x9B43, 0xB382, 0x9B43, 0x9B43, 0x9B43, 0x9B43,
    0x9B43, 0x9B43, 0x9B43, 0x9B43, 0xB382, 0x9B43, 0x9B43, 0xB382, 0x9B43, 0xB382, 0xB382, 0x9B43, 0xB382, 0x9B43, 0xB382, 0x9B43, 0xB382, 0xB382, 0x8AC1, 0x6A63, 0x6A63, 0x49E5, 0x3985, 0x2103, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985,
    0x3985, 0x3985, 0x3985, 0x3985, 0x2103, 0x3985, 0x3985, 0x2103, 0x2103, 0x2103, 0x2103, 0x2103, 0x3985,
    0x3985, 0x3985, 0x49E5, 0x4A27, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x9B43, 0x6A63, 0x9B43, 0x9B43, 0x9B43, 0x9B43, 0x9B43, 0x9B43, 0x9B43, 0x9B43, 0x9B43, 0x9B43, 0x9B43, 0x9B43, 0x9B43, 0x9B43, 0x9B43, 0x9B43, 0x9B43, 0x9B43, 0x9B43, 0x9B43, 0x9B43,
    0x9B43, 0x9B43, 0x9B43, 0x9B43, 0x9B43, 0x9B43, 0x9B43, 0x9B43, 0x9B43, 0x9B43, 0x9B43, 0x8AC1, 0x8AC1, 0x9B43, 0x9B43, 0x9B43, 0x9B43, 0x8AC1, 0x9B43, 0x6A63, 0x6A63, 0x6A63, 0x49E5, 0x49E5, 0x49E5, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985,
    0x3985, 0x3985, 0x2103, 0x3985, 0x3985, 0x3985, 0x2103, 0x2103, 0x2103, 0x2103, 0x2103, 0x2103, 0x2103,
    0x3985, 0x3985, 0x3985, 0x3985, 0x4A27, 0x4A27, 0x49E5, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x8AC1, 0x6A63, 0x6A63, 0x8AC1, 0x6A63, 0x6A63, 0x6A63, 0x9B43, 0x6A63, 0x6A63, 0x9B43, 0x6A63, 0x6A63, 0x6A63,
    0x9B43, 0x6A63, 0x6A63, 0x9B43, 0x6A63, 0x6A63, 0x6A63, 0x9B43, 0x6A63, 0x6A63, 0x8AC1, 0x6A63, 0x6A63, 0x6A63, 0x8AC1, 0x8AC1, 0x6A63, 0x8AC1, 0x6A63, 0x8AC1, 0x6A63, 0x49E5, 0x49E5, 0x49E5, 0x2103, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985,
    0x2103, 0x3985, 0x3985, 0x3985, 0x2103, 0x2103, 0x2103, 0x2103, 0x2103, 0x2103, 0x2103, 0x3985, 0x3985,
    0x3985, 0x2103, 0x3985, 0x3985, 0x3985, 0x3985, 0x4A27, 0x5269, 0x49E5, 0x6A63, 0x49E5, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x49E5, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x49E5, 0x4A27, 0x6A63, 0x49E5, 0x6A63, 0x6A63, 0x6A63, 0x49E5,
    0x6A63, 0x6A63, 0x49E5, 0x6A63, 0x49E5, 0x6A63, 0x6A63, 0x49E5, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x49E5, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x6A63, 0x49E5, 0x49E5, 0x3985, 0x2103, 0x6A63, 0x3985, 0x3985, 0x3985, 0x3985, 0x3985,
    0x3985, 0x3985, 0x2103, 0x2103, 0x2103, 0x2103, 0x2103, 0x2103, 0x2103, 0x2103, 0x2103, 0x3985, 0x3985
};

GUI_CONST_STORAGE GUI_BITMAP bmon =
{
    74, // xSize
    30, // ySize
    148, // BytesPerLine
    16, // BitsPerPixel
    (unsigned char *)_acon,  // Pointer to picture data
    NULL,  // Pointer to palette
    GUI_DRAW_BMP565
};

/*************************** End of file ****************************/
