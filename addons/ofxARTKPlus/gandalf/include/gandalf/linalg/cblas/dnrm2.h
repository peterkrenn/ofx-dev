/**************************************************************************
*
* File:          $RCSfile: dnrm2.h,v $
* Module:        BLAS function
* Part of:       Gandalf Library
*
* Revision:      $Revision: 1.3 $
* Last edited:   $Date: 2005/02/25 09:30:20 $
* Author:        $Author: pm $
* Copyright:     Modifications (c) 2000 Imagineer Software Limited
*
* Notes:
* Private func:
* History:       Modified from original CLAPACK source code
*
**************************************************************************/

#ifndef _GAN_DNRM2_H
#define _GAN_DNRM2_H

#include <gandalf/common/misc_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

/* only declare this function locally if there is no LAPACK installed */
#if !defined(HAVE_LAPACK) || defined(FORCE_LOCAL_LAPACK)
double gan_dnrm2 ( long n, double *x, long incx );
#endif

#ifdef __cplusplus
}
#endif

#endif /* #ifndef _GAN_DNRM2_H */
