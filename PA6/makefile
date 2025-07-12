# Derleyici ve ayarları
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -Werror -pedantic -O2

# Kaynak dosyaları
SRCS = \
    main.cpp \
    MediaObject.cpp \
    Playable.cpp \
    Image.cpp \
    Video.cpp \
    Audio.cpp \
    Text.cpp \
    Dataset.cpp \
    Player.cpp \
    Viewer.cpp

# Her .cpp için karşılık gelen .o dosyaları
OBJS = $(SRCS:.cpp=.o)

# Başlık dosyaları (dependency kontrolü)
DEPS = \
    MediaObject.h \
    Visual.h \
    NonVisual.h \
    Playable.h \
    NonPlayable.h \
    Image.h \
    Video.h \
    Audio.h \
    Text.h \
    Observer.h \
    Dataset.h \
    Player.h \
    Viewer.h

# Varsayılan hedef: media_dataset adlı çalıştırılabilir dosya
all: media_dataset

media_dataset: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# .cpp -> .o dönüşümü
%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Temizlik hedefi (sak iş dosyalarını siler)
clean:
	rm -f $(OBJS) media_dataset

.PHONY: all clean
