//
// Created by Hitoshi Sauji
//
// 参考サイト : https://algorithm.joho.info/image-processing/bmp-file-data-header/

#include "../myImage.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

/**
 * @param filename 読み込みたいファイルのパス
 * @return 入力画像のクラス
*/
ImageMat read_image(const std::string &filename)
{
  ImageMat image_mat;
  std::ifstream image_file(filename, std::ios::binary);// バイナリデータとして画像を読み込む

  if (!image_file)
  {
    std::cout << "can't open reading file!" << std::endl;
    return image_mat;
  }

  image_file.seekg(0, std::ios::end); // ポインタをバイナリファイルの一番うしろまで進める
  const auto &size = image_file.tellg(); // ポインタの位置 = ファイルのサイズになってるのでsizeはの位置はファイルサイズそのものになる

  std::cout << "file_size: " << size << std::endl;
  image_file.seekg(0, std::ios::beg); // 読み込みファイルの先頭に戻る
  image_file.read(reinterpret_cast<char *>(image_mat.m_header.data()), 54); // ファイルの上から54番目までを読み込む

  image_mat.m_width = image_mat.m_header[18] +
                      image_mat.m_header[19] * 256 +
                      image_mat.m_header[20] * 256 * 256 +
                      image_mat.m_header[21] * 256 * 256 * 256;

  image_mat.m_height = image_mat.m_header[22] +
                       image_mat.m_header[23] * 256 +
                       image_mat.m_header[24] * 256 * 256 +
                       image_mat.m_header[25] * 256 * 256 * 256;

  image_mat.m_length = image_mat.m_header[34] +
                       image_mat.m_header[35] * 256 +
                       image_mat.m_header[36] * 256 * 256 +
                       image_mat.m_header[37] * 256 * 256 * 256;

  auto &pixel_data = image_mat.m_pixels;
  pixel_data.resize(image_mat.m_length);
  image_file.read(reinterpret_cast<char *>(pixel_data.data()), pixel_data.size());

  std::cout << "loaded image :" << image_mat.m_width << " x " << image_mat.m_height << std::endl;

  return image_mat;
}

/**
 * @param ImageMat 出力したい画像のクラス
 * @param string 画像を出力したいディレクトリへのパス
 * @return 
*/
void write_image(const ImageMat &image, const std::string &filename)
{
  if (image.m_ch == 1)
  {
    ImageMat pseudo_gray = gray2color(image);
    write_image(pseudo_gray, filename);
    return;
  }

  std::ofstream image_file(filename, std::ios::binary);
  if (!image_file)
  {
    std::cout << "can't open writing file!";
    return;
  }

  // 縦、横の大きさを再度求める
  // 処理によって画像サイズが変化した場合に必要
  auto image_header = image.m_header;
  int width = image.m_width;
  for (int i = 18; i <= 21; i++)
  {
    image_header[i] = width % 256;
    width = width / 256;
  }

  int height = image.m_height;
  for (int i = 22; i <= 25; i++)
  {
    image_header[i] = height % 256;
    height = height / 256;
  }

  image_header[26] = image.m_ch;

  int length = image.m_length;
  for (int i = 35; i <= 37; i++)
  {
    image_header[i] = length % 256;
    length = length / 256;
  }

  auto image_pixels = image.m_pixels;
  image_file.write(reinterpret_cast<char *>(image_header.data()), image_header.size());
  image_file.write(reinterpret_cast<char *>(image_pixels.data()), image_pixels.size());

  image_file.close();

  std::cout << "wrote image :" << image.m_width << " x " << image.m_height << std::endl;

  return;
}
