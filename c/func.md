# 実装するもの
https://algorithm.joho.info/image-processing/manga-ka-fu/

## rgb2y
- 書式：rgb2y(int pix)
- 機能：RGB画素をグレースケール（輝度値）に変換する
- 引数：24bitRGB画素値
- 返り値：輝度値
- ヒント：https://qiita.com/yuripapageno/items/fbaae6dbda3ac726b62c

## edge_fil
- 書式：edge_fil(int, int, int, int, int, int, int, int, int)
- 機能：エッジを検出する
- 引数：注目画素と近傍画素
- 返り値：畳み込み結果
- ヒント：https://www.clg.niigata-u.ac.jp/~medimg/practice_medical_imaging/imgproc_scion/4filter/index.htm

## ternary
- 書式：ternary(int pix, int tmp)
- 機能：三値化する
- 引数pix：画素
- 引数tmp：画素の座標のテンプレート画素
- 返り値：出力結果
- ヒント：
