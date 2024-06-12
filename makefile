# Folders
BIN = bin
OBJ = obj
# Others
EXE = listen_up
INCLUDE = include

# Begin Make
all: $(BIN)/$(EXE)

# Creates exe
$(BIN)/$(EXE): $(OBJ)/Main.o $(OBJ)/BST.o $(OBJ)/Song.o $(OBJ)/MaxHeap.o 
	g++ $(OBJ)/Main.o $(OBJ)/BST.o $(OBJ)/Song.o $(OBJ)/MaxHeap.o  -o $(BIN)/$(EXE)

# Creates Main.o
$(OBJ)/Main.o: Main.cpp $(INCLUDE)/Commands.h
	g++ -c -g Main.cpp -o $(OBJ)/Main.o

# Creates BST.o
$(OBJ)/BST.o: BST.cpp $(INCLUDE)/BST.h
	g++ -c -g BST.cpp -o $(OBJ)/BST.o

# Creates MaxHeap.o
$(OBJ)/MaxHeap.o: MaxHeap.cpp $(INCLUDE)/MaxHeap.h
	g++ -c -g MaxHeap.cpp -o $(OBJ)/MaxHeap.o

# Creates Song.o
$(OBJ)/Song.o: Song.cpp $(INCLUDE)/Song.h
	g++ -c -g Song.cpp -o $(OBJ)/Song.o


clean:
	rm -f $(OBJ)/*.o $(BIN)/$(EXE)