EXT = cpp
CXX = g++

EXEC = exe

UNAME = $(shell uname)

ifeq ($(UNAME), Darwin)
CXXFLAGS = -Wall  -g
LDFLAGS = -framework OpenGL -framework ApplicationServices -lSOIL -L/usr/local/lib -lglfw3
endif

ifeq ($(UNAME), Linux)
CXXFLAGS = -Wall
LDFLAGS = -lSOIL -lGL -lGLU -lglfw3 -lX11 -lXxf86vm -lXrandr -lpthread -lXi
endif
 
 
OBJDIR = obj
SRC = $(wildcard *.$(EXT))
OBJ = $(SRC:.$(EXT)=.o)
OBJ := $(addprefix $(OBJDIR)/, $(OBJ))
 
all: $(EXEC)
 
$(EXEC): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)
 
$(OBJDIR)/%.o: %.$(EXT)
	$(CXX) -o $@ -c $< $(CXXFLAGS)
 
clean:
	@rm -rf $(OBJDIR)/*.o
	@rm -f $(EXEC)

deploy: $(EXEC)
	install_name_tool -change /usr/lib/libSystem.B.dylib @executable_path/lib/libSystem.B.dylib $(EXEC)
	install_name_tool -change /usr/local/lib/libSOIL.dylib @executable_path/lib/libSOIL.dylib $(EXEC)
	install_name_tool -change /usr/local/lib/libglfw3.3.0.dylib @executable_path/lib/libglfw3.3.0.dylib $(EXEC)
	install_name_tool -change /usr/lib/libc++.1.dylib @executable_path/lib/libc++.1.dylib $(EXEC)

zip: deploy
	zip out.zip $(EXEC) lib/* texture/textures.png texture/water_still.png