//
// Created by Hitoshi Sauji
//

#include "../myImage.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// 移動平均法での画像処理
/**
 * @param gray_img 1チャンネル画像
 * @return 画像処理後の1チャンネル画像
 */
ImageMat moving_average(const ImageMat &gray_img)
{
  ImageMat moving_img = gray_img;
  for (int y = 1; y < gray_img.m_height - 1; y++)
  {
    for (int x = 1; x < gray_img.m_width - 1; x++)
    {
      moving_img.m_pixels[(x + y * gray_img.m_width)] =
          (gray_img.m_pixels[((x - 1) + (y - 1) * gray_img.m_width)] +
           gray_img.m_pixels[(x + (y - 1) * gray_img.m_width)] +
           gray_img.m_pixels[(x + 1 + (y - 1) * gray_img.m_width)] +
           gray_img.m_pixels[((x - 1) + y * gray_img.m_width)] +
           gray_img.m_pixels[(x + y * gray_img.m_width)] +
           gray_img.m_pixels[((x + 1) + y * gray_img.m_width)] +
           gray_img.m_pixels[((x - 1) + (y + 1) * gray_img.m_width)] +
           gray_img.m_pixels[(x + (y + 1) * gray_img.m_width)] +
           gray_img.m_pixels[((x + 1) + (y + 1) * gray_img.m_width)]) /
          9;
    }
  }

  return moving_img;
}

// 移動平均法の画像処理
/**
 * @param gray_img 1チャンネル画像
 * @return 画像処理後の1チャンネル画像
 */
ImageMat median(const ImageMat &gray_img)
{
  ImageMat median_img = gray_img;
  std::vector<int> pixels(9);

  for (int y = 1; y < gray_img.m_width - 1; y++)
  {
    for (int x = 1; x < gray_img.m_height - 1; x++)
    {
      pixels[0] = median_img.m_pixels[((x - 1) + (y - 1) * gray_img.m_width)];
      pixels[1] = median_img.m_pixels[(x + (y - 1) * gray_img.m_width)];
      pixels[2] = median_img.m_pixels[((x + 1) + (y - 1) * gray_img.m_width)];
      pixels[3] = median_img.m_pixels[((x - 1) + y * gray_img.m_width)];
      pixels[4] = median_img.m_pixels[(x + y * gray_img.m_width)];
      pixels[5] = median_img.m_pixels[((x + 1) + y * gray_img.m_width)];
      pixels[6] = median_img.m_pixels[((x - 1) + (y + 1) * gray_img.m_width)];
      pixels[7] = median_img.m_pixels[(x + (y + 1) * gray_img.m_width)];
      pixels[8] = median_img.m_pixels[((x + 1) + (y + 1) * gray_img.m_width)];

      std::sort(pixels.begin(), pixels.end());
      median_img.m_pixels[(x + y * gray_img.m_width)] = pixels[4];
    }
  }

  return median_img;
}
