JFLAGS = -g
JC = javac
.SUFFIXES: .java .class
.java.class: clean
	$(JC) $(JFLAGS) $*.java

CLASSES = FilteringJTree.java \
        TreeDemo.java

default: classes

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class

