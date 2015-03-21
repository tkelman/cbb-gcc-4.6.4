/*****************************************************************************/
/*                                                                           */
/*  midipix target definitions                                               */
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

#include <stdio.h>
#include "coretypes.h"


/* identify targets */
#define TARGET_NT64				(TARGET_64BIT)
#define TARGET_NT32				(!TARGET_64BIT)


/* target constraints */
#undef  TARGET_SEH
#define TARGET_SEH				(flag_unwind_tables)

#undef  MAX_OFILE_ALIGNMENT
#define MAX_OFILE_ALIGNMENT			(8 * (2 * 4096))

#define NT64_MAX_STACK_ALIGNMENT		(8 * 16)
#define NT32_MAX_STACK_ALIGNMENT		MAX_OFILE_ALIGNMENT

#define NT64_STACK_BOUNDARY			(8 * 16)
#define NT32_STACK_BOUNDARY			BITS_PER_WORD

#undef  MAX_STACK_ALIGNMENT
#define MAX_STACK_ALIGNMENT			(TARGET_NT64                \
						? NT64_MAX_STACK_ALIGNMENT  \
						: NT32_MAX_STACK_ALIGNMENT)

#undef  STACK_BOUNDARY
#define STACK_BOUNDARY				(TARGET_NT64)            \
						? (NT64_STACK_BOUNDARY)  \
						: (NT32_STACK_BOUNDARY)

#undef  STACK_CHECK_BUILTIN
#define STACK_CHECK_BUILTIN			(1)

#undef  STACK_CHECK_STATIC_BUILTIN
#define STACK_CHECK_STATIC_BUILTIN		(1)

#undef  DEFAULT_ABI
#define DEFAULT_ABI				(TARGET_NT64)  \
						? MS_ABI       \
						: SYSV_ABI


#undef  MULTIPLE_SYMBOL_SPACES
#define MULTIPLE_SYMBOL_SPACES			(1)

#undef  MS_AGGREGATE_RETURN
#define MS_AGGREGATE_RETURN			(0)

#undef  DEFAULT_PCC_STRUCT_RETURN
#define DEFAULT_PCC_STRUCT_RETURN		(0)

#undef  NO_PROFILE_COUNTERS
#define NO_PROFILE_COUNTERS			(1)

#undef  NT_MANDATED_FLAG_PIC
#define NT_MANDATED_FLAG_PIC			(TARGET_NT64)          \
						? (flag_pic ? 1 : 0 )  \
						: 0

#undef  SUBTARGET_OVERRIDE_OPTIONS
#define SUBTARGET_OVERRIDE_OPTIONS		do {					  \
							flag_pic = NT_MANDATED_FLAG_PIC;  \
						} while (0)

#undef  PCC_BITFIELD_TYPE_MATTERS
#define PCC_BITFIELD_TYPE_MATTERS		(1)


#define TARGET_OS_CPP_BUILTINS			midipix_target_os_cpp_builtins
#define EXTRA_OS_CPP_BUILTINS			midipix_extra_os_cpp_builtins


/* general target options */
#undef  TARGET_PECOFF
#define TARGET_PECOFF				(1)

#undef  TARGET_EXECUTABLE_SUFFIX
#define TARGET_EXECUTABLE_SUFFIX		""

#undef  MATH_LIBRARY
#define MATH_LIBRARY				""

#undef  CHECK_STACK_LIMIT
#define CHECK_STACK_LIMIT			(4096 - (8*32))

#undef  TARGET_DLLIMPORT_DECL_ATTRIBUTES
#define TARGET_DLLIMPORT_DECL_ATTRIBUTES	(1)

#undef  TARGET_POSIX_IO
#define TARGET_POSIX_IO				(1)

#undef  TARGET_SUBTARGET_DEFAULT
#define TARGET_SUBTARGET_DEFAULT		(MASK_ALIGN_DOUBLE    \
						| MASK_STACK_PROBE    \
						| MASK_80387          \
						| MASK_IEEE_FP        \
						| MASK_FLOAT_RETURNS)


/* assembler options */
#undef  HAVE_GAS_PE_SECREL32_RELOC
#define HAVE_GAS_PE_SECREL32_RELOC		(1)

#undef  HAVE_GAS_BALIGN_AND_P2ALIGN
#define HAVE_GAS_BALIGN_AND_P2ALIGN		(1)

#undef  SUPPORTS_ONE_ONLY
#define SUPPORTS_ONE_ONLY			(1)

#undef  GAS_SPACE
#define GAS_SPACE				" "

#undef  GAS_TAB
#define GAS_TAB					"\t"

#undef  GAS_SECTION
#define GAS_SECTION				GAS_TAB ".section" GAS_SPACE

#undef  DRECTVE_SECTION_NAME
#define DRECTVE_SECTION_NAME			".drectve"

#undef  RODATA_SECTION_NAME
#define RODATA_SECTION_NAME			".rdata,\"r\""

#undef  GAS_PE_ASM_SET_OP
#define GAS_PE_ASM_SET_OP			"\t.set\t"

#undef  SET_ASM_OP
#define SET_ASM_OP				GAS_PE_ASM_SET_OP

#undef  READONLY_DATA_SECTION_ASM_OP
#define READONLY_DATA_SECTION_ASM_OP		GAS_SECTION RODATA_SECTION_NAME

#undef  TARGET_EMUTLS_VAR_SECTION_EMUTLS
#define TARGET_EMUTLS_VAR_SECTION_EMUTLS


/* debugging options */
#undef  PREFERRED_DEBUGGING_TYPE
#define PREFERRED_DEBUGGING_TYPE		DWARF2_DEBUG

#undef  DWARF_FRAME_REGISTERS
#define DWARF_FRAME_REGISTERS			(TARGET_NT64 ? 33 : 17)

#undef  DBX_DEBUGGING_INFO
#define DBX_DEBUGGING_INFO			(1)

#undef  SDB_DEBUGGING_INFO
#define SDB_DEBUGGING_INFO			(1)

#undef  DWARF2_DEBUGGING_INFO
#define DWARF2_DEBUGGING_INFO			(1)

#undef  HAVE_ENABLE_EXECUTE_STACK
#define HAVE_ENABLE_EXECUTE_STACK		(1)

#undef  CHECK_EXECUTE_STACK_ENABLED
#define CHECK_EXECUTE_STACK_ENABLED		(1)

#undef  DBX_REGISTER_NUMBER
#define DBX_REGISTER_NUMBER(n)			midipix_dbx_get_register_number(n)

#undef  DWARF_FRAME_REGNUM
#define DWARF_FRAME_REGNUM(n)			midipix_dbx_get_dwarf_frame_register_number(n)

#undef  ASM_OUTPUT_DWARF_OFFSET
#define ASM_OUTPUT_DWARF_OFFSET			midipix_asm_output_dwarf_offset

/* assembler labels */
#undef  USER_LABEL_PREFIX
#define USER_LABEL_PREFIX			(TARGET_NT64 ? ""   : "_")

#undef  LOCAL_LABEL_PREFIX
#define LOCAL_LABEL_PREFIX			(TARGET_NT64 ? "."  : "")

#undef  LPREFIX
#define LPREFIX					(TARGET_NT64 ? ".L" : "L")

#undef	ASM_COMMENT_START
#define ASM_COMMENT_START			"\t#"

#undef  ASM_OUTPUT_LABELREF
#define ASM_OUTPUT_LABELREF			midipix_asm_output_label_ref

#undef  ASM_GENERATE_INTERNAL_LABEL
#define ASM_GENERATE_INTERNAL_LABEL		midipix_asm_generate_internal_label

#undef  ASM_DECLARE_OBJECT_NAME
#define ASM_DECLARE_OBJECT_NAME			midipix_asm_declare_object_name

#undef  ASM_OUTPUT_DEF_FROM_DECLS
#define ASM_OUTPUT_DEF_FROM_DECLS		midipix_asm_output_def_from_decls

#undef  ASM_OUTPUT_EXTERNAL
#define ASM_OUTPUT_EXTERNAL			midipix_asm_output_external

#undef  ASM_OUTPUT_EXTERNAL_LIBCALL
#define ASM_OUTPUT_EXTERNAL_LIBCALL		midipix_asm_output_external_libcall

#undef  TARGET_USE_LOCAL_THUNK_ALIAS_P
#define TARGET_USE_LOCAL_THUNK_ALIAS_P		midipix_target_use_local_thunk_alias

#undef  drectve_section
#define drectve_section				midipix_asm_drectve_section


/* common target hooks */
#undef  ASM_DECLARE_FUNCTION_NAME
#define ASM_DECLARE_FUNCTION_NAME		midipix_i386_pe_start_function

#undef  ASM_DECLARE_FUNCTION_SIZE
#define ASM_DECLARE_FUNCTION_SIZE		midipix_i386_pe_end_function

#undef  TARGET_ASM_ASSEMBLE_VISIBILITY
#define TARGET_ASM_ASSEMBLE_VISIBILITY		midipix_i386_pe_assemble_visibility

#undef  TARGET_ASM_FILE_END
#define TARGET_ASM_FILE_END			i386_pe_file_end

#undef  ASM_OUTPUT_ALIGNED_BSS
#define ASM_OUTPUT_ALIGNED_BSS			asm_output_aligned_bss

#undef  ASM_OUTPUT_ALIGNED_DECL_COMMON
#define ASM_OUTPUT_ALIGNED_DECL_COMMON		i386_pe_asm_output_aligned_decl_common

#undef  TARGET_ASM_UNIQUE_SECTION
#define TARGET_ASM_UNIQUE_SECTION		i386_pe_unique_section

#undef  TARGET_ASM_NAMED_SECTION
#define TARGET_ASM_NAMED_SECTION		i386_pe_asm_named_section

#undef  TARGET_SECTION_TYPE_FLAGS
#define TARGET_SECTION_TYPE_FLAGS		i386_pe_section_type_flags

#undef  TARGET_MANGLE_ASSEMBLER_NAME
#define TARGET_MANGLE_ASSEMBLER_NAME		i386_pe_mangle_assembler_name

#undef  SUBTARGET_ENCODE_SECTION_INFO
#define SUBTARGET_ENCODE_SECTION_INFO		i386_pe_encode_section_info

#undef  TARGET_VALID_DLLIMPORT_ATTRIBUTE_P
#define TARGET_VALID_DLLIMPORT_ATTRIBUTE_P	i386_pe_valid_dllimport_attribute_p

#undef  TARGET_CXX_ADJUST_CLASS_AT_DEFINITION
#define TARGET_CXX_ADJUST_CLASS_AT_DEFINITION	i386_pe_adjust_class_at_definition

#undef  SUBTARGET_MANGLE_DECL_ASSEMBLER_NAME
#define SUBTARGET_MANGLE_DECL_ASSEMBLER_NAME	i386_pe_mangle_decl_assembler_name

#undef  TARGET_ASM_RELOC_RW_MASK
#define TARGET_ASM_RELOC_RW_MASK		midipix_i386_pe_reloc_rw_mask


/* libgcc */
#define __CXX_SEH__				(1)

#define LIBGCC2_TF_CEXT				q
#define LIBGCC2_TF_SIZE				113

#undef  TF_SIZE
#define TF_SIZE					LIBGCC2_TF_SIZE

#undef  LIBGCC2_HAS_TF_MODE
#define LIBGCC2_HAS_TF_MODE			(1)


/* source compatibility: seh prototypes */
extern void midipix_seh_hook__pe_seh_init(FILE *);
extern void midipix_seh_hook__pe_seh_end_prologue(FILE *);
extern void midipix_seh_hook__pe_seh_unwind_emit(FILE *, rtx);
extern void midipix_seh_hook__pe_seh_emit_except_personality(rtx);
extern void midipix_seh_hook__pe_seh_init_sections(void);


/* SEH hooks: 64-bit provided by winnt.c, 32-bit (to be) provided by midipix.c */
#define TARGET_ASM_UNWIND_EMIT			midipix_seh_hook__pe_seh_unwind_emit
#define TARGET_ASM_FUNCTION_END_PROLOGUE	midipix_seh_hook__pe_seh_end_prologue
#define TARGET_ASM_EMIT_EXCEPT_PERSONALITY	midipix_seh_hook__pe_seh_emit_except_personality
#define TARGET_ASM_INIT_SECTIONS		midipix_seh_hook__pe_seh_init_sections
#define SUBTARGET_ASM_UNWIND_INIT		midipix_seh_hook__pe_seh_init


/* target-specific definitions */
#ifndef IN_TARGET_LIBRARY_BUILD

#undef  BIGGEST_FIELD_ALIGNMENT
#define BIGGEST_FIELD_ALIGNMENT			(8 * __CHAR_BIT__)

#undef  ASM_WEAKEN_DECL
#define ASM_WEAKEN_DECL				midipix_i386_pe_asm_weaken_decl

#undef  ASM_WEAKEN_LABEL
#define ASM_WEAKEN_LABEL			midipix_i386_pe_asm_weaken_label

#undef  TARGET_ASM_FUNCTION_SECTION
#define TARGET_ASM_FUNCTION_SECTION		midipix_i386_pe_function_section


/* forward declarations */
extern void builtin_define_std			(const char *);

extern void midipix_asm_drectve_section		(void);
extern void midipix_asm_generate_internal_label	(char * strbuf, const char * prefix, unsigned long number);

extern int  midipix_target_use_local_thunk_alias(tree decl);
extern void midipix_i386_pe_assemble_visibility (tree decl, int visible);

extern void midipix_asm_output_external		(FILE * asmout, tree decl, const char * name);
extern void midipix_asm_output_def_from_decls	(FILE * asmout, tree decl, tree target);
extern void midipix_asm_output_external_libcall (FILE * asmout, rtx fn);

extern void midipix_asm_declare_object_name	(FILE * asmout, const char * name, tree decl);
extern void midipix_i386_pe_start_function	(FILE * asmout, const char * name, tree decl);
extern void midipix_i386_pe_end_function	(FILE * asmout, const char * name, tree decl);
extern void midipix_asm_output_label_ref	(FILE * asmout, const char * name);
extern void midipix_i386_pe_asm_weaken_label	(FILE * asmout, const char * name);

extern void midipix_i386_pe_asm_weaken_decl	(FILE * asmout,  tree decl, const char * name, const char * alias);
extern void midipix_asm_output_dwarf_offset	(FILE * asmout,  unsigned size, const char * label, section * section);

extern unsigned int midipix_dbx_get_register_number		(unsigned int n);
extern unsigned int midipix_dbx_get_dwarf_frame_register_number	(unsigned int n);

extern section * midipix_i386_pe_function_section(
	tree			decl,
	enum node_frequency	freq,
	bool			startup,
	bool			exit);


/* inlined functions */
static inline void midipix_extra_os_cpp_builtins(void)
{
	if (TARGET_NT64)
		builtin_define_std("__NT64");
	else
		builtin_define_std("__NT32");
}

static inline void midipix_target_os_cpp_builtins(void)
{
	builtin_define_std("__NTAPI");
	builtin_define_std("__MIDIPIX");
	midipix_extra_os_cpp_builtins();
}

static inline int midipix_i386_pe_reloc_rw_mask	(void)
{
	return 0;
}

#endif
