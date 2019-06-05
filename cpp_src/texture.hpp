#ifndef __ICMCCG_TEXTURE_HPP
#define __ICMCCG_TEXTURE_HPP
#include <string>
#include <memory>

class Texture {
public:
  Texture();

  void setTextureFilename(std::string &path);

  std::string &getFilename();

  // TODO: change to shaded pointer
  void setImage(unsigned char **image, int width, int height, int channels);

  int getWidth();
  int getHeight();
  unsigned char *getImageData();

protected:
  std::string _texPath;
  unsigned char *_image;
  int _width, _height, _channels;
};

#endif