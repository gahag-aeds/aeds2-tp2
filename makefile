SrcDir = src
BinDir = bin

OutputFileName   = tp2
OutputFile       = $(BinDir)/$(OutputFileName)
CompilationUnits = $(shell find $(SrcDir) -name '*.c')

Build    = clang
Standard = c99
Warnings = -Wall -Wextra
Optimize = -flto -O2

BuildFlags  = $(Warnings)       \
              -std=$(Standard)  \
              $(Optimize)       \
              $(Libs)           \
              -I $(SrcDir)      \
              -o $(OutputFile)

ReleaseFlags = -DNDEBUG -s


directories: $(SrcDir)
	@[ -d "$(BinDir)" ] || mkdir "$(BinDir)";


build: directories
	@$(Build) $(BuildFlags) $(CompilationUnits)

release: directories
	@$(Build) $(ReleaseFlags) $(BuildFlags) $(CompilationUnits)


clean:
	rm -f $(OutputFile)
