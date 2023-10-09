//
// Created by Hitoshi Sauji
//
// 参考サイト: https://www.peko-step.com/tool/hslrgb.html,  https://docs.opencv.org/3.4/de/d25/imgproc_color_conversions.html

#include <cmath>
#include <vector>
#include <algorithm>

#include "../myImage.hpp"

// 色相回転
/**
 * @param hls_image ヘッダ情報用3チャンネル画像
 * @param angle_degree エッジ角度
 * @return 画像処理済3チャンネル画像
*/
ImageMat rotate_hue(const ImageMat &hls_image, const double &angle_degree)
{
  ImageMat rotate_image = hls_image;
  
  //処理を記述

  return rotate_image;
}

// BGR表色系からHLS表色系への変換
/**
 * @param bgr_image 3チャンネル画像
 * @return 画像処理済み3チャンネル画像
*/
ImageMat bgr2hls(const ImageMat &bgr_image)
{
  ImageMat hls_image = bgr_image;

  //処理を記述

  return hls_image;
}


// HLS表色系からBGR表色系への変換
/**
 * @param hls_image 3チャンネル画像
 * @return 画像処理済み3チャンネル画像
*/
ImageMat hls2bgr(const ImageMat &hls_image)
{
  ImageMat bgr_image = hls_image;

  //処理を記述

  return bgr_image;
}
