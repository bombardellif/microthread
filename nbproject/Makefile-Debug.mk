#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/List.o \
	${OBJECTDIR}/src/OrderedQueue.o \
	${OBJECTDIR}/src/Scheduler.o \
	${OBJECTDIR}/src/Tcb.o \
	${OBJECTDIR}/src/mmutex_t.o \
	${OBJECTDIR}/src/mthread.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk lib/libmthread.a

lib/libmthread.a: ${OBJECTFILES}
	${MKDIR} -p lib
	${RM} lib/libmthread.a
	${AR} -rv lib/libmthread.a ${OBJECTFILES} 
	$(RANLIB) lib/libmthread.a

${OBJECTDIR}/src/List.o: src/List.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/List.o src/List.c

${OBJECTDIR}/src/OrderedQueue.o: src/OrderedQueue.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/OrderedQueue.o src/OrderedQueue.c

${OBJECTDIR}/src/Scheduler.o: src/Scheduler.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Scheduler.o src/Scheduler.c

${OBJECTDIR}/src/Tcb.o: src/Tcb.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/Tcb.o src/Tcb.c

${OBJECTDIR}/src/mmutex_t.o: src/mmutex_t.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/mmutex_t.o src/mmutex_t.c

${OBJECTDIR}/src/mthread.o: src/mthread.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} "$@.d"
	$(COMPILE.c) -g -Wall -Iinclude -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/src/mthread.o src/mthread.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} lib/libmthread.a

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
