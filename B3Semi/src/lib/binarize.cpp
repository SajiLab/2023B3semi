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
  int white = 255;
  ImageMat dilate_img = binarize_img;

  for (int y = 1; y < binarize_img.m_height - 1; y++)
  {
    for (int x = 1; x < binarize_img.m_width - 1; x++)
    {
      if (binarize_img.m_pixels[(x + y * binarize_img.m_width)] == white)
      {
        dilate_img.m_pixels[((x - 1) + (y - 1) * binarize_img.m_width)] = white;
        dilate_img.m_pixels[((x - 1) + y * binarize_img.m_width)] = white;
        dilate_img.m_pixels[((x - 1) + (y + 1) * binarize_img.m_width)] = white;
        dilate_img.m_pixels[(x + (y - 1) * binarize_img.m_width)] = white;
        dilate_img.m_pixels[(x + y * binarize_img.m_width)] = white;
        dilate_img.m_pixels[(x + (y + 1) * binarize_img.m_width)] = white;
        dilate_img.m_pixels[((x + 1) + (y - 1) * binarize_img.m_width)] = white;
        dilate_img.m_pixels[((x + 1) + y * binarize_img.m_width)] = white;
        dilate_img.m_pixels[((x + 1) + (y + 1) * binarize_img.m_width)] = white;
      }
    }
  }

  // 画像の周囲1pxに対する処理

  // 左下
  if (binarize_img.m_pixels[0] == white)
  {
    dilate_img.m_pixels[0] = white;
    dilate_img.m_pixels[1] = white;
    dilate_img.m_pixels[dilate_img.m_width] = white;
    dilate_img.m_pixels[dilate_img.m_width + 1] = white;
  }

  // 右下
  if (binarize_img.m_pixels[binarize_img.m_width - 1] == white)
  {
    dilate_img.m_pixels[dilate_img.m_width - 2] = white;
    dilate_img.m_pixels[dilate_img.m_width - 1] = white;
    dilate_img.m_pixels[dilate_img.m_width - 2 + dilate_img.m_width] = white;
    dilate_img.m_pixels[dilate_img.m_width - 1 + dilate_img.m_width] = white;
  }

  // 左上
  if (binarize_img.m_pixels[(binarize_img.m_height - 1) * binarize_img.m_width] == white)
  {
    dilate_img.m_pixels[(dilate_img.m_height - 1) * dilate_img.m_width] = white;
    dilate_img.m_pixels[(dilate_img.m_height - 2) * dilate_img.m_width] = white;
    dilate_img.m_pixels[(dilate_img.m_height - 1) * dilate_img.m_width + 1] = white;
    dilate_img.m_pixels[(dilate_img.m_height - 2) * dilate_img.m_width + 1] = white;
  }

  // 右上
  if (binarize_img.m_pixels[(binarize_img.m_height - 1) * binarize_img.m_width + binarize_img.m_width - 1] == white)
  {
    dilate_img.m_pixels[(dilate_img.m_height - 1) * dilate_img.m_width + dilate_img.m_width - 1] = white;
    dilate_img.m_pixels[(dilate_img.m_height - 1) * dilate_img.m_width + dilate_img.m_width - 2] = white;
    dilate_img.m_pixels[(dilate_img.m_height - 2) * dilate_img.m_width + dilate_img.m_width - 1] = white;
    dilate_img.m_pixels[(dilate_img.m_height - 2) * dilate_img.m_width + dilate_img.m_width - 2] = white;
  }

  // 下1列
  for (int x = 1; x < binarize_img.m_width - 1; x++)
  {
    if (binarize_img.m_pixels[x] == white)
    {
      dilate_img.m_pixels[x - 1] = white;
      dilate_img.m_pixels[x] = white;
      dilate_img.m_pixels[x + 1] = white;
      dilate_img.m_pixels[x - 1 + dilate_img.m_width] = white;
      dilate_img.m_pixels[x + dilate_img.m_width] = white;
      dilate_img.m_pixels[x + 1 + dilate_img.m_width] = white;
    }
  }

  // 上1列
  for (int x = 1; x < binarize_img.m_width - 1; x++)
  {
    if (binarize_img.m_pixels[x + (binarize_img.m_height - 1) * binarize_img.m_width] == white)
    {
      dilate_img.m_pixels[x - 1 + (dilate_img.m_height - 1) * dilate_img.m_width] = white;
      dilate_img.m_pixels[x + (dilate_img.m_height - 1) * dilate_img.m_width] = white;
      dilate_img.m_pixels[x + 1 + (dilate_img.m_height - 1) * dilate_img.m_width] = white;
      dilate_img.m_pixels[x - 1 + (dilate_img.m_height - 2) * dilate_img.m_width] = white;
      dilate_img.m_pixels[x + (dilate_img.m_height - 2) * dilate_img.m_width] = white;
      dilate_img.m_pixels[x + 1 + (dilate_img.m_height - 2) * dilate_img.m_width] = white;
    }
  }

  // 左1列
  for (int y = 1; y < binarize_img.m_height - 1; y++)
  {
    if (binarize_img.m_pixels[y * binarize_img.m_width] == white)
    {
      dilate_img.m_pixels[(y - 1) * dilate_img.m_width] = white;
      dilate_img.m_pixels[y * dilate_img.m_width] = white;
      dilate_img.m_pixels[(y + 1) * dilate_img.m_width] = white;
      dilate_img.m_pixels[(y - 1) * dilate_img.m_width + 1] = white;
      dilate_img.m_pixels[y * dilate_img.m_width + 1] = white;
      dilate_img.m_pixels[(y + 1) * dilate_img.m_width + 1] = white;
    }
  }

  // 右1列
  for (int y = 1; y < binarize_img.m_height - 1; y++)
  {
    if (binarize_img.m_pixels[binarize_img.m_width - 1 + y * binarize_img.m_width] == white)
    {
      dilate_img.m_pixels[dilate_img.m_width - 1 + (y - 1) * dilate_img.m_width] = white;
      dilate_img.m_pixels[dilate_img.m_width - 1 + y * dilate_img.m_width] = white;
      dilate_img.m_pixels[dilate_img.m_width - 1 + (y + 1) * dilate_img.m_width] = white;
      dilate_img.m_pixels[dilate_img.m_width - 2 + (y - 1) * dilate_img.m_width] = white;
      dilate_img.m_pixels[dilate_img.m_width - 2 + y * dilate_img.m_width] = white;
      dilate_img.m_pixels[dilate_img.m_width - 2 + (y + 1) * dilate_img.m_width] = white;
    }
  }

  return dilate_img;
}

// 収縮
/**
 * @param binarize_img 2値化処理済み1チャンネル画像
 * @return 画像処理済1チャンネル画像
*/
ImageMat erosion(const ImageMat &binarize_img)
{
  ImageMat erode_img = binarize_img;
  int black = 0;

  for (int y = 1; y < binarize_img.m_height - 1; y++)
  {
    for (int x = 1; x < binarize_img.m_width - 1; x++)
    {
      if (binarize_img.m_pixels[(x + y * binarize_img.m_width)] == black)
      {
        erode_img.m_pixels[((x - 1) + (y - 1) * binarize_img.m_width)] = black;
        erode_img.m_pixels[((x - 1) + y * binarize_img.m_width)] = black;
        erode_img.m_pixels[((x - 1) + (y + 1) * binarize_img.m_width)] = black;
        erode_img.m_pixels[(x + (y - 1) * binarize_img.m_width)] = black;
        erode_img.m_pixels[(x + y * binarize_img.m_width)] = black;
        erode_img.m_pixels[(x + (y + 1) * binarize_img.m_width)] = black;
        erode_img.m_pixels[((x + 1) + (y - 1) * binarize_img.m_width)] = black;
        erode_img.m_pixels[((x + 1) + y * binarize_img.m_width)] = black;
        erode_img.m_pixels[((x + 1) + (y + 1) * binarize_img.m_width)] = black;
      }
    }
  }

  // 画像の周囲1pxに対する処理

  // 左下
  if (binarize_img.m_pixels[0] == black)
  {
    erode_img.m_pixels[0] = black;
    erode_img.m_pixels[1] = black;
    erode_img.m_pixels[erode_img.m_width] = black;
    erode_img.m_pixels[erode_img.m_width + 1] = black;
  }

  // 右下
  if (binarize_img.m_pixels[binarize_img.m_width - 1] == black)
  {
    erode_img.m_pixels[erode_img.m_width - 2] = black;
    erode_img.m_pixels[erode_img.m_width - 1] = black;
    erode_img.m_pixels[erode_img.m_width - 2 + erode_img.m_width] = black;
    erode_img.m_pixels[erode_img.m_width - 1 + erode_img.m_width] = black;
  }

  // 左上
  if (binarize_img.m_pixels[(binarize_img.m_height - 1) * binarize_img.m_width] == black)
  {
    erode_img.m_pixels[(erode_img.m_height - 1) * erode_img.m_width] = black;
    erode_img.m_pixels[(erode_img.m_height - 2) * erode_img.m_width] = black;
    erode_img.m_pixels[(erode_img.m_height - 1) * erode_img.m_width + 1] = black;
    erode_img.m_pixels[(erode_img.m_height - 2) * erode_img.m_width + 1] = black;
  }

  // 右上
  if (binarize_img.m_pixels[(binarize_img.m_height - 1) * binarize_img.m_width + binarize_img.m_width - 1] == black)
  {
    erode_img.m_pixels[(erode_img.m_height - 1) * erode_img.m_width + erode_img.m_width - 1] = black;
    erode_img.m_pixels[(erode_img.m_height - 1) * erode_img.m_width + erode_img.m_width - 2] = black;
    erode_img.m_pixels[(erode_img.m_height - 2) * erode_img.m_width + erode_img.m_width - 1] = black;
    erode_img.m_pixels[(erode_img.m_height - 2) * erode_img.m_width + erode_img.m_width - 2] = black;
  }

  // 下1列
  for (int x = 1; x < binarize_img.m_width - 1; x++)
  {
    if (binarize_img.m_pixels[x] == black)
    {
      erode_img.m_pixels[x - 1] = black;
      erode_img.m_pixels[x] = black;
      erode_img.m_pixels[x + 1] = black;
      erode_img.m_pixels[x - 1 + erode_img.m_width] = black;
      erode_img.m_pixels[x + erode_img.m_width] = black;
      erode_img.m_pixels[x + 1 + erode_img.m_width] = black;
    }
  }

  // 上1列
  for (int x = 1; x < binarize_img.m_width - 1; x++)
  {
    if (binarize_img.m_pixels[x + (binarize_img.m_height - 1) * binarize_img.m_width] == black)
    {
      erode_img.m_pixels[x - 1 + (erode_img.m_height - 1) * erode_img.m_width] = black;
      erode_img.m_pixels[x + (erode_img.m_height - 1) * erode_img.m_width] = black;
      erode_img.m_pixels[x + 1 + (erode_img.m_height - 1) * erode_img.m_width] = black;
      erode_img.m_pixels[x - 1 + (erode_img.m_height - 2) * erode_img.m_width] = black;
      erode_img.m_pixels[x + (erode_img.m_height - 2) * erode_img.m_width] = black;
      erode_img.m_pixels[x + 1 + (erode_img.m_height - 2) * erode_img.m_width] = black;
    }
  }

  // 左1列
  for (int y = 1; y < binarize_img.m_height - 1; y++)
  {
    if (binarize_img.m_pixels[y * binarize_img.m_width] == black)
    {
      erode_img.m_pixels[(y - 1) * erode_img.m_width] = black;
      erode_img.m_pixels[y * erode_img.m_width] = black;
      erode_img.m_pixels[(y + 1) * erode_img.m_width] = black;
      erode_img.m_pixels[(y - 1) * erode_img.m_width + 1] = black;
      erode_img.m_pixels[y * erode_img.m_width + 1] = black;
      erode_img.m_pixels[(y + 1) * erode_img.m_width + 1] = black;
    }
  }

  // 右1列
  for (int y = 1; y < binarize_img.m_height - 1; y++)
  {
    if (binarize_img.m_pixels[binarize_img.m_width - 1 + y * binarize_img.m_width] == black)
    {
      erode_img.m_pixels[erode_img.m_width - 1 + (y - 1) * erode_img.m_width] = black;
      erode_img.m_pixels[erode_img.m_width - 1 + y * erode_img.m_width] = black;
      erode_img.m_pixels[erode_img.m_width - 1 + (y + 1) * erode_img.m_width] = black;
      erode_img.m_pixels[erode_img.m_width - 2 + (y - 1) * erode_img.m_width] = black;
      erode_img.m_pixels[erode_img.m_width - 2 + y * erode_img.m_width] = black;
      erode_img.m_pixels[erode_img.m_width - 2 + (y + 1) * erode_img.m_width] = black;
    }
  }

  return erode_img;
}
