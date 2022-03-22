CC := g++ -std=c++14
OUTPUT := HyperbolicTileMapping
BUILD  := Build
SOURCE := Source
DLL    := Dlls
TEXTURES := Textures
SHADERS  := Shaders
LDFLAGS := -L$(CURDIR)/Deps/SDL2/lib -L$(CURDIR)/Deps/glext/lib
IFLAGS := -I$(CURDIR)/Deps/stb -I$(CURDIR)/Deps/SDL2/include -I$(CURDIR)/Deps/glm \
		  -I$(CURDIR)/Deps/glext/include -I$(CURDIR)
LDLIBS := -w -lmingw32 -lSDL2main -lSDL2 -lopengl32 -lglu32 -lglext

$(BUILD)/$(OUTPUT).exe: $(SOURCE)/*.cpp
	mkdir -p $(BUILD)
	cp -f $(CURDIR)/$(DLL)/*.dll $(BUILD)/
	cp -r $(CURDIR)/$(TEXTURES) $(BUILD)/
	cp -r $(CURDIR)/$(SHADERS) $(BUILD)/	
	$(CC) $^ $(IFLAGS) $(LDFLAGS) $(LDLIBS) -o $@  

.PHONY: clean

clean:
	rm -rf $(CURDIR)/$(BUILD)