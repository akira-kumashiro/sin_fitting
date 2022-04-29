# sin_fitting
入力したcsvから基本波の正弦波近似します
## 流れ
1. CSVファイルのインポート
空の行から末尾までインポートします
1. データクレンジング
平均値0にします
1. GAによるフィッティング
振幅(最大値)、位相、周波数の3変数を最適化します
1. 表示
csvで保存すると便利です。
## その他
最適化範囲はハードコーディングしているので都度変えてコンパイルする
(デフォは振幅：0.7～0.02、位相：-100～-190()deg、周波数：51～49(Hz))
## 評価関数
![\sum_{n=1}^{24}(Amp \times \rm{sin} ( \omega t + \theta \times \frac{\pi}{180}) - RawData_i)](https://latex.codecogs.com/gif.latex?\sum_{n=1}^{24}(Amp%20\times%20\rm{sin}%20(%20\omega%20t%20+%20\theta%20\times%20\frac{\pi}{180})%20-%20RawData_i))
