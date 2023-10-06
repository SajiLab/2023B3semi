//
// Created by Hitoshi Sauji
//

#include "../myImage.hpp"

//角度未定義
static const double NO_ANG = -1.0;

// エッジ抽出
/**
 * @param gray_img 1チャンネル画像
 * @return edge_data[1]: 1チャンネル エッジ角度 画像、edge_data[2]: 1チャンネル エッジ強度 画像
*/
std::array<ImageMatD, 2> extract_edge(const ImageMat &gray_image) // 例はprewitt
{
  
  ImageMatD edge_angle, edge_strength;
  double prewitt_row[3][3] = {{-1, 0, 1}, 
                              {-1, 0, 1}, 
                              {-1, 0, 1}};
  
  double prewitt_col[3][3] = {{-1, -1, -1}, 
                              {0, 0, 0}, 
                              {1, 1, 1}};

  //クラスの初期値を設定
  edge_angle.m_header = edge_strength.m_header = gray_image.m_header;
  edge_angle.m_width = edge_strength.m_width = gray_image.m_width;
  edge_angle.m_height = edge_strength.m_height = gray_image.m_height;
  edge_angle.m_ch = edge_strength.m_ch = gray_image.m_ch;
  edge_angle.m_length = edge_strength.m_length = gray_image.m_length; 
  edge_angle.m_pixels.resize(edge_angle.m_length);
  edge_strength.m_pixels.resize(edge_strength.m_length);
  edge_angle.m_pixels.assign(edge_angle.m_length, NO_ANG); //配列の初期化
  edge_strength.m_pixels.assign(edge_strength.m_length, 0);



  for(int y = 1; y < gray_image.m_height - 1; y++)
  {
    for(int x = 1; x < gray_image.m_width - 1; x++)
    {
      double dx, dy; //各方向にフィルタをかけたときの差分
      dx = dy = 0;

      for(int col = -1; col <= 1; col++)
      {
        for(int row = -1; row <= 1; row++)
        { 
          dx += gray_image.m_pixels[(x + row) + (y + col) * gray_image.m_width] * prewitt_row[row + 1][col + 1];
          dy += gray_image.m_pixels[(x + row) + (y + col) * gray_image.m_width] * prewitt_col[row + 1][col + 1];
        }
      }

      auto gradient_strength = sqrt((double)(dx * dx + dy * dy)); // エッジ強度
      edge_strength.setPixel(x, y, 0, gradient_strength);

      auto angle = ((double)atan2(dy, dx) + M_PI); // エッジ角度
      edge_angle.setPixel(x, y, 0, angle);
    }
  }


  //エッジ角度の正規化
  const auto max_angle = *max_element(edge_angle.m_pixels.begin(), edge_angle.m_pixels.end());
  const auto min_angle = *min_element(edge_angle.m_pixels.begin(), edge_angle.m_pixels.end());

  for(int y = 0; y < edge_angle.m_height; y++)
  {
    for(int x = 0; x < edge_angle.m_width; x++)
    {
      double norm = (edge_angle.getPixel(x, y, 0) - min_angle) / (max_angle - min_angle) * 255.0;
      edge_angle.setPixel(x, y, 0, norm);
    }
  }

  std::array<ImageMatD, 2> edge_data = {edge_angle, edge_strength}; 

  return edge_data;
}


