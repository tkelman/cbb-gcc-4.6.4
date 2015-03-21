/*************************************************************************/
/*  compiler building blocks: definitions for all musl-libc ELF targets  */
/*************************************************************************/

#ifndef __ASSEMBLER__

#include "cbb-common.h"

#ifdef __cplusplus
extern "C" {
#endif


/* features */
#undef	TARGET_C99_FUNCTIONS
#define	TARGET_C99_FUNCTIONS	(1)

#undef  TARGET_HAS_SINCOS
#define TARGET_HAS_SINCOS	(0)

#undef  TARGET_POSIX_IO
#define TARGET_POSIX_IO		(1)


/* preferences */
#undef  NO_IMPLICIT_EXTERN_C
#define NO_IMPLICIT_EXTERN_C	(1)

#undef  GTHREAD_USE_WEAK
#define GTHREAD_USE_WEAK	(0)

#undef  USE_PT_GNU_EH_FRAME
#define USE_PT_GNU_EH_FRAME	(1)

#undef  STANDARD_INCLUDE_DIR
#define STANDARD_INCLUDE_DIR	"/include"

#undef  LOCAL_INCLUDE_DIR
#define LOCAL_INCLUDE_DIR	"/local/include"


/* arch */
#define CBB_STR(s)		#s
#define CBB_XSTR(s)		CBB_STR(s)

#undef  MUSL_DYNAMIC_LINKER
#define MUSL_DYNAMIC_LINKER	"ld-musl-" CBB_XSTR(CBB_ARCH) ".so.1"

#ifndef CBB_LINK_EMULATION
#define CBB_LINK_EMULATION	""
#endif

#undef  LINK_EMULATION
#define LINK_EMULATION		CBB_LINK_EMULATION


/* specs */
#undef  CC1_SPEC
#define CC1_SPEC		"%(cc1_cpu) %{profile:-p}"

#undef  CPP_SPEC
#define CPP_SPEC		"%{posix:-D_POSIX_SOURCE}"

#undef  STARTFILE_PREFIX_SPEC
#define STARTFILE_PREFIX_SPEC	"%R/lib/"

#undef  LINK_EH_SPEC
#define LINK_EH_SPEC		" --eh-frame-hdr "

#undef  LINK_GCC_C_SEQUENCE_SPEC
#define LINK_GCC_C_SEQUENCE_SPEC						   \
				"%{static:--start-group} "			   \
				"%L %G "					   \
				"%{static:--end-group}%{!static:%G} "		   \
				"--as-needed -lc"

#undef  LIB_SPEC
#define LIB_SPEC		"%{pthread:-lpthread} "				   \
				"%{shared:-lc} "

#undef  STARTFILE_SPEC
#define STARTFILE_SPEC		"%{!shared: "					   \
					"%(startfile_prefix_spec)%{pie:S}crt1.o} " \
					"%(startfile_prefix_spec)crti.o "	   \
				"%{shared|pie:"					   \
					"crtbeginS.o%s;:crtbegin.o%s}"

#undef  ENDFILE_SPEC
#define ENDFILE_SPEC		"%{shared|pie:crtendS.o%s;:crtend.o%s} "	   \
				"%(startfile_prefix_spec)crtn.o"


#undef  LINK_EMULATION_SPEC
#define LINK_EMULATION_SPEC	{ "link_emulation", LINK_EMULATION }

#undef  DYNAMIC_LINKER_SPEC
#define DYNAMIC_LINKER_SPEC	{ "dynamic_linker", \
				  "%(startfile_prefix_spec)" MUSL_DYNAMIC_LINKER }

#undef  SUBTARGET_EXTRA_SPECS
#define SUBTARGET_EXTRA_SPECS	LINK_EMULATION_SPEC , DYNAMIC_LINKER_SPEC

#undef  LINK_SPEC
#define LINK_SPEC		"-dynamic-linker %(dynamic_linker) "		   \
				"%{shared:-shared} "				   \
				"%{static:-static} "				   \
				"%{rdynamic:-export-dynamic}"


#ifdef __cplusplus
}
#endif

#endif /* __ASSEMBLER__ */
