#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
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
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/CV_ZONE_CTRL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/CV_ZONE_CTRL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/main.o ${OBJECTDIR}/cv_controller.o ${OBJECTDIR}/cv.o ${OBJECTDIR}/termostat.o ${OBJECTDIR}/valve.o ${OBJECTDIR}/pumps.o
POSSIBLE_DEPFILES=${OBJECTDIR}/main.o.d ${OBJECTDIR}/cv_controller.o.d ${OBJECTDIR}/cv.o.d ${OBJECTDIR}/termostat.o.d ${OBJECTDIR}/valve.o.d ${OBJECTDIR}/pumps.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/main.o ${OBJECTDIR}/cv_controller.o ${OBJECTDIR}/cv.o ${OBJECTDIR}/termostat.o ${OBJECTDIR}/valve.o ${OBJECTDIR}/pumps.o


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
	${MAKE} ${MAKE_OPTIONS} -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/CV_ZONE_CTRL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F46K22
MP_PROCESSOR_OPTION_LD=18f46k22
MP_LINKER_DEBUG_OPTION=
# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -scs -I"C:/Users/Jeremy/ORCAD/CV_BOTS/CV_ZONE_CTRL/CV_ZONE_CTRL.X" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/main.o   main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/cv_controller.o: cv_controller.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/cv_controller.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -scs -I"C:/Users/Jeremy/ORCAD/CV_BOTS/CV_ZONE_CTRL/CV_ZONE_CTRL.X" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/cv_controller.o   cv_controller.c 
	@${DEP_GEN} -d ${OBJECTDIR}/cv_controller.o 
	@${FIXDEPS} "${OBJECTDIR}/cv_controller.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/cv.o: cv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/cv.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -scs -I"C:/Users/Jeremy/ORCAD/CV_BOTS/CV_ZONE_CTRL/CV_ZONE_CTRL.X" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/cv.o   cv.c 
	@${DEP_GEN} -d ${OBJECTDIR}/cv.o 
	@${FIXDEPS} "${OBJECTDIR}/cv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/termostat.o: termostat.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/termostat.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -scs -I"C:/Users/Jeremy/ORCAD/CV_BOTS/CV_ZONE_CTRL/CV_ZONE_CTRL.X" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/termostat.o   termostat.c 
	@${DEP_GEN} -d ${OBJECTDIR}/termostat.o 
	@${FIXDEPS} "${OBJECTDIR}/termostat.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/valve.o: valve.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/valve.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -scs -I"C:/Users/Jeremy/ORCAD/CV_BOTS/CV_ZONE_CTRL/CV_ZONE_CTRL.X" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/valve.o   valve.c 
	@${DEP_GEN} -d ${OBJECTDIR}/valve.o 
	@${FIXDEPS} "${OBJECTDIR}/valve.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/pumps.o: pumps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/pumps.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -D__DEBUG -D__MPLAB_DEBUGGER_ICD3=1 -p$(MP_PROCESSOR_OPTION) -scs -I"C:/Users/Jeremy/ORCAD/CV_BOTS/CV_ZONE_CTRL/CV_ZONE_CTRL.X" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/pumps.o   pumps.c 
	@${DEP_GEN} -d ${OBJECTDIR}/pumps.o 
	@${FIXDEPS} "${OBJECTDIR}/pumps.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
else
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -scs -I"C:/Users/Jeremy/ORCAD/CV_BOTS/CV_ZONE_CTRL/CV_ZONE_CTRL.X" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/main.o   main.c 
	@${DEP_GEN} -d ${OBJECTDIR}/main.o 
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/cv_controller.o: cv_controller.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/cv_controller.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -scs -I"C:/Users/Jeremy/ORCAD/CV_BOTS/CV_ZONE_CTRL/CV_ZONE_CTRL.X" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/cv_controller.o   cv_controller.c 
	@${DEP_GEN} -d ${OBJECTDIR}/cv_controller.o 
	@${FIXDEPS} "${OBJECTDIR}/cv_controller.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/cv.o: cv.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/cv.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -scs -I"C:/Users/Jeremy/ORCAD/CV_BOTS/CV_ZONE_CTRL/CV_ZONE_CTRL.X" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/cv.o   cv.c 
	@${DEP_GEN} -d ${OBJECTDIR}/cv.o 
	@${FIXDEPS} "${OBJECTDIR}/cv.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/termostat.o: termostat.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/termostat.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -scs -I"C:/Users/Jeremy/ORCAD/CV_BOTS/CV_ZONE_CTRL/CV_ZONE_CTRL.X" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/termostat.o   termostat.c 
	@${DEP_GEN} -d ${OBJECTDIR}/termostat.o 
	@${FIXDEPS} "${OBJECTDIR}/termostat.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/valve.o: valve.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/valve.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -scs -I"C:/Users/Jeremy/ORCAD/CV_BOTS/CV_ZONE_CTRL/CV_ZONE_CTRL.X" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/valve.o   valve.c 
	@${DEP_GEN} -d ${OBJECTDIR}/valve.o 
	@${FIXDEPS} "${OBJECTDIR}/valve.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
${OBJECTDIR}/pumps.o: pumps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/pumps.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE) -p$(MP_PROCESSOR_OPTION) -scs -I"C:/Users/Jeremy/ORCAD/CV_BOTS/CV_ZONE_CTRL/CV_ZONE_CTRL.X" -ms -oa-  -I ${MP_CC_DIR}\\..\\h  -fo ${OBJECTDIR}/pumps.o   pumps.c 
	@${DEP_GEN} -d ${OBJECTDIR}/pumps.o 
	@${FIXDEPS} "${OBJECTDIR}/pumps.o.d" $(SILENT) -rsi ${MP_CC_DIR}../ -c18 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/CV_ZONE_CTRL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w -x -u_DEBUG   -z__MPLAB_BUILD=1  -u_CRUNTIME -z__MPLAB_DEBUG=1 -z__MPLAB_DEBUGGER_ICD3=1 $(MP_LINKER_DEBUG_OPTION) -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/CV_ZONE_CTRL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
else
dist/${CND_CONF}/${IMAGE_TYPE}/CV_ZONE_CTRL.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_LD} $(MP_EXTRA_LD_PRE)   -p$(MP_PROCESSOR_OPTION_LD)  -w    -z__MPLAB_BUILD=1  -u_CRUNTIME -l ${MP_CC_DIR}\\..\\lib  -o dist/${CND_CONF}/${IMAGE_TYPE}/CV_ZONE_CTRL.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}   
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
