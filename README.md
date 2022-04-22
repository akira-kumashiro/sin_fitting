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
<!--アルゴリズム特論課題2  
C++版です
## 各種ファイル
### [report2_git.cpp](https://github.com/akira-kumashiro/report2_git/blob/master/report2_git/report2_git/report2_git.cpp "report2_git.cpp")
`main()`とかが入ってるやつ
### [GA.h](https://github.com/akira-kumashiro/report2_git/blob/master/report2_git/report2_git/GA.h "GA.h")
`GA`クラスの定義とか
### [GA.cpp](https://github.com/akira-kumashiro/report2_git/blob/master/report2_git/report2_git/GA.cpp "GA.cpp")
`GA`クラスの関数とか
### [stdafx.h](https://github.com/akira-kumashiro/report2_git/blob/master/report2_git/report2_git/stdafx.h "stdafx.h")
インクルードしたヘッダの記述  
いるのは16行目から  
(正直[report2_git.cpp](https://github.com/akira-kumashiro/report2_git/blob/master/report2_git/report2_git/report2_git.cpp "report2_git.cpp")に統合していいかな感)
## コピーの仕方
上の4つのファイルを中身を含めて作る→新しいプロジェクトを作ってVisualStudioの右側にある「ソリューション エクスプローラー」にD&D
## 関数と評価値について
`functionValue`には与えられた関数の値が入ってます  
`result`には`functionValue`の最大値を引いたものを2乗して入れてます
## その他
α=0.5、突然変異率0.1です。  
3000ステップいかないくらいで収束します。-->

