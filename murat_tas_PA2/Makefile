# Derleyici ve derleyici bayrakları
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Kaynak ve hedef dosyalar
SRC = main.cpp Sparse1D.cpp Sparse2D.cpp
OBJ = $(SRC:.cpp=.o)
TARGET = main

# Varsayılan hedef (all): Derle ve çalıştır
all: $(TARGET)
	./$(TARGET)

# Derleme hedefi: Çalıştırılabilir dosya oluşturma
$(TARGET): $(OBJ)
	$(CXX) $(OBJ) -o $(TARGET)

# Kaynak dosyalarını derleme adımı
%.o: %.cpp Sparse1D.h Sparse2D.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Temizlik hedefi: Derleme dosyalarını sil
clean:
	rm -f $(OBJ) $(TARGET)
