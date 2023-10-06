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
  for (int y = 0; y < hls_image.m_height; y++)
  {
    for (int x = 0; x < hls_image.m_width; x++)
    {
      double hue = hls_image.getPixel(x, y, 0);
      hue = hue * 2 + angle_degree;
      if (hue >= 360)
        hue = hue - 360;

      hue = hue / 2;
      rotate_image.setPixel(x, y, 0, (uint8_t)hue);
    }
  }

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

  for (int y = 0; y < bgr_image.m_height; y++)
  {
    for (int x = 0; x < bgr_image.m_width; x++)
    {
      const double b = bgr_image.getPixel(x, y, 0) / 255.0; // 正規化
      const double g = bgr_image.getPixel(x, y, 1) / 255.0;
      const double r = bgr_image.getPixel(x, y, 2) / 255.0;

      const double value_max = std::max(b, std::max(g, r));
      const double value_min = std::min(b, std::min(g, r));

      const double lightness = (value_max + value_min) / 2.0;

      double saturation; 
      if (value_max == value_min)
        saturation = 0;
      else if (lightness < 0.5)
        saturation = (value_max - value_min) / (value_max + value_min);
      else
        saturation = (value_max - value_min) / (2.0 - (value_max + value_min));

      double hue;
      if (saturation == 0)
        hue = 0;
      else if (value_max == r)
        hue = (60.0 * (g - b)) / saturation;
      else if (value_max == g)
        hue = 120.0 + (60.0 * (b - r) / saturation);
      else
        hue = 240.0 + (60.0 * (r - g) / saturation);

      if (hue <= 0)
        hue = hue + 360.0; 

      hls_image.setPixel(x, y, 0, (uint8_t)(hue / 2));
      hls_image.setPixel(x, y, 1, (uint8_t)(lightness * 255));
      hls_image.setPixel(x, y, 2, (uint8_t)(saturation * 255));
    }
  }

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

  for (int y = 0; y < hls_image.m_height; y++)
  {
    for (int x = 0; x < hls_image.m_width; x++)
    {
      double hue = hls_image.getPixel(x, y, 0) * 2.0;
      const double lightness = hls_image.getPixel(x, y, 1) / 255.0;
      const double saturation = hls_image.getPixel(x, y, 2) / 255.0;

      if (hue > 300.0)
        hue = hue - 360.0;

      double value_max, value_min;
      if (lightness < 0.5)
      {
        value_max = (lightness + lightness * saturation);
        value_min = (lightness - lightness * saturation);
      }
      else
      {
        value_max = (lightness + (1 - lightness) * saturation);
        value_min = (lightness - (1 - lightness) * saturation);
      }

      double b, g, r;
      if (hue >= -60.0 && hue < 0.0)
      {
        b = ((-hue) / 60.0) * (value_max - value_min) + value_min;
        g = value_min;
        r = value_max;
      }
      else if (hue >= 0.0 && hue < 60.0)
      {
        b = value_min;
        g = (hue / 60.0) * (value_max - value_min) + value_min;
        r = value_max;
      }
      else if (hue >= 60.0 && hue < 120.0)
      {
        b = value_min;
        g = value_max;
        r = ((120.0 - hue) / 60.0) * (value_max - value_min) + value_min;
      }
      else if (hue >= 120.0 && hue < 180.0)
      {
        b = ((hue - 120.0) / 60.0) * (value_max - value_min) + value_min;
        g = value_max;
        r = value_min;
      }
      else if (hue >= 180.0 && hue < 240.0)
      {
        b = value_max;
        g = ((240.0 - hue) / 60.0) * (value_max - value_min) + value_min;
        r = value_min;
      }
      else if (hue >= 240.0 && hue <= 300.0)
      {
        b = value_max;
        g = value_min;
        r = ((hue - 240.0) / 60.0) * (value_max - value_min) + value_min;
      }

      bgr_image.setPixel(x, y, 0, (uint8_t)(b * 255.0));
      bgr_image.setPixel(x, y, 1, (uint8_t)(g * 255.0));
      bgr_image.setPixel(x, y, 2, (uint8_t)(r * 255.0));
    }
  }

  return bgr_image;
}
