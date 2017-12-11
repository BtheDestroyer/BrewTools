#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# DATA is a list of directories containing data files
# INCLUDES is a list of directories containing header files
#---------------------------------------------------------------------------------
export TARGET		:=	brewtools
export BUILD		:=	build
export SOURCES		:=	source
export DATA		:=	data
export INCLUDES	:=	include

export ROOT := $(CURDIR)

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
export ARCH	:=	-march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft

export CFLAGS	:=	-g -Wall -Werror -Wextra -O2 -mword-relocations -ffunction-sections -fno-strict-aliasing -fomit-frame-pointer

export CFLAGS	+= $(INCLUDE)

export CXXFLAGS	:= $(CFLAGS) -fno-rtti -fno-exceptions -std=gnu++11

export ASFLAGS	:= -g $(ARCH)

#---------------------------------------------------------------------------------

export CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
export CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
export SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
export BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
#---------------------------------------------------------------------------------
	export LD	:=	$(CC)
#---------------------------------------------------------------------------------
else
#---------------------------------------------------------------------------------
	export LD	:=	$(CXX)
#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------

#---------------------------------------------------------------------------------
# Build all libs
#---------------------------------------------------------------------------------

all:
	@echo "########## Building and installing all versions ##########"
	@$(MAKE) --no-print-directory windows
	@$(MAKE) --no-print-directory 3ds-install
	@$(MAKE) --no-print-directory wiiu-install
	@echo "########## All builds complete! ##########"

#---------------------------------------------------------------------------------
# Builds
#---------------------------------------------------------------------------------

windows:
	@echo "##### Building for Windows™ development #####"
	@$(MAKE) --no-print-directory -fMakefileWin MAKEFILE="$(ROOT)/MakefileWin" BUILD="$(ROOT)/$(BUILD)/Windows"
	@echo "##### Build complete! #####"

3ds:
	@echo "##### Building for Nintendo 3DS™ development #####"
	@$(MAKE) --no-print-directory -fMakefile3DS MAKEFILE="$(ROOT)/Makefile3DS" BUILD="$(ROOT)/$(BUILD)/3DS"
	@echo "##### Build complete! #####"

wiiu:
	@echo "##### Building for Wii U™ development #####"
	@$(MAKE) --no-print-directory -fMakefileWiiU MAKEFILE="$(ROOT)/MakefileWiiU" BUILD="$(ROOT)/$(BUILD)/WiiU"
	@echo "##### Build complete! #####"

#---------------------------------------------------------------------------------
# Installs
#---------------------------------------------------------------------------------

windows-install:
	@echo "##### Building and installing for Windows™ development #####"
	@$(MAKE) --no-print-directory -fMakefileWin install MAKEFILE="$(ROOT)/MakefileWin" BUILD="$(ROOT)/$(BUILD)/Windows"
	@echo "##### Build and install complete! #####"

3ds-install:
	@echo "##### Building and installing for Nintendo 3DS™ development #####"
	@$(MAKE) --no-print-directory -fMakefile3DS install MAKEFILE="$(ROOT)/Makefile3DS" BUILD="$(ROOT)/$(BUILD)/3DS"
	@echo "##### Build and install complete! #####"

wiiu-install:
	@echo "##### Building and installing for Wii U™ development #####"
	@$(MAKE) --no-print-directory -fMakefileWiiU install MAKEFILE="$(ROOT)/MakefileWiiU" BUILD="$(ROOT)/$(BUILD)/WiiU"
	@echo "##### Build and install complete! #####"

#---------------------------------------------------------------------------------
# Cleanup
#---------------------------------------------------------------------------------

clean:
	@echo "##### Cleaning all builds! #####"
	@$(MAKE) --no-print-directory -f=MakefileWin clean MAKEFILE="$(ROOT)/MakefileWin" BUILD="$(ROOT)/$(BUILD)/Windows"
	@$(MAKE) --no-print-directory -f=Makefile3DS clean MAKEFILE="$(ROOT)/Makefile3DS" BUILD="$(ROOT)/$(BUILD)/3DS"
	@$(MAKE) --no-print-directory -f=MakefileWiiU clean MAKEFILE="$(ROOT)/MakefileWiiU" BUILD="$(ROOT)/$(BUILD)/WiiU"
	@echo "##### Clean complete! #####"

#---------------------------------------------------------------------------------
