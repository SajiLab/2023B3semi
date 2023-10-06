//
// Created by Hitoshi Sauji
//

// 二重インクルードの防止
#pragma once

// 各種ライブラリのインクルード
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <climits>
#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>
#include <map>
#include <random>


template <class T>
class ImageMat_
{
public:
  std::array<unsigned char, 54> m_header;
  int m_width, m_height;
  int m_ch = 3;
  int m_length;
  std::vector<T> m_pixels;

  T getPixel(const int &x, const int &y, const int &ch) const
  {
    return m_pixels[(x + y * m_width) * m_ch + ch];
  }
  void setPixel(const int &x, const int &y, const int &ch, const T &newdata)
  {
    m_pixels[(x + y * m_width) * m_ch + ch] = newdata;
  }
};
using ImageMat = ImageMat_<uint8_t>;
using ImageMatI = ImageMat_<int32_t>;
using ImageMatF = ImageMat_<float>;
using ImageMatD = ImageMat_<double>;

/* bmp画像の入出力で使用 */

ImageMat read_image(const std::string &filename);

void write_image(const ImageMat &image, const std::string &filename);

/* 3chグレー画像処理に使用 */

ImageMat color2gray(const ImageMat &color_image);

ImageMat gray2color(const ImageMat &gray_image);

ImageMat moving_average(const ImageMat &gray_image);

ImageMat median(const ImageMat &gray_image);

/* モルフォロジー変換で使用 */

ImageMat binarize(const ImageMat &gray_image, const int &threshold);

ImageMat dilation(const ImageMat &binarize_image);

ImageMat erosion(const ImageMat &binarize_image);

/*　領域ラベリングで使用 */
static int search_deep_label_hash(const std::unordered_map<int32_t, int32_t> &hash_table, const int32_t &label);
static void update_label_hash(std::unordered_map<int32_t, int32_t> &hash_table, const int32_t &label, const int32_t &true_label);
static std::unordered_map<int32_t, int32_t> create_latest_label_table(const std::unordered_map<int32_t, int32_t> &hash_table);
ImageMatI labeled_region(const ImageMat &binarize_img);
ImageMat visualize_labeled_result(const ImageMatI &labeled_img);
std::map<int32_t, uint64_t> calc_label_region_area(const ImageMatI &labeled_img);

/* hls変換で使用 */

ImageMat rotate_hue(const ImageMat &hls_image, const double &angle_degree);

ImageMat bgr2hls(const ImageMat &bgr_image);

ImageMat hls2bgr(const ImageMat &hsl_image);

std::vector<ImageMat> split_Channel(const ImageMat &image);

ImageMat merge_Channel(ImageMat ch1, ImageMat ch2, ImageMat ch3);

/* エッジ検出で使用 */

std::array<ImageMatD, 2> extract_edge(const ImageMat &gray_image);

ImageMat double2uint8t(const ImageMatD &double_data);

/* アフィン変換で使用 */

ImageMat affine_transform(const ImageMat &gray_image);

int nearest_neighbor(const ImageMat &gray_image, double inverse_x, double inverse_y);

/* hough変換で使用 */

std::array<ImageMat, 2> hough_transform(const ImageMatD &edge_strength, const int &threshold);

ImageMatI vote_hough_space(const ImageMatI &hough_space_image, const int &x, const int &y);

ImageMat output_hough_space(const ImageMatI &hough_space_img);

ImageMat draw_line(const ImageMatI &hough_space_image, const ImageMat &edge_strength);
