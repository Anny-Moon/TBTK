# Copyright 2016 Anna Sinelnikova and Kristofer Björnson
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

## @file Makefile
## @brief ...
##
## Run $make list_of_objects to see
## the rule for compilation only onle file.
##
## @author Anna Sinelnikova
## @author Kristofer Björnson
##
## @cond

# Main compiler
CC:= g++

# CUDA compiler
NVCC:= nvcc

# Compiler flags
CFLAGS:= -std=c++11 -Wall -fopenmp -O3

# CUDA compiler flags
NVCCFLAGS:= -D_FORCE_INLINES -std=c++11 --compiler-options "-fopenmp"

# Libraries (can also include path to these libraries as -L/SOME_PATH)
LIB:= -lm

#
CUDA_LIB:=

# Optimization (-O3 or -O2)
OPT:= -O3

# Optimization (-O3 or -O2)
NVCCOPT:= -O3

# Directory for executables
BIN_DIR:= .

# Name for exectutable
STATIC_LIB = build/libTBTK.a

# Root directories for .h files
INC_DIR = include/Builders/
INC_DIR += include/Core/
INC_DIR += include/Lattices/
INC_DIR += include/Lattices/D2/
INC_DIR += include/Lattices/D3/
INC_DIR += include/Properties/
INC_DIR += include/PropertyExtractors/
INC_DIR += include/Solvers/
INC_DIR += include/StatesAndOperators/
INC_DIR += include/Utilities/
INC_DIR += include/Uncategorized/
INC_DIR += $(TBTK_dir)/hdf5/hdf5-build/hdf5/include/
INC_DIR += $(TBTK_dir)/hdf5/hdf5-1.8.16/include/

# Main source directory
SRC_DIR = src/Builders
SRC_DIR += src/Core
SRC_DIR += src/Lattices
SRC_DIR += src/Lattices/D2
SRC_DIR += src/Lattices/D3
SRC_DIR += src/Properties
SRC_DIR += src/PropertyExtractors
SRC_DIR += src/Solvers
SRC_DIR += src/StatesAndOperators
SRC_DIR += src/Utilities
SRC_DIR += src/Uncategorized

# CUDA source directory
CUDA_SRC_DIR:= src/cuda

#No CUDA source directory
NOCUDA_SRC_DIR:= src/nocuda

# Directory for Objects
OBJ_DIR:= build


#---------------------No need to change the following!-------------------

# Include files are needed fot Includes
INC_FILES :=  $(wildcard $(INC_DIR)/*.h))

# All include directories are needed for Includes
INC_DIRS:= $(dir $(INC_FILES))

# Includes: -I ...
LDLIBS:=$(addprefix -I, $(INC_DIRS))

# Source files
#SRC :=  $(wildcard $(SRC_DIR)/*.cpp)
SRC :=  $(foreach srcDir, $(SRC_DIR), $(wildcard $(srcDir)/*.cpp))

# CUDA source files
CUDA_SRC := $(wildcard $(CUDA_SRC_DIR)/*.cu)

# No CUDA source files
NOCUDA_SRC := $(wildcard $(NOCUDA_SRC_DIR)/*.cpp)

# Object files
OBJ := $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.cpp=.o)))

# CUDA object files
CUDA_OBJ := $(addprefix $(OBJ_DIR)/, $(addprefix cuda, $(notdir $(CUDA_SRC:.cu=.o))))

# CUDA object files
NOCUDA_OBJ := $(addprefix $(OBJ_DIR)/, $(addprefix nocuda, $(notdir $(NOCUDA_SRC:.cpp=.o))))

#All object files
ALL_OBJ := $(OBJ) $(CUDA_OBJ)

# File names of objects without directory name
OBJ_PURE := $(notdir $(OBJ))

# CUDA file names of objects without directory name
CUDA_OBJ_PURE := $(notdir $(CUDA_OBJ))

# CUDA file names of objects without directory name
NOCUDA_OBJ_PURE := $(notdir $(NOCUDA_OBJ))

all: $(STATIC_LIB)

# Linking
$(STATIC_LIB): $(OBJ) $(CUDA_OBJ)
	@echo "Linking: " $(notdir $(STATIC_LIB))
	@ar rcs $(STATIC_LIB) $(OBJ) $(CUDA_OBJ)

cuda: $(OBJ) $(CUDA_OBJ)
	@echo "Linking: " $(notdir $(STATIC_LIB))
	@ar rcs $(STATIC_LIB) $(OBJ) $(CUDA_OBJ)

nocuda: $(OBJ) $(NOCUDA_OBJ)
	@echo "Linking: " $(notdir $(STATIC_LIB))
	@ar rcs $(STATIC_LIB) $(OBJ) $(NOCUDA_OBJ)

# Compilation rule
define app_compile_template
 $(1)_OBJ = $$(addprefix $$(OBJ_DIR)/, $$(notdir $$(patsubst %.cpp, %.o, $(1))))

$$($(1)_OBJ): $(1)
	@echo "Compiling: $(1)"
	@$$(CC) $$(CFLAGS) $$(OPT) -c $(1) -o $$($(1)_OBJ) $$(LDLIBS)
endef

# CUDA compilation rule
define cuda_app_compile_template
 $(1)_OBJ = $$(addprefix $$(OBJ_DIR)/, $$(addprefix cuda, $$(notdir $$(patsubst %.cu, %.o, $(1)))))

$$($(1)_OBJ): $(1)
	@echo "Compiling: $(1)"
	@$$(NVCC) $$(NVCCFLAGS) $$(NVCCOPT) -c $(1) -o $$($(1)_OBJ) $$(LDLIBS)
endef

# No CUDA compilation rule
define nocuda_app_compile_template
 $(1)_OBJ = $$(addprefix $$(OBJ_DIR)/, $$(addprefix nocuda, $$(notdir $$(patsubst %.cpp, %.o, $(1)))))

$$($(1)_OBJ): $(1)
	@echo "Compiling: $(1)"
	@$$(CC) $$(CFLAGS) $$(OPT) -c $(1) -o $$($(1)_OBJ) $$(LDLIBS)
endef

# Compile
$(foreach app, $(SRC), $(eval $(call app_compile_template,$(app))))

# CUDA compile
$(foreach app, $(CUDA_SRC), $(eval $(call cuda_app_compile_template,$(app))))

# No CUDA compile
$(foreach app, $(NOCUDA_SRC), $(eval $(call nocuda_app_compile_template,$(app))))

# Cleaning
clean:
	@echo "Cleaning: build/"
	@rm -r build/*

list_of_objects:
	@echo $(OBJ)

# For debugging makefile
print:
	@echo $(SRC_DIR)
	@echo $(SRC)
	@echo $(CUDA_SRC)
	@echo $(LDLIBS)
	@echo INC_DIR
#	@echo $(OBJ)
#	@echo $(addprefix ./build/, $(notdir $(patsubst %.cpp, %.o, $(SRC))))

## @endconf

