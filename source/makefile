CC := g++
CFALGS := -Wall -g

INCLUDE_PATH := ..\include
LIB_FLAG := -lfreeglut -lglew32 -lopengl32 
LIB_PATH := ..\lib
BUILD_PATH := ..\build


.PHONY: clean all

%.exe: %.o
	if not exist $(BUILD_PATH)\$* mkdir $(BUILD_PATH)\$*
	$(CC) -o $(BUILD_PATH)\$*\$@ $< -L$(LIB_PATH) $(LIB_FLAG)
	copy $(LIB_PATH)\*.dll $(BUILD_PATH)\$*
	$(BUILD_PATH)\$*\$@

%.dll: %.o
	$(CC) -shared $< -o $(LIB_PATH)\$@

%.o: %.cpp
	$(CC) -c $< -o $@ -I$(INCLUDE_PATH)
%.o: %.c
	$(CC) -c $< -o $@ -I$(INCLUDE_PATH)

clean:
	-del *.o *.dll




