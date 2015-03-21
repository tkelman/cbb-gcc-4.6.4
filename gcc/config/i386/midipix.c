/*****************************************************************************/
/*                                                                           */
/*  midipix target interfaces                                                */
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

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "rtl.h"
#include "output.h"
#include "tree.h"
#include "flags.h"
#include "target.h"
#include "i386-protos.h"

/* common specs */
const int TARGET_NOP_FUN_DLLIMPORT	= 0;
const int use_pe_aligned_common		= 1;
const int flag_writable_rel_rdata	= 0;

/* target SEH providers */
#define TARGET_SEH_WINNT			(TARGET_NT64 && flag_unwind_tables)
#define TARGET_SEH_MIDIPIX			(TARGET_NT32 && flag_unwind_tables)

#undef  TARGET_SEH_WINNT
#undef  TARGET_SEH_MIDIPIX

#define TARGET_SEH_WINNT			(TARGET_NT64)
#define TARGET_SEH_MIDIPIX			(TARGET_NT32)

/* 64-bit seh provided by winnt */
void winnt_x86_64_pe_seh_init(FILE *);
void winnt_x86_64_pe_seh_end_prologue(FILE *);
void winnt_x86_64_pe_seh_unwind_emit(FILE *, rtx);
void winnt_x86_64_pe_seh_emit_except_personality(rtx);
void winnt_x86_64_pe_seh_init_sections(void);


/* 32-bit seh provided by midipix */
void midipix_i386_pe_seh_init(FILE *);
void midipix_i386_pe_seh_end_prologue(FILE *);
void midipix_i386_pe_seh_unwind_emit(FILE *, rtx);
void midipix_i386_pe_seh_emit_except_personality(rtx);
void midipix_i386_pe_seh_init_sections(void);


/* debugging */
unsigned int midipix_dbx_get_register_number(unsigned int n)
{
	if (TARGET_NT64 )
		return dbx64_register_map[n];
	else if (write_symbols == DWARF2_DEBUG)
		return svr4_dbx_register_map[n];
	else
		return dbx_register_map[n];
}


unsigned int midipix_dbx_get_dwarf_frame_register_number(unsigned int n)
{
	if (TARGET_NT64)
		return dbx64_register_map[n];
	else
		return svr4_dbx_register_map[n];
}


void midipix_asm_output_dwarf_offset(
	FILE *		gas_exhaled,
	unsigned	size,
	const char *	label,
	section * section __attribute__((unused)))
{
	#define PE_SIZE_IDENTIFIER	4
	#define PEP_SIZE_IDENTIFIER	8

	extern void assemble_name (FILE *, const char *);

	if ((size == PE_SIZE_IDENTIFIER) || (size == PEP_SIZE_IDENTIFIER)) {
		fputs ("\t.secrel32\t", gas_exhaled);
		assemble_name(gas_exhaled, label);

		/* in PE32+, section relocation need to be zero-extended */
		if (size == PEP_SIZE_IDENTIFIER)
			fputs ("\n\t.int\t0", gas_exhaled);
	} else
		gcc_unreachable();
}


/* assembler labels */
void midipix_asm_output_label_ref (FILE * gas_exhaled, const char * name)
{
	extern const char * user_label_prefix;

	/* in __fastcall labels the @ prefix is already present */
	if (*name != FASTCALL_PREFIX)
		fputs(user_label_prefix, gas_exhaled);

	fputs(name, gas_exhaled);
}


void midipix_asm_generate_internal_label (
	char * strbuf, const char * prefix, unsigned long number)
{
	sprintf (strbuf, "*%s%s%ld",
			LOCAL_LABEL_PREFIX,
			prefix,
			number);
}


void midipix_asm_declare_object_name(FILE * gas_exhaled, const char * name, tree decl)
{
	extern void assemble_name (FILE *, const char *);
	extern void i386_pe_maybe_record_exported_symbol (tree, const char *, int);

	i386_pe_maybe_record_exported_symbol(decl, name, true);
	assemble_name(gas_exhaled, name);
	fputs (":\n", gas_exhaled);
}


void midipix_asm_drectve_section(void)
{
	extern FILE *    asm_out_file;
	extern section * in_section;

	in_section = (section *)0;

	fprintf (asm_out_file, "%s%s\n",
			GAS_SECTION,
			DRECTVE_SECTION_NAME);
}


int midipix_target_use_local_thunk_alias(tree decl)
{
	return !DECL_ONE_ONLY(decl);
}


void midipix_asm_output_external(
	FILE *		asmout __attribute__((unused)),
	tree		decl,
	const char *	name)
{
	if (TREE_CODE(decl) == FUNCTION_DECL)
		i386_pe_record_external_function(
			decl,name);
}


void midipix_asm_output_external_libcall (FILE * asmout, rtx fn)
{
	i386_pe_declare_function_type(
		asmout,
		XSTR(fn,0),
		true);
}


void midipix_asm_output_def_from_decls(
	FILE *	asmout,
	tree	decl,
	tree	target)
{
	const char * sym;

	sym = IDENTIFIER_POINTER(
		DECL_ASSEMBLER_NAME(decl));

	i386_pe_maybe_record_exported_symbol(
		decl,sym,false);

	if (TREE_CODE(decl) == FUNCTION_DECL)
		i386_pe_declare_function_type(
			asmout,
			sym,
			TREE_PUBLIC(decl));

	ASM_OUTPUT_DEF(
		asmout,
		sym,
		IDENTIFIER_POINTER(target));
}


/* visibility */
void midipix_i386_pe_assemble_visibility (
	tree	decl	__attribute__((unused)),
	int	visible __attribute__((unused)))
{
	/* todo: add the symbol to a special section (.hidden),
	   and teach the linker to not export symbols that are
	   listed under that section. */
}




/* seh hook selectors */
void midipix_seh_hook__pe_seh_init(FILE * f)
{
	if (TARGET_SEH_WINNT)
		winnt_x86_64_pe_seh_init(f);
	else if (TARGET_SEH_MIDIPIX)
		midipix_i386_pe_seh_init(f);
}


void midipix_seh_hook__pe_seh_end_prologue(FILE * f)
{
	if (TARGET_SEH_WINNT)
		winnt_x86_64_pe_seh_end_prologue(f);
	else if (TARGET_SEH_MIDIPIX)
		midipix_i386_pe_seh_end_prologue(f);
}


void midipix_seh_hook__pe_seh_unwind_emit(FILE * f, rtx r)
{
	if (TARGET_SEH_WINNT)
		winnt_x86_64_pe_seh_unwind_emit(f,r);
	else if (TARGET_SEH_MIDIPIX)
		midipix_i386_pe_seh_unwind_emit(f,r);
}



void midipix_seh_hook__pe_seh_emit_except_personality(rtx r)
{
	if (TARGET_SEH_WINNT)
		winnt_x86_64_pe_seh_emit_except_personality(r);
	else if (TARGET_SEH_MIDIPIX)
		midipix_i386_pe_seh_emit_except_personality(r);
}


void midipix_seh_hook__pe_seh_init_sections(void)
{
	if (TARGET_SEH_WINNT)
		winnt_x86_64_pe_seh_init_sections();
	else if (TARGET_SEH_MIDIPIX)
		midipix_i386_pe_seh_init_sections();
}



/* 64-bit seh hooks (winnt) */
void winnt_x86_64_pe_seh_init(FILE * f)
{
	i386_pe_seh_init(f);
}


void winnt_x86_64_pe_seh_end_prologue(FILE * f)
{
	i386_pe_seh_end_prologue(f);
}


void winnt_x86_64_pe_seh_unwind_emit(FILE * f, rtx r)
{
	i386_pe_seh_unwind_emit(f,r);
}


void winnt_x86_64_pe_seh_emit_except_personality(rtx r __attribute__((unused)))
{
	/* i386_pe_seh_emit_except_personality(r); */
}


void winnt_x86_64_pe_seh_init_sections(void)
{
	/* i386_pe_seh_init_sections(); */
}



/* 32-bit seh hooks (midipix) */
void midipix_i386_pe_seh_init(FILE * f __attribute__((unused)))
{
}


void midipix_i386_pe_seh_end_prologue(FILE * f __attribute__((unused)))
{
}


void midipix_i386_pe_seh_unwind_emit(
	FILE *	f __attribute__((unused)),
	rtx	r __attribute__((unused)))
{
}


void midipix_i386_pe_seh_emit_except_personality(rtx r __attribute__((unused)))
{
}


void midipix_i386_pe_seh_init_sections(void)
{
}


section * midipix_i386_pe_function_section (
	tree			decl,
	enum node_frequency	freq,
	bool			startup,
	bool			exit)
{
	extern section * default_function_section (
		tree			decl,
		enum node_frequency	freq,
		bool			startup,
		bool			exit);

	const char *	fname;
	char *		secname;
	size_t		size;

	bool		weak;
	section *	asm_section;

	weak = (decl && DECL_WEAK (decl));

	if (weak && DECL_ATTRIBUTES(decl) && lookup_attribute (
			"weak_import",
			DECL_ATTRIBUTES(decl)))
		weak = 0;

	fname = IDENTIFIER_POINTER (DECL_ASSEMBLER_NAME (decl));

	#ifdef MIDIPIX_TARGET_DEBUG
	fputs ("\t# <", asm_out_file);
	assemble_name (asm_out_file, fname);
	fputs (": section>\n", asm_out_file);
	#endif

	if (weak) {
		#ifdef MIDIPIX_TARGET_DEBUG
		fputs("\t# (weak symbol section)\n",asm_out_file);
		#endif

		size  = strlen(fname) + 6; /* .text$ */

		if (!(secname = (char *)xmalloc(size)))
			gcc_unreachable();

		sprintf(secname,".text$%s",fname);
		asm_section = get_named_section(decl, secname, 1);
		free(secname);
	} else if (decl) {
		#ifdef MIDIPIX_TARGET_DEBUG
		fputs("\t# (strong symbol section)\n",asm_out_file);
		#endif

		asm_section = default_function_section(decl, freq, startup, exit);
	} else {
		fputs("\t# should never get here?\n",asm_out_file);
		asm_section = (section *)0;
	}

	#ifdef MIDIPIX_TARGET_DEBUG
	fputs ("\t# </", asm_out_file);
	assemble_name (asm_out_file, fname);
	fputs (": section>\n", asm_out_file);
	#endif

	return asm_section;
}


void midipix_i386_pe_start_function (FILE * gas_exhaled, const char *name, tree decl)
{
	#ifdef MIDIPIX_TARGET_DEBUG
	fputs ("\t# <", gas_exhaled);
	assemble_name (gas_exhaled, name);
	fputs (">\n", gas_exhaled);
	#endif

	i386_pe_start_function (gas_exhaled, name, decl);
}


void midipix_i386_pe_end_function (FILE * gas_exhaled, const char * name, tree decl)
{
	i386_pe_end_function (gas_exhaled, name, decl);

	#ifdef MIDIPIX_TARGET_DEBUG
	fputs ("\t# </", gas_exhaled);
	assemble_name (gas_exhaled, name);
	fputs (">\n\n\n", gas_exhaled);
	#endif
}


void midipix_i386_pe_asm_weaken_decl(
	FILE *		gas_exhaled,
	tree		decl,
	const char *	name,
	const char *	alias __attribute__((unused)))
{
	if ((decl) && DECL_EXTERNAL(decl)) {
		#ifdef MIDIPIX_TARGET_DEBUG
		fputs ("\t# (external weak symbol label)\n", gas_exhaled);
		#endif

		fputs ("\t.weak\t", gas_exhaled);
		assemble_name (gas_exhaled, name);
		fputs ("\n", gas_exhaled);
	} else {
		#ifdef MIDIPIX_TARGET_DEBUG
		fputs("\t# (normal weak symbol label)\n", gas_exhaled);
		#endif

		/* write a patch for ld so that we can use .globl instead */
		fputs("\t.weak\t", gas_exhaled);
		assemble_name (gas_exhaled, name);
		fputs ("\n", gas_exhaled);
	}
}


void midipix_i386_pe_asm_weaken_label(FILE * gas_exhaled, const char * name)
{
	midipix_i386_pe_asm_weaken_decl(
		gas_exhaled,
		(tree)0,
		name,
		(const char *)0);
}
