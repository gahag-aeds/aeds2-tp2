SrcDir = src
DataDir = data
BinDir = bin

LibAeds = $(SrcDir)/libaeds


OutputFileName   = tp2
OutputFile       = $(BinDir)/$(OutputFileName)
CompilationUnits = $(shell find $(SrcDir) -name '*.c')


Build       = clang
Standard    = c99
Warnings    = -Wall -Wextra
Optimize    = -flto -O2
Libs        = -lm
Debug       = -g

BuildFlags  = $(Warnings)       \
              -std=$(Standard)  \
              $(Optimize)       \
							$(Libs)		        \
              -I $(SrcDir)      \
              -o $(OutputFile)

ReleaseFlags = -DNDEBUG -s



directories: $(SrcDir)
	@[ -d "$(BinDir)" ] || mkdir "$(BinDir)";

datadir:
	@[ -d "$(DataDir)" ] || mkdir "$(DataDir)";


build: directories
	@$(Build) $(BuildFlags) $(CompilationUnits)

release: directories
	@$(Build) $(ReleaseFlags) $(BuildFlags) $(CompilationUnits)


# valgrind: directories build
# 	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes $(OutputFile) $(SettingsFile)

# debug: directories
# 	@$(Build) $(Debug) $(BuildFlags) $(CompilationUnits)
# 	@gdb --args $(OutputFile) $(SettingsFile)


clean:
	rm -f $(OutputFile)
