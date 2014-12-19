#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/pic18MultitaskCCS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/pic18MultitaskCCS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/pic18MuiltitaskCCS.o
POSSIBLE_DEPFILES=${OBJECTDIR}/pic18MuiltitaskCCS.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/pic18MuiltitaskCCS.o


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/pic18MultitaskCCS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_CC="C:\PROGRA~2\PICC\CCSCON.exe"
MP_LD="C:\PROGRA~2\PICC\CCSCON.exe"
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/pic18MuiltitaskCCS.o: pic18MuiltitaskCCS.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR} 
ifeq (1,1) 
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  out="dist/${CND_CONF}/${IMAGE_TYPE}"  "pic18MuiltitaskCCS.c" +FH +DF  #__DEBUG=1 +ICD +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F4550=TRUE 
	@mv dist/${CND_CONF}/${IMAGE_TYPE}/pic18MuiltitaskCCS.cof dist/${CND_CONF}/${IMAGE_TYPE}/pic18MultitaskCCS.X.${IMAGE_TYPE}.cof 
	@mv dist/${CND_CONF}/${IMAGE_TYPE}/pic18MuiltitaskCCS.hex dist/${CND_CONF}/${IMAGE_TYPE}/pic18MultitaskCCS.X.${IMAGE_TYPE}.hex
else 
	${MP_CC}  out="${OBJECTDIR}" "pic18MuiltitaskCCS.c" +EXPORT +FH +DF  #__DEBUG=1 +ICD +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F4550=TRUE +EXPORTD="${OBJECTDIR}"  
	
endif 
	
else
${OBJECTDIR}/pic18MuiltitaskCCS.o: pic18MuiltitaskCCS.c  nbproject/Makefile-${CND_CONF}.mk
	${MKDIR} ${OBJECTDIR} 
ifeq (1,1) 
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC}  out="dist/${CND_CONF}/${IMAGE_TYPE}"  "pic18MuiltitaskCCS.c" +FH +DF +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F4550=TRUE 
	@mv dist/${CND_CONF}/${IMAGE_TYPE}/pic18MuiltitaskCCS.cof dist/${CND_CONF}/${IMAGE_TYPE}/pic18MultitaskCCS.X.${IMAGE_TYPE}.cof 
	@mv dist/${CND_CONF}/${IMAGE_TYPE}/pic18MuiltitaskCCS.hex dist/${CND_CONF}/${IMAGE_TYPE}/pic18MultitaskCCS.X.${IMAGE_TYPE}.hex
else 
	${MP_CC}  out="${OBJECTDIR}" "pic18MuiltitaskCCS.c" +EXPORT +FH +DF +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P #__18F4550=TRUE +EXPORTD="${OBJECTDIR}"  
	
endif 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/pic18MultitaskCCS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
ifeq (1,1) 
	
else 
	${MP_LD}   out="dist/${CND_CONF}/${IMAGE_TYPE}"  +FH +DF LINK="pic18MultitaskCCS.X.${IMAGE_TYPE}.hex=${OBJECTDIR}/pic18MuiltitaskCCS.o" +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P
	
endif 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/pic18MultitaskCCS.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
ifeq (1,1) 
	
else 
	${MP_LD}   out="dist/${CND_CONF}/${IMAGE_TYPE}"  +FH +DF LINK="pic18MultitaskCCS.X.${IMAGE_TYPE}.hex=${OBJECTDIR}/pic18MuiltitaskCCS.o" +Y=9 +EA +DF +LN +T +A +M +J +EA +Z -P
	
endif 
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
