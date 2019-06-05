#include <texture.hpp>

Texture::Texture() {}

int Texture::getWidth() { return _width; }
int Texture::getHeight() { return _height; }
unsigned char *Texture::getImageData() { return _image; }

void Texture::setImage(unsigned char **image, int width, int height,
                       int channels) {
  _image = *image;
  _width = width;
  _height = height;
  _channels = channels;
}

void Texture::setTextureFilename(std::string &path) {
  _texPath = std::string(path);
}

std::string &Texture::getFilename() { return _texPath; }
