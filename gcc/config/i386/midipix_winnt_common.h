/*****************************************************************************/
/*                                                                           */
/*  midipix common definitions and source-compatibility layer                */
/*                                                                           */
/*  Copyright (C)  2014,2015  Z. Gilboa                                      */
/*                                                                           */
/*  This program is free software: you can redistribute it and/or modify     */
/*  it under the terms of the GNU General Public License as published by     */
/*  the Free Software Foundation, either version 3 of the License, or        */
/*  (at your option) any later version.                                      */
/*                                                                           */
/*  This program is distributed in the hope that it will be useful,          */
/*  but WITHOUT ANY WARRANTY; without even the implied warranty of           */
/*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the             */
/*  GNU General Public License for more details.                             */
/*                                                                           */
/*  You should have received a copy of the GNU General Public License        */
/*  along with this program. If not, see <http://www.gnu.org/licenses/>.     */
/*                                                                           */
/*****************************************************************************/

#ifndef MIDIPIX_WINNT_COMMON_H
#define MIDIPIX_WINNT_COMMON_H

/* midipix: source-compatibility: fwritable-relocated-rdata */
#ifndef IN_TARGET_LIBRARY_BUILD
	extern const int flag_writable_rel_rdata;
#else
	/* always off */
	const int x_flag_writable_rel_rdata = 0;
	#define flag_writable_rel_rdata x_flag_writable_rel_rdata
#endif


/* midipix: source-compatibility: mpe-aligned-commons */
#ifndef IN_TARGET_LIBRARY_BUILD
	extern const int use_pe_aligned_common;
#else
	/* always on */
	const int x_use_pe_aligned_common = 1;
	#define use_pe_aligned_common x_use_pe_aligned_common
#endif


/* midipix: source-compatibility: mnop-fun-dllimport */
#ifndef IN_TARGET_LIBRARY_BUILD
	extern const int TARGET_NOP_FUN_DLLIMPORT;
#else
	/* always off */
	const int x_TARGET_NOP_FUN_DLLIMPORT = 0;
	#define TARGET_NOP_FUN_DLLIMPORT x_TARGET_NOP_FUN_DLLIMPORT
#endif

#endif /* MIDIPIX_WINNT_COMMON_H */
