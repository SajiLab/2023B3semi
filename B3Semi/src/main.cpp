//
// Created by Hitoshi Sauji
//

#include "myImage.hpp"
#include <iostream>
#include <algorithm>
#include <vector>
#include <array>
#include <fstream>

// sh build_run.sh で実行

int main()
{
  
  /*ここにmain関数の処理を記述する*/
  std::string filename = "img/lenna.bmp";
  ImageMat img = read_image(filename);
  write_image(img, "result/output.bmp");

  return 0;
}