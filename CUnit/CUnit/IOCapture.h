/**
 * Optional support for stdout/stderr capture.
 *
 * IO capture relies on use of temporary files in the same directory as any
 * junit xml reports.
 */

/*
 *  CUnit - A Unit testing framework library for C.
 *  Copyright (C) 2001       Anil Kumar
 *  Copyright (C) 2004-2006  Anil Kumar, Jerry St.Clair
 *  Copyright (C) 2018       Ian Norton
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef CUNIT_IOCAPTURE_H
#define CUNIT_IOCAPTURE_H

#include "CUnit/CUnitCITypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Return CU_TRUE if capture of stdout/stderr into reports is supported
 * */
CU_EXPORT CU_BOOL CUnit_IOCapture_get_enabled(void);

CU_EXPORT void CUnit_IOCapture_enable(void);

CU_EXPORT void CUnit_IOCapture_disable(void);

#ifdef __cplusplus
} /* extern "C" */
#endif


#endif
