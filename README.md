# so_long
X11を使用した42の独自ライブラリを使用して、ミニゲームを作ります。
![Image](https://github.com/user-attachments/assets/9e0c39e1-fd0a-480e-923f-e02e975de648)

# 課題要件
* .berで終わるマップ記述ファイルをパラメータとして受け取り、読み込むことができること
* マップ上のすべてのアイテムを集めるとゴールができるようにすること
* プレイヤーはWASDで上下左右の4方向に移動できるようにすること
* ウィンドウの×ボタンをクリックまたはESCキーを押下したときウィンドウが閉じられてプログラムが終了するようにすること
* 読み込むマップの例
```
1111111111111
1C0100000V001
1000011111001
1P0011E000001
1111111111111
```
* プレイ不可能なマップの場合、「Error\n」に続いてエラーメッセージを返すこと
  etc...

# 作成時のルール
* 使用してよい関数はopen・close・read・write・malloc・free・perror・strerror・exitのみ
* 
