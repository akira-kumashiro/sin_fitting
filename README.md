# sin_fitting
入力したcsvから基本波の正弦波近似します
## 流れ
1. 指定フォルダ内のファイルリスト取得  
CSVファイルをすべて開きます
3. CSVファイルのインポート  
空の行から末尾までインポートします  
時間の解像度・チャンネル名は自動で取得します  
データは全ファイル×各チャンネル×各行で保持します
1. データクレンジング  
各チャンネルごとに平均値0にします
1. GAによるフィッティング  
基本波の振幅(最大値)、位相の2変数を最適化します
1. 表示  
csvで保存すると便利です。
## その他
最適化範囲はハードコーディングしているので都度変えてコンパイルする
## 評価関数
![\sum_{i=1}^{RawData.size()}(Amp \times \rm{sin} ( \omega t + \theta \times \frac{\pi}{180}) - RawData_i)](https://latex.codecogs.com/gif.latex?\sum_{i=1}^{RawData.size()}(Amp%20\times%20\rm{sin}%20(%20\omega%20t%20+%20\theta%20\times%20\frac{\pi}{180})%20-%20RawData_i))
