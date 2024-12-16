MANIFEST_VERSION=Manifest-Version: 1.0
MANIFEST_MAIN_CLASS=Main-Class
MAINCLASS=Main
JAR_NAME=app

%.class: %.java
	javac $<

package: Main.class Divider.java Multiplicator.java
	jar -cfe $(JAR_NAME).jar $(MAINCLASS) Divider.class Multiplicator.class Main.class
	

