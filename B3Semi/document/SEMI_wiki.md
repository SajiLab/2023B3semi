# B3ゼミWiki

<details>
<summary> <b>目次をクリックで展開</b> </summary>
<div>

+ [講義資料の開発環境について](#anchor1)

+ [環境構築について](#anchor2)

+ [Markdownの記述について](#anchor3)

+ [TeXの記述について](#anchor4)
</dev>
</details>

<a id="anchor1"></a>

## 講義資料の開発環境について

開発環境は以下のとおりです。

| 使用環境 |  |
|------|-----|
|CPU |Intel(R) Core(TM) i7-10510U CPU @ 1.80GHz   2.30 GHz |
|メモリ|8.00GB|
|OS|Windows 10 Pro|
|使用言語| C++17|

<a id="anchor2"></a>

## 環境構築について

想定する環境構築の流れを大雑把に説明するので、あくまで参考程度にお願いします。

本ゼミの実行環境はWSL(Windows Subsystem for Linux)を想定しています。そのため、手元にLinux環境が存在しない方はWSL環境の構築をお願いしています。

環境の構築方法についてはMicrosoft公式ページ\[[1]\]に記載がありますので、そちらを参考にしてみてください。

[1]: https://learn.microsoft.com/ja-jp/windows/wsl/setup/environment

|使用環境||
|-|-|
Ubuntu 22.04.3
WSL 2


WSLのインストールが完了したら、次にVSCodeのインストール\[[2]\]を行ないます。完了している方は飛ばしてください。

[2]: https://code.visualstudio.com/download

VSCodeのインストールが完了したら、コマンドパレットに以下を入力します。
```
C:\Users\Username> Ubuntu
```
Ubuntuが開きますので、以下の2つをコードを入れて、build-essentialとcmakeをインストールします。先頭の`$`は入れないでください。
```
$ sudo apt install build-essential
$ sudo apt install cmake
```

インストールが完了したら、VSCodeを開きます。
```
$ code
```
VSCodeが開けたら、`ctl + @`でターミナルを表示し、Linux上の好きなディレクトリにB3ゼミ用のディレクトリを作成してください。

```
$ mkdir ディレクトリの名前(英語が望ましい、以下では`saji-lab`)
```

作成したらカレントディレクトリを作成したディレクトリにします。
```
$ cd saji-lab
```

ディレクトリ内に講義資料をcloneします。
```
$ git clone https://github.com/SajiLab/2023B3semi.git
```

これでゼミ用の環境構築は終了です。

最後に動作をテストします。
B3Semiディレクトリにて以下のコマンドを入れてください。

```
$ sh build_run.sh
```

"Hello, World"がターミナルに出力されればOKです。

<a id="anchor3"></a>

## Markdownの記述について

Markdownの記述で使いやすそうな記事です。

[リンク1](https://qiita.com/toyokky/items/47a5a56c20ad99e1784c)

[リンク2](https://qiita.com/kamorits/items/6f342da395ad57468ae3)

<a id="anchor4"></a>

## Texでの記述について
GitLabのwikiに記載がありそうなので適当に持ってくる(~~単純に自分の環境に落とし込めてないから説明できないよーの状態~~)


