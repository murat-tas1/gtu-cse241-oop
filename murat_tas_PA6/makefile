CXX       := g++
CXXFLAGS  := -std=c++11 -Wall -g

# Proje kökünde bulunan tüm .cpp dosyaları
SRCS := \
    BaseMedia.cpp \
    Text.cpp \
    Image.cpp \
    Audio.cpp \
    Video.cpp \
    Dataset.cpp \
    Player.cpp \
    Viewer.cpp \
    main.cpp

# Her .cpp için karşılık gelen .o dosyası
OBJS := $(SRCS:.cpp=.o)

# Oluşturulacak executable adı
TARGET := pa6

.PHONY: all clean

# "make" yazdığında önce all hedefi çalışır -> $(TARGET)
all: $(TARGET)

# Linkleme kuralı: TARGET (pa6), OBJS (tüm .o'lar) üzerinden oluşturulur
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Her .cpp → .o derleme kuralı
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Temizlik
clean:
	rm -f *.o $(TARGET)

