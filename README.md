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
## 参考
- [Markdown記法 サンプル集](https://qiita.com/tbpgr/items/989c6badefff69377da7)
- [Qiitaの数式チートシート](https://qiita.com/PlanetMeron/items/63ac58898541cbe81ada)
- [GithubのREADMEとかwikiで数式を書く](http://idken.net/posts/2017-02-28-math_github/)
- [[C++] 文字列から空白を取り除く方法 (std::string)](https://b.0218.jp/20150625194056.html)
- [C++でフォルダ以下のファイル一覧を取得する](https://qiita.com/tes2840/items/8d295b1caaf10eaf33ad)
- [リファレンス/filesystem/path](https://cpprefjp.github.io/reference/filesystem/path.html)
- [C++でCSVファイルを読み込む](https://cvtech.cc/readcsv/)
- [C++ 動的配列クラス std::vector 入門](http://vivi.dyndns.org/tech/cpp/vector.html)
- [C++ 文字列クラス std::string 入門](http://vivi.dyndns.org/tech/cpp/string.html)
- [Visual C++で円周率のM_PIを使う](https://hayakute.kantan-sakusaku.com/?p=2235)
- [T - 2.03.多次元配列 ](https://atcoder.jp/contests/APG4b/tasks/APG4b_t)
- [C++11で数字→文字列はstd::to_string()、文字列→数字はstd::stoi()とかstd::stod()とか](https://minus9d.hatenablog.com/entry/2014/06/05/233727)
- [akira-kumashiro/report2_git](https://github.com/akira-kumashiro/report2_git)
