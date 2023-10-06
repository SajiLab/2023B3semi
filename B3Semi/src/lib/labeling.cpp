//
// Created by Hitoshi Sauji
// Updated by Gotohayami KohakuNushi
//


#include "../myImage.hpp"
#include <unordered_map>
#include <map>
#include <random>

// ラベルハッシュテーブルを探索し, 最終的なラベルを取得する
static int search_deep_label_hash(const std::unordered_map<int32_t, int32_t> &hash_table, const int32_t &label)
{
  if (hash_table.find(label) == hash_table.end()) // ラベルがハッシュに存在しない場合はそのまま返す
    return label;

  auto visited_label = label;
  auto hash_value = hash_table.at(visited_label); // constで宣言したunordered_mapはatを使用して読みだす
  while (hash_value != visited_label)
  {
    visited_label = hash_value;
    hash_value = hash_table.at(visited_label);
  }

  return visited_label;
}

// ラベルハッシュテーブルを探索し, 真のラベルに更新していく
static void update_label_hash(std::unordered_map<int32_t, int32_t> &hash_table, const int32_t &label, const int32_t &true_label)
{
  if (hash_table.find(label) == hash_table.end()) // ラベルがハッシュに存在しない場合は即終了
    return;

  auto visited_label = label;
  auto hash_value = hash_table.at(label);
  while (hash_value != visited_label)
  {
    hash_table[visited_label] = true_label;
    visited_label = hash_value;
    hash_value = hash_table.at(visited_label);
  }
}

// 初期ラベルをキーとし, 新しいラベル番号(ゼロ始まりに再割り当て済み)をvalueとするハッシュテーブルを返す
static std::unordered_map<int32_t, int32_t> create_latest_label_table(
    const std::unordered_map<int32_t, int32_t> &hash_table)
{
  std::unordered_map<int32_t, int32_t> latest_label_table;
  std::map<int32_t, int32_t> label_list_map;

  /* 最終的に残ったラベルを列挙 */
  for (const auto &[_, value] : hash_table)
    label_list_map[value] = value;

  /* label_list_map(ゼロ始まりで空白のないラベルの再割り当て) */
  /* このブロックは, ブロック以降使用しないvectorのライフタイムを縮めているだけです. */
  {
    std::vector<int32_t> list_using_sort;
    for (const auto &[_, value] : label_list_map)
      list_using_sort.push_back(value);

    /* 昇順ソート, map系列はsortできないのでvectorをかませる */
    std::sort(list_using_sort.begin(), list_using_sort.end(),
              [](const auto &a, const auto &b)
              { return a < b; });

    /* vectorの値が古いラベル, 添え字が真のラベルになる */
    for (size_t idx = 0; idx < list_using_sort.size(); idx++)
      label_list_map[list_using_sort[idx]] = idx;
  }

  /* 旧ラベルに新ラベルを割り当て */
  for (const auto &[old_label, ref_label] : hash_table)
    latest_label_table[old_label] = label_list_map[ref_label];

  return latest_label_table;
}

// ラベリング処理を行ない、処理後のImageMatIクラス画像を返す
/**
 * @param binarize_img 2値化処理済み1チャンネル画像
 * @return 画像処理済みImageMatIクラス1チャンネル画像
*/
ImageMatI labeled_region(const ImageMat &binarize_img)
{
  ImageMatI labeled_img;
  // ヘッダの設定処理
  labeled_img.m_header = binarize_img.m_header;
  labeled_img.m_height = binarize_img.m_height;
  labeled_img.m_width = binarize_img.m_width;
  labeled_img.m_length = binarize_img.m_length;
  labeled_img.m_ch = binarize_img.m_ch;
  labeled_img.m_pixels.resize(labeled_img.m_length);
  labeled_img.m_pixels.assign(labeled_img.m_length, 0);

  int new_label = 1; // new_labelは常にラベルを新しく入れるテーブルを指す
  std::unordered_map<int32_t, int32_t> hash_table;
  hash_table[0] = 0; // 背景ラベルを登録


  for (int y = 0; y < binarize_img.m_height; y++)
  {
    for (int x = 0; x < binarize_img.m_width; x++)
    {
      if (binarize_img.getPixel(x, y, 0) != 255) // 白色画素のみが処理対象なので早期continue
        continue;

      int left_pixel = 0;
      if (x != 0)
      {
        const auto pre_left_pixel = labeled_img.getPixel(x - 1, y, 0);
        left_pixel = search_deep_label_hash(hash_table, pre_left_pixel);
        labeled_img.setPixel(x - 1, y, 0, left_pixel);
      }

      int under_pixel = 0;
      if (y != 0)
      {
        const auto pre_under_pixel = labeled_img.getPixel(x, y - 1, 0);
        under_pixel = search_deep_label_hash(hash_table, pre_under_pixel);
        labeled_img.setPixel(x, y - 1, 0, under_pixel);
      }

      // どちらも黒
      if (left_pixel == 0 && under_pixel == 0)
      {
        //
        // 処理を記述
        //
      }
      // left_pixelにラベルあり
      else if (left_pixel != 0 && under_pixel == 0)
      {
        //
        // 処理を記述
        //
      }

      // under_pixelにラベルあり
      else if (left_pixel == 0 && under_pixel != 0)
      {
        //
        // 処理を記述
        //
      }

      // どちらにもラベル
      else if (left_pixel != 0 && under_pixel != 0)
      {
        //
        // 処理を記述
        //
      }
    }
  }

  /* ラベル画像の塗りなおし */
  hash_table = create_latest_label_table(hash_table);
  for (auto &pix : labeled_img.m_pixels)
    pix = hash_table[pix];

  return labeled_img;
}

//ImaegMatIクラスの画像を可視化する
/**
 * @param labeled_img ラベリング処理済み1チャンネル画像
 * @return 可視化処理済みImageMatクラス1チャンネル画像
*/
ImageMat visualize_labeled_result(const ImageMatI &labeled_img /* 1ch画像 */)
{
  ImageMat color_img;
  /* ヘッダの設定 */
  color_img.m_header = labeled_img.m_header;
  color_img.m_height = labeled_img.m_height;
  color_img.m_width = labeled_img.m_width;
  color_img.m_length = labeled_img.m_length * 3;
  color_img.m_ch = 3; // カラーチャンネル
  color_img.m_pixels.resize(color_img.m_length);
  color_img.m_pixels.assign(color_img.m_length, 0);

  /* ちゃんとラベルを再割り当てしているので, ラベル画像の最大値+1がラベル数 */
  const auto label_num = 1 + (*std::max_element(labeled_img.m_pixels.begin(),
                                                labeled_img.m_pixels.end()));

  /* ラベル色パレットの作成 */
  std::unordered_map<int32_t, std::vector<uint8_t>> color_palette;

  std::default_random_engine random_engine;
  std::uniform_int_distribution<uint8_t> random_dist(0, 255);

  for (int32_t label_idx = 1; label_idx < label_num; label_idx++)
  {
    auto &color = color_palette[label_idx];
    color.resize(3);
    for (int32_t ch = 0; ch < 3; ch++)
      color[ch] = random_dist(random_engine);
  }

  for (int y = 0; y < labeled_img.m_height; y++)
  {
    for (int x = 0; x < labeled_img.m_width; x++)
    {
      const auto &label = labeled_img.getPixel(x, y, 0);
      if (label <= 0)
        continue;

      const auto &color = color_palette[label];
      for (int ch = 0; ch < 3; ch++)
        color_img.setPixel(x, y, ch, color[ch]);
    }
  }

  return color_img;
}

std::map<int32_t, uint64_t> calc_label_region_area(const ImageMatI &labeled_img)
{
  /* ちゃんとラベルを再割り当てしているので, ラベル画像の最大値+1がラベル数 */
  const auto label_num = 1 + (*std::max_element(labeled_img.m_pixels.begin(),
                                                labeled_img.m_pixels.end()));

  std::map<int32_t, uint64_t> region_area_list;
  for (auto &pix : labeled_img.m_pixels)
    // []に関して, atと異なるのは呼び出し時に要素を自動追加することです. この行は，必ず要素は1始まりということになります.
    // すぐインクリメントされるので.面積の場合は添え字の個数分足すので, 問題ないです.
    region_area_list[pix]++;

  return region_area_list;
}