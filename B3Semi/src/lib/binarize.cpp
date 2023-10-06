//
// Created by Hitoshi Sauji.
//

#include "../myImage.hpp"

// 画像の2値化処理
/**
 * @param gray_img 1チャンネル画像
 * @param threshold しきい値
 * @return 2値化画像
 */
ImageMat binarize(const ImageMat &gray_img, const int &threshold)
{
  ImageMat binarize_img = gray_img;

  int black = 0;
  int white = 255;

  for (int i = 0; i < gray_img.m_length; i++)
  {
    if (gray_img.m_pixels[i] >= threshold)
      binarize_img.m_pixels[i] = white;
    else
      binarize_img.m_pixels[i] = black;
  }

  return binarize_img;
}

// 膨張処理
/**
 * @param binarize_img 2値化処理済み1チャンネル画像
 * @return 画像処理済1チャンネル画像
 */
ImageMat dilation(const ImageMat &binarize_img)
{
  ImageMat dilate_img;

  //
  // 処理を記述
  // 周囲1pxに対する処理を忘れずに
  //
}

// 収縮
/**
 * @param binarize_img 2値化処理済み1チャンネル画像
 * @return 画像処理済1チャンネル画像
 */
ImageMat erosion(const ImageMat &binarize_img)
{
  ImageMat erode_img = binarize_img;

  //
  // 処理を記述
  // 周囲1pxに対する処理を忘れずに
  //
}
