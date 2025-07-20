# Derleyici ve derleme ayarları
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Tüm kaynak kod dosyaları
SRCS = main.cpp world.cpp robot.cpp humanic.cpp optimusprime.cpp robocop.cpp roomba.cpp bulldozer.cpp kamikaze.cpp

# Otomatik olarak .cpp dosyalarının .o karşılığı
OBJS = $(SRCS:.cpp=.o)

# Üretilecek çalıştırılabilir dosya adı
TARGET = sim

# Varsayılan hedef: sim üret
all: $(TARGET)

# sim, tüm .o dosyalarına bağlıdır
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Her .cpp dosyasını .o dosyasına dönüştür
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

# Temizlik komutu: .o dosyalarını ve çalıştırılabilir dosyayı sil
clean:
	rm -f $(OBJS) $(TARGET)

