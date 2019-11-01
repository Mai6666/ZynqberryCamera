# 画像処理
## rgb2y
- 書式：rgb2y(int pix)
- 機能：RGB画素をグレースケール（輝度値）に変換する
- 引数：RGB画素
- 返り値：輝度値

## edge_fil
- 書式：edge_fil(int, int, int, int, int, int, int, int, int)
- 機能：エッジを検出する
- 引数：注目画素と近傍画素
- 返り値：畳み込み結果

## ternary
- 書式：ternary(int pix, int tmp)
- 機能：三値化する
- 引数pix：画素
- 引数tmp：画素の座標のテンプレート画素
- 返り値：出力結果
