//
// Created by Hitoshi Sauji.
//

#include "../myImage.hpp"
#include <iostream>
#include <string>
#include <vector>

// 3チャンネルカラー画像を1チャンネルグレースケール画像に変換
/**
 * @param color_img 3チャンネル画像
 * @return 1チャンネル画像
*/
ImageMat color2gray(const ImageMat &color_img)
{
  ImageMat gray_img = color_img;

  gray_img.m_ch = 1;
  gray_img.m_length = gray_img.m_width * gray_img.m_height * gray_img.m_ch;

  gray_img.m_pixels.resize(gray_img.m_length);

  // 色変換処理
  // 3チャンネルの平均値を1チャンネル画像の画素値にする
  for (int i = 0; i < gray_img.m_length; i++)
  {
    // 処理を記述
  }

  return gray_img;
}

// 1チャンネルグレースケール画像を3チャンネルカラー画像に変換
/**
 * @param gray_img 1チャンネル画像
 * @return 3チャンネル画像
*/
ImageMat gray2color(const ImageMat &gray_img)
{
  //
  // 処理を記述
  //

  // リターンした画像は3つのチャンネルすべてが同じ値なのでグレーになります
  return color_img;
}



//此処から先は完成しています


// 3チャンネルを1チャンネルずつに分け、1チャンネル分の画像データ3つを配列3つで返す
/**
 * @param img 3チャンネル画像
 * @return 1チャンネル画像 * 3つ
*/
std::vector<ImageMat> split_Channel(const ImageMat &img)
{

  if (img.m_ch == 1)
    return {img};

  const auto gray_img = color2gray(img);
  ImageMat img_ch1 = gray_img;
  ImageMat img_ch2 = gray_img;
  ImageMat img_ch3 = gray_img;

  for (int new_idx = 0; new_idx < gray_img.m_length; new_idx++)
  {
    img_ch1.m_pixels[new_idx] = img.m_pixels[3 * new_idx];
    img_ch2.m_pixels[new_idx] = img.m_pixels[3 * new_idx + 1];
    img_ch3.m_pixels[new_idx] = img.m_pixels[3 * new_idx + 2];
  }

  return {img_ch1, img_ch2, img_ch3};
}

// 1チャンネルのデータ3つを3チャンネル画像1枚にまとめて返す
/**
 * @param ch1, ch2, ch3 1チャンネル画像
 * @return 3チャンネル画像
*/
ImageMat merge_Channel(ImageMat ch1, ImageMat ch2, ImageMat ch3)
{
  ImageMat multi_ch_img = gray2color(ch1); // ヘッダの書き込み
  for (int new_idx = 0; new_idx < ch1.m_length; new_idx++)
  {
    multi_ch_img.m_pixels.push_back(ch1.m_pixels[new_idx]);
    multi_ch_img.m_pixels.push_back(ch2.m_pixels[new_idx]);
    multi_ch_img.m_pixels.push_back(ch3.m_pixels[new_idx]);
  }

  return multi_ch_img;
}

// ImageMatD -> ImageMatに変換
/**
 * @param double_data ImageMatDクラス画像
 * @return ImageMatクラス画像
*/
ImageMat double2uint8t(const ImageMatD &double_data) // double->uint8_t
{
  ImageMat uint_data;

  // クラスの初期値を定義
  uint_data.m_header = double_data.m_header;
  uint_data.m_width = double_data.m_width;
  uint_data.m_height = double_data.m_height;
  uint_data.m_ch = double_data.m_ch;
  uint_data.m_length = double_data.m_length;
  uint_data.m_pixels.resize(double_data.m_length);
  uint_data.m_pixels.assign(double_data.m_length, 0); // 配列の初期化

  for (int y = 0; y < double_data.m_height; y++)
  {
    for (int x = 0; x < double_data.m_width; x++)
    {
      auto data = (uint8_t)double_data.getPixel(x, y, 0);
      uint_data.setPixel(x, y, 0, data);
    }
  }

  return uint_data;
}
