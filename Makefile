HyperbolicTileMapping.exe: Window.cpp SubPlane.cpp HyperMath.cpp Main.cpp
	g++ -std=c++14 $^ $(IFLAGS) $(LDFLAGS) $(LDLIBS) -o $@  

LDFLAGS = -L$(CURDIR)/Deps/SDL2/lib -L$(CURDIR)/Deps/glext/lib
IFLAGS = -I$(CURDIR)/Deps/stb -I$(CURDIR)/Deps/SDL2/include -I$(CURDIR)/Deps/glm -I$(CURDIR)/Deps/glext/include -I$(CURDIR)
LDLIBS = -w -Wl,-subsystem,windows -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lglu32 -lglext

clean:
	rm -rf $(CURDIR)/HyperbolicTileMapping.exe