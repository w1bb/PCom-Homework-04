# Copyright Valentin-Ioan Vintila 2023.
# All rights reserved.

.DEFAULT_GOAL := build
.PHONY: build clean pack

# C++ options
CXX = g++
CXXFLAGS = -g -std=c++17 -Wall -Wextra -Wshadow -Wmissing-declarations
LDFLAGS = # -lm

# Final result
OUTPUT = main

# Intermediate results
OBJFILES = 

# Archive name
ARCHIVE = Vintila_Valentin-Ioan_323CA_Tema3PC.zip



# ======== BUILD INSTRUCTIONS ========

build: $(OUTPUT)

$(OUTPUT): $(OUTPUT).cpp $(OBJFILES)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@



# ======== CLEANUP AND PACKING ========

clean:
	rm -rf $(OUTPUT) $(OBJFILES)

pack:
	zip $(ARCHIVE) -r -9 *.cpp *.hpp Makefile README nlohmann
