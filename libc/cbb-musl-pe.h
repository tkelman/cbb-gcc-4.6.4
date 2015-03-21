/************************************************************************/
/*  compiler building blocks: definitions for all musl-libc PE targets  */
/************************************************************************/

#ifndef __ASSEMBLER__

#include "cbb-common.h"

#ifdef __cplusplus
extern "C" {
#endif


/* features */
#undef	TARGET_C99_FUNCTIONS
#define	TARGET_C99_FUNCTIONS		(1)

#undef  TARGET_HAS_SINCOS
#define TARGET_HAS_SINCOS		(0)

#undef  TARGET_POSIX_IO
#define TARGET_POSIX_IO			(1)


/* preferences */
#undef  EMUTLS_PROVIDED_BY_PLATFORM
#define EMUTLS_PROVIDED_BY_PLATFORM	(1)

#undef  NO_IMPLICIT_EXTERN_C
#define NO_IMPLICIT_EXTERN_C		(1)

#undef  GTHREAD_USE_WEAK
#define GTHREAD_USE_WEAK		(0)

#undef  USE_PT_GNU_EH_FRAME
#define USE_PT_GNU_EH_FRAME		(1)

#undef  STANDARD_INCLUDE_DIR
#define STANDARD_INCLUDE_DIR		"/include"

#undef  LOCAL_INCLUDE_DIR
#define LOCAL_INCLUDE_DIR		"/local/include"


/* specs */
#undef  ASM_SPEC_ARCH
#define ASM_SPEC_ARCH			"%{m32:--32} "	\
					"%{m64:--64} "
#undef  ASM_SPEC_AVX
#define ASM_SPEC_AVX			"%{!mno-sse2avx:%{mavx:-msse2avx}} " \
					"%{msse2avx:%{!mavx:-msse2avx}} "
#undef  ASM_SPEC
#define ASM_SPEC			ASM_SPEC_ARCH ASM_SPEC_AVX

#undef  CPP_SPEC_POSIX
#define CPP_SPEC_POSIX			"%{posix|mposix:-D_POSIX_SOURCE} "

#undef  CPP_SPEC_LDSO
#define CPP_SPEC_LDSO			"%{mldso:-D_LDSO} "

#undef  CPP_SPEC_LDSO_ABSOLUTE_PATH
#define CPP_SPEC_LDSO_ABSOLUTE_PATH	"%{mldso-absolute-path:-D_LDSO -D_LDSO_ABSOLUTE_PATH} "

#undef  CPP_SPEC_LDSO_DEFAULT_PATH
#define CPP_SPEC_LDSO_DEFAULT_PATH	"%{mldso-default-path:-D_LDSO -D_LDSO_DEFAULT_PATH} "

#undef  CPP_SPEC_LDSO_APP_DIR_ONLY
#define CPP_SPEC_LDSO_APP_DIR_ONLY	"%{mldso-app-dir-only:-D_LDSO -D_LDSO_APP_DIR_ONLY} "

#undef  CPP_SPEC_LDSO_KERNEL_DRIVER
#define CPP_SPEC_LDSO_KERNEL_DRIVER	"%{mldso-kernel-driver:-D_LDSO -D_LDSO_KERNEL_DRIVER} "

#undef  CPP_SPEC_NTAPI
#define CPP_SPEC_NTAPI			"%{mntapi:-ffreestanding} "

#undef  CPP_SPEC
#define CPP_SPEC 			CPP_SPEC_POSIX			\
					CPP_SPEC_LDSO			\
					CPP_SPEC_LDSO_ABSOLUTE_PATH	\
					CPP_SPEC_LDSO_DEFAULT_PATH	\
					CPP_SPEC_LDSO_APP_DIR_ONLY	\
					CPP_SPEC_LDSO_KERNEL_DRIVER	\
					CPP_SPEC_NTAPI

#undef  LIB_SPEC
#define LIB_SPEC			"%{shared:-lc} "	\
					"%{pthread:-lpthread} " \
					"--no-as-needed -lc "	\
					"--as-needed -lpsxscl "

#undef  STARTFILE_SPEC
#define STARTFILE_SPEC			"%{!shared:%{"					\
						"mldso"					\
						"|mldso-absolute-path"			\
						"|mldso-default-path"			\
						"|mldso-app-dir-only"			\
						"|mldso-root-relative"			\
						"|mldso-kernel-driver"			\
						":%R/lib/crtldso.o}} "			\
					"%{!shared:%R/lib/%{"				\
						"mldso-absolute-path:crtldsoa.o;"	\
						"mldso-default-path:crtldsod.o;"	\
						"mldso-app-dir-only:crtldson.o;"	\
						"mldso-root-relative:crtldsor.o;"	\
						"mldso-kernel-driver:crtldsok.o;"	\
						":%{static:S}crt1.o}} "			\
					"%{!shared:%{mposix:%R/lib/crtposix.o}} "	\
					"%{!shared:%{mtty-console:%R/lib/crtdev.o}} "	\
					"%{shared:%R/lib/crte.o} "			\
					"%R/lib/crti.o "				\
					"%{static:crtbeginT.o%s;"			\
					"shared|pie:crtbeginS.o%s;"			\
					":crtbegin.o%s} "

#undef  ENDFILE_SPEC
#define ENDFILE_SPEC			"%{shared|pie:crtendS.o%s;:crtend.o%s} "	\
					"%R/lib/crtn.o " LIB_SPEC

#undef  LINK_GCC_C_SEQUENCE_SPEC
#define LINK_GCC_C_SEQUENCE_SPEC	"%{static:--start-group} "		\
					"%L %G " 				\
					"%{static:--end-group}%{!static:%G} "	\
					"--no-as-needed -lc "

#undef  LINK_DSO_SYM_SPEC
#define LINK_DSO_SYM_SPEC 		"--exclude-symbols="		\
						"__EH_FRAME_BEGIN__,"	\
						"__dso_handle,"		\
						"_init,_fini,"		\
						"_so_entry_point,"	\
						"dso_main_routine "

#undef  LINK_SPEC
#define LINK_SPEC			"%{rdynamic:--export-all-symbols} "             \
					"%{mntapi:-nostdlib} "				\
					"%{static:-static} "				\
					"%{shared:-shared} "				\
					"%{shared:%{moutput-def:"			\
						"--output-def %{o*:%.so.def%*}}} "	\
					"%{shared:%{mout-implib:"			\
						"--out-implib %{o*:%.lib.a%*}}} "	\
					"%{!shared:--entry _start} "			\
					"%{!shared:--image-base 0x1920000} "		\
					"%{shared:--entry _so_entry_point} "		\
					"%{shared:--enable-auto-image-base} "		\
					"--subsystem windows "				\
					LINK_DSO_SYM_SPEC

#undef  SUBTARGET_EXTRA_SPECS
#define SUBTARGET_EXTRA_SPECS


#ifdef __cplusplus
}
#endif

#endif /* __ASSEMBLER__ */
