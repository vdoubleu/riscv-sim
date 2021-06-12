CXX = g++
CXXFLAGS = -Wall -MMD -g
EXEC = assembler
SRCDIR = src
OBJDIR = obj
BINDIR = bin
SOURCES := ${wildcard ${SRCDIR}/*.cpp}
OBJECTS := ${patsubst ${SRCDIR}/%.cpp,${OBJDIR}/%.o,${SOURCES}}
DEPENDS = ${OBJECTS:.o=.d}

${BINDIR}/${EXEC}: ${OBJECTS} | ${BINDIR}
	${CXX} ${OBJECTS} -o ${BINDIR}/${EXEC}

${OBJDIR}/%.o: ${SRCDIR}/%.cpp | ${OBJDIR}
	${CXX} ${CXXFLAGS} -c -o $@ $<

${BINDIR}:
	mkdir $@

${OBJDIR}:
	mkdir $@

-include ${DEPENDS}

.PHONY: clean

clean:
	rm -r ${OBJDIR} ${BINDIR}
