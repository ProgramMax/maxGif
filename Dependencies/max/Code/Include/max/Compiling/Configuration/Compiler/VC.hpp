// Copyright 2015, The max Contributors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MAX_COMPILING_CONFIGURATION_COMPILER_VC_HPP
#define MAX_COMPILING_CONFIGURATION_COMPILER_VC_HPP

#define MAX_COMPILER_VC
#if _MSC_VER == 800
	// VC 1.0
	#define MAX_COMPILER_VERSION_MAJOR 1
	#define MAX_COMPILER_VERSION_MINOR 0
#elif _MSC_VER == 900
	// VC 3.0
	#define MAX_COMPILER_VERSION_MAJOR 3
	#define MAX_COMPILER_VERSION_MINOR 0
#elif _MSC_VER == 1000
	// VC 4.0
	#define MAX_COMPILER_VERSION_MAJOR 4
	#define MAX_COMPILER_VERSION_MINOR 0
#elif _MSC_VER == 1020
	// VC 4.2
	#define MAX_COMPILER_VERSION_MAJOR 4
	#define MAX_COMPILER_VERSION_MINOR 2
#elif _MSC_VER == 1100
	// VC 5.0
	#define MAX_COMPILER_VERSION_MAJOR 5
	#define MAX_COMPILER_VERSION_MINOR 0
#elif _MSC_VER == 1200
	// VC 6.0 or 6.0 SP6
	#define MAX_COMPILER_VERSION_MAJOR 6
	#define MAX_COMPILER_VERSION_MINOR 0
#elif _MSC_VER == 1300
	// VC 7.0 (2002)
	#define MAX_COMPILER_VERSION_MAJOR 7
	#define MAX_COMPILER_VERSION_MINOR 0
#elif _MSC_VER == 1310
	// VC 7.1 (2003)
	#define MAX_COMPILER_VERSION_MAJOR 7
	#define MAX_COMPILER_VERSION_MINOR 1
#elif _MSC_VER == 1400
	// VC 8.0 (2005)
	#define MAX_COMPILER_VERSION_MAJOR 8
	#define MAX_COMPILER_VERSION_MINOR 0
#elif _MSC_VER == 1500
	// VC 9.0 (2008)
	#define MAX_COMPILER_VERSION_MAJOR 9
	#define MAX_COMPILER_VERSION_MINOR 0
#elif _MSC_VER == 1600
	// VC 10.0 (2010)
	#define MAX_COMPILER_VERSION_MAJOR 10
	#define MAX_COMPILER_VERSION_MINOR  0
#elif _MSC_VER == 1700
	// VC 11.0 (2012)
	#define MAX_COMPILER_VERSION_MAJOR 11
	#define MAX_COMPILER_VERSION_MINOR  0
#elif _MSC_VER == 1800
	// VC 12.0 (2013)
	#define MAX_COMPILER_VERSION_MAJOR 12
	#define MAX_COMPILER_VERSION_MINOR  0
#elif _MSC_VER == 1900
	// VC 14.0 (2015)
	#define MAX_COMPILER_VERSION_MAJOR 14
	#define MAX_COMPILER_VERSION_MINOR  0
#endif
#define MAX_COMPILER_VERSION_PATCH 0


// VC sets _CPPUNWIND on /EHsc but not /EHa ... I think?
#if defined(_CPPUNWIND)
	#define MAX_EXCEPTIONS_SUPPORTED
#endif

#if _MSC_FULL_VER >= 180021114
	#define MAX_NOEXCEPT_SUPPORTED
#endif

#if _MSC_VER >= 1900
	#define	MAX_INLINE_NAMESPACES_SUPPORTED
#endif

#if _MSC_VER > 1900
	#error "Unknown compiler version"
#endif

#endif // #ifndef MAX_COMPILING_CONFIGURATION_COMPILER_VC_HPP
