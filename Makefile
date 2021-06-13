CXX = g++
CXXFLAGS = -Wall -MMD -g
TESTFLAGS = -lboost_unit_test_framework
EXEC = assembler
TESTEXEC = test
SRCDIR = src
OBJDIR = obj
BINDIR = bin
TESTDIR = test
SOURCES := ${wildcard ${SRCDIR}/*.cpp}
OBJECTS := ${patsubst ${SRCDIR}/%.cpp,${OBJDIR}/%.o,${SOURCES}}
DEPENDS = ${OBJECTS:.o=.d}

TESTSOURCES := ${wildcard ${TESTDIR}/*.cpp}
TESTOBJECTS := ${patsubst ${TESTDIR}/%.cpp,${OBJDIR}/%.o,${TESTSOURCES}}
TESTDEPENDS = ${TESTOBJECTS:.o=.d}

COMBINEDOBJECTS = ${filter-out ${OBJDIR}/main.o, ${TESTOBJECTS} ${OBJECTS}}
COMBINEDSOURCES = ${filter-out ${SRCDIR}/main.cpp, ${TESTSOURCES} ${SOURCES}}
COMBINEDDEPENDS = ${filter-out ${OBJDIR}/main.d, ${TESTDEPENDS} ${DEPENDS}}


${BINDIR}/${EXEC}: ${OBJECTS} | ${BINDIR}
	${CXX} ${OBJECTS} -o ${BINDIR}/${EXEC}

${OBJDIR}/%.o: ${SRCDIR}/%.cpp | ${OBJDIR}
	${CXX} ${CXXFLAGS} -c -o $@ $<

test: ${COMBINEDOBJECTS} | ${BINDIR}
	${CXX} ${TESTFLAGS} ${COMBINEDOBJECTS} -o ${BINDIR}/${TESTEXEC}

${OBJDIR}/%.o: ${TESTDIR}/%.cpp | ${OBJDIR}
	${CXX} ${CXXFLAGS} -c -o $@ $<

${BINDIR}:
	mkdir $@

${OBJDIR}:
	mkdir $@

-include ${DEPENDS}

.PHONY: clean

clean:
	rm -r ${OBJDIR} ${BINDIR}

