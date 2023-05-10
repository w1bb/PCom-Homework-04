# Copyright Valentin-Ioan Vintila 2023.
# All rights reserved.

.DEFAULT_GOAL := build
.PHONY: build clean pack

# C++ options
CXX = g++
CXXFLAGS = -g -std=c++17 -Wall -Wextra -Wshadow -Wmissing-declarations
LDFLAGS = # -lm

# Final result
OUTPUT = client

# Intermediate results
OBJFILESCPP = buffer.o helpers.o structures.o
OBJFILESC = 

# Archive name
ARCHIVE = Vintila_Valentin-Ioan_323CA_Tema3PC.zip



# ======== BUILD INSTRUCTIONS ========

build: $(OBJFILESC) $(OBJFILESCPP) $(OUTPUT)

$(OBJFILESC): %.o:%.c %.h
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@

$(OBJFILESCPP): %.o:%.cpp %.hpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c $< -o $@

$(OUTPUT): $(OUTPUT).cpp $(OBJFILESC) $(OBJFILESCPP)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o $@



# ======== CLEANUP AND PACKING ========

clean:
	rm -rf $(OUTPUT) $(OBJFILESC) $(OBJFILESCPP)

pack:
	zip $(ARCHIVE) -r -9 *.c *.cpp *.hpp Makefile README nlohmann
