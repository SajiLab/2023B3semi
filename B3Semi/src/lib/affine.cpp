//
// Created by Hitoshi Sauji
//

#include "../myImage.hpp"
#include <iostream>
#include <cfloat>
#include <cmath>

// アフィン変換
/**
 * @param gray_img 1チャンネル画像
 * @return 1チャンネル画像
*/
ImageMat affine_transform(const ImageMat &gray_image)
{
  ImageMat affine_image = gray_image;

  //アフィン変換のパラメータ設定
  double param_a = 1;
  double param_b = 0;
  double param_c = 100;
  double param_d = 0;
  double param_e = 1;
  double param_f = -100;

  // アフィン逆変換
  double mat_determinant = param_a * param_e - param_b * param_d; 
  
  if (fabs(mat_determinant) < DBL_EPSILON) // mat_determinantが極小すぎる場合に処理ができないため
  {
    std::cout << "error! determinant = 0" << std::endl;
    return affine_image;
  }

  for (int y = 0; y < gray_image.m_height; y++)
  {
    for (int x = 0; x < gray_image.m_width; x++)
    {
      //逆変換後の座標(x', y')を求める
      double inverse_x = (param_e * x - param_b * y + (param_b * param_f - (param_c * param_e))) / mat_determinant;
      double inverse_y = ((-1) * param_d * x + param_a * y + (param_c * param_d - (param_a * param_f))) / mat_determinant;
      
      
      //画素補間してセット
      affine_image.setPixel(x, y, 0, (uint8_t)nearest_neighbor(gray_image, inverse_x, inverse_y));
    }
  }

  return affine_image;
}


// 補間関数の例(ニアレストネイバー法)
// 逆行列で求めた(x, y)が一番近い整数(x, y)が示すpixel値を取得する
int nearest_neighbor(const ImageMat &gray_image, double inverse_x, double inverse_y)
{
  int pixel;
  auto x = (int)floor(inverse_x);
  auto y = (int)floor(inverse_y);

  if(fabs(inverse_x) < DBL_EPSILON && fabs(inverse_y) < DBL_EPSILON)
  {
    pixel = gray_image.getPixel(x, y, 0);
  }
  else
  {
    if(0 <= x && x < gray_image.m_width && 0 <= y && y < gray_image.m_height)
    {
      pixel = (int)gray_image.getPixel(x, y, 0);
    }
    else
      pixel = 0;
  }

  return pixel;
}