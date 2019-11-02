# 写真を漫画家風に加工する
https://algorithm.joho.info/image-processing/manga-ka-fu/

#include
manga_fil.h

# src
- manga_fil.cpp
-- 写真を漫画家風に加工する
- (rgb2y.cpp)
-- RGBをグレースケールに変換する
- (edge_fil.cpp)
-- エッジを検出する
- (ternary.cpp)
-- 三値化し、スクリーントーンと画像を入れ替える

# test
- test.cpp
-- manga_fil.cppのテスト
- cvtest.cpp
-- ほかの関数のテスト用
