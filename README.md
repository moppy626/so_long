# so_long
* X11を使用した42の独自ライブラリを使用して、ミニゲームを作ります
![Image](https://github.com/user-attachments/assets/9e0c39e1-fd0a-480e-923f-e02e975de648)

## 課題内容
* プレイヤーはWASDで上下左右の4方向に移動できるようにする
* マップ上のすべてのアイテムを集めるとゴールができるようにする
* ウィンドウの×ボタンをクリックまたはESCキーを押下したときウィンドウが閉じられてプログラムが終了するようにする
* 移動した補数を出力する
* .berで終わるマップ記述ファイルをパラメータとして受け取り、読み込むことができる
* 読み込むマップの例
```
1111111111111
1C0100000V001
1000011111001
1P0011E000001
1111111111111
```
* マップの記号の意味
  * P...プレーヤー初期位置
  * C...アイテム
  * 1...壁（マップの四方が壁で囲まれていない場合はプレイ不可）
  * E...ゴール
  * 0...床
  * V...敵のパトロール初期位置（私が勝手に追加した独自ルール）
* マップが四角でない場合、アイテムが1つもない場合はプレイ不可にする
* プレイ不可能なマップの場合、「Error\n」に続いてエラーメッセージを返す
* 使用してよい関数はopen・close・read・write・malloc・free・perror・strerror・exit
* 関数の長さは25行以内にすること\
 etc...

## 使用した素材
[RIKUDOU PRODUCTS様HP](https://kai-rikudou.com/)
