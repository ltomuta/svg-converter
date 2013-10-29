# ============================================================================
#  Name	 : build_help.mk
#  Part of  : svgtester
# ============================================================================
#  Name	 : build_help.mk
#  Part of  : svgtester
#
#  Description: This make file will build the application help file (.hlp)
# 
# ============================================================================

do_nothing :
	@rem do_nothing

# build the help from the MAKMAKE step so the header file generated
# will be found by cpp.exe when calculating the dependency information
# in the mmp makefiles.

MAKMAKE : svgtester_0xE65D4A7B.hlp
svgtester_0xE65D4A7B.hlp : svgtester.xml svgtester.cshlp Custom.xml
	cshlpcmp svgtester.cshlp
ifeq (WINSCW,$(findstring WINSCW, $(PLATFORM)))
	md $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
	copy svgtester_0xE65D4A7B.hlp $(EPOCROOT)epoc32\$(PLATFORM)\c\resource\help
endif

BLD : do_nothing

CLEAN :
	del svgtester_0xE65D4A7B.hlp
	del svgtester_0xE65D4A7B.hlp.hrh

LIB : do_nothing

CLEANLIB : do_nothing

RESOURCE : do_nothing
		
FREEZE : do_nothing

SAVESPACE : do_nothing

RELEASABLES :
	@echo svgtester_0xE65D4A7B.hlp

FINAL : do_nothing
